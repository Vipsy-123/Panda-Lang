int readFile(const int argc, char* argv[],string &contents){
    if(argc!=2){
        cerr<<"Incorrect Usage. Correct usage is ...\n";
        cerr<<"./panda <input.pd>\n";
        return EXIT_FAILURE;
    }
    string path=argv[1];
    
    int i=0;
    while(argv[1][i]!='\0')i++;
    i--;
    if(argv[1][i-2]!='.'||argv[1][i-1]!='p'||argv[1][i]!='d'){
        cerr<<"Incorrect file format. Requires a panda file <input.pd>\n";
        return EXIT_FAILURE;
    }
    
    path="../test/"+path;
    fstream input(path,ios::in);

    stringstream contentsStream;
    contentsStream << input.rdbuf();

    contents=contentsStream.str();
    // cout<<contents<<endl;

    return EXIT_SUCCESS;
}
string readFileToString(const int argc, char* argv[]){
    string str;
    if(readFile(argc,argv,str))exit(EXIT_FAILURE);
    return str;
}