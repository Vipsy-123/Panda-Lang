#include"compilerLib.h"

void writeAsmFile(string str){
    fstream output("../test/outputFile/test.asm",ios::out);
    output<<str;
    /* test.asm -> test.o -> test(exec)
    nasm -f macho64 test.asm && ld test.o -o test -demangle -dynamic -macos_version_min 11.0 -L/usr/local/lib -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -lSystem -no_pie && ./test 
    */
}

int pandaCompiler(const string &fileContents){
    
    Lexer lexer(fileContents);
    vector<Token> tokens=lexer.tokenize();

    Parser parser(tokens);
    optional<NodeProg> tree=parser.parserProg();

    if(!tree.has_value()){
        cerr<<"Could not parse"<<endl;
        exit(EXIT_FAILURE);
    }

    Genrator genrator(tree.value());
    string output=genrator.genProg();

    writeAsmFile(output);
    return EXIT_SUCCESS;
}


int main(int argc,char* argv[]){
    
    string fileContents=readFileToString(argc,argv);
    return pandaCompiler(fileContents);

}