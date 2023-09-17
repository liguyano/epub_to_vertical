#include <Windows.h>
#include <Logger.h>
#include <MyFile.h>
SNSTART("form_epub")
#include <iostream>
#include "unzip.h"
#include "zip.h"
#include <cstdio>
#include "MYString.h"
#include <self_made.h>
#include <fstream>
#include <exception>
#include "tinyxml/tinyxml.h"
#include <MyVectors.h>
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
        outcss.open("_temp.css",std::ios::out);auto a="\xe3\x80\x8d";
     /*   outString=replaceAllOccurrences(outString,std::string("“"),std::string("\xe3\x80\x8c"));
        outString=replaceAllOccurrences(outString,"”","\xa1\xb9");*/
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
void StartCOnvert(std::string fileName,int repalceThchar,int replaceTheComplex)
{
    linfo("open "+fileName);
    filePath=getExtensionBeforLastDot(fileName,'\\')+"\\";
    fileName=getExtensionAfterLastDot(fileName,'\\');
    unzipFile(filePath+fileName);
    linfo("change the spine");
    changCofFile();
    linfo("add rtl succed");
    linfo("chang html FIle");
    changeHtmlFile();
    linfo("merge to a new epub file");
    saveEpubFile(filePath+"vertical_"+fileName);
    linfo("end");
}
HWND hwndCheckbox1, hwndCheckbox2, hwndCheckbox3, hwndButton,hwndInput,hwndButton2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // 创建输入框
            hwndInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 10, 150, 30, hwnd, NULL, NULL, NULL);

            // 创建按钮
            hwndButton2 = CreateWindow("BUTTON", "...", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 170, 10, 80, 30, hwnd, (HMENU)1, NULL, NULL);

            // 创建三个复选框和一个按钮
            hwndCheckbox1 = CreateWindow("BUTTON", "\xcc\xe6\xbb\xbb\xb1\xea\xb5\xe3\xb7\xfb\xba\xc5", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 40, 150, 30, hwnd, NULL, NULL, NULL);
            hwndCheckbox2 = CreateWindow("BUTTON", "\xcc\xe6\xbb\xbb\xbc\xf2\xb7\xb1\xcc\xe5", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 80, 150, 30, hwnd, NULL, NULL, NULL);
            hwndCheckbox3 = CreateWindow("BUTTON", "Checkbox 3", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 120, 150, 30, hwnd, NULL, NULL, NULL);
            hwndButton = CreateWindow("BUTTON", "\xbf\xaa\xca\xbc\xd7\xaa\xbb\xbb", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 160, 150, 30, hwnd, (HMENU)2, NULL, NULL);

            break;
        }
        case WM_COMMAND: {
            // 处理按钮点击事件
            if (LOWORD(wParam) == (WORD)hwndButton) {
                MessageBox(hwnd, "Button clicked!", "Message", MB_OK | MB_ICONINFORMATION);
            }
            if (HIWORD(wParam) == BN_CLICKED)
            {

                if (HWND(wParam)==HWND(1))
                {
                    std::string path;
                    OpenFileSelectionDialog(path);
                    SetWindowText(hwndInput, "");
                    SetWindowText(hwndInput, path.c_str());
                    ninfo("which: ");std::cout<<HWND(wParam) END;
                }else  if (HWND(wParam)==HWND(2))
                {       int textLength = GetWindowTextLength(hwndInput);

                    char *buffer = (char *)malloc(textLength + 1);

                    GetWindowText(hwndInput, buffer, textLength + 1);
                    linfo(buffer);

                    free(buffer);
                    StartCOnvert(buffer,1,1);
                    ninfo("which: ");std::cout<<HWND(wParam) END;
                }
            }

                break;
        }
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main() {
    // 注册窗口类
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance =GetModuleHandle(NULL);
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    // 创建主窗口
    HWND hwnd = CreateWindow("MyWindowClass", "Window with Controls", WS_OVERLAPPEDWINDOW, 100, 100, 300, 250, NULL, NULL, GetModuleHandle(NULL), NULL);

    // 显示主窗口
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
