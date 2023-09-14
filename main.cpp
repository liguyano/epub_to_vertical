#include <iostream>
#include <Logger.h>
#include "windows.h"
#include "unzip.h"
#include "zip.h"
#include <cstdio>
#include "MYString.h"
#include <self_made.h>
#include <encoding.h>
#include <MyFile.h>
#include <fstream>
#include <exception>
#include "tinyxml/tinyxml.h"
SNSTART("EPUB")
using namespace String;
const static std::string makeItVertical="   \twriting-mode: vertical-rl;\n"
                                        "\t-webkit-writing-mode: vertical-rl;\n"
                                        "\t-webkit-writing-mode: vertical-rl;";

const static std::string rtolString="page-progression-direction=\"rtl\"";
static std::string filePath="";
//unzip in the dir now , then copy it to the direction
int unzipFile(std::string fileName,std::string outPutPath="temp")
{
    try {
        stringVe needDeleteDir;
        HZIP hz = OpenZip(fileName.c_str(), 0);
        ZIPENTRY ze;
        GetZipItem(hz, -1, &ze);
        int numitems = ze.index;
        ldebug(std::to_string(numitems));
        createFolderIfNotExists(outPutPath);
        for (int i = 0; i < numitems; i++) {
            GetZipItem(hz, i, &ze);
            UnzipItem(hz, i, ze.name);
            //linfo(ze.name);
            ldebug(std::string ("copying  ") +filePath+ze.name);
            //move file to the direction
            auto filePaths = String::split(ze.name, "/");
            std::string FIleName(ze.name);
            auto f=FIleName.find('/');
            //linfo(filePaths[0]);
            if (f !=std::string ::npos )//means that we need create dircetion
            {
                ldebug("create");
                //create the folder
                std::string pathNow = "";
                if (filePaths.size()==1)
                {
                    createFolderIfNotExists(filePath+outPutPath+"/"+filePaths[0]);
                }
                for (int j = 0; j < filePaths.size() - 1; ++j) {
                    pathNow +=  filePaths[j]+"/";
                    needDeleteDir.push_back(filePath+pathNow);
                    //linfo(pathNow);
                    ldebug("create " + pathNow);
                    createFolderIfNotExists(filePath+outPutPath +"/"+ pathNow);
                }

            }
            if (filePaths.size()==1 && (FIleName[FIleName.size()-1]=='/'))
            {
                continue;
            }
            ldebug(filePath+outPutPath + "/" + ze.name);
            copyFile((filePath+ze.name).c_str(), (filePath+outPutPath + "/" + ze.name).c_str());
            remove((filePath+ze.name).c_str());
        }
        //delete the not temp folder
        for (auto s: needDeleteDir) {
            ldebug("delete "+s);
            deleteFolder(s);
        }
        needDeleteDir.clear();

        CloseZip(hz);
        return 1;
    }
    catch (const std::exception& e) {
        lerror(e.what());
        return 0;
    }
}
int changCofFile()
{
    auto cofFile =new TiXmlDocument;
    cofFile->LoadFile((filePath+"/temp/content.opf").c_str(),TIXML_ENCODING_UTF8);
    if (cofFile->Error())
    {
        lerror(cofFile->ErrorDesc());
        return -1;
    }
    auto Package=cofFile->FirstChildElement();
    ldebug(Package->Value());
    TiXmlElement* spine= dynamic_cast<TiXmlElement *>(Package->FirstChild("spine"));
    ldebug(spine->Value());
    spine->SetAttribute("page-progression-direction","rtl");
    cofFile->SaveFile();
    cofFile->Clear();
}
std::vector<std::string> removeDuplicates(const std::vector<std::string>& inputVec) {
    std::vector<std::string> resultVec = inputVec;
    std::sort(resultVec.begin(), resultVec.end());
    auto it = std::unique(resultVec.begin(), resultVec.end());
    resultVec.erase(it, resultVec.end());
    return resultVec;
}
stringVe getAllClasses()
{stringVe allClasses;
    auto fs= GetFilesInFolder(filePath+"temp/");
    for (auto s:fs) {
        auto pres=String::split(s,".");
        if (pres[pres.size()-1]=="html")
        {
            ldebug(s);
            auto htmlFile=new TiXmlDocument;
            htmlFile->LoadFile((filePath+"temp/"+s).c_str(),TIXML_ENCODING_UTF8);
            if (htmlFile->Error())
            {
                lerror(htmlFile->ErrorDesc());
                throw "erro";
            }
            auto html=htmlFile->FirstChildElement();
            ldebug(html->Value());
            auto body=html->FirstChildElement("body");
            ldebug(body->Value());
            auto _class=body->Attribute("class");
            allClasses.push_back(String::split(_class," ")[0]);
        }

    }
    allClasses= removeDuplicates(allClasses);
    for (auto s: allClasses) {
        ldebug(s);

    }
    return allClasses;
}

template <typename T>
bool containsElement(const std::vector<T>& vec, const T& target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    return it != vec.end();
}
void changeHtmlFile()
{
    auto allClass=getAllClasses();
    auto tempv= GetFilesInFolder("temp/","temp/");
    stringVe allcss;
    //filter if the file is css File.
    for (auto s:tempv) {
        auto sv=String::split(s,".");
        if (sv[sv.size()-1]=="css")
        {
            allcss.push_back(s);
        }
    }
    for (auto s:allcss) {
        ldebug(s);
        std::ifstream cssFile;
        cssFile.open(s, std::ios::in);
        std::string outString;
        std::string temp = "1";
        bool isClass= false;
        do  {
            temp="";
            cssFile>>temp;
            outString+=temp+" ";
            if (temp[0]=='}')
            {
                outString+='\n';
            }
            if (temp[0]=='.')
            {
                auto className=temp.substr(1,temp.size());
                ldebug(temp);
                if (containsElement(allClass,className))
                {
                    ldebug("need add;");
                    isClass= true;
                }
            }
            if (isClass) {
                if (temp[0] == '{')
                {
                    isClass= false;
                    outString+="\n"+makeItVertical;
                    ldebug("added");
                }
            }
        }while (! cssFile.eof());//while
        ldebug(outString);
        std::ofstream outcss;
        outcss.open("_temp.css",std::ios::out);
        outcss<<outString;
        outcss.close();
        copyFile("_temp.css",s.c_str());
        remove("_temp.css");
    }
}
void saveEpubFile(std::string outFIleName)
{
    HZIP epub=CreateZip("temp.zip",0);
    auto allFile=GetFilesInFolder(filePath+"temp/");
    for (auto s: allFile)
    {ldebug(s);
        ZipAdd(epub,s.c_str(),(filePath+"temp/"+s).c_str());
    }
    CloseZip(epub);
    deleteFolder("temp");
    copyFile("temp.zip",outFIleName.c_str());
    remove("temp.zip");
}

int main() {
    try {
       // system("chcp 65001");
        //system("\"D:\\Program` Files\\Calibre2\\ebook-convert.exe\" ");

        std::string filePaths;
        OpenFileSelectionDialog(filePaths);
        filePaths=Encoding::GbkToUtf8(filePaths.c_str());
        auto wh=getExtensionAfterLastDot(filePaths);
        if (wh=="azw3"|| wh=="mobi")
        {auto str=getExtensionBeforLastDot(filePaths);
            linfo(str);
            system(("\'D:\\Program Files\\Calibre2\\ebook-convert.exe\' "+filePaths+"\" \""+str+".epub\"").c_str());
            linfo(("\"D:\\Program Files\\Calibre2\\ebook-convert.exe\" "+filePaths+"\" \""+str+".epub\"").c_str())
            filePaths=str+".epub";
        }
        if (filePaths.size()<1)
        {
            throw "no file selected";
        }
        linfo("open "+filePaths);
        auto sv=String::split(filePaths,"\\");
        filePaths="";
        std::string fileName;
        if (sv.size()>1)
        {
            for (int i = 0; i < sv.size()-1; ++i) {
                auto s=sv[i];
                filePaths+=s+"/";

            } fileName=sv[sv.size()-1];
        }else
        {
            sv=String::split(filePaths,"/");
            for (int i = 0; i < sv.size()-1; ++i) {
                auto s=sv[i];
                filePaths+=s+"/";
            }
            fileName=sv[sv.size()-1];
        }
        linfo(filePaths);
        ldebug(makeItVertical);
        linfo("unzip "+filePaths+fileName);
        filePath=filePaths;
        unzipFile(filePaths+fileName);
        linfo("change the spine");
        changCofFile();
        linfo("add rtl succed");
        linfo("chang html FIle");
        changeHtmlFile();
        linfo("merge to a new epub file");
        saveEpubFile(filePath+"vertical_"+fileName);
        linfo("end");
    }   catch (const std::exception& e) {
        lerror(e.what());
        MessageBox(NULL, e.what(), "ERROR", MB_OK | MB_ICONINFORMATION);
        return -1;
    }
   
    return 0;
}
