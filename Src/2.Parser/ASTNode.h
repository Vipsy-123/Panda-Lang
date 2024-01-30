struct NodeExprIntLit{
    Token intLit;
};
struct NodeExprIdent{
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
    variant<NodeBinAdd*,NodeBinMul*> var;
};
struct NodeExpr{
    variant<NodeExprIntLit*,NodeExprIdent*,NodeBinExpr*> var;
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