void CommandLine::checkForFlagName(){
    int f_index = 0; 
    flag_value = 5; //default
    
    if( ((f_index=args.indexOf("-f"))!=-1) || ((f_index=args.indexOf("--flag"))!=-1) )
    {
        flag_value = args.at(f_index+1).toInt(); //return 0 if not Int
        //Check for Errors
        if(flag_value == 0 || flag_value < someAmount){
            cerr << "Error: Bad argument" << endl;
            exit(1);
        }
        args.removeAt(f_index+1);  //Remove flag value from array
        args.removeAt(f_index);    //Remove flag name from array
    }
}
