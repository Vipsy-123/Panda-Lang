class Genrator{
    
public:
    NodeProg root;
    stringstream output;    
    Genrator(NodeProg root){
        this->root=root;
        output<<"";
    }

    void genExpr(NodeExpr expr){
        struct ExprVisitor{
            Genrator* gen;
            void operator()(NodeExprIntLit intLit){
                gen->output<<"\tmov rax, "<<intLit.intLit.val.value()<<"\n";
                gen->output<<"\tpush rdi \n";
            }
            void operator()(NodeExprIdent ident){
            
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
                gen->output<<"\tpop rdi\n";
                gen->output<<"\tsyscall\n";
            }
            void operator()(NodeStmtsVar letStmts){
                
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