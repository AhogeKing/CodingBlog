#include "../inc/head.hpp"
#include "../inc/lexcial.hpp"
#include "../inc/syntax.hpp"
using namespace std;

fstream sourceRearder::file;

int main()
{
    // sourceRearder::initReader("../test/test1.cpp");
    sourceRearder::initReader("../test/test.cpp");
    string source = sourceRearder::getAllLine();
    // cout << format("{}\n", source) << endl;2
    sourceRearder::closeReader();

    LexcialAnalizer lex(source);
    lex.tokenize();
    lex.printTokens();
    // lex.printTokensToFile("../out/test1_tokens.txt");

    SyntaxAnalizer syn(lex.getTokens());
    syn.parseProgram();
}