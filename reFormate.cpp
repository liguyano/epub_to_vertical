//
// Created by kurum on 2023/11/30.
//
#include <Logger.h>
SNSTART("reformat")
void convert(std::string fileName,std::string tobe)
{
    system(("\"D:\\Program Files\\Calibre2\\ebook-convert.exe\" "+fileName+" "+tobe).c_str());
}

int main()
{
    linfo("hello");
    system("\"D:\\Program Files\\Calibre2\\ebook-convert.exe\" a.epub a.azw3");
    return 0;
}