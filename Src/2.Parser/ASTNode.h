struct NodeTermIntLit{
    Token intLit;
};
struct NodeTermIdent{
    Token ident;
};
struct NodeExpr;

struct NodeBinAdd{
    NodeExpr* lhs;
    NodeExpr* rhs;
};
struct NodeBinMul{
    NodeExpr* lhs;
    NodeExpr* rhs;
};

struct NodeBinExpr{
    variant<NodeBinAdd*,NodeBinMul*>var;
    // NodeBinAdd* var;
};
struct NodeTerm{
    variant<NodeTermIntLit*,NodeTermIdent*> var;
};

struct NodeExpr{
    variant<NodeTerm*,NodeBinExpr*> var;
};

struct NodeStmtsExit{
    NodeExpr* expr;
};
struct NodeStmtsVar{
    Token ident;
    NodeExpr* expr;

};

struct NodeStmts{
    variant<NodeStmtsExit*, NodeStmtsVar*> var;
};
struct NodeProg{
    vector<NodeStmts*> stmts;
};