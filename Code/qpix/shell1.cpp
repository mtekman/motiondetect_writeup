for left in $(seq 0 50); do		          # Shell script calling 
   for top in $(seq 0 50); do		      # -t flag for different
      for mod in $(seq 1 0.2 3); do	      # image sizes
         for off in $(seq 0 10 100); do
            /opt/motiondetect/bin/motiondetect -t $mod $off $left $top
         done
      done
   done
done

###===========C++ code to handle -t flag================##
if( (t_index=args.indexOf("-t"))!=-1)
{
       mod = args.at(t_index+1).toInt(); offset = args.at(t_index+2).toInt();
       left = args.at(t_index+3).toInt(); right = args.at(t_index+4).toInt();
}

QImage thumbQ(image(left,top), 
	image.width()/mod + offset,   image.height()/mod + offset, 
	QImage::Format_RGB32);  
ui->imageLab->setPixmap(QPixmap::fromImage(thumbQ));

