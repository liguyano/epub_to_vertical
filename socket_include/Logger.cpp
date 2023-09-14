//
// Created by kurum on 2023/8/2.
//
#include "Logger.h"
Logger::~Logger()
{
#ifdef FILESAVEON
    if (logFile.is_open())
        logFile.close();
#endif
}
std::string Logger::getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    // Convert the time_t value to a string representation
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
    return timeStr;
}

void Logger::debug(std::string mess,int line) {

#ifdef __MINGW32__
    #ifdef NDEBUG
    #else
    #ifdef STDOUTON
    bluePrint(getTime()) ;
    pr "  [";
    pr name;
    pr '-' AN line;
    pr '-';
    pr "debug";
    pr "]  ";
    pr mess;
    lnprint("");
    #endif
    #ifdef FILESAVEON
    logFile<<getTime()<< "  ["<<name<<'-' AN line<< '-' AN "debug"<<"]  "<<mess END;
                                           #else
                                           #endif
#endif
#else
#ifdef _DEBUG
    #ifdef STDOUTON
    bluePrint(getTime()) ;
    pr "  [";
    pr name;
    pr '-' AN line;
    pr '-';
    pr "debug";
    pr "]  ";
    pr mess;
    lnprint("");
    #endif
    #ifdef FILESAVEON
    logFile<<getTime()<< "  ["<<name<<'-' AN line<< '-' AN "debug"<<"]  "<<mess END;
                                           #else
                                           #endif
#endif
#endif

}

Logger::Logger(std::string nam,std::string proName) :name(nam){
#ifdef FILESAVEON
    proName+=".log";
    if (std::filesystem::exists(proName))
    {
       logFile.open(proName,std::ios::app);
    }else
    {
        logFile.open(proName,std::ios::out);
    }
#else
#endif
}

void Logger::info(std::string mess,int line,std::string endc) {
#ifdef STDOUTON
    ;
    bluePrint(getTime()) ;
    pr "  [";
    pr name;
    pr '-' AN line;
    pr '-' AN "info";
    pr "]  ";
    pr mess;
    pr endc;
#endif
#ifdef FILESAVEON
    logFile<<getTime()<< "  ["<<name<<'-' AN line<< '-' AN "info"<<"]  "<<mess <<endc;
#else
#endif
}

void Logger::error(std::string mess,int line) {
#ifdef STDOUTON
    bluePrint(getTime()) ;
    pr "  [";
    pr name;
    pr '-' AN line;
    pr '-' AN "error";
    pr "]  ";
    redPrint(mess) ;
    lnprint("\n");
#endif
#ifdef FILESAVEON
    logFile<<getTime()<< "  ["<<name<<'-' AN line<< '-' AN "error"<<"]  "<<mess END;
#else
#endif
}

std::string Logger::GetContentAfterLastSlash(const std::string &path) {
        size_t lastSlashPos = path.find_last_of('\\');
        if (lastSlashPos != std::string::npos && lastSlashPos + 1 < path.length()) {
            return path.substr(lastSlashPos + 1);
        }
        lastSlashPos = path.find_last_of('/');
        if (lastSlashPos != std::string::npos && lastSlashPos + 1 < path.length()) {
            return path.substr(lastSlashPos + 1);
        }
        return path;
}
