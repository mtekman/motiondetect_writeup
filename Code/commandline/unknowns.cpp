void CommandLine::unknowns(){
    if(args.length()!=0){

          cerr << "Could not parse: "; //Start listing
          for(int i=0; i< args.length(); i++){
              cerr << args.at(i).toUtf8().data() << " ";
          }
          cerr << endl;                //Stop listing

          cerr << "Please try --help for more info " << endl;
          exit(1);
    }
}
