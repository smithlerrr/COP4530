#CC = -c -g -Wall -Wextra -Werror -std=c++11 -pedantic
CC = -c -g -std=c++11  -I .
OUT_NAME_1 = spass.x
OO1 = -lm -lcrypt -o $(OUT_NAME_1)
COMPILER = g++47

# Uncomment this to have .o file auto removed once program is compiled
# all: main clean

main: hashtable.o spass.o
	$(COMPILER) $(OO1) hashtable.o spass.o
hashtable.o: hashtable.h hashtable.cpp
	$(COMPILER) $(CC) hashtable.cpp
spass.o: spass.cpp
	$(COMPILER) $(CC) spass.cpp
clean: 
	rm -f *.o *.h.gch core.* $(OUT_NAME_1) $(OUT_NAME_2)