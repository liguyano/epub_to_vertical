//
// Created by kurum on 2023/7/7.
//


#include <fstream>
#include "MyFile.h"
namespace fs = std::filesystem;
bool copyFile(const char* sourceFile, const char* destinationFile) {
    std::ifstream source(sourceFile, std::ios::binary);
    if (!source.is_open()) {
        throw  "Failed to open the source file";
        return false;
    }

    std::ofstream destination(destinationFile, std::ios::binary);
    if (!destination.is_open()) {
       throw "Failed to create or open the destination file" ;
        source.close();
        return false;
    }

    destination << source.rdbuf();

    source.close();
    destination.close();

  //  std::cout << "File copied successfully from " << sourceFile << " to " << destinationFile << std::endl;
    return true;
}

std::vector<std::string> ListFiles(const std::string& path)
{
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            files.push_back(entry.path().string());
        }
    }

    return files;
}
std::vector<std::string> GetFilesInFolder(std::string folderPath,  std::string prefix )
{
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            std::string filePath = prefix + entry.path().filename().string();
            files.push_back(filePath);
        }
        else if (entry.is_directory())
        {
            std::string subFolderPath = entry.path().string();
            std::string subFolderPrefix = prefix + entry.path().filename().string() + "/";
            std::vector<std::string> subFiles = GetFilesInFolder(subFolderPath, subFolderPrefix);
            files.insert(files.end(), subFiles.begin(), subFiles.end());
        }
    }

    return files;
}
bool OpenFileSelectionDialog(std::string& selectedFilePath) {
    OPENFILENAME ofn;
    char szFile[260] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "BooK Files\0*.epub\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        selectedFilePath = ofn.lpstrFile;
        return true;
    } else {
        return false;
    }
}
bool createFolderIfNotExists(const std::string& folderPath) {
    if (folderExists(folderPath)) {
        //std::cout << "Folder already exists: " << folderPath << std::endl;
        return true;
    }

    if (fs::create_directory(folderPath)) {
        std::cout << "Successfully created folder: " << folderPath << std::endl;
        return true;
    } else {
        std::cerr << "Failed to create folder: " << folderPath << std::endl;
        return false;
    }
}
bool folderExists(const std::string& folderPath) {
    return fs::exists(folderPath) && fs::is_directory(folderPath);
}
bool deleteFolder(const std::string& folderPath) {
        fs::remove_all(folderPath); // 使用 remove_all 函数删除文件夹及其内容
       // std::cout << "Successfully deleted folder: " << folderPath << std::endl;
        return true;
}