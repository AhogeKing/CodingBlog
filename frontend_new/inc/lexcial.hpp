#ifndef LEXCIAL_HPP
#define LEXCIAL_HPP
#include "head.hpp"
using namespace std;

enum TokenType
{
    UNKNOWN,        // 未知a
    KEYWORD,        // 关键字
    IDENTIFIER,     // 标识符
    FLOATING,       // 浮点数
    INTEGER,        // 整数
    OPERATOR,       // 运算符
    DELIMITER,      // 分隔符
    STRING_LITERAL, // 字符串
    CHARACTER,      // 字符
    TYPE_KEYWORD,   // 类型说明符
    OBJECT,         // 对象
    END,            // 结束符
};

// 标识符正则表达式
static const regex IdentifierRegex(R"(^\w[\w|\d|]*)");

// 整数正则（匹配含符号的纯整数）
static const regex IntegerRegex(R"(^[+-]?\d+)");
// 浮点数正则（仅匹配含小数点或指数的数字）
static const regex FloatingRegex(R"(^[+-]?(?:\d+\.\d*|\.\d+)(?:[eE][+-]?\d+)?)");
static const regex CharacterRegex(R"(^'(\\'|[^']|.)')");
static const regex StringLiteralRegex(R"(^"(?:[^"\\]|\\.)*")");

// 可以用于匹配空格（忽略的字符）
static const regex WhiteSpaceRegex(R"(^\s+)");
static const regex CommentRegex(R"(^\/\/.*|\/\*[\s\S]*?\*\/)");

// 用于表示运算符和分隔符的字符串集合
static const vector<string> OrderedOperators{
    "++", "--", "<=", ">=", "==", "!=", "+=", "-=", "*=", "/=", "%=", "&&", "||", "<<", ">>", "->", "::", "=", "+", "-", "*", "/", "%", "<", ">", "!", "&", ".", "|"};
static const unordered_set<char> DelimiterRegex{
    '[', ']', '(', ')', '{', '}', ',', ';', ':'};

// 关键字集合
static const unordered_set<string> Keywords{
    "auto",
    "bool",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "class",
    "default",
    "do",
    "double",
    "delete",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "false",
    "if",
    "int",
    "inline",
    "namespace",
    "new",
    "nullptr",
    "private",
    "protected",
    "public",
    "return",
    "sizeof",
    "static",
    "struct",
    "switch",
    "template",
    "this",
    "true",
    "typedef",
    "union",
    "unsigned",
    "signed",
    "void",
    "while",
    "using",
};

struct Token
{
    TokenType type;
    string value;

    Token(TokenType t, string v) : type(t), value(v) {}
};

class LexcialAnalizer
{
    string source;        // 字符序列
    size_t position;      // 位置指针
    size_t numOfTokens;   // 词素数量
    vector<Token> tokens; // 词素序列

    inline void addToken(TokenType type, const string &value)
    {
        tokens.emplace_back(Token(type, value));
    }

public:
    LexcialAnalizer(const string &input) : source(input + "\0"), position(0) {}

    void tokenize();

    void printTokens() const;

    void printTokensToFile(const string &fileName) const;

    string getTokenName(TokenType type) const;

    inline vector<Token> &getTokens()
    {
        return tokens;
    }

    inline bool isOperator(const string &str)
    {
        for (auto elem : OrderedOperators)
            if (elem == str)
                return true;
        return false;
    }

    inline bool isDelimiterRegex(char ch)
    {
        return DelimiterRegex.find(ch) != DelimiterRegex.end();
    }

    inline bool isKeyword(const string &str)
    {
        return Keywords.find(str) != Keywords.end();
    }
};

#endif // LEXCIAL_HPP