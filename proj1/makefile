# Declaration of variables
CC = g++
CC_FLAGS = -w

# File names
EXEC = assign1.run
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

#CC The name of the compiler

#DEBUG The debugging flag. This is -g in both g++ and cxx. 
#The purpose of the flag is to include debugging information into 
#the executable, so that you can use utilities such as gdb to debug the code.

#LFLAGS The flags used in linking. As it turns out, you don't need any 
#special flags for linking. The option listed is "-Wall" which tells 
#the compiler to print all warnings. But that's fine. We can use that.

#CFLAGS The flags used in compiling and creating object files. This includes
#both "-Wall" and "-c". The "-c" option is needed to create object files, i.e. .o files.