DIR_INC = ./
DIR_SRC = ./
DIR_OBJ = ./out
DIR_BIN = ./

SRC = $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 
DEPS = $(patsubst %.c, ${DIR_OBJ}/%.d, $(notdir ${SRC}))

TARGET = openwrt-ser

BIN_TARGET = ${DIR_BIN}/${TARGET}
 
CC = mips-openwrt-linux-gcc
CFLAGS = -g -Wall -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@
${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ -MMD -MF ${DIR_OBJ}/$*.d
.PHONY:clean
clean:
	find ${DIR_OBJ} -name '*.o' -exec rm -rf {} \;
	find ${DIR_OBJ} -name '*.d'	-exec rm -rf {} \;
-include $(DEPS)

