CC = -c -g -std=c++11
NAME = proj4.x
OBJECT = -o $(NAME)
COMPILER = g++

main: proj4_driver.o
	$(COMPILER) $(OBJECT) proj4_driver.o

proj4_driver.o: proj4_driver.cpp bet.h bet.hpp
	$(COMPILER) $(CC) proj4_driver.cpp

clean: 
	rm -f *.o *.h.gch core.* $(NAME) 