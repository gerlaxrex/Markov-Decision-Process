#ifndef STATE_HPP
#define STATE_HPP

#include<iostream>
#include<map>
#include<utility>
#include<string>
#include<sstream>
#include<vector>
#include<memory>
#include "Action.hpp"

class Action;
// State of a Markov Decision Process:
//      Every states has a vector of possible actions. Of course actions can be used as base class for inheritance, so we implemented this vector as a vector of pointers to Action

class State{
private:
    unsigned int id; //unique identifier for the state
    std::string name; //eventual name for the state (can also be empty)
    std::vector<std::shared_ptr<Action>> possibleActions;
public:
    friend std::ostream& operator<<(std::ostream& out, const State& s);
    State(unsigned id); //Default constructor
    State(const std::string& n, unsigned id);   //Name Initialization
    State(const State& s);
    virtual ~State(); //virtual destructor
    //Utility overloaded operators
    State& operator=(const State&a);
    bool operator==(const State& a) const;
    bool operator<(const State& a) const;
    bool operator<=(const State& a) const;
    bool operator>(const State& a) const;
    bool operator>=(const State& a) const;
    int getId() const ; //Id getter
    std::string getName() const; //Name Getter
    State& addAction(const std::shared_ptr<Action>& newAction); //Add an action to a state
    std::vector<std::shared_ptr<Action>> getActions() const;
    std::shared_ptr<Action> getAction(unsigned int id) const;
};

struct HashState{
    size_t operator()(const State& s) const;
};

#endif