#include "../inc/lexcial.hpp"
using namespace std;

void LexcialAnalizer::tokenize()
{
    smatch isMatch;
    const size_t length = source.length();

    while (position < length)
    {
        string remaining = source.substr(position);

        // 跳过预处理指令
        if (remaining[0] == '#')
        {
            while (position < length && source[position] != '\n' && source[position] != '\0')
                position++;
            position++;
            continue;
        }

        // 跳过空白符
        if (regex_search(remaining, isMatch, WhiteSpaceRegex))
        {
            position += isMatch.str(0).length();
            continue;
        }

        // 跳过注释
        if (source[position] == '/')
        {
            if (source[position + 1] == '/')
            {
                while (source[position] != '\n' && position < length)
                    position++;
                position++;
                continue;
            }
            else if (position + 1 < length && source[++position] == '*')
            {
                position++;
                while (position + 1 < length && (source[position] != '*' && source[position + 1] != '/'))
                    position++;
                position++;
                continue;
            }
        }

        // 处理关键字和标识符
        if (remaining[0] == '_' || isalpha(remaining[0])) // 标识符的开始字符必须是字母或下划线
        {
            // 逐个字符检查是否为标识符
            size_t endPosition = position;
            while (endPosition < length && (isalnum(source[endPosition]) || source[endPosition] == '_'))
                endPosition++;

            string word = source.substr(position, endPosition - position);

            if (isKeyword(word))
                addToken(TokenType::KEYWORD, word);
            else
                addToken(TokenType::IDENTIFIER, word);

            position = endPosition;
            continue;
        }

        // 处理整数字面量
        if (regex_search(remaining, isMatch, IntegerRegex))
        {
            string integer = isMatch.str(0);
            addToken(TokenType::INTEGER, integer);
            position += integer.length();
            continue;
        }

        // 处理浮点数字面量
        if (regex_search(remaining, isMatch, FloatingRegex))
        {
            string floating = isMatch.str(0);
            addToken(TokenType::FLOATING, floating);
            position += floating.length();
            continue;
        }

        // 处理字符串字面量
        if (remaining[0] == '\"')
        {
            size_t cnt = 1;        // 从第二个字符开始遍历，因为第一个是双引号
            string literal = "\""; // 字符串字面量以双引号开始

            // 遍历字符串字面量中的字符，直到找到结束的双引号
            while (position + cnt < length && remaining[cnt] != '\"')
            {
                // 处理转义字符
                if (remaining[cnt] == '\\' && cnt + 1 < remaining.length())
                {
                    char escapeChar = remaining[cnt + 1];
                    if (escapeChar == '\"' || escapeChar == '\\' || escapeChar == 'n' || escapeChar == 't')
                    {
                        literal += '\\';       // 加上反斜杠
                        literal += escapeChar; // 加上转义字符
                        cnt += 2;              // 跳过转义字符
                        continue;
                    }
                }
                literal += remaining[cnt]; // 正常字符
                cnt++;
            }

            // 跳过双引号，确保完整提取字符串字面量
            if (remaining[cnt] == '\"')
            {
                literal += '\"';
                position += cnt + 1; // 更新位置，跳过结束的双引号
            }

            // 添加字符串字面量token
            addToken(TokenType::STRING_LITERAL, literal);
            continue;
        }

        // 处理运算符和分隔符
        bool tokenFound = false;
        // 优先匹配双字符运算符（如 ::, ++, +=）
        if (position + 1 < length)
        {
            string twoChar = source.substr(position, 2);
            if (isOperator(twoChar))
            {
                addToken(TokenType::OPERATOR, twoChar);
                position += 2;
                tokenFound = true;
            }
        }

        // 若未匹配双字符，尝试单字符运算符或分隔符
        if (!tokenFound)
        {
            char currentChar = source[position];
            // 检查是否为分隔符（如 ;, {, }）
            if (isDelimiterRegex(currentChar))
            {
                addToken(TokenType::DELIMITER, string(1, currentChar));
                position++;
                tokenFound = true;
                continue;
            }
            // 检查是否为单字符运算符（如 +, -, *）
            else if (isOperator(string(1, currentChar)))
            {
                addToken(TokenType::OPERATOR, string(1, currentChar));
                position++;
                tokenFound = true;
                continue;
            }
        }

        // 若仍未匹配，归纳为未知词素
        addToken(TokenType::UNKNOWN, string(1, source[position]));
        position++;
    }
    // 添加结束标记
    addToken(TokenType::END, "");
}

void LexcialAnalizer::printTokens() const
{
    for (const auto &token : tokens)
        cout << format("< {}, {} >\n", getTokenName(token.type), token.value);
    cout << endl;
}

void LexcialAnalizer::printTokensToFile(const string &fileName) const
{
    ofstream outFile(fileName);
    if (!outFile)
    {
        std::cerr << "Error: Unable to open file for writing: " << fileName << std::endl;
        return;
    }

    for (const auto &token : tokens)
        outFile << "< " << getTokenName(token.type) << ", " << token.value << " >\n";

    outFile.close();
    cout << "Tokens saved to " << fileName << format("\nThere are {} tokens", tokens.size()) << endl;
}

string LexcialAnalizer::getTokenName(TokenType type) const
{
    switch (type)
    {
    case TokenType::UNKNOWN:
        return "UNKNOWN";
    case TokenType::KEYWORD:
        return "KEYWORD";
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::FLOATING:
        return "FLOATING";
    case TokenType::OPERATOR:
        return "OPERATOR";
    case TokenType::INTEGER:
        return "INTEGER";
    case TokenType::TYPE_KEYWORD:
        return "TYPE_KEYWORD";
    case TokenType::DELIMITER:
        return "DELIMITER";
    case TokenType::STRING_LITERAL:
        return "STRING_LITERAL";
    case TokenType::CHARACTER:
        return "CHARACTER";
    case TokenType::END:
        return "END";
    default:
        return "ERROR";
    }
}
