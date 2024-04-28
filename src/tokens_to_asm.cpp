#include"compilerLib.h"

// Types of Tokens available
enum class TokenType{
    exit,
    int_lit,
    semi
};

// Tokens will be put in value
struct Token{
    TokenType type;
    std::optional<std::string> value;
};

// Convert input into sequence of Tokens
std::vector<Token> tokenize(const std::string& str){
    std::vector<Token> tokens;
    std::string buf ;
    // cout<<"Inside Tokenize Function"<<endl;
    for(int i = 0; i < str.length(); i++){
        char c = str.at(i);
        // cout<< c;
        if(std::isalpha(c)){
            buf.push_back(c);
            i++;
            while(std::isalnum(str.at(i))){
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            if(buf == "exit") {
                tokens.push_back({.type = TokenType::exit});
                buf.clear();
                continue;
            }else{
                std::cerr << "You messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(std::isdigit(c)) {
            buf.push_back(c);
            i++;
            while(std::isdigit(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();
        }
        else if (c == ';'){
            tokens.push_back({.type = TokenType::semi});
            // cout << "Semi colon added" <<endl;
        }
        else if(std::isspace(c)) {
            continue;
        }
        else {
            std::cerr << "You messed up !" << std::endl;
            exit(EXIT_FAILURE);
        }
        
    }
     return tokens;
}

// Convert tokens into Assembly code
std::string tokens_to_asm(const std::vector<Token>& tokens){
    std::stringstream output;
    output << "   global _start\n";
    output << "   _start:\n";
    // cout << "Tokens size " << tokens.size() << endl;
    for(int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);
        // cout << "Token " << i <<endl;
        if(token.type == TokenType::exit) {
            // cout << "In return \n" ;
            // cout << tokens.at(i + 1).type << endl;
            if(i + 1 < tokens.size() && tokens.at(i + 1).type == TokenType::int_lit) {
                // cout << "In int literal \n" ;
                if(i + 2 < tokens.size() && tokens.at(i + 2).type == TokenType::semi) {
                    // cout << "In here";
                    output << "      mov rax, 60 \n";
                    output << "      mov rdi, "<< tokens.at(i+1).value.value() << "\n";
                    output << "      syscall";
                }
            }
        }
    }
    return output.str();
}
// Main Function         

int main(int argc, char* argv[]){
    // std::cout<< argv[0] << std::endl;
    if(argc != 2 ){
        std::cerr << "Incorrect usage . Correct usage is ..." << std::endl;
        std::cerr << "panda <input.pd>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream; 
        std::fstream input(argv[1], std::ios::in); // A std::fstream named input is created, representing a file stream. It is opened in input mode (std::ios::in). 
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    std::vector<Token> tokens = tokenize(contents);
    // std::cout<<"Tokens size::"<<tokens.size()<<std::endl;

    {
        std::fstream file("out.asm", std::ios::out);
        file << tokens_to_asm(tokens);
    }
    
    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    // std::cout  << tokens_to_asm(tokens)<< std::endl;

    return EXIT_SUCCESS;
}