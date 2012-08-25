#Shell script to test Image Formats and Sizes
for ii in $(seq 4 16); do
   for jj in $(seq 1.4 0.2 3); do
       echo 'index='$ii 'divider='$jj
       /opt/motiondetect/bin/motiondetect -t $ii $jj
   done
done

void MainWindow::newImage(const FCam::Image &image){
   int ind = 0; float div = 2;
   ind = indy;  div = divvy;
   enum QImage::Format index;
   switch(ind){
   case 0:index = QImage::Format_ARGB32; break;
   case 1:index = QImage::Format_ARGB32_Premultiplied; break;
   case 2:index = QImage::Format_ARGB4444_Premultiplied; break;
   case 3:index = QImage::Format_ARGB6666_Premultiplied;break;
   case 4:index = QImage::Format_ARGB8555_Premultiplied;break;
   case 5:index = QImage::Format_ARGB8565_Premultiplied;break;
   case 6:index = QImage::Format_Indexed8;break;
   case 7:index = QImage::Format_Invalid;break;
   case 8:index = QImage::Format_Mono;break;
   case 9:index = QImage::Format_MonoLSB;break;
   case 10:index = QImage::Format_RGB16;break;
   case 11:index = QImage::Format_RGB32;break;
   case 12:index = QImage::Format_RGB444;break;
   case 13:index = QImage::Format_RGB555;break;
   case 14:index = QImage::Format_RGB666;break;
   case 15:index = QImage::Format_RGB888;break;
   }
   cout << "image/"<<div<<" format=" << ind << endl;
   QImage thumbQ(image(0,0),
                 (int)((float)(image.width())/(float)(div)),
                 (int)((float)(image.height())/(float)(div)), index);
   ui->imageLab->setPixmap(QPixmap::fromImage(thumbQ));
}

