#include"compilerLib.h"


// vector<Token> tokanize(string str){
//     vector<Token> tokens;
//     string buf="";
//     for(int i=0;i<str.length();i++){
//         if(isspace(str.at(i)))continue;
//         if(isalpha(str.at(i))){
//             buf+=str.at(i);
//             i++;
//             while(isalnum(str.at(i))){
//                 buf.push_back(str.at(i));
//                 i++;
//             }
//             i--;
//             if(buf=="ret")tokens.push_back({.type=TokenType::ret});
//             else{
//                 cout<<"you messed up!";
//                 exit(EXIT_FAILURE);
//             }
//             buf.clear();
//         }
//         else if(isdigit(str.at(i))){
//             buf+=str.at(i);
//             i++;
//             while(isdigit(str.at(i))){
//                 buf.push_back(str.at(i));
//                 i++;
//             }
//             i--;
//             tokens.push_back({.type=TokenType::digit,.val=buf});
//             buf.clear();
//         }
//         else if(str.at(i)==';'){
//             tokens.push_back({.type=TokenType::semi});
//         }
//         else{
//             cout<<"you messed up!";
//             exit(EXIT_FAILURE);
//         }
//     }
//     return tokens;
// }
    
int main(int argc,char* argv[]){
    string str=readFileToString(argc,argv);

    Lexer lexer(str);
    vector<Token> tokens=lexer.tokenize();
    cout<<(tokens.size());
    
    return 0;
}