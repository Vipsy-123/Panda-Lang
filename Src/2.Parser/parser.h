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
    Token tryConsume(TokenType type,string errMsg){
        if(peek().has_value() && peek().value().type==type){
            return consume();
        }
        else{
            cerr<<errMsg<<"\n";
            exit(EXIT_FAILURE);
        }
    }
    optional<Token> tryConsume(TokenType type){
        if(peek().has_value() && peek().value().type==type){
            return consume();
        }
        else{
            return{};
        }
    }
public:
    Parser(vector<Token> tokens):allocator(1024*1024*4){
        this->tokens=tokens;
        this->curIdx=0;
    }
    optional<NodeBinExpr*>parserBinExpr(){
        if(auto lhs=parseExpr()){
            auto binExpr=allocator.alloc<NodeBinExpr>();
            if(auto val=tryConsume(TokenType::plus)){
                auto binExprAdd=allocator.alloc<NodeBinAdd>();
                binExprAdd->lhs=lhs.value();
                if(auto rhs=parseExpr()){
                    binExprAdd->rhs=rhs.value();
                    binExpr->var=binExprAdd;
                    return binExpr;
                }
                else{
                    cerr<<"Error in RHS."<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            if(auto val=tryConsume(TokenType::mul)){
                auto binExprMul=allocator.alloc<NodeBinMul>();
                binExprMul->lhs=lhs.value();
                if(auto rhs=parseExpr()){
                    binExprMul->rhs=rhs.value();
                    binExpr->var=binExprMul;
                    return binExpr;
                }
                else{
                    cerr<<"Error in RHS."<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else{
                cerr<<"Unsupported BinOp."<<endl;
                exit(EXIT_FAILURE);
            }
        }
        return {};
    }
    optional<NodeTerm*> parseTerm(){
        if(auto val=tryConsume(TokenType::digit)){
            auto nodeTermIntLit=allocator.alloc<NodeTermIntLit>();
            nodeTermIntLit->intLit=val.value();
            auto term=allocator.alloc<NodeTerm>();
            term->var=nodeTermIntLit;
            return term;
        }
        if(auto val=tryConsume(TokenType::ident)){
            auto nodeTermIdent=allocator.alloc<NodeTermIdent>();
            nodeTermIdent->ident=val.value();
            auto term=allocator.alloc<NodeTerm>();
            term->var=nodeTermIdent;
            return term;
        }
        if(auto val=tryConsume(TokenType::openParen)){
            auto expr=parseExpr();
            if(!expr.has_value()){
                cerr<<"Expected Experssion\n";
                exit(EXIT_FAILURE);
            }
            tryConsume(TokenType::closeParen,"Expected ')'");
            auto nodeTermParen=allocator.alloc<NodeTermParen>();
            nodeTermParen->var=expr.value();
            auto term=allocator.alloc<NodeTerm>();
            term->var=nodeTermParen;
            return term;
        }
        return {};
    }
    optional<NodeExpr*> parseExpr(int minPrec=0){

        optional<NodeTerm*> lhs=parseTerm();
        if(!lhs.has_value())return {};
        auto lhsExpr=allocator.alloc<NodeExpr>();
        lhsExpr->var=lhs.value();

        while(1){
            optional<Token> curToken=peek();
            optional<int> prec;
            if(curToken.has_value()){
                prec=binOpPrec(curToken->type);
                if(!prec||prec<minPrec)break;
            }
            else break;

            Token op=consume();
            int nextPrec=prec.value()+1;
            auto rhsExpr=parseExpr(nextPrec);
            if(!rhsExpr.has_value()){
                cerr<<"unable to parse Expr\n";
                exit(EXIT_FAILURE);
            }
            auto expr=allocator.alloc<NodeBinExpr>();
            auto lhsExpr2=allocator.alloc<NodeExpr>();
            if(op.type==TokenType::plus){
                auto add=allocator.alloc<NodeBinAdd>();
                lhsExpr2->var=lhsExpr->var;
                add->lhs=lhsExpr2;
                add->rhs=rhsExpr.value();
                expr->var=add;
            }
            else if(op.type==TokenType::mul){
                auto mul=allocator.alloc<NodeBinMul>();
                lhsExpr2->var=lhsExpr->var;
                mul->lhs=lhsExpr2;
                mul->rhs=rhsExpr.value();
                expr->var=mul;
            }
            else if(op.type==TokenType::sub){
                auto sub=allocator.alloc<NodeBinSub>();
                lhsExpr2->var=lhsExpr->var;
                sub->lhs=lhsExpr2;
                sub->rhs=rhsExpr.value();
                expr->var=sub;
            }
            else if(op.type==TokenType::div){
                auto div=allocator.alloc<NodeBinDiv>();
                lhsExpr2->var=lhsExpr->var;
                div->lhs=lhsExpr2;
                div->rhs=rhsExpr.value();
                expr->var=div;
            }
            lhsExpr->var=expr;
        }
        return lhsExpr;
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
            tryConsume(TokenType::closeParen,"Expexted ')'\n");
            tryConsume(TokenType::semi,"Expexted ';'\n");
            
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