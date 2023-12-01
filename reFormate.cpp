//
// Created by kurum on 2023/11/30.
//
#include <Logger.h>
#include "Python.h"
#include <encoding.h>
SNSTART("pyTest")
void convert(std::string fileName,std::string tobe)
{
    system(("\"D:\\Program Files\\Calibre2\\ebook-convert.exe\" "+fileName+" "+tobe).c_str());
}

int main()
{
    std::ofstream allGbk;
    allGbk.open("./allGbk.txt",std::ios::out);
    unsigned high=0x81 ,low=0x40;
    //system("chcp 65001");b9ea//fd94
    while (high<=0xFE)
    {
        printf_s("%c%c: 0x%02x%02x\n",high,low,high,low);

        allGbk<<(char )high<<(char)low;
        low++;
        if (low==0x7f)low++;
        if (low>0xfe)
        {
            high++;
            low=0x40;
            allGbk<<'\n';
        }

    }
    allGbk.close();
    linfo("hello\x81\x59");
    linfo("忧郁的乌龟");
    Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('D:\\python\\Scripts')"); //定位到所要调用py文件的文件夹


    if (!Py_IsInitialized())
    {
        lerro("初始化失败！");
        return 0;
    }
    PyRun_SimpleString("print(\"hello word\")");
    PyRun_SimpleString("import zhconv\nprint(\"line1\")\nprint(\"line2\")"
                       "\na=zhconv.convert(\'忧郁的乌龟\', 'zh-tw')\n"
                       "print(a)");
    PyObject* pMoudle=PyImport_ImportModule("demo02"); //导入demo02.py模块，注意文件名字大小写
    linfo("import moudele succed");
    PyObject* pFunc3 = PyObject_GetAttrString(pMoudle, "fun3");//这里是要调用的函数名
    std::ifstream inGbk;
    std::ofstream complexGbk("comGbk.txt",std::ios::out);
    inGbk.open("allGbk.txt",std::ios::in);
    PyObject* pargs;
    PyObject* pRet;
    std::string tem="hello";
    while (!inGbk.eof())
    {
        char *b;
        int a,c;
        inGbk>>tem;
        pargs=Py_BuildValue("sii",Encoding::GbkToUtf8(tem.c_str()).c_str(), 25, 6);//给python函数参数赋值
         pRet = PyObject_CallObject(pFunc3, pargs);//调用函数
        if (PyErr_Occurred()) {
            PyErr_Print();
        }
       PyArg_ParseTuple(pRet,"sii",&b, &a, &c);
        if (PyErr_Occurred()) {
            PyErr_Print();
        }
        tem=b;
        complexGbk<<tem<<'\n';
    }char *b;
     pargs=Py_BuildValue("sii","忧郁的乌龟", 25, 6);//给python函数参数赋值
     pRet = PyObject_CallObject(pFunc3, pargs);//调用函数
    int a,d,c;
    linfo("ren succed");
    PyArg_ParseTuple(pRet,"sii",&b,&a,&d);
    linfo("parse succed");
    linfo("%s %d %d",Encoding::Utf8ToGbk(b).c_str(),a,d);
    Py_Finalize(); // 与初始化对应
    return 0;
}