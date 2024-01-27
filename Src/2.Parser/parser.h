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
        if(peek().has_value() && peek().value().type==TokenType::digit){
            return NodeExpr{.var=NodeExprIntLit{.intLit=consume()}};
        }
        if(peek().has_value() && peek().value().type==TokenType::ident){
            return NodeExpr{.var=NodeExprIdent{.ident=consume()}};
        }
        return {};
    }

    optional<NodeStmts> parseStmts(){
        if(peek().value().type == TokenType::ret && peek(1).value().type == TokenType::openParen){
            consume();consume();
            NodeStmtsExit exitStmts;
            if(auto nodeExpr=parseExpr()){
                exitStmts={.expr=nodeExpr.value()};
            }
            else {
                cerr<<"Invalid Expression...\n";
                exit(EXIT_FAILURE);
            }
            if(peek().has_value() && peek().value().type==TokenType::closeParen){
            consume();
            }
            else{
                cerr<<"Expected ')'\n";
                exit(EXIT_FAILURE);
            }
            if(peek().has_value() && peek().value().type==TokenType::semi)
                consume();
            else{
                cerr<<"Expected ';'\n";
                exit(EXIT_FAILURE);
            }
            return NodeStmts{.var=exitStmts};
        }
        else if(peek().has_value() &&
                peek().value().type == TokenType::let &&
                peek(1).has_value() &&
                peek(1).value().type == TokenType::ident &&
                peek(2).has_value() && 
                peek(2).value().type == TokenType::equal)
        {
            consume();
            auto varStmts=NodeStmtsVar{.ident=consume()};
            consume();
            if(auto nodeExpr=parseExpr()){
                varStmts.expr=nodeExpr.value();
            }
            else{
                cerr<<"Invalid Experssion"<<endl;
                exit(EXIT_FAILURE);
            }
            if(peek().has_value() && peek().value().type==TokenType::semi)
                consume();
            else{
                cerr<<"Expected ';'\n";
                exit(EXIT_FAILURE);
            }
            return NodeStmts{.var=varStmts};
        }
        return {};
    }
    
    optional<NodeProg> parserProg(){
        NodeProg prog;
        while(peek().has_value()){
            if(auto stmt=parseStmts()){
                prog.stmts.push_back(stmt.value());
            }
            else{
                cerr<<"Invalid Statement\n";
                exit(EXIT_FAILURE);
            }
        }
        return prog;
    }
};