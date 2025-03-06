#include "../inc/syntax.hpp"

using Helper = SyntaxAnalizer::Helper;
using Error = SyntaxAnalizer::Error;

void SyntaxAnalizer::parseProgram()
{
    while (pos < length)
    {
        parseDecl();
    }

    if (tokens[pos].type == TokenType::END)
        cout << "syntax analysis finish!" << endl;
}

void SyntaxAnalizer::parseDecl()
{
    if (!Helper::checkPosition(PARSER_ARGS, length))
    {
        cout << str1 << endl;
        exit(1);
    }

    if (tokens[pos].type == TokenType::KEYWORD && tokens[pos].value == "struct")
    {
        parseStructDecl(); // TODO 3-4 没有消化掉 struct
        return;
    }

    Error err = Helper::is_type_id(PARSER_ARGS);
    if (err == Error::nil)
    {
        pos += 2;
        if (!Helper::checkPosition(PARSER_ARGS, length))
        {
            cout << "expected \';\' or \'function declaration or expression in " << pos + 1 << endl;
            exit(1);
        }
        parseSuffix(); //* finished 3-5
    }
    else if (err == Error::TYPE)
    {
        cout << "expected type in " << pos + 1 << endl;
        exit(1);
    }
    else if (err == Error::ID)
    {
        cout << "expected identifier in " << pos + 1 << endl;
        exit(1);
    }
}

void SyntaxAnalizer::parseSuffix()
{
    Token cur = tokens[pos];
    if ((cur.type == TokenType::DELIMITER && cur.value == ";") || (cur.type == TokenType::OPERATOR && cur.value == "=")) // 变量声明
    {
        parseVarDeclSuffix(); // TODO 3-5
    }
    else if (cur.type == TokenType::DELIMITER && cur.value == "(") // 函数声明
    {
        parseFunctionSuffix(); // TODO 3-5
    }
    else
    {
        cout << str1 << pos + 1 << endl;
        exit(1);
    }
}

void SyntaxAnalizer::parseVarDeclSuffix()
{
    if (tokens[pos].value == ";") // 未初始化的变量声明
    {
        pos++; // 消化掉分号
        return;
    }

    // 有初始化的变量声明
    pos++; // 消化掉赋值号
    if (!Helper::checkPosition(PARSER_ARGS, length))
    {
        cout << "expected expression statement in " << pos + 1 << endl;
        exit(1);
    }
    parseExpressionStatement();
}

// 主动消耗分号
//? struct id? { Decl... } id? ;
void SyntaxAnalizer::parseStructDecl()
{
    pos++; // 消化掉 struct
    if (!Helper::checkPosition(PARSER_ARGS, length))
    {
        cout << "expected definition or declaration in " << pos + 1 << endl;
        exit(1);
    }

    int tag = 1;
    Token cur = tokens[pos];
    if (cur.type == IDENTIFIER) // 如果定义前有标识符
    {
        pos++; // 消化掉标识符
        if (!Helper::checkPosition(PARSER_ARGS, length))
        {
            cout << "expected identifier or \';\' in " << pos + 1 << endl;
            exit(1);
        }
        tag--;
        cur = tokens[pos];
        if (cur.type == TokenType::DELIMITER && cur.value == ";") // 应对 struct identifier ; 这种情况
        {
            pos++; // 消化掉分号
            return;
        }
    }

    cur = tokens[pos];
    if (cur.type == TokenType::DELIMITER && cur.value == "{")
    {
        pos++; // 消化掉左花括号
        if (!Helper::checkPosition(PARSER_ARGS, length))
        {
            cout << "expected declaration at " << pos + 1 << endl;
            exit(1);
        }

        while (!(tokens[pos].type == TokenType::DELIMITER && tokens[pos].value == "}"))
        {
            parseDecl();
            if (!Helper::checkPosition(PARSER_ARGS, length))
            {
                cout << "unexpected end of struct declaration at " << pos + 1 << endl;
                exit(1);
            }
        }
        pos++; // 消化掉右花括号
        if (!Helper::checkPosition(PARSER_ARGS, length))
        {
            cout << "expected \';\' in struct declaration at " << pos + 1 << endl;
            exit(1);
        }

        // struct id { Decl... } ;
        if (tokens[pos].type == TokenType::DELIMITER && tokens[pos].value == ";")
        {
            pos++; // 消化掉分号
            return;
        }
        else if (tokens[pos].type == TokenType::IDENTIFIER) // struct id { Decl... } id ;
        {
            tag--;
            pos++; // 消化掉标识符
            if (!Helper::checkPosition(PARSER_ARGS, length))
            {
                cout << "expected \';\' in struct declaration at " << pos + 1 << endl;
                exit(1);
            }
            pos++; // 消化掉分号
            if (tag == 0)
                cout << "Warning: struct declaration with alias is uncommon in modern C++. Consider using 'using' or 'typedef'." << endl;
            return;
        }
        else
        {
            cout << "expected \';\' in struct declaration at " << pos + 1 << endl;
            exit(1);
        }
    }
}

void SyntaxAnalizer::parseFunctionSuffix()
{
    pos++; // 消化掉 左括号
    if (!Helper::checkPosition(PARSER_ARGS, length))
    {
        cout << "expected param list of function declaration at " << pos + 1 << endl;
        exit(1);
    }
    parseParam(); // 解析形参列表
    pos++;        // 消耗 右括号
    if (!Helper::checkPosition(PARSER_ARGS, length))
    {
        cout << "expected \';\' in function declaration at " << pos + 1 << endl;
        exit(1);
    }
    parseFunctionBody(); // 解析函数体
}

void SyntaxAnalizer::parseParam()
{
    Token cur = tokens[pos];
    while (!(cur.type == TokenType::DELIMITER && cur.value == ")"))
    {
        Error err = Helper::is_type_id(PARSER_ARGS);
        if (err == Error::nil)
        {
            pos += 2; // 消耗类型名和标识符
            if (!Helper::checkPosition(PARSER_ARGS, length))
            {
                cout << "expected \')\' in function declaration at " << pos + 1 << endl;
                exit(1);
            }

            if (pos >= length || (tokens[pos].type == TokenType::DELIMITER && tokens[pos].value == ")"))
                break; // 解析完形参列表

            cur = tokens[pos];
            if (cur.type == TokenType::DELIMITER && cur.value == ",")
            {
                pos++; // 消耗逗号
                if (!Helper::checkPosition(PARSER_ARGS, length) || (tokens[pos].type == TokenType::DELIMITER && tokens[pos].value == ")"))
                {
                    cout << "expected type in function param at " << pos + 1 << endl;
                    exit(1);
                }
            }
        }
        else if (err == Error::TYPE)
        {
            cout << "expected type in param declaration at " << pos + 1 << endl;
            exit(1);
        }
        else if (err == Error::ID)
        {
            cout << "expected identifier in param declaration at " << pos + 1 << endl;
            exit(1);
        }
    }
}

void SyntaxAnalizer::parseFunctionBody() // TODO 3_6 12:30
{
    Token cur = tokens[pos];
    //? type identifier ( Param... ) ;  // 没有函数体的函数声明
    if (cur.type == TokenType::DELIMITER && cur.value == ";")
    {
        pos++; // 消耗掉分号
        return;
    }

    if (!(cur.type == TokenType::DELIMITER && cur.value == "{"))
    {
        cout << "expected \';\' in function declaration at " << pos + 1 << endl;
        exit(1);
    }
    pos++; //  消耗 左花括号
    if (!Helper::checkPosition(PARSER_ARGS, length))
    {
        cout << "expected statement or \'}\' in function declaration at " << pos + 1 << endl;
        exit(1);
    }

    while (!(cur.type == TokenType::DELIMITER && cur.value == "}"))
    {
        parseStatement();
    }
    pos++; // 消耗 右花括号
}

void SyntaxAnalizer::parseExpressionStatement() {
    
}
