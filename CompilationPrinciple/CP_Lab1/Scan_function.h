//
// Created by 杨龙澧 on 24-10-19.
//

#ifndef SCAN_FUNCTION_H
#define SCAN_FUNCTION_H

#include "Token.h"

using namespace std;

void print(TokenCode codes, ofstream &outputFile);

bool isKey(const string &token);

int getKeyID(const string &token);

bool isLetter(char letter);

bool isDigit(char digit);

void lexicalAnalysis(ifstream &file, ofstream &outputFile);

void processFile(const string &inputFilePath, const string &outputFilePath);

#endif //SCAN_FUNCTION_H
