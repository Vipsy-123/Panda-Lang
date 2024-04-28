#include"compilerLib.h"
     
int main(int argc, char* argv[]){
    // std::cout<< argv[0] << std::endl;
    if(argc != 2 ){
        std::cerr << "Incorrect usage . Correct usage is ..." << std::endl;
        std::cerr << "panda <input.pd>" << std::endl;
        return EXIT_FAILURE;
    }

    // Input the content in test.pd file
    std::string contents;
    {
        std::stringstream contents_stream; 
        std::fstream input(argv[1], std::ios::in); // A std::fstream named input is created, representing a file stream. It is opened in input mode (std::ios::in). 
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();
    auto values = tokenizer.m_values;

    printf("Done with Tokenization . \n");
    Parser parser(std::move(tokens));
    std::optional<NodeProg> prog = parser.parse_prog();
    printf("Done with Parsing .. \n");

    if(!prog.has_value())
    {
        std::cerr << "Invalid Program"<< std::endl;
        exit(EXIT_FAILURE);
    }    

    {   
        Generator generator(prog.value(),values);
        std::fstream file("out.asm", std::ios::out);
        file << generator.gen_prog();
    }

    printf("Done with Generation ... \n");
    system("nasm -felf64 out.asm"); // Assemble .asm file
    system("ld -o out out.o"); // Linking and generating exe

    return EXIT_SUCCESS;
}