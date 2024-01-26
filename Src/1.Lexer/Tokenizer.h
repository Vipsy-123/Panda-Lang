#include<iostream>
using namespace std;

struct Token{
    TokenType type;
    optional<string> val;
};

class Lexer{
    int curIdx;
    string src;

    char peak(int ahead=1){
        if(curIdx+ahead>src.length())return {};
        return src[curIdx];
    }
    char consume(){
        return src[curIdx++];
    }

public:
    Lexer(const string src){
        this->src=src;
        curIdx=0;
    }
    vector<Token> tokenize(){
        vector<Token> tokens;
        string buf="";

        while(peak()){
            if(isalpha(peak())){
                while(peak() && isalnum(peak()))buf.push_back(consume());
                if(buf=="ret")tokens.push_back({.type=TokenType::ret});
                else{
                    cout<<"you messed up!";
                    exit(EXIT_FAILURE);
                }
                buf.clear();
            }
            else if(isdigit(peak())){
                while(peak() && isdigit(peak()))buf.push_back(consume());
                tokens.push_back({.type=TokenType::digit,.val=buf});
                buf.clear();
            }
            else if(peak()==';'){
                tokens.push_back({.type=TokenType::semi});
                consume();buf.clear();
            }
            else if(isspace(peak())){
                consume();buf.clear();
            }
            else{
                cout<<"you messed up!";
                exit(EXIT_FAILURE);
            }
        }
        return tokens;
    }
};