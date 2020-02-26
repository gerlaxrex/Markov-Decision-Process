CXX = g++
CXXFLAGS = -o make/
CXXVERSION = -std=c++17

#main: Action.cpp State.cpp MDP.cpp main.cpp
#	$(CXX) main.cpp MDP.cpp State.cpp Action.cpp $(CXXFLAGS)

main: make/Action.o make/State.o make/MDP.o make/main.o
	$(CXX) -g make/main.o make/Action.o make/State.o make/MDP.o $(CXXVERSION) $(CXXFLAGS)MDP

main.o: main.cpp MDP.hpp Action.hpp State.hpp
	$(CXX) -c main.cpp $(CXXVERSION) $(CXXFLAGS)main.o

MDP.o: MDP.cpp MDP.hpp Action.hpp State.hpp
	$(CXX) -c MDP.cpp $(CXXVERSION) $(CXXFLAGS)MDP.o

State.o: State.cpp State.hpp Action.hpp
	$(CXX) -c State.cpp $(CXXVERSION) $(CXXFLAGS)State.o

Action.o: Action.cpp Action.hpp
	$(CXX) -c Action.cpp $(CXXVERSION) $(CXXFLAGS)Action.o

