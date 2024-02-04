struct Token{
    TokenType type;
    optional<string> val;
};

optional<int> binOpPrec(TokenType type){
    switch (type){
    case TokenType::plus:
    case TokenType::minus:return 1;
    case TokenType::star: 
    case TokenType::fslash: return 2;
    default:
        return{};
    }
}

class Lexer{
    size_t curIdx;
    string src;

    char peek(int ahead=0){
        if(curIdx+ahead>=src.length())return {};
        return src[curIdx+ahead];
    }
    char consume(){
        return src[curIdx++];
    }

public:
    Lexer(const string src){
        this->src=src;
        curIdx=0;
    }
    vector<Token> tokenize(){
        vector<Token> tokens;
        string buf="";

        while(peek()){
            if(isalpha(peek())){
                while(peek() && (isalnum(peek())||peek()==':'))buf.push_back(consume());
                if(buf=="ret")tokens.push_back({.type=TokenType::ret});
                else if(buf=="let:digit")tokens.push_back({.type=TokenType::let});
                else if(buf=="if")tokens.push_back({.type=TokenType::if_});
                else tokens.push_back({.type=TokenType::ident,.val=buf});
                buf.clear();
            }
            else if(peek()=='/' && peek(1) && peek(1)=='/'){
                while(peek()!='\n')consume();
                consume();
            }
            else if(peek()=='/' && peek(1) && peek(1)=='*'){
                while(!(peek()=='*' && peek(1) && peek(1)=='/'))consume();
                consume();consume();
            }
            else if(isdigit(peek())){
                while(peek() && isdigit(peek()))buf.push_back(consume());
                tokens.push_back({.type=TokenType::digit,.val=buf});
                buf.clear();
            }
            else if(peek()=='='){
                tokens.push_back({.type=TokenType::equal});
                consume();buf.clear();
            }
            else if(peek()=='+'){
                tokens.push_back({.type=TokenType::plus});
                consume();buf.clear();
            }
            else if(peek()=='*'){
                tokens.push_back({.type=TokenType::star});
                consume();buf.clear();
            }
            else if(peek()=='/'){
                tokens.push_back({.type=TokenType::fslash});
                consume();buf.clear();
            }
            else if(peek()=='-'){
                tokens.push_back({.type=TokenType::minus});
                consume();buf.clear();
            }
            else if(peek()=='('){
                tokens.push_back({.type=TokenType::openParen});
                consume();buf.clear();
            }
            else if(peek()==')'){
                tokens.push_back({.type=TokenType::closeParen});
                consume();buf.clear();
            }
            else if(peek()=='{'){
                tokens.push_back({.type=TokenType::openCurly});
                consume();buf.clear();
            }
            else if(peek()=='}'){
                tokens.push_back({.type=TokenType::closeCurly});
                consume();buf.clear();
            }
            else if(peek()==';'){
                tokens.push_back({.type=TokenType::semi});
                consume();buf.clear();
            }
            else if(isspace(peek())){
                consume();buf.clear();
            }
            else{
                cout<<"you messed up!";
                exit(EXIT_FAILURE);
            } 
        }
        return tokens;
    }
};