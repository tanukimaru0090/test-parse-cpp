#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
// #define DEBUG
#ifdef DEBUG
const char* inputSource = "10*2-(140-12)-(12+2)\n";
#endif
// 標準出力で使える色の種類を表す列挙型
enum class PrintColors {
    Black,   // 黒
    White,   // 白
    Red,     // 赤
    Blue,    // 青
    Green,   // 緑
    Yellow,  // 黄色
    Purple,  // 紫
    Cyan,    // 水色
};

enum class TokenType {
    Let,         // 変数宣言キーワード
    Eq,          // 等しい
    NotEq,       // 等しくない
    Lt,          // より小さい
    Le,          // 以下
    Gl,          // より大きい
    Ge,          // 以上
    Ident,       // 識別子
    IntValue,    // 整数リテラル
    Add,         // 加算
    Sub,         // 減算
    Mul,         // 乗算
    Div,         // 除算
    LeftParen,   // 左括弧
    RightParen,  // 右括弧
    NewLine,     // 改行
    Semicolon,   // セミコロン
    Eof,         // 入力の終わり
};
struct Token {
    int line, column;
    std::string value;
    TokenType type;
    Token(TokenType type, std::string value, int line, int column) {
        this->type = type;
        this->line = line;
        this->column = column;
        this->value = value;
    }
};
class Lex {
   public:
    Lex(std::string input) : input(input),index(0),line(1),column(0) {
    
    }
    char currentChar() { return input[index]; }

    char peekToken(int offset = 1) {
        if (index + offset >= input.size()) {
            std::cerr << "いんでっくすがい！" << std::endl;
            return '\0';
        }
        return input[index + offset];
    }
    char previousToken(int offset = 1) {
        if (index - offset < 0) {
            std::cerr << "いんでっくすがい！" << std::endl;
            return '\0';
        }
        return input[index - offset];
    }
    void nextChar() {
        if (currentChar() == '\n') {
            index++;
            line++;
            column = 0;
            return;
        }
        index++;
        column++;
    }
    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        Token token = nextToken();
        while (true) {
            tokens.push_back(token);
            token = nextToken();
            if (token.type == TokenType::Eof) {
                tokens.push_back(token);
                break;
            }
        }
        return tokens;
    }
    Token readIntLiteral() {
        std::string value;
        while (isdigit(currentChar())) {
            value += currentChar();
            nextChar();
        }
        return Token(TokenType::IntValue, value, line, column);
    }
    // 識別子やキーワードを読み込むメソッド
    Token readIdent() {
        std::string value = "";
        while (isalpha(currentChar()) || isdigit(currentChar()) ||
               currentChar() == '_') {
            value += currentChar();
            nextChar();
        }
        TokenType type;
        if (value == "let") {
            type = TokenType::Let;
        } else {
            type = TokenType::Ident;
        }
        return Token(type, value, line, column);
    }
    bool isEof() { return index >= input.size(); }
    Token nextToken() {
        symbolSkip();
        char c = currentChar();
        if (isEof()) {
            return Token(TokenType::Eof, "EOF", line, column);
        } else if (c == '\r' || c == '\n') {
            nextChar();
            return Token(TokenType::NewLine, "\\n", line, column);
        } else if (isalpha(c) || c == '_') {
            return readIdent();
        } else if (isdigit(c)) {
            return readIntLiteral();
        } else if (c == '+') {
            nextChar();
            return Token(TokenType::Add, "+", line, column);
        } else if (c == '-') {
            nextChar();
            return Token(TokenType::Sub, "-", line, column);
        } else if (c == '*') {
            nextChar();
            return Token(TokenType::Mul, "*", line, column);
        } else if (c == '/') {
            nextChar();
            return Token(TokenType::Div, "/", line, column);
        } else if (c == '(') {
            nextChar();
            return Token(TokenType::LeftParen, "(", line, column);
        } else if (c == ')') {
            nextChar();
            return Token(TokenType::RightParen, ")", line, column);
        } else if (c == ';') {
            nextChar();
            return Token(TokenType::Semicolon, ";", line, column);
        } else {
            std::cerr << "Invalid charctor:" << c << std::endl;
            exit(1);
        }
    }
    void symbolSkip() {
        while (currentChar() == ' ' || currentChar() == '\t') {
            nextChar();
        }
    }

   private:
    std::string input;
    int line, column, index;
};

std::string tokenTypeToString(TokenType type) {
    std::string temp;
    switch (type) {
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
        case TokenType::Ident:
            temp += "Ident";
            break;
        case TokenType::Let:
            temp += "Let";
            break;
        case TokenType::Semicolon:
            temp += "Semicolon";
            break;
        case TokenType::Eq:
            temp += "Eq";
            break;
        case TokenType::NotEq:
            temp += "NotEq";
            break;
        case TokenType::Lt:
            temp += "Lt";
            break;
        case TokenType::Le:
            temp += "NewLine";
            break;
        case TokenType::Gl:
            temp += "Gl";
            break;
        case TokenType::Ge:
            temp += "Ge";
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
void printCenterString(const std::string& string, int width) {
    int padding = (width - string.length()) / 2;
    if (padding > 0) {
        std::cout << std::setw(padding) << ' ';
    }
    std::cout << string << std::endl;
}
void printAllLexData(std::vector<Token>& tokens) {
    printCenterString(colorToPrintString("||LEXERS||", PrintColors::Purple),
                      43);
    std::cout << "|" << colorToPrintString(" type ", PrintColors::Yellow) << "|"
              << "|" << colorToPrintString(" value ", PrintColors::Cyan) << "|"
              << "|" << colorToPrintString(" line ", PrintColors::Green) << "|"
              << "|" << colorToPrintString(" column ", PrintColors::Green)
              << "|\n"
              << std::endl;
    for (auto&& tk : tokens) {
        std::cout << "| "
                  << colorToPrintString(tokenTypeToString(tk.type),
                                        PrintColors::Yellow)
                  << " |";
        std::cout << "| (" << colorToPrintString(tk.value, PrintColors::Cyan)
                  << ") |";
        std::cout << "| "
                  << colorToPrintString(std::to_string(tk.line),
                                        PrintColors::Green)
                  << " |";
        std::cout << "| "
                  << colorToPrintString(std::to_string(tk.column),
                                        PrintColors::Green)
                  << " |";
        std::cout << "\n";
    }
}

enum class NodeType {
    Eq,          // 等しい
    NotEq,       // 等しくない
    Lt,          // より小さい
    Le,          // 以下
    Gl,          // より大きい
    Ge,          // 以上
    Variable,    // 変数
    Assign,      // 代入
    IntValue,    // 整数リテラル
    Add,         // 加算
    Sub,         // 減算
    Mul,         // 乗算
    Div,         // 除算
    LeftParen,   // 左括弧
    RightParen,  // 右括弧
    Program,     // コード全体を表す
};
struct Node {
    //    std::unique_ptr<Node>left;
    //    std::unique_ptr<Node>right;
    Node(NodeType type, Node* left, Node* right, std::string value = "")
        : type(type), left(left), right(right), value(value) {}
    Node* left;
    Node* right;
    NodeType type;
    std::string value;
};
class Parser {
   public:
    Parser(std::vector<Token>& tokens) : tokens(tokens), index(0) {}
    Token currentTokens() { return tokens[index]; }
    void nextTokens() { index += 1; }
    Node* primary() {
        if (currentTokens().type == TokenType::Ident) {
            Node* node = new Node(NodeType::Variable, nullptr, nullptr);
            return node;
        }
    }
    Node* relational() {}
    Node* equality() {
        Node* node = relational();
        while (true) {
            if (currentTokens().type == TokenType::Eq) {
                //} else if () {
                //} else if () {
            } else {
                return node;
            }
        }
    }
    Node* assign() {
        // Node* node =
    }
    Node* stmt() {}
    Node* parseProgram() {}
    Node* expr() {
        Node* node = mul();
        while (true) {
            if (currentTokens().type == TokenType::NewLine) {
                nextTokens();
                return node;
            } else if (currentTokens().type == TokenType::Add) {
                nextTokens();
                node = new Node(NodeType::Add, node, mul());
            } else if (currentTokens().type == TokenType::Sub) {
                nextTokens();
                node = new Node(NodeType::Sub, node, mul());
            } else {
                return node;
            }
        }
    }

    Node* mul() {
        Node* node = paren();
        while (true) {
            if (currentTokens().type == TokenType::Mul) {
                nextTokens();
                node = new Node(NodeType::Mul, node, paren());
            } else if (currentTokens().type == TokenType::Div) {
                nextTokens();
                node = new Node(NodeType::Div, node, paren());
            } else {
                return node;
            }
        }
    }

    Node* paren() {  // 次のトークンが"(“なら、”(" expr ")"のはず
        if (currentTokens().type == TokenType::LeftParen) {
            nextTokens();  // 左括弧を読み飛ばす
            Node* node = expr();
            nextTokens();  // 右括弧を読み飛ばす
            return node;
        }
        auto val = new Node(NodeType::IntValue, nullptr, nullptr,
                            currentTokens().value);
        nextTokens();  // 整数値を読み飛ばす
        return val;
    }
    // std::unique_ptr<Node> parse(){}

    // std::unique_ptr<Node> expr(){}
    // std::unique_ptr<Node> term(){}
    // std::unique_ptr<Node> factor(){}
   private:
    int index;
    std::vector<Token> tokens;
};
void deleteNode(Node* node) {
    // 左右のサブツリーを順番に開放
    if (node->left != nullptr) {
        deleteNode(node->left);
    }
    if (node->right != nullptr) {
       deleteNode(node->right);
    }
    delete node;
}
void deleteNodeLists(std::vector<Node*>& nodeLists) {}
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
        case NodeType::Program:
            temp += "Program";
            break;
        case NodeType::Variable:
            temp += "Variable";
            break;
        case NodeType::Eq:
            temp += "Eq";
            break;
        case NodeType::NotEq:
            temp += "NotEq";
            break;
        case NodeType::Lt:
            temp += "Lt";
            break;
        case NodeType::Le:
            temp += "NewLine";
            break;
        case NodeType::Gl:
            temp += "Gl";
            break;
        case NodeType::Ge:
            temp += "Ge";
            break;

        default:
            temp += "Error";
            break;
    }
    return temp;
}

void printNodeTree(Node* node, int depth = 1) {
    if (node == nullptr) {
        return;
    }

    std::cout << "| "
              << colorToPrintString(nodeTypeToString(node->type),
                                    PrintColors::Yellow)
              << " |";
    std::cout << "| (" << colorToPrintString(node->value, PrintColors::Cyan)
              << ") |" << std::endl;
    for (int i = 0; i < depth; i++) {
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
void printAllNodeTree(Node* node, int depth = 1) {
    std::cout << "\n";
    printCenterString(colorToPrintString("||PARSERS||", PrintColors::Purple),
                      45);
    std::cout << "      ";
    std::cout << "|" << colorToPrintString(" type ", PrintColors::Yellow)
              << "|";
    std::cout << "      ";
    std::cout << "|" << colorToPrintString(" value ", PrintColors::Cyan)
              << "|\n"
              << std::endl;
    printNodeTree(node, depth);
}

int main(int argc, char** argv) {
#ifndef DEBUG
    // 引数処理
    if (argc < 2) {
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
    // ストリームを閉じる
    inputFile.close();
#endif
    // コード全体のノードを格納する変数
    std::vector<Node*> program;
    // 入力
    std::string input(inputSource);
    // トークナイズ
    Lex lex(input);
    auto tokens = lex.tokenize();
    // トークン化されたデータを表示
    printAllLexData(tokens);
    // パース
    Parser parser(tokens);
    auto node1 = parser.expr();
    auto node2 = parser.expr();
    // パース済みのデータを表示
    printAllNodeTree(node1);
    deleteNode(node1);
}
