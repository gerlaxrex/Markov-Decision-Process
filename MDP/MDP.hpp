#ifndef MDP_HPP
#define MDP_HPP

#include<iostream>
#include<map>
#include<utility>
#include<string>
#include<sstream>
#include<vector>
#include<memory>
#include"Action.hpp"


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

class MDP {
private:
    State* currentState; //Pointer to the current state of the Markov Decision Process
    std::vector<State> states; //STATES
    std::map<State, double> rewards;  //REWARD FUNCTION
    std::map<State, Action*> policy;   //POLICY FUNCTION
    std::map<std::pair<State,Action*>, std::map<State, double>> transitions;  //TRANSITION PROBABILITY (for each state and action we have a probability distr. over all states)
    const State& computeProbability(const std::map<State,double>& distr); //Function that returns a state over a probability function
    double maxDistance(const std::map<State,double>& u, const std::map<State,double>& v); //Computes the maximum distance between two utility vectors (TRHOWS EXCEPTION)
public:
    MDP(const std::vector<State>& sts); //Builds a MDP from a vector of States
    ~MDP();
    State& getState(unsigned int i);   //Gets the state with Id equal to i (TRHOWS EXCEPTION)
    MDP& addReward(const State& s, double reward);   //Adds a reward in the rewards map 
    MDP& addTransition(const std::pair<State,Action*>& sa,std::map<State,double>& distr);    //Adds a transition distribution for a given pair and normalizes the distribution
    MDP& computePolicy(); //MAIN METHOD, computes the optimal policy for the function
    void printRewards();
    void printPolicy();
    void printTransitions();
    MDP& setCurrentState(unsigned int i);
    MDP& step(); //This function makes a stochastic step of the MDP. From the current state examines the policy, then moves probabilistically to one of the next states.
};


#endif
