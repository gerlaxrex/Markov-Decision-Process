#ifndef STATE_HPP
#define STATE_HPP

#include<iostream>
#include<map>
#include<utility>
#include<string>
#include<sstream>
#include<vector>
#include "Action.hpp"

class Action;
// State of a Markov Decision Process:
//      Every states has a vector of possible actions. Of course actions can be used as base class for inheritance, so we implemented this vector as a vector of pointers to Action

class State{
private:
    unsigned int id; //unique identifier for the state
    std::string name; //eventual name for the state (can also be empty)
    static unsigned int actual_id; //Counter for the number of states;
    std::vector<Action*> possibleActions;
public:
    friend std::ostream& operator<<(std::ostream& out, const State& s);
    State(); //Default constructor
    State(const std::string& n);   //Name Initialization
    State(const State& s);
    virtual ~State(); //virtual destructor
    //Utility overloaded operators
    State& operator=(const State&a);
    bool operator==(const State& a) const;
    bool operator<(const State& a) const;
    bool operator<=(const State& a) const;
    bool operator>(const State& a) const;
    bool operator>=(const State& a) const;
    int getId(); //Id getter
    std::string& getName(); //Name Getter
    State& addAction(Action* newAction); //Add an action to a state
    std::vector<Action*> getActions();
    Action* getAction(unsigned int id);
};

#endif