QImage thumbQ(image(left_i,right_i), 
       image.width()/mod + offset, 
       image.height()/mod + offset, 
       QImage::Format_RGB32);
ui->imageLab->setPixmap(QPixmap::fromImage(thumbQ));

//where image is &image.
