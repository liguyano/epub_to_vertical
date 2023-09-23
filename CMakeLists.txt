cmake_minimum_required(VERSION 3.26)
project(epubToRight)

set(CMAKE_CXX_STANDARD 23)
set(SELFHEAD "D:/OneDrive - jxstnu.edu.cn/c++/socket/socket_include/")
set(LINK_DIR ./libs)
INCLUDE_DIRECTORIES("D:\\OneDrive - jxstnu.edu.cn\\c++\\socket\\socket_include")
add_executable(epubToRight main.cpp
        "${SELFHEAD}Logger.cpp"
unzip.cpp zip.cpp
        ${SELFHEAD}MyFile.cpp
)
add_custom_command(
        OUTPUT source.i
        COMMAND ${CMAKE_CXX_COMPILER} -E ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp -o ${CMAKE_BINARY_DIR}/source.i
        DEPENDS main.cpp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_executable( FORM form.cpp
        "${SELFHEAD}Logger.cpp"
        ${SELFHEAD}MyFile.cpp
        unzip.cpp zip.cpp)
add_executable(StringTest testy/CHangeStringTest.cpp
        "${SELFHEAD}Logger.cpp")
target_link_libraries(epubToRight xmlt)
target_link_libraries(FORM xmlt)
