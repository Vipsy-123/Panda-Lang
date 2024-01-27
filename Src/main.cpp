#include"compilerLib.h"

void writeAsmFile(string str){
    fstream output("../test/outputFile/test.asm",ios::out);
    output<<str;
}

int pandaCompiler(const string &fileContents){
    
    Lexer lexer(fileContents);
    vector<Token> tokens=lexer.tokenize();

    Parser parser(tokens);
    optional<NodeExit>tree=parser.parse();

    if(!tree.has_value()){
        cerr<<"No exit statement"<<endl;
        exit(EXIT_FAILURE);
    }

    Genrator genrator(tree);
    string output=genrator.Genrate();

    writeAsmFile(output);
    return EXIT_SUCCESS;
}


int main(int argc,char* argv[]){
    
    string fileContents=readFileToString(argc,argv);
    return pandaCompiler(fileContents);

}