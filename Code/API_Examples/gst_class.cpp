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
gst_element_set_state(pipeline, GST_STATE_PLAYING);
