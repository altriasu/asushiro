 # Makefile
 > [参考Makefile实战](https://www.yuque.com/linuxer/xngi03/nfsm1k?)
 # CMake
 > [参考-CMake实战](https://www.yuque.com/linuxer/xngi03/cs5y85?)
 语法：INCLUDE_DIRECTORIES找头文件
 ```
 INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/dir1")
 ```
 语法：ADD_SUBDIRECTORY添加子目录
 ```
 ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/dir1")
 ```
 语法：ADD_LIBRARY生成库文件
 ```
 ADD_LIBRARY(hello_shared SHARED libHelloSLAM.cpp) # 生成动态库
 ADD_LIBRARY(hello_static STATIC libHelloSLAM.cpp) # 生成静态库
 ```
 语法：TARGET_LINK_LIBRARIES链接库文件到执行文件上
 ```
 TARGET_LINK_LIBRARIES(hello_shared ${OpenCV_LIBS}) # 链接动态库到执行文件上
 ```