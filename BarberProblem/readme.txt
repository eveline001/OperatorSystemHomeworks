report.pdf	:	实验报告

exe/barber	:	二进制文件
exe/img, src/img:	用到的图片文件

src/common.h	:	公共头文件定义
src/glo.h	:	全局变量声明
src/window.h	:	程序窗口类定义
src/main.cpp	:	主程序文件，包括两个理发师和顾客线程
src/glo.cpp	:	全局变量定义
src/window.cpp	:	GUI实现
src/linux.pro	:	工程文件
src/Makefile	:	Makefile

如果编译失败，先执行
apt-get install libqt4-dev libqt4-gui
然后在目录中执行
qmake -project
qmake
make
完成编译。