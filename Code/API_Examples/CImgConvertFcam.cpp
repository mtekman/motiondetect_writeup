CImg<unsigned char> newimg1(image.width(), image.height(),32,32){
	CImg<unsigned char> img; //constructor
	unsigned char * imgBuffer1 = img.data();
	for (int y=0;y<image.height();y++){
        	for (int x=0;x<image.width();x++){
                	imgBuffer1[0] = (*(image(x,y)+1));//+*(image(x,y)+3))/2;
               		imgBuffer1++;
		}
	}
} 
