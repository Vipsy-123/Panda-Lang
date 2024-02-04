class Genrator{
    
public:
    NodeProg root;
    stringstream output;  
    size_t stackSize;  
    int labelCount;

    struct Var{
        string name;
        size_t stackLoc;
    };
    vector<Var>varsMap {};
    vector<size_t>scopeVar {};

    Genrator(NodeProg root){
        this->root=root;
        stackSize=0;
        labelCount=0;
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
    vector<Var>::iterator find(Var var){
        for(auto it=varsMap.begin();it<varsMap.end();it++){
            if((*it).name ==var.name)return it;  
        }
        return varsMap.end();
    }
    void scopeBegin(){
        scopeVar.push_back(varsMap.size());
    }
    void scopeEnd(){
        size_t popCount=varsMap.size()-scopeVar.back();
        output<<"\tadd rsp,"<<popCount*8<<"\n";
        stackSize-=popCount;
        for(int i=0;i<popCount;i++){
            varsMap.pop_back();
        }
        scopeVar.pop_back();
    }
    string getLabel(){
        return "label_"+to_string(labelCount);
    }
    void genTerm(NodeTerm* term){
        struct TermVisitor{
            Genrator& gen;
            void operator()(NodeTermIntLit* termIntLit){
                gen.output<<"\tmov rax, "<<termIntLit->intLit.val.value()<<"\n";
                gen.push("rax");
            }
            void operator()(NodeTermIdent* termIdent){
                auto it=gen.find({.name=termIdent->ident.val.value()});
                if(it==gen.varsMap.end()){
                    cerr<<"Undeclared identifier: "<<termIdent->ident.val.value()<<"\n";
                    exit(EXIT_FAILURE);
                }
                stringstream offset;
                auto loc=it->stackLoc;
                offset<<"QWORD[rsp + "<<(gen.stackSize - loc-1)*8 << "]";
                gen.push(offset.str());
            }
            void operator()(NodeTermParen* expr){
                gen.genExpr(expr->var);
            }
        };
        TermVisitor visitor{.gen=*this};
        visit(visitor,term->var);
    }
    void genBin(NodeBinExpr* term){
        struct BinOpVisitor{
            Genrator& gen;
            void operator()(NodeBinAdd* binExprAdd){
                gen.genExpr(binExprAdd->rhs);
                gen.genExpr(binExprAdd->lhs);
                gen.pop("rax");
                gen.pop("rbx");
                gen.output<<"\tadd rax,rbx\n";
                gen.push("rax");
            }
            void operator()(NodeBinMul* binExprMul){
                gen.genExpr(binExprMul->rhs);
                gen.genExpr(binExprMul->lhs);
                gen.pop("rax");
                gen.pop("rbx");
                gen.output<<"\tmul rbx,\n";
                gen.push("rax");
            }
            void operator()(NodeBinDiv* binExprDiv){
                gen.genExpr(binExprDiv->rhs);
                gen.genExpr(binExprDiv->lhs);
                gen.pop("rax");
                gen.pop("rbx");
                gen.output<<"\tdiv rbx,\n";
                gen.push("rax");
            }
            void operator()(NodeBinSub* binExprSub){
                gen.genExpr(binExprSub->rhs);
                gen.genExpr(binExprSub->lhs);
                gen.pop("rax");
                gen.pop("rbx");
                gen.output<<"\tsub rax,rbx\n";
                gen.push("rax");
            }
        };
        BinOpVisitor visitor{.gen=*this};
        visit(visitor,term->var);
    }

    void genExpr(NodeExpr* expr){
        struct ExprVisitor{
            Genrator* gen;
            void operator()(NodeTerm* term){
                gen->genTerm(term);
            }
            void operator()(NodeBinExpr* binExpr){
                gen->genBin(binExpr);
            }
        };
        ExprVisitor vistor{.gen=this};
        visit(vistor,expr->var);
    }

    void genScope(NodeScope* scope){
        scopeBegin();
        for(NodeStmts* stmts: scope->stmts)genStmts(stmts);
        scopeEnd();
    }

    void genStmts(NodeStmts* stmts){
        struct StmtVisitor{
            Genrator& gen;
            void operator()(NodeStmtsExit* exitStmts){
                gen.genExpr(exitStmts->expr);
                gen.output<<"\tmov rax, 0x2000001\n";
                gen.pop("rdi");
                gen.output<<"\tsyscall\n";
            }
            void operator()(NodeStmtsVar* letStmts){
                auto it=gen.find({.name=letStmts->ident.val.value()});
                if(it!=gen.varsMap.end()){
                    cerr<<"Identifier Value Already used."<<letStmts->ident.val.value()<<"\n";
                    exit(EXIT_FAILURE);
                }
                gen.varsMap.push_back({.name=letStmts->ident.val.value(),.stackLoc=gen.stackSize});
                gen.genExpr(letStmts->expr);
            }
            void operator()(NodeScope* scope){
                gen.genScope(scope);
            }
            void operator()(NodeIf* ifStmt){
                gen.genExpr(ifStmt->expr);
                auto label=gen.getLabel();
                gen.pop("rax");
                gen.output<<"\ttest rax,rax\n";
                gen.output<<"\tjz "<<label<<"\n";
                gen.genScope(ifStmt->scope);
                gen.output<<label<<":\n";
            }
        };
        StmtVisitor visitor{.gen=*this}; 
        visit(visitor,stmts->var);
    }

    string genProg(){
        output<<"global _main\n_main:\n";

        for(auto stmt:root.stmts){
            genStmts(stmt);
        } 

        output<<"\n\tmov rax, 0x2000001\n";
        output<<"\tmov rdi, 0\n";
        output<<"\tsyscall\n";
        return output.str();
    }
};