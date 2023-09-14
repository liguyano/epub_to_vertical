from pypinyin import pinyin
import pyperclip
codetype='utf-8'

#Shift_JIS ,GBK23001 , BIG5，utf-8

if __name__ == '__main__':
    a="xml文件加载失败".encode(encoding=codetype)
    print(str(a)[2:-1])
    pyperclip.copy("\""+str(a)[2:-1]+"\"")
    b=a.decode(encoding=codetype)
   # print(type(a))
   # print(hex(a[0]))
    print("char b[]={",end='')
    for byte in a:
        print(hex(byte),end=",")
    print("0x00};//",end="")
    for p in pinyin(b):
        print(str(p).replace("[","").replace("]","").replace("'",""),end=' ')
   # print(a)
   # print(b)