class Genrator{
    NodeProg root;
public:
    Genrator(NodeProg root){
        this->root=root;
    }
    string Genrate(){
        stringstream output;
        output<<"bglobal _main\n_main:\n";


        output<<"\tmov rax, 0x2000001\n";
        output<<"\tmov rdi, 0\n";
        output<<"\tsyscall\n";
        return output.str();
    }
};