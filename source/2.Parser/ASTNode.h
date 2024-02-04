struct NodeTermIntLit{
    Token intLit;
};
struct NodeTermIdent{
    Token ident;
};
struct NodeExpr;

struct NodeTermParen{
    NodeExpr* var;
};

struct NodeBinAdd{
    NodeExpr* lhs;
    NodeExpr* rhs;
};
struct NodeBinMul{
    NodeExpr* lhs;
    NodeExpr* rhs;
};
struct NodeBinSub{
    NodeExpr* lhs;
    NodeExpr* rhs;
};
struct NodeBinDiv{
    NodeExpr* lhs;
    NodeExpr* rhs;
};

struct NodeBinExpr{
    variant<NodeBinAdd*,NodeBinMul*,NodeBinDiv*,NodeBinSub*>var;
    // NodeBinAdd* var;
};
struct NodeTerm{
    variant<NodeTermIntLit*,NodeTermIdent*,NodeTermParen*> var;
    // NodeTermIntLit* var;
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
struct NodeStmts;
struct NodeScope{
   vector<NodeStmts*> stmts;
};
struct NodeIf{
    NodeExpr* expr;
    NodeScope* scope;
};

struct NodeStmts{
    variant<NodeStmtsExit*, NodeStmtsVar*,NodeScope*,NodeIf*> var;
};
struct NodeProg{
    vector<NodeStmts*> stmts;
};