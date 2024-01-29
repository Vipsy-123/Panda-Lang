class Genrator{
    
public:
    NodeProg root;
    stringstream output;  
    size_t stackSize;  

    struct Var{
        size_t stackLoc;
    };
    unordered_map<string,Var>varsMap;

    Genrator(NodeProg root){
        this->root=root;
        stackSize=0;
        varsMap={};
        output<<"";
    }
    void push(string reg){
        output<<"\tpush "<<reg<<",\n";
        stackSize++;
    }
    void pop(string reg){
        output<<"\tpop "<<reg<<",\n";
        stackSize--;
    }
    
    void genExpr(NodeExpr expr){
        struct ExprVisitor{
            Genrator* gen;
            void operator()(NodeExprIntLit intLit){
                gen->output<<"\tmov rax, "<<intLit.intLit.val.value()<<"\n";
                gen->push("rax");
            }
            void operator()(NodeExprIdent ident){
                if(!gen->varsMap.contains(ident.ident.val.value())) {
                    cerr<<"Undeclared identifier:"<<ident.ident.val.value()<<"\n";
                    exit(EXIT_FAILURE);
                }  
                stringstream offset;
                auto loc=gen->varsMap[ident.ident.val.value()].stackLoc;
                offset<<"QWORD[rsp + "<<(gen->stackSize - loc-1)*8 << "]";
                gen->push(offset.str()); 
            }
        };
        ExprVisitor vistor{.gen=this};
        visit(vistor,expr.var);
    }

    void genStmts(NodeStmts stmts){
        struct StmtVisitor{
            Genrator* gen;
            void operator()(NodeStmtsExit exitStmts){
                gen->genExpr(exitStmts.expr);
                gen->output<<"\tmov rax, 0x2000001\n";
                gen->pop("rdi");
                gen->output<<"\tsyscall\n";
            }
            void operator()(NodeStmtsVar letStmts){
                if(gen->varsMap.contains(letStmts.ident.val.value())){
                    cerr<<"Identifier Value Already used."<<letStmts.ident.val.value()<<"\n";
                    exit(EXIT_FAILURE);
                }
                gen->varsMap.insert({letStmts.ident.val.value(),Var{.stackLoc=gen->stackSize}});
                gen->genExpr(letStmts.expr);
            }
        };
        StmtVisitor visitor{.gen=this}; 
        visit(visitor,stmts.var);
    }

    string genProg(){
        output<<"global _main\n_main:\n";

        for(auto stmt:root.stmts){
            genStmts(stmt);
        }

        output<<"\tmov rax, 0x2000001\n";
        output<<"\tmov rdi, 0\n";
        output<<"\tsyscall\n";
        return output.str();
    }
};