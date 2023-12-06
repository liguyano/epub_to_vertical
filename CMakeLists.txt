cmake_minimum_required(VERSION 3.26)
project(epubToRight)

set(CMAKE_CXX_STANDARD 23)
set(SELFHEAD "D:/OneDrive - jxstnu.edu.cn/c++/socket/socket_include/")
set(LINK_DIR ./libs)
INCLUDE_DIRECTORIES("D:\\OneDrive - jxstnu.edu.cn\\c++\\socket\\socket_include"
"./include"
)
link_directories(${LINK_DIR})
add_executable(epubToRight main.cpp
        "${SELFHEAD}Logger.cpp"
unzip.cpp zip.cpp
        ${SELFHEAD}MyFile.cpp
)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
list(APPEND SOURCES ${SOURCES_DIR}/logo.rc)
add_executable( FORM form.cpp
        "${SELFHEAD}Logger.cpp"
        ${SELFHEAD}MyFile.cpp
        unzip.cpp zip.cpp
        "${SELFHEAD}ToComplex.cpp" logo.rc)
add_executable(StringTest testy/CHangeStringTest.cpp
        "${SELFHEAD}Logger.cpp")
add_executable(FormatTest reFormate.cpp "${SELFHEAD}Logger.cpp" logo.rc)
add_executable(TOcomplex toComplex.cpp "${SELFHEAD}Logger.cpp"
       "${SELFHEAD}ToComplex.cpp")
target_link_libraries(epubToRight xmlt)
target_link_libraries(FORM xmlt)
target_link_libraries( FormatTest python3 python311)
