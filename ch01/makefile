commonDir = ../commonAlg
comobj = $(commonDir)/mysort.c $(commonDir)/mysort.h

#这个也可行的。会生成目标文件，有.o文件等。
# solution1:solution1.o mysort.o
# 	gcc -o solution1 solution1.o mysort.o
# gcc -c 进行编译，不会进行连接，因此没有mysort.o 也不错有问题。 gcc -o 会进行链接。
# 预处理(gcc -E)==>.i。 编译(gcc -c)==>.o。 汇编(gcc -S)==>.s。 链接(gcc -o)==>.out。 
# 一般如果没有特别指定前一个步骤，当前步骤会默认进行先前的步骤。 如只有gcc -o 如果没有前面的步骤，默认都处理了，即处理 预处理 编译 汇编 链接。
# solution1.o:solution1.c common.h
# 	gcc -c solution1.c
# mysort.o:$(commonDir)/mysort.c $(commonDir)/mysort.h
# 	gcc -c $(commonDir)/mysort.c


#或者
# solution1:solution1.c common.h $(commonDir)/mysort.c $(commonDir)/mysort.h
# 	gcc -o solution1 solution1.c $(commonDir)/mysort.c

# gcc 中只能有源文件，不能有.h 文件的。gcc -o solution1 solution1.c $(comobj)  错误了。
# 头文件只要能找到就行(原文件中include 或 编译时-I)，是在预编译找的，是不放在编译中进行编译的。
solution1:solution1.c common.h $(comobj)
	gcc -o solution1 solution1.c $(commonDir)/mysort.c

solution2:solution2.c common.h $(comobj)
	gcc -o solution2 solution2.c $(commonDir)/mysort.c

solution3:solution3.c common.h
	gcc -o solution3 solution3.c

generateData:generateData.c common.h
	gcc -o generateData generateData.c

clean:
	rm solution1 solution2 solution3 generateData