CXX = g++
CXXFLAGS = -o make/
CXXVERSION = -std=c++17

$(shell mkdir -p make)

main: Action.o State.o MDP.o MDPFactory.o main.o
	$(CXX) -g make/main.o make/Action.o make/State.o make/MDP.o make/MDPFactory.o $(CXXVERSION) $(CXXFLAGS)MDP

main.o: main.cpp MDPFactory.hpp MDP.hpp
	$(CXX) -c main.cpp $(CXXVERSION) $(CXXFLAGS)main.o

MDPFactory.o: MDPFactory.cpp MDPFactory.hpp MDP.hpp
	$(CXX) -c MDPFactory.cpp $(CXXVERSION) $(CXXFLAGS)MDPFactory.o

MDP.o: MDP.cpp MDP.hpp Action.hpp State.hpp
	$(CXX) -c MDP.cpp $(CXXVERSION) $(CXXFLAGS)MDP.o

State.o: State.cpp State.hpp Action.hpp
	$(CXX) -c State.cpp $(CXXVERSION) $(CXXFLAGS)State.o

Action.o: Action.cpp Action.hpp
	$(CXX) -c Action.cpp $(CXXVERSION) $(CXXFLAGS)Action.o

