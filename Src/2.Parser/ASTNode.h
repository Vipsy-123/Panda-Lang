struct NodeExprIntLit{
    Token intLit;
};
struct NodeExprIdent{
    Token ident;
};


struct NodeExpr{
    variant<NodeExprIntLit,NodeExprIdent> var;
};

struct NodeStmtsExit{
    NodeExpr expr;
};
struct NodeStmtsVar{
    Token ident;
    NodeExpr expr;

};

struct NodeStmts{
    variant<NodeStmtsExit, NodeStmtsVar> var;
};
struct NodeProg{
    vector<NodeStmts> stmts;
};