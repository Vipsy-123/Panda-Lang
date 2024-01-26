#include"compilerLib.h"

int pandaCompiler(const string &fileContents){
    
    Lexer lexer(fileContents);
    vector<Token> tokens=lexer.tokenize();
    cout<<(tokens.size());

    return EXIT_SUCCESS;
}

int main(int argc,char* argv[]){
    
    string fileContents=readFileToString(argc,argv);
    return pandaCompiler(fileContents);

}