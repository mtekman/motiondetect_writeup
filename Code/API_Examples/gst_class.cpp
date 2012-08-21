	gst_init(argc, argv);  /* Initialize Gstreamer */
	/* Create pipeline and attach a callback to it's
	 * message bus */
	pipeline = gst_pipeline_new("test-camera");

	bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
	gst_bus_add_watch(bus, (GstBusFunc)bus_callback, appdata);
	gst_object_unref(GST_OBJECT(bus));
	
	/* Save pipeline to the AppData structure */
	appdata->pipeline = pipeline;
	
	/* Create elements */
	/* Camera video stream comes from a Video4Linux driver */
	camera_src = gst_element_factory_make(VIDEO_SRC, "camera_src");
	/* Colorspace filter is needed to make sure that sinks understands
	 * the stream coming from the camera */
	csp_filter = gst_element_factory_make("ffmpegcolorspace", "csp_filter");
	/* Tee that copies the stream to multiple outputs */
	tee = gst_element_factory_make("tee", "tee");
	/* Queue creates new thread for the stream */
	screen_queue = gst_element_factory_make("queue", "screen_queue");
	/* Sink that shows the image on screen. Xephyr doesn't support XVideo
	 * extension, so it needs to use ximagesink, but the device uses
	 * xvimagesink */
	screen_sink = gst_element_factory_make(VIDEO_SINK, "screen_sink");
	/* Creates separate thread for the stream from which the image
	 * is captured */
	image_queue = gst_element_factory_make("queue", "image_queue");
	/* Filter to convert stream to use format that the gdkpixbuf library
	 * can use */
	image_filter = gst_element_factory_make("ffmpegcolorspace", "image_filter");
	/* A dummy sink for the image stream. Goes to bitheaven */
	image_sink = gst_element_factory_make("fakesink", "image_sink");

	/* Check that elements are correctly initialized */
	if(!(pipeline && camera_src && screen_sink && csp_filter && screen_queue
		&& image_queue && image_filter && image_sink))
	{
		g_critical("Couldn't create pipeline elements");
		return FALSE;
	}

	/* Set image sink to emit handoff-signal before throwing away
	 * it's buffer */
	g_object_set(G_OBJECT(image_sink),
			"signal-handoffs", TRUE, NULL);
	
	/* Add elements to the pipeline. This has to be done prior to
	 * linking them */
	gst_bin_add_many(GST_BIN(pipeline), camera_src, csp_filter,
			tee, screen_queue, screen_sink, image_queue,
			image_filter, image_sink, NULL);
	
	/* Specify what kind of video is wanted from the camera */
	caps = gst_caps_new_simple("video/x-raw-rgb",
			"width", G_TYPE_INT, 640,
			"height", G_TYPE_INT, 480,
			NULL);
			

	/* Link the camera source and colorspace filter using capabilities
	 * specified */
	if(!gst_element_link_filtered(camera_src, csp_filter, caps))
	{
		return FALSE;
	}
	gst_caps_unref(caps);
	
	/* Connect Colorspace Filter -> Tee -> Screen Queue -> Screen Sink
	 * This finalizes the initialization of the screen-part of the pipeline */
	if(!gst_element_link_many(csp_filter, tee, screen_queue, screen_sink, NULL))
	{
		return FALSE;
	}

	/* gdkpixbuf requires 8 bits per sample which is 24 bits per
	 * pixel */
	caps = gst_caps_new_simple("video/x-raw-rgb",
			"width", G_TYPE_INT, 640,
			"height", G_TYPE_INT, 480,
			"bpp", G_TYPE_INT, 24,
			"depth", G_TYPE_INT, 24,
			"framerate", GST_TYPE_FRACTION, 15, 1,
			NULL);

	/* Link the image-branch of the pipeline. The pipeline is
	 * ready after this */
	if(!gst_element_link_many(tee, image_queue, image_filter, NULL)) return FALSE;
	if(!gst_element_link_filtered(image_filter, image_sink, caps)) return FALSE;

	gst_caps_unref(caps);
	
	/* As soon as screen is exposed, window ID will be advised to the sink */
	g_signal_connect(appdata->screen, "expose-event", G_CALLBACK(expose_cb),
			 screen_sink);

	gst_element_set_state(pipeline, GST_STATE_PLAYING);
