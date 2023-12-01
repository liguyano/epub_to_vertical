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
    auto allCOmplex=loadDate();
    auto s=toComplex(allCOmplex,Encoding::Utf8ToGbk("About 特征的未来"));
    linfo("%s",s.c_str());
    //system("chcp 65001");

    printf_s("%c%c%c",allCOmplex[77][483],allCOmplex[77][484],allCOmplex[77][485]);
    printf_s("%d\n",0xff-0x40);
    return 0;

}
