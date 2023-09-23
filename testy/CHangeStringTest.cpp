//
// Created by kurum on 2023/9/23.
//
#include <MYString.h>
#include <Logger.h>
#include <iostream>
#include <cstdarg>
SNSTART("stringTest")
int main()
{
    system("chcp 65001");
    std::string a="hello";
    lerror("%s",a.c_str());
    auto x=1;
    info_f("\xe6\x95\xb0\xe5\xad\x97\xe3\x81\xaf:\xe3\x80\x8c""%d,%d,%s""\xe3\x80\x8d",5,6,"\xe6\x84\x9b\xe3\x81\x97\xe3\x81\xa6\xe3\x82\x8b");
    auto num= printf_s("hello%d\n" ,1);
    info_f("num:%d",num);
    ldebug("debuf:%d",12);
    printf("2:%d,",printf("1:%d,",scanf_s("%d",&x)));
    lnprint("");
    auto s=String::replaceAllOccurrences("I want to eat""\xe3\x80\x9d","\xe2\x80\x9d","\xe3\x80\x8d");
    linfo(s);
    return 0;
}
