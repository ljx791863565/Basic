all: libutils.a 

clean:
	rm -rf *~ *.o *.d *.gcno *.gcda *.gcov libutils.a 

install:
	@echo Nothing to be mode.

include ../lib.rules

LIB_OBJS=

LIB_OBJS += os_unix.o

# ar 参数
# -c 创建一个库。不管库是否存在，都将创建
# -r 将文件插入备存文件中
libutils.a: $(LIB_OBJS)
	$(AR) crT $@ $?
# 在指令前加-表示忽略指令执行错误
-include $(OBJS:%.o=%.d)