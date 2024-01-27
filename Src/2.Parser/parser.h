class Parser{
    size_t curIdx;
    vector<Token> tokens;

    optional<Token>peek(int offset=0){
        if(curIdx+offset>=tokens.size())return {};
        return tokens[curIdx+offset];
    }
    Token consume(){
        return tokens[curIdx++];
    }
public:
    Parser(vector<Token> tokens){
        this->tokens=tokens;
        this->curIdx=0;
    }
    optional<NodeExpr> parseExpr(){
        if(peek().has_value()&&peek().value().type==TokenType::digit){
            return NodeExpr{.intLit=consume()};
        }
        return {};
    }
    optional<NodeExit> parse(){
        NodeExit exitNode;
        while(peek().has_value()){
            if(peek().value().type == TokenType::ret){
                consume();
                if(auto nodeExpr=parseExpr()){
                    exitNode=NodeExit{.expr=nodeExpr.value()};
                }
                else {
                    cerr<<"Invalid Expression1...\n";
                    exit(EXIT_FAILURE);
                }
            }
            if(peek().has_value() && peek().value().type==TokenType::semi)
                consume();
            else{
                cerr<<"Invalid Expression...\n";
                exit(EXIT_FAILURE);
            }
        }
        return exitNode;
    }
};