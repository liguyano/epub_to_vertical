#include <iostream>
#include <Logger.h>
#include "windows.h"
#include "unzip.h"
#include <cstdio>
#include "MYString.h"
#include <self_made.h>
#include <MyFile.h>
SNSTART("EPUB")
const static std::string makeItVertical="   \twriting-mode: vertical-rl;\n"
                                        "\t-webkit-writing-mode: vertical-rl;\n"
                                        "\t-webkit-writing-mode: vertical-rl;";




int main() {
    stringVe needDeleteDir;
    system("chcp 65001");
    ldebug(makeItVertical);
    HZIP hz = OpenZip("test.epub",0);
    ZIPENTRY ze;
    GetZipItem(hz,-1,&ze);
    int numitems=ze.index;
    createFolderIfNotExists("./temp");
    for (int i=0; i<numitems; i++)
    {
        GetZipItem(hz,i,&ze);
        UnzipItem(hz,i,ze.name);
        //linfo(ze.name);
        ninfo("copying ");
        lnprint(ze.name);
        copyFile(ze.name,(std::string ("temp/")+ze.name).c_str());
        auto filePath=String::split(ze.name,"/");
        if (filePath.size()>1)//means that we need create dircetion
        {
            //create the folder
            std::string pathNow="temp";

            for (int j = 0; j < filePath.size()-1; ++j) {
                pathNow+="/"+filePath[j];
                needDeleteDir.push_back(pathNow);
                //linfo(pathNow);
                createFolderIfNotExists(pathNow);
            }

        }

    }
   /* for (auto s: needDeleteDir) {
        ninfo("be delete");pr s END;
        deleteFolder(s);
    }*/
    //move file to the direction
    remove(ze.name);
    CloseZip(hz);
    linfo("end");
    return 0;
}
