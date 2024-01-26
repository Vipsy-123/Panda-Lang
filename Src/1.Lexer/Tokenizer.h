struct Token{
    TokenType type;
    optional<string> val;
};

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
                while(peek() && isalnum(peek()))buf.push_back(consume());
                if(buf=="ret")tokens.push_back({.type=TokenType::ret});
                else{
                    cout<<"you messed up!";
                    exit(EXIT_FAILURE);
                }
                buf.clear();
            }
            else if(isdigit(peek())){
                while(peek() && isdigit(peek()))buf.push_back(consume());
                tokens.push_back({.type=TokenType::digit,.val=buf});
                buf.clear();
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