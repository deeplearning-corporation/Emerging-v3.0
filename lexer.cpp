// lexer.cpp
// Emerging Language Lexer
// Version 3.0
// Fixed for Visual C++

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    STRING,
    OPERATOR,
    PUNCTUATION,
    COMMENT,
    WHITESPACE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

class EmergingLexer {
private:
    std::string source;
    size_t position;
    int line;
    int column;
    
    std::vector<std::string> keywords = {
        "if", "else", "while", "for", "return",
        "int", "char", "void", "struct", "union",
        "const", "static", "extern", "inline",
        "break", "continue", "goto", "sizeof",
        "unsigned", "short", "long", "uint8_t",
        "uint16_t", "uint32_t", "uint64_t"
    };
    
public:
    EmergingLexer(const std::string& src) : source(src), position(0), line(1), column(1) {}
    
    char current() {
        if (position >= source.length()) return '\0';
        return source[position];
    }
    
    char peek() {
        if (position + 1 >= source.length()) return '\0';
        return source[position + 1];
    }
    
    void advance() {
        if (current() == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        position++;
    }
    
    void skipWhitespace() {
        while (position < source.length() && std::isspace(current())) {
            advance();
        }
    }
    
    Token readIdentifier() {
        size_t start = position;
        int startLine = line;
        int startColumn = column;
        
        while (position < source.length() && (std::isalnum(current()) || current() == '_')) {
            advance();
        }
        
        std::string value = source.substr(start, position - start);
        TokenType type = TokenType::IDENTIFIER;
        
        // 检查是否为关键字
        for (const auto& keyword : keywords) {
            if (value == keyword) {
                type = TokenType::KEYWORD;
                break;
            }
        }
        
        return {type, value, startLine, startColumn};
    }
    
    Token readNumber() {
        size_t start = position;
        int startLine = line;
        int startColumn = column;
        
        while (position < source.length() && std::isdigit(current())) {
            advance();
        }
        
        // 检查十六进制
        if (current() == 'x' || current() == 'X') {
            advance();
            while (position < source.length() && std::isxdigit(current())) {
                advance();
            }
        }
        
        return {TokenType::NUMBER, source.substr(start, position - start), startLine, startColumn};
    }
    
    Token readString() {
        size_t start = position;
        int startLine = line;
        int startColumn = column;
        char quote = current();
        advance(); // 跳过开头的引号
        
        while (position < source.length() && current() != quote) {
            if (current() == '\\') {
                advance(); // 跳过转义字符
            }
            advance();
        }
        
        if (position < source.length()) {
            advance(); // 跳过结尾的引号
        }
        
        return {TokenType::STRING, source.substr(start, position - start), startLine, startColumn};
    }
    
    Token readComment() {
        size_t start = position;
        int startLine = line;
        int startColumn = column;
        
        if (current() == '/' && peek() == '/') {
            // 单行注释
            while (position < source.length() && current() != '\n') {
                advance();
            }
        } else if (current() == '/' && peek() == '*') {
            // 多行注释
            advance(); advance(); // 跳过 /*
            while (position < source.length() && !(current() == '*' && peek() == '/')) {
                advance();
            }
            if (position < source.length()) {
                advance(); advance(); // 跳过 */
            }
        }
        
        return {TokenType::COMMENT, source.substr(start, position - start), startLine, startColumn};
    }
    
    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        
        while (position < source.length()) {
            skipWhitespace();
            if (position >= source.length()) break;
            
            char c = current();
            
            if (std::isalpha(c) || c == '_') {
                tokens.push_back(readIdentifier());
            } else if (std::isdigit(c)) {
                tokens.push_back(readNumber());
            } else if (c == '"' || c == '\'') {
                tokens.push_back(readString());
            } else if (c == '/' && (peek() == '/' || peek() == '*')) {
                tokens.push_back(readComment());
            } else {
                // 操作符和标点
                size_t start = position;
                int startLine = line;
                int startColumn = column;
                
                std::string op;
                op += c;
                advance();
                
                // 检查双字符操作符
                if ((c == '=' && peek() == '=') ||
                    (c == '!' && peek() == '=') ||
                    (c == '<' && peek() == '=') ||
                    (c == '>' && peek() == '=') ||
                    (c == '+' && peek() == '+') ||
                    (c == '-' && peek() == '-') ||
                    (c == '&' && peek() == '&') ||
                    (c == '|' && peek() == '|') ||
                    (c == '=' && peek() == '=') ||
                    (c == '!' && peek() == '=') ||
                    (c == '<' && peek() == '<') ||
                    (c == '>' && peek() == '>')) {
                    op += current();
                    advance();
                }
                
                // 标点符号
                if (c == ';' || c == ',' || c == '.' || c == '(' || c == ')' || 
                    c == '{' || c == '}' || c == '[' || c == ']') {
                    tokens.push_back({TokenType::PUNCTUATION, op, startLine, startColumn});
                } else {
                    tokens.push_back({TokenType::OPERATOR, op, startLine, startColumn});
                }
            }
        }
        
        return tokens;
    }
    
    void printTokens(const std::vector<Token>& tokens) {
        std::cout << "=== Emerging Language Lexer Output ===" << std::endl;
        std::cout << "Total tokens: " << tokens.size() << std::endl << std::endl;
        
        for (const auto& token : tokens) {
            std::cout << "Line " << token.line << ", Col " << token.column << ": ";
            switch (token.type) {
                case TokenType::KEYWORD: std::cout << "KEYWORD"; break;
                case TokenType::IDENTIFIER: std::cout << "IDENTIFIER"; break;
                case TokenType::NUMBER: std::cout << "NUMBER"; break;
                case TokenType::STRING: std::cout << "STRING"; break;
                case TokenType::OPERATOR: std::cout << "OPERATOR"; break;
                case TokenType::PUNCTUATION: std::cout << "PUNCTUATION"; break;
                case TokenType::COMMENT: std::cout << "COMMENT"; break;
                default: std::cout << "UNKNOWN"; break;
            }
            std::cout << " - '" << token.value << "'" << std::endl;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: emerging-lexer <file.emg>" << std::endl;
        return 1;
    }
    
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
        return 1;
    }
    
    // 读取整个文件
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    
    EmergingLexer lexer(content);
    auto tokens = lexer.tokenize();
    lexer.printTokens(tokens);
    
    return 0;
}
