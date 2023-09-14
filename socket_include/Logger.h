//
// Created by kurum on 2023/7/31.
//
#pragma once
#ifndef OPENGL_DEMO_LOGGER_H
#define OPENGL_DEMO_LOGGER_H
#define STSTART static Logger logger(Logger::GetContentAfterLastSlash(__FILE__));
#define SNSTART(NAme )static Logger logger(Logger::GetContentAfterLastSlash(__FILE__),NAme);
#include <iostream>
#include <fstream>
#include <chrono>
#include "self_made.h"
#include <filesystem>
#include <ctime>
/*
 * configue
 * */
#define  FILESAVEON //this means if the log need to be save in a .log file. FILESAVEOFF means not FILESAVEON means yes
#define STDOUTON// if the log need output in the console. Same as the FILESAVEON
//end configue
#define PROJECTNAME  "include_test"

#define linfo(mess) logger.info(mess,__LINE__);
#define ninfo(mess) logger.info(mess,__LINE__,"");

#define lerror(mess) logger.error(mess,__LINE__)
#define lerro(mess) logger.error(mess,__LINE__)
#ifdef __MINGW32__
#ifdef NDEBUG
#define ldebug(mess)
#else
#define ldebug(mess) logger.debug(mess,__LINE__)
#endif
#else
#ifdef _DEBUG
#define ldebug(mess) logger.debug(mess,__LINE__)
#else
#define ldebug(mess)
#endif
#endif
class Logger {
private:
    std::string name;
#ifdef FILESAVEON
    std::fstream logFile;
#else
#endif
public:
    static std::string GetContentAfterLastSlash(const std::string& path);
    /**
     * @param proName this define where to save the log file, add .log in the end auto.
     * @param nam define the output part name
     * */
    explicit Logger(std::string nam ,std::string   proName=PROJECTNAME);
    void info(std::string mess,int line=__LINE__,std::string endc="\n");
    /**
     * @return return time now by a string
     * */
    std::string getTime();
    void debug(std::string mess,int line=__LINE__);
    void error(std::string mess,int line=__LINE__);
     ~Logger();
};




#endif //OPENGL_DEMO_LOGGER_H
