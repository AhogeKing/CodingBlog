#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include "lexcial.hpp"
using namespace std;

using TokenStream = vector<Token>;

static const string str1 = "expected \';\' in ";

// 形参列表宏（如果需要保留宏，可继续使用，否则建议用成员变量）
#define PARSER_PARAM TokenStream &tokens, size_t pos
#define PARSER_ARGS tokens, pos

class SyntaxAnalizer
{
private:
    size_t pos;
    size_t length;
    TokenStream tokens;

    //* 变量声明
    void parseDecl();           //* finished 3_4
    void parseStructDecl();     //* finished 3_5
    void parseSuffix();         //! type id 常为各种声明的前缀 finished 3_4
    void parseVarDeclSuffix();  // TODO 变量声明后缀
    void parseFunctionSuffix(); // TODO 函数声明后缀

    //* 语句部分
    void parseExpressionStatement(); // TODO

    //* 形参列表
    void parseParam(); // TODO 3_5

    //* 代码块
    void parseFunctionBody(); // TODO 3_5
public:
    // 构造函数：传入 Token 流
    SyntaxAnalizer(TokenStream &t) : pos(0), length(t.size() - 1), tokens(t) {}

    enum Error
    {
        nil,
        TYPE,
        ID,
    };

    // Helper 类：提供静态工具方法
    class Helper
    {
        inline static const unordered_set<string> type{
            "int", "double", "string", "char", "bool", "auto"};

    public:
        // 判断当前 Token 是否是类型关键字
        inline static bool isType(const Token &curT)
        {
            return type.find(curT.value) != type.end();
        }

        // 判断是否是“结构体”或类型关键字（可能是结构体声明的开头）
        inline static bool isVarDecl(const Token &curT)
        {
            return (curT.value == "struct") || isType(curT);
        }

        // 检查是否越界
        inline static bool checkPosition(PARSER_PARAM, size_t Max_Position)
        {
            if (pos >= Max_Position)
            {
                cout << "Syntax error: Unexpected end of input." << endl;
                return false;
            }
            return true;
        }

        // 判断是否为“类型 标识符”结构
        // 例如：int a
        // 先判断：是不是一个类型？然后再看下一个 token 是否是标识符
        //! 它是一个值传递函数
        inline static Error is_type_id(PARSER_PARAM)
        {
            Token tmp = tokens[pos];
            if (tmp.type != TokenType::KEYWORD || !isType(tmp))
                return Error::TYPE; // 不是类型关键字
            ++pos;                  // 消费类型关键字

            if (pos >= tokens.size())
                return Error::ID; // 缺少标识符

            tmp = tokens[pos];
            if (tmp.type != TokenType::IDENTIFIER)
                return Error::ID; // 不是标识符

            // 说明“类型+标识符”都匹配成功
            return Error::nil;
        }

        static bool eatSemicolon(PARSER_PARAM);
    };

    // 最外层的解析函数
    void parseProgram();
};

#endif // SYNTAX_HPP