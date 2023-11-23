#include <iomanip>
#include <string> 
#include <iostream> 
#include <fstream>
#include <memory> 
#include <vector>
#define DEBUG 
#ifdef DEBUG 
const char* inputSource = 
"10*2-(140-12)-(12+2)\n";
#endif
// 標準出力で使える色の種類を表す列挙型
enum class PrintColors {
  Black,   // 黒
  White,   // 白
  Red,	   // 赤
  Blue,	   // 青
  Green,   // 緑
  Yellow,  // 黄色
  Purple,  // 紫
  Cyan,	   // 水色
};


enum class TokenType{
    IntValue,
    Add,
    Sub,
    Mul,
    Div,
    LeftParen,
    RightParen,
    NewLine,
    Eof,
};
struct Token{
    int line,column;
    std::string value;
    TokenType type;
    Token(TokenType type,std::string value,int line,int column){
      this->type = type;
      this->line = line;
      this->column = column;
      this->value = value;
    }
};
class Lex{
public:
  Lex(std::string input):input(input){
      this->index = 0;
      this->line = 1;
      this->column = 0;
  }
  char currentChar(){
      return input[index];
  }

  char peekToken(int offset=1){
      if(index+offset >= input.size()){
          std::cerr << "いんでっくすがい！" <<std::endl;
          return '\0';
      }
      return input[index+offset];
  }
  char previousToken(int offset=1){
      if(index-offset<0){
          std::cerr << "いんでっくすがい！" <<std::endl;
          return '\0';      
      }
      return input[index-offset];
  } 
 void nextChar(){ 
    if(currentChar() == '\n'){ 
        index++;
        line++; 
        column = 0;
        return;
    } 
    index++; column++; 
}
  std::vector<Token> tokenize(){
      std::vector<Token> tokens;
      Token token = nextToken();
      while(true){
        tokens.push_back(token);
        token = nextToken();
        if(token.type == TokenType::Eof){
              tokens.push_back(token);
              break;
        }
    }
      return tokens;
  }
  Token readIntLiteral(){
    std::string value;
    while(isdigit(currentChar())){
        value+= currentChar();
        nextChar();
    }
    return Token(TokenType::IntValue,value,line,column);
  }
  bool isEof(){
    return index >= input.size();
  }
  Token nextToken(){
      symbolSkip();
      char c = currentChar();
      if(isEof()){
          return Token(TokenType::Eof,"EOF",line,column);
      }else if(c == '\r' ||c == '\n'){   
        nextChar();
        return Token(TokenType::NewLine,"\\n",line,column);
      }else if(isdigit(c)){
          return readIntLiteral();
      }else if(c == '+'){
          nextChar();
          return Token(TokenType::Add,"+",line,column);
      }else if(c == '-'){
          nextChar();
          return Token(TokenType::Sub,"-",line,column);
      }else if(c == '*'){
          nextChar();
          return Token(TokenType::Mul,"*",line,column);
      }else if(c == '/'){
          nextChar();
          return Token(TokenType::Div,"/",line,column);
      }else if(c == '('){
          nextChar();
          return Token(TokenType::LeftParen,"(",line,column);
      }else if(c == ')'){
          nextChar();
          return Token(TokenType::RightParen,")",line,column);
      }else{
          std::cerr << "Invalid charctor:"<<c<< std::endl;
          exit(1);
      }
  }
 void symbolSkip(){
  while(currentChar() == ' '
        ||currentChar() == '\t'
  ){
      nextChar(); 
  }
}


private:
  std::string input; 
  int line,column,index;
};


std::string tokenTypeToString(TokenType type){
    std::string temp;
    switch(type){
       case TokenType::IntValue:
             temp += "IntValue";
             break;
        case TokenType::Add:
             temp += "Add";
             break;
        case TokenType::Sub:
             temp += "Sub";
             break;
        case TokenType::Mul:
             temp += "Mul";
             break;
        case TokenType::Div:
             temp += "Div";
             break;
        case TokenType::RightParen:
             temp += "RightParen";
             break;
        case TokenType::LeftParen:
             temp += "LeftParen";
             break;
        case TokenType::Eof:
             temp += "Eof";
             break;
        case TokenType::NewLine:
             temp += "NewLine";
             break;
        default:
             temp += "Error";
             break;    
    }
    return temp;
}




std::string colorToPrintString(const std::string& string, PrintColors color) {
  std::string colors_left;
  std::string colors_end = "\033[0m";
  switch (color) {
    case PrintColors::Black:
      colors_left = "\033[30m";
      break;
    case PrintColors::White:
      colors_left = "\033[37m";
      break;
    case PrintColors::Red:
      colors_left = "\033[31m";
      break;
    case PrintColors::Blue:
      colors_left = "\033[34m";
      break;
    case PrintColors::Green:
      colors_left = "\033[32m";
      break;
    case PrintColors::Yellow:
      colors_left = "\033[33m";
      break;
    case PrintColors::Purple:
      colors_left = "\033[35m";
      break;
    case PrintColors::Cyan:
      colors_left = "\033[36m";
      break;
    default:
      break;
  }

  return colors_left + string + colors_end;
}
void printCenterString(const std::string& string,int width) {
    int padding = (width - string.length()) / 2;
    if (padding > 0) {
        std::cout << std::setw(padding) << ' ';
    }
    std::cout << string << std::endl;
}
void printAllLexData(std::vector<Token>& tokens){
    printCenterString(colorToPrintString("||LEXERS||",PrintColors::Purple),43);
    std::cout <<"|" << colorToPrintString(" type ",PrintColors::Yellow) <<"|" << "|" << colorToPrintString(" value ",PrintColors::Cyan) <<"|" << "|" << colorToPrintString(" line ",PrintColors::Green) <<"|" << "|" << colorToPrintString(" column ",PrintColors::Green) <<"|\n" << std::endl;
    for(auto&& tk:tokens){
        std::cout << "| " << colorToPrintString(tokenTypeToString(tk.type),PrintColors::Yellow) <<" |";
        std::cout << "| (" <<colorToPrintString(tk.value, PrintColors::Cyan) << ") |";
        std::cout << "| "  << colorToPrintString(std::to_string(tk.line),PrintColors::Green) << " |" ;
        std::cout << "| "  << colorToPrintString(std::to_string(tk.column),PrintColors::Green)  << " |";
        std::cout << "\n";
    }
}

enum class NodeType{
    IntValue,
    Add,
    Sub,
    Mul,
    Div,
    LeftParen,
    RightParen,
};
struct Node{
//    std::unique_ptr<Node>left;
//    std::unique_ptr<Node>right;
    Node(NodeType type,Node* left,Node* right,std::string value = ""):type(type),left(left),right(right),value(value){}
    Node* left;
    Node* right;
    NodeType type;  
    std::string value;
};
class Parser{
public:
    Parser(std::vector<Token>&tokens):tokens(tokens),index(0){}
    Token currentTokens(){
        return tokens[index];
    }
    void nextTokens(){
        index+=1;
    }
  Node* parse(){
        while(true){
            
        }
  }
  Node* expr(){
            Node* node = mul();
            while(true){
                if(currentTokens().type == TokenType::NewLine){
                      nextTokens();
                    return node;
                }
                else if(currentTokens().type == TokenType::Add){
                        nextTokens();
                        node = new Node(NodeType::Add,node,mul());
                }else if(currentTokens().type == TokenType::Sub){
                        nextTokens();
                        node = new Node(NodeType::Sub,node,mul());
                }else{
                    return node;                    
                }
            }
    }


    Node* mul(){
            Node* node = primary();
            while(true){
                if(currentTokens().type == TokenType::Mul){
                        nextTokens();
                        node = new Node(NodeType::Mul,node,primary());
                }else if(currentTokens().type == TokenType::Div){
                        nextTokens();
                        node = new Node(NodeType::Div,node,primary());
                }else{
                    return node;
                }
            }
    }
    
    
    Node* primary(){ // 次のトークンが"(“なら、”(" expr ")"のはず 
    if (currentTokens().type == TokenType::LeftParen) { 
        nextTokens(); // 左括弧を読み飛ばす 
        Node *node = expr(); 
        nextTokens(); // 右括弧を読み飛ばす 
        return node; 
    } 
    auto val = new Node(NodeType::IntValue,nullptr,nullptr,currentTokens().value); 
    nextTokens(); // 整数値を読み飛ばす 
    return val; 
    }
        //std::unique_ptr<Node> parse(){}
    
   // std::unique_ptr<Node> expr(){}
   // std::unique_ptr<Node> term(){}
   // std::unique_ptr<Node> factor(){}
private:
    int index;
    std::vector<Token> tokens;
};


 std::string nodeTypeToString(const NodeType& type) {
    std::string temp = "";
    switch (type) {
      case NodeType::IntValue:
	temp += "IntValue";
	break;
      case NodeType::Add:
	temp += "Add";
	break;
      case NodeType::Sub:
	temp += "Sub";
	break;
      case NodeType::Mul:
	temp += "Mul";
	break;
      case NodeType::Div:
	temp += "Div";
	break;
    default:
	temp += "Error";
	break;
    }
    return temp;
  }

void printNodeTree(Node* node, int depth =1) {
  if (node == nullptr) {
    return;
  }

 

  std::cout  <<  "| " << colorToPrintString(nodeTypeToString(node->type),PrintColors::Yellow) << " |";
  std::cout  <<  "| (" << colorToPrintString(node->value,PrintColors::Cyan) << ") |" << std::endl;
  for(int i=0;i<depth;i++){
        std::cout << ' ';
  }
  // 左右のサブツリーを再帰的に表示
  if (node->left != nullptr) {
    printNodeTree(node->left, depth + 1);
  }
  if (node->right != nullptr) {
    printNodeTree(node->right, depth + 1);
  }
}
void printAllNodeTree(Node*node,int depth =1){
    std::cout << "\n";
    printCenterString(colorToPrintString("||PARSERS||",PrintColors::Purple),45);
    std::cout <<"      ";
    std::cout <<"|" << colorToPrintString(" type ",PrintColors::Yellow) <<"|";
    std::cout <<"      ";
    std::cout << "|" << colorToPrintString(" value ",PrintColors::Cyan) <<"|\n" <<std::endl; 
    printNodeTree(node,depth);
}
int main(int argc,char** argv){
#ifndef DEBUG 
  if(argc < 2){
        std::cerr << "引数が少ないよ(。_。)" << std::endl;
  }
 
  // コマンドライン引数からファイル名を受け取る
  std::ifstream inputFile(argv[1]);

  // もしファイルが存在しないなら
  if (!inputFile.is_open()) {
    std::cout << "ファイルを読み取ることができません" << std::endl;
    return -1;
  }
  // スクリプトを一度に読み込む
  std::string inputSource((std::istreambuf_iterator<char>(inputFile)),
		    (std::istreambuf_iterator<char>()));
 
  inputFile.close();
#endif 
  
  std::string input(inputSource);
  Lex lex(input);
  auto tokens = lex.tokenize();
  printAllLexData(tokens); 
  Parser parser(tokens);
  auto node1 =parser.expr();
  printAllNodeTree(node1);
}