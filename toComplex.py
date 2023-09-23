import zhconv
import sys
if len(sys.argv) > 1:
    outHtml="";
    with open("__temp.html" ,encoding="utf-8") as htmlFile:
        for line in htmlFile:
            #print(zhconv.convert(line, 'zh-tw'))
            line=zhconv.convert(line, 'zh-tw');
            outHtml+=line+"\n";
    file=open("__temp.html",'w',encoding="utf-8")
    file.write(outHtml)
else:
    print("未提供命令行参数")