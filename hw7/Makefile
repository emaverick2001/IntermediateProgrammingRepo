CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g -O0

tTrieTest: TTrieTest.o 
	$(CXX) -o tTrieTest TTrieTest.o

cTrieTest: CTrieTest.o CTrie.o
	$(CXX) -o cTrieTest CTrieTest.o CTrie.o

CTrieTest.o: CTrieTest.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c CTrieTest.cpp

CTrie.o: CTrie.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c CTrie.cpp

wordHunt: wordHuntMain.o CTrie.o WordHunt.o
	$(CXX) -o wordHunt wordHuntMain.o CTrie.o WordHunt.o

wordHuntMain.o: wordHuntMain.cpp WordHunt.h CTrie.h
	$(CXX) $(CXXFLAGS) -c wordHuntMain.cpp

WordHunt.o: WordHunt.cpp WordHunt.h
	$(CXX) $(CXXFLAGS) -c WordHunt.cpp

TTrieTest.o: TTrieTest.cpp TTrie.h TTrie.inc
	$(CXX) $(CXXFLAGS) -c TTrieTest.cpp
	
clean:
	rm -f *.o cTrieTest tTrieTest wordHunt *:Zone.Identifier
