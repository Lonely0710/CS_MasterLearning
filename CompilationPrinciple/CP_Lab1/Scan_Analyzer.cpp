#include "Token.h"

void print(TokenCode codes, ofstream &outputFile)
{
    // 将词法分析结果写入输出文件
    switch (codes)
    {
        case TK_UNDEF:
            outputFile << '(' << codes << ',' << token << ")" << "未识别的符号在第" << row << "行。" << endl;
            return;

        case KW_VOID:
        case KW_MAIN:
        case KW_INT:
        case KW_DOUBLE:
        case KW_FOR:
        case KW_WHILE:
        case KW_SWITCH:
        case KW_CASE:
        case KW_IF:
        case KW_ELSE:
        case KW_RETURN:
            outputFile << '(' << codes << ',' << token << ")" << endl;
            break;

        case TK_PLUS:
        case TK_MINUS:
        case TK_STAR:
        case TK_DIVIDE:
        case TK_ASSIGN:
        case TK_EQ:
        case TK_LT:
        case TK_LEQ:
        case TK_GT:
        case TK_GEQ:
        case TK_OPENPA:
        case TK_CLOSEPA:
        case TK_OPENBR:
        case TK_CLOSEBR:
        case TK_BEGIN:
        case TK_END:
        case TK_COMMA:
        case TK_SEMOCOLOM:
            outputFile << '(' << codes << ',' << token << ")" << endl;
            break;

        case TK_INT:
        case TK_DOUBLE:
            if (token.find('.') == string::npos)
                outputFile << '(' << codes << ',' << atoi(token.c_str()) << ")" << endl; // 整型
            else
                outputFile << '(' << codes << ',' << atof(token.c_str()) << ")" << endl; // 浮点型
            return;

        case TK_IDENT:
            outputFile << '(' << codes << ',' << token << ")" << endl;
            break;

        default:
            break;
    }
}

bool isKey(const string &tokens)
{
    for (int i = 0; i < MAX; i++)
    {
        if (tokens.compare(keyWord[i]) == 0)
            return true;
    }
    return false;
}

int getKeyID(const string &tokens)
{
    for (int i = 0; i < MAX; i++)
    {
        if (tokens.compare(keyWord[i]) == 0)
            return i + 1;
    }
    return -1;
}

bool isLetter(char letter)
{
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}

bool isDigit(char digit)
{
    return (digit >= '0' && digit <= '9');
}

void lexicalAnalysis(ifstream &file, ofstream &outputFile)
{
    char ch;
    while (file.get(ch)) // 从文件流中获取一个字符
    {
        token = ch;
        if (ch == ' ' || ch == '\t' || ch == '\n')
        {
            if (ch == '\n')
                row++; // 遇到换行符，行数加1
            continue;
        }
        else if (isLetter(ch)) // 以字母开头，关键字或标识符
        {
            token.clear();
            while (isLetter(ch) || isDigit(ch)) // 非字母或数字时退出，将单词存储在token中
            {
                token.push_back(ch);
                if (!file.get(ch))
                    break;
            }
            file.unget();     // 文件指针后退一个字节
            if (isKey(token)) // 判断是否为关键字
                code = TokenCode(getKeyID(token));
            else
                code = TK_IDENT;
        }
        else if (isDigit(ch)) // 无符号常数以数字开头
        {
            token.clear();
            bool isDouble = false;
            while (isDigit(ch) || (ch == '.' && !isDouble)) // 处理浮点数
            {
                if (ch == '.')
                    isDouble = true;
                token.push_back(ch);
                if (!file.get(ch))
                    break;
            }
            file.unget(); // 文件指针后退一个字节
            if (isDouble)
                code = TK_DOUBLE;
            else
                code = TK_INT;
        }
        else // 处理运算符和分隔符
        {
            switch (ch)
            {
                case '+':
                    code = TK_PLUS;
                    break;
                case '-':
                    code = TK_MINUS;
                    break;
                case '*':
                    code = TK_STAR;
                    break;
                case '/':
                    code = TK_DIVIDE;
                    break;
                case '=':
                    if (file.get(ch) && ch == '=')
                        code = TK_EQ;
                    else
                    {
                        code = TK_ASSIGN;
                        file.unget();
                    }
                    break;
                case '<':
                    if (file.get(ch) && ch == '=')
                        code = TK_LEQ;
                    else
                    {
                        code = TK_LT;
                        file.unget();
                    }
                    break;
                case '>':
                    if (file.get(ch) && ch == '=')
                        code = TK_GEQ;
                    else
                    {
                        code = TK_GT;
                        file.unget();
                    }
                    break;
                case '(':
                    code = TK_OPENPA;
                    break;
                case ')':
                    code = TK_CLOSEPA;
                    break;
                case '[':
                    code = TK_OPENBR;
                    break;
                case ']':
                    code = TK_CLOSEBR;
                    break;
                case '{':
                    code = TK_BEGIN;
                    break;
                case '}':
                    code = TK_END;
                    break;
                case ',':
                    code = TK_COMMA;
                    break;
                case ';':
                    code = TK_SEMOCOLOM;
                    break;
                default:
                    code = TK_UNDEF;
                    break;
            }
        }
        print(code, outputFile); // 将结果写入输出文件
    }
}

void processFile(const string &inputFilePath, const string &outputFilePath)
{
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);

    if (!inputFile.is_open())
    {
        cerr << "无法打开输入文件: " << inputFilePath << endl;
        return;
    }

    if (!outputFile.is_open())
    {
        cerr << "无法创建输出文件: " << outputFilePath << endl;
        inputFile.close();
        return;
    }

    // 输出到文件开头写一些信息
    outputFile << "词法分析结果：" << endl;
    outputFile << "处理文件：" << inputFilePath << endl;

    // 调用词法分析函数，传入输入文件流和输出文件流
    lexicalAnalysis(inputFile, outputFile);

    inputFile.close();
    outputFile.close();
}