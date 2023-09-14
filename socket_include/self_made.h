//
// Created by kurum on 12/31/2022.
//

#ifndef WIFI_AUTO_ANS_SELF_MADE_H
#define WIFI_AUTO_ANS_SELF_MADE_H
#define RESET  "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"
#define pr std::cout<<
#define END <<std::endl;
#define AN <<
#define lnprint(A) std::cout<<A<<std::endl;
#define redPrint(A) std::cout<<RED<<A<<RESET;
#define bluePrint(A) std::cout<<BLUE<<A<<RESET;
#define yellowPrint(A) std::cout<<YELLOW<<A<<RESET;
#define greenPrint(A) std::cout<<GREEN<<A<<RESET;
#define colorprint(Color,Str) std::cout<<Color<<Str<<RESET;
#define stringVe std::vector<std::string>
#endif //WIFI_AUTO_ANS_SELF_MADE_H
#define C_STR(A) A.toStdString().c_str()
