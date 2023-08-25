DIR_OBJ += Obj
TARGET = Ttest
CFLAGS += -std=c++11
LDFLAGS += -Wall, -rpath

CC = g++
SRC = $(wildcard ${EXTENDDISK_SRC}/*.cpp)  #wildcard 来获取工作目录下的所有的.cpp文件列表
DIR = $(notdir $(SRC))   				 #notdir用于去掉文件的绝对路径，只保留文件名
#$(patsubst 原模式， 目标模式， 文件列表)  在$(patsubst %.c,%.o,$(dir) )中，patsubst把$(dir)中的变量符合后缀是.c的全部替换成.o
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))   

all: CHECKDIR $(TARGET)
CHECKDIR:
	@echo "**********************************************************"
	mkdir -p $(DIR_OBJ)
	@echo "**********************************************************"
$(TARGET): $(OBJ) 
	$(CC) -o $@ $? $(LDFLAGS) 
$(DIR_OBJ)/%.o: ./%.cpp
	
.PHONY:clean
clean:
	rm -rf Ttest 
