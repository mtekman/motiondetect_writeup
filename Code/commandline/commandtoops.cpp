//op and commands are pointers to other class (the camera thread: Operations, and the commandline class: CommandLine)
op = new Operations; //camera thread

if(commands == 0){           //Not assigned
        ..
        op->timelapse = false;
        op->echo_to_log = false;
        ..
}
else{   //Pointer not empty: perform commandLineOps
        
        //Assign values from commandline to CameraThread
        op->timelapse = commands->timelapse;
        op->limitVal = commands->white;
        op->interval_max = commands->max;
	..
        //Terminate app when camera thread finishes
        connect(op,SIGNAL(finished()), this, SLOT(closeAndExit()));

        op->start();	   //Initialise camera, and start!

        delete commands;  //destroys commandline and frees memory
}
