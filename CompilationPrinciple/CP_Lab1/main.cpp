//
// Created by 杨龙澧 on 24-10-19.
//
#include "Scan_function.h"

TokenCode code = TK_UNDEF;
int row = 1;
string token;
string keyWord[MAX] = {"void", "main", "int", "double", "for", "while", "switch", "case", "if", "else", "return"}; // 存储关键词

int main()
{
    string inputDir = "../input";   // 输入文件夹路径
    string outputDir = "../output"; // 输出文件夹路径

    try {
        // 创建输出文件夹，如果不存在的话
        if (!fs::exists(outputDir)) {
            fs::create_directory(outputDir);
        }

        // 遍历 ../input 文件夹中的所有文件
        for (const auto &entry : fs::directory_iterator(inputDir)) {
            // 获取输入文件路径
            string inputFilePath = entry.path().string();

            // 提取文件名，并生成对应的输出文件路径
            string fileName = entry.path().filename().string();
            string outputFilePath = outputDir + "/output_" + fileName;

            cout << "处理文件: " << fileName << endl;

            // 处理文件：词法分析并将结果写入输出文件
            processFile(inputFilePath, outputFilePath);
        }

        cout << "所有文件处理完成。" << endl;
    } catch (const fs::filesystem_error& e) {
        cerr << "文件系统错误: " << e.what() << endl;
        return 1;
    }

    return 0;
}