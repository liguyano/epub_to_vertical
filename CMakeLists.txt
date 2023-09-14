cmake_minimum_required(VERSION 3.26)
project(epubToRight)

set(CMAKE_CXX_STANDARD 23)
set(SELFHEAD "D:/OneDrive - jxstnu.edu.cn/c++/socket/socket_include/")
INCLUDE_DIRECTORIES("D:\\OneDrive - jxstnu.edu.cn\\c++\\socket\\socket_include")
add_executable(epubToRight main.cpp
        "${SELFHEAD}Logger.cpp"
unzip.cpp
)
