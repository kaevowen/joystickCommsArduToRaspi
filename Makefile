DIR_OBJ = ./OBJ
DIR_BIN = ./bin

OBJ_C = $(wildcard ${DIR_OBJ}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

LIB = -lwiringPi -lpthread
LIB2 = -lwiringPi -lm
TARGET = JOYSTICK
CC = gcc

DEBUG = -g -O0 
CFLAGS += $(DEBUG)

${TARGET} : ${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB2)

${DIR_BIN}/%.o : $(DIR_OBJ)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIB)


clean:
	rm -f $(DIR_BIN)/*.*
	rm -f $(TARGET)
