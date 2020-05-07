#ifndef MDP_HPP
#define MDP_HPP

#include<iostream>
#include<map>
#include<unordered_map>
#include<utility>
#include<string>
#include<sstream>
#include<vector>
#include"Action.hpp"
#include"State.hpp"


class Action;
class State;

class MDP {
private:
    bool debugMode;
    static unsigned numStates;
    State* currentState; //Pointer to the current state of the Markov Decision Process
    std::vector<State> states; //STATES
    std::unordered_map<State, double,HashState> rewards;  //REWARD FUNCTION
    std::unordered_map<State, std::shared_ptr<Action>, HashState> policy;   //POLICY FUNCTION
    std::map<std::pair<State,std::shared_ptr<Action>>, std::map<State, double>> transitions;  //TRANSITION PROBABILITY (for each state and action we have a probability distr. over all states)
    //const State& computeProbability(const std::map<State,double>& distr); //Function that returns a state over a probability function
    //double maxDistance(const std::map<State,double>& u, const std::map<State,double>& v); //Computes the maximum distance between two utility vectors (TRHOWS EXCEPTION)
protected:
    const State& computeProbability(const std::map<State,double>& distr); //Function that returns a state over a probability function
    double maxDistance(const std::map<State,double>& u, const std::map<State,double>& v); //Computes the maximum distance between two utility vectors (TRHOWS EXCEPTION)
    MDP& addReward(const State& s, double reward);   //Adds a reward in the rewards map 
    MDP& addTransition(const std::pair<State,std::shared_ptr<Action>>& sa, const std::map<State,double>& distr);    //Adds a transition distribution for a given pair and normalizes the distribution 
public:
    MDP(const std::vector<State>& sts); //Builds a MDP from a vector of States
    MDP(unsigned int sn);
    ~MDP();
    State& getState(unsigned int i);   //Gets the state with Id equal to i (TRHOWS EXCEPTION)
    MDP& createReward(unsigned int sn, double reward);
    MDP& createTransition(unsigned int stateId, unsigned int actionId, const std::map<unsigned int,double>& distr);
    MDP& addAction(unsigned state, const std::string actionName, unsigned actionId);
    MDP& computePolicy(); //MAIN METHOD, computes the optimal policy for the function
    void printRewards();
    void printPolicy();
    void printTransitions();
    MDP& setCurrentState(unsigned int i);
    void activateDebug();
    MDP& step(); //This function makes a stochastic step of the MDP. From the current state examines the policy, then moves probabilistically to one of the next states.
};


#endif
