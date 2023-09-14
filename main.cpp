#include <iostream>
#include <Logger.h>
#include "windows.h"
#include "unzip.h"
SNSTART("EPUB")
const static std::string makeItVertical="   \twriting-mode: vertical-rl;\n"
                                        "\t-webkit-writing-mode: vertical-rl;\n"
                                        "\t-webkit-writing-mode: vertical-rl;";

int main() {
    system("chcp 65001");
    ldebug(makeItVertical);
    HZIP hz = OpenZip("test.epub",0);
    ZIPENTRY ze;
    GetZipItem(hz,-1,&ze);
    int numitems=ze.index;

    for (int i=0; i<numitems; i++)
    {
        GetZipItem(hz,i,&ze);
        UnzipItem(hz,i,ze.name);
        linfo(ze.name);
        //move file to the direction
        std::string  command="xcopy /X /Y \"";
        command+=ze.name;
        command+="\" \"temp/";
        command+=ze.name;
        command+="\"";
        linfo(command);
        system(command.c_str());//can'run beacuse of the assecc problem
    }
    CloseZip(hz);
    linfo("end");
    return 0;
}
