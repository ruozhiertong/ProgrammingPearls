Code for Programming Pearls--编程珠玑 第二版

ch01:
0.编译运行： 使用make管理。https://blog.csdn.net/weixin_38391755/article/details/80380786
make xxx  // xxx为源文件不带后缀的名称
./xxx     //运行程序

make clean //清除所有编译出来的文件。


1.随机数 srand  rand

2.time 获取时间。

3.sprintf  sscanf

3.文件操作：
fopen fclose。
fprintf fscanf
文件定位 fseek。

4.make 用法。
# gcc 中只能有源文件，不能有.h 文件的。gcc -o solution1 solution1.c $(comobj)  错误了。
# 头文件只要能找到就行(原文件中include 或 编译时-I)，是在预编译找的，是不放在编译中进行编译的。
# gcc -c 进行编译，不会进行连接，因此没有mysort.o 也不错有问题。 gcc -o 会进行链接。
# 预处理(gcc -E)==>.i。 编译(gcc -c)==>.o。 汇编(gcc -S)==>.s。 链接(gcc -o)==>.out。 
# 一般如果没有特别指定前一个步骤，当前步骤会默认进行先前的步骤。 如只有gcc -o 如果没有前面的步骤，默认都处理了，即处理 预处理 编译 汇编 链接。

5.gcc 使用


5.bit map 的妙用。 位操作。

6.solution1.c 外部排序多路归并。 solution2.c 多次读取数据文件。 solution3.c 利用位图。