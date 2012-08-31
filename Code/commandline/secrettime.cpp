void CommandLine::secretDate(){  // --teenage-diplomacy <DateTime> <Convert> <Delete> <Width> <fps>
    int d_index=0; timelapse = false;
    if ( ( d_index=args.indexOf("--teenage-diplomacy"))!=-1){  //Two words unlikely to be typed next to each other
        //Date will be yyyy:mm:dd:HH:MM:SS
        QStringList date_time = args.at(d_index+1).split(":");

        //Booleans: Delete and Convert. 1= true, -1= false;
        int in_convert = args.at(d_index+2).toInt();
        int in_del = args.at(d_index+3).toInt();

        //Parse framerate
        mask = args.at(d_index+5).toInt();

        if( in_convert==0 || in_del==0 || date_time.length()!=6 || mask==0){
            cerr << red << "Nice try." << stop << endl;
            exit(1);
        }

        //Parse Bools:
        convert = (in_convert==1); del = (in_del==1);

        //Parse size:
        width = args.at(d_index+4).toInt();
        switch(width){
        case 320:  height=240; break;
        case 640:  height=480; break;
        case 800:  height=600; break;
        case 1280: height=960; break;
        default:
            cerr << red << "Yep. Something went wrong. Debug to find out." << stop << endl;
            exit(1);
        }

        //Parse Date:
        int year = date_time.at(0).toInt(), month = date_time.at(1).toInt(), day = date_time.at(2).toInt();
        int hour = date_time.at(3).toInt(), minute = date_time.at(4).toInt(), second = date_time.at(5).toInt();

        time = new QDateTime( QDate(year,month,day), QTime(hour,minute,second) );

        //Finish
        timelapse = true;
        args.removeAt(d_index+5); args.removeAt(d_index+4);
        args.removeAt(d_index+3); args.removeAt(d_index+2);
        args.removeAt(d_index+1); args.removeAt(d_index);
    }
}
