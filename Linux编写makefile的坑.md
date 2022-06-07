
makefile超级菜鸟坑（Makefile:2: *** 遗漏分隔符 。 停止）
Makefile
请注意，在第二行的“gcc”命令之前必须要有一个tab缩进。语法规定Makefile中的任何命令之前都必须要有一个tab缩进，否则make就会报错
cc = gcc
prom = calc
source = xxx.c 
 
$(prom): $(source)
    $(cc) -o $(prom) $(source)
#   $(cc)前一定要记得TAB键啊  
