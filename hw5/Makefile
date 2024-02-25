CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++11

phone_db : phone_db.o helperfunct.o
	$(CXX) -o phone_db phone_db.o helperfunct.o

phone_db.o : phone_db.cpp helperfunct.h
	$(CXX) $(CXXFLAGS) -c phone_db.cpp -o phone_db.o

helperfunct.o : helperfunct.cpp helperfunct.h
	$(CXX) $(CXXFLAGS) -c helperfunct.cpp -o helperfunct.o

clean:
	${RM} phone_db *.o *:Zone.Identifier name*.txt
