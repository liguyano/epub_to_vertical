//
// Created by kurum on 2023/12/1.
//
#include <Logger.h>
#include <encoding.h>
SNSTART("Tocomplex")
#include<ToComplex.h>
using namespace std;
using namespace ComplexChinese;

int main()
{
    system("chcp 65001");
    auto allCOmplex=loadDate("./comGbk.txt");
    //linfo(Encoding::Utf8ToGbk("About 特征的未来《》"));
    auto s=toComplex(allCOmplex,Encoding::Utf8ToGbk("·"));
    linfo("%s",s.c_str());
    //system("chcp 65001");

    printf_s("%c%c%c",allCOmplex[32][351],allCOmplex[32][352],allCOmplex[32][353]);
    linfo("%d",allCOmplex[32][351]);
    printf_s("\xe3\x80\x8a\xe3\x80\x8c《%d\n",0xff-0x40);
    return 0;

}
