CXX = g++
CXXFLAGS = -o MDP
CXXVERSION = -std=c++17

#main: Action.cpp State.cpp MDP.cpp main.cpp
#	$(CXX) main.cpp MDP.cpp State.cpp Action.cpp $(CXXFLAGS)

main: Action.o State.o MDP.o main.o
	$(CXX) -g main.o Action.o State.o MDP.o $(CXXVERSION) $(CXXFLAGS)

main.o: main.cpp MDP.hpp Action.hpp State.hpp
	$(CXX) -c main.cpp $(CXXVERSION)

MDP.o: MDP.cpp MDP.hpp Action.hpp State.hpp
	$(CXX) -c MDP.cpp $(CXXVERSION)

State.o: State.cpp State.hpp Action.hpp
	$(CXX) -c State.cpp $(CXXVERSION)

Action.o: Action.cpp Action.hpp
	$(CXX) -c Action.cpp $(CXXVERSION)

