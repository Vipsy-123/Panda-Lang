class Genrator{
    optional<NodeExit>  root;
public:
    Genrator(optional<NodeExit> root){
        this->root=root;
    }
    string Genrate(){
        stringstream output;
        output<<"bits 64\nsection .text\nglobal _main\n\n";
        output<<"_main:\n";
        output<<"\tmov rax, 0x2000001\n";
        output<<"\tmov rdi, "<<root.value().expr.intLit.val.value()<<"\n";
        output<<"\tsyscall\n";
        return output.str();
    }
};