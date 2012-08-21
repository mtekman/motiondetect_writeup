void convertToCImg(const FCam::Frame &frame){
    const FCam::Image &image = frame.image();
    CImg<unsigned int> img(image.width(), image.height(), 2, 1);
    for (unsigned int i = 0; i < image.height(); ++i)
    {
        for (unsigned int j = 0; j < image.width(); j += 2)
        {
            unsigned char * pixels = image (j, i);
            img(i,j) = pixels[1];
            img(i,j+1) = pixels[3];
        }
    }
    //return img;
}
