IplImage * get_grayscale(FCam::Frame &frame){
	const FCam::Image & image = frame.image();
	IplImage * img = cvCreateImage(cvSize(image.width (), image.height ()), IPL_DEPTH_8U, 1);
	for (unsigned int i = 0; i < image.height(); ++i)
	{
       		for (unsigned int j = 0; j < image.width(); j += 2)
       		{
        		unsigned char * pixels = image (j, i);
           		CV_IMAGE_ELEM (img, float, i, j) = pixels[1]/255.0;
           		CV_IMAGE_ELEM (img, float, i, j + 1) = pixels[3]/255.0;
       		}
	}
	return img;
}
