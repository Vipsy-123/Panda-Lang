class Parser{
    size_t curIdx;
    vector<Token> tokens;
    ArenaAllocator allocator;

    optional<Token>peek(int offset=0){
        if(curIdx+offset>=tokens.size())return {};
        return tokens[curIdx+offset];
    }
    Token consume(){
        return tokens[curIdx++];
    }
public:
    Parser(vector<Token> tokens):allocator(1024*1024*4){
        this->tokens=tokens;
        this->curIdx=0;
    }
    optional<NodeExpr*> parseExpr(){
        if(peek().has_value() && peek().value().type==TokenType::digit){
            auto nodeExprIntLit=allocator.alloc<NodeExprIntLit>();
            nodeExprIntLit->intLit=consume();
            auto expr=allocator.alloc<NodeExpr>();
            expr->var=nodeExprIntLit;
            return expr;
        }
        if(peek().has_value() && peek().value().type==TokenType::ident){
            auto nodeExprIdent=allocator.alloc<NodeExprIdent>();
            nodeExprIdent->ident=consume();
            auto expr=allocator.alloc<NodeExpr>();
            expr->var=nodeExprIdent;
            return expr;
        }
        return {};
    }

    optional<NodeStmts*> parseStmts(){
        if(peek().value().type == TokenType::ret && peek(1).value().type == TokenType::openParen){
            consume();consume();
            auto exitStmts=allocator.alloc<NodeStmtsExit>();
            if(auto nodeExpr=parseExpr()){
                exitStmts->expr=nodeExpr.value();
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
            auto nodeStmt=allocator.alloc<NodeStmts>();
            nodeStmt->var=exitStmts;
            return nodeStmt;
        }
        else if(peek().has_value() &&
                peek().value().type == TokenType::let &&
                peek(1).has_value() &&
                peek(1).value().type == TokenType::ident &&
                peek(2).has_value() && 
                peek(2).value().type == TokenType::equal)
        {
            consume();
            auto varStmts=allocator.alloc<NodeStmtsVar>();
            varStmts->ident=consume();
            consume();
            if(auto nodeExpr=parseExpr()){
                varStmts->expr=nodeExpr.value();
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
            auto stmt=allocator.alloc<NodeStmts>();
            stmt->var=varStmts;
            return stmt;
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
                cerr<<"Invalid Statement1\n";
                exit(EXIT_FAILURE);
            }
        }
        return prog;
    }
};