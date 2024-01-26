class Parser{
    size_t curIdx;
    vector<Token> tokens;

    optional<Token> peak(int ahead=1){
        if(curIdx+ahead>tokens.size())return {};
        return tokens[curIdx];
    }
    Token consume(){
        return tokens[curIdx++];
    }
public:
    Parser(vector<Token> tokens){
        this->tokens=tokens;
        this->curIdx=curIdx;
    }
    optional<NodeExit> parse(){
        while(peak().has_value()){
            
        }
    }

};