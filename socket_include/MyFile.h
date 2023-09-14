//
// Created by kurum on 2023/7/7.
//

#ifndef WBUILDER_MYFILE_H
#define WBUILDER_MYFILE_H
#include <filesystem>
#include <iostream>
#include <windows.h>
std::vector<std::string> ListFiles(const std::string& path);
std::vector<std::string> GetFilesInFolder(std::string folderPath, std::string prefix = "");
bool OpenFileSelectionDialog(std::string& selectedFilePath);
bool createFolderIfNotExists(const std::string& folderPath);
bool folderExists(const std::string& folderPath);
bool copyFile(const char* sourceFile, const char* destinationFile);
bool deleteFolder(const std::string& folderPath);
#endif //WBUILDER_MYFILE_H
