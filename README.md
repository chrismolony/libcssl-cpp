libcssl cpp
-------------

linux 串口测试程序基于库libcssl https://github.com/mwheels/libcssl

修改为C++格式

对于一帧数据包分多次接收的现象，进行了数据处理，达到一帧后再打印处理

详细见回调函数

使用串口 /ttyUSB0，可在源代码中修改

By StevenShi 

2017/03/13

编译：
 make 

测试:
 ./test



