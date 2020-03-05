#include"MDP.hpp"
#include"State.hpp"
#include"Action.hpp"
#include<iostream>
#include<string>
#include<map>
#include<utility>

int main(){
    //States of the MDP
    State s0,s1,s2;

    //Function addAction(action)   examples
    s0.addAction(new Action("A",0));
    s1.addAction(new Action("B",1));
    s1.addAction(new Action("C",2));
    s1.addAction(new Action("D",3));
    s2.addAction(new Action("E",4));
    s2.addAction(new Action("F",5));

    //Write our states transitions with probabilities to be used next (We could also declare them in the addTransition)
    std::map<State,double> distr1 = {{s0,0.2},{s1,0.8}};
    std::map<State,double> distr2 = {{s0,0.7},{s1,0.4}};
    std::map<State,double> distr3 = {{s0,0.0},{s1,1.0}};
    std::map<State,double> distr4 = {{s1,0.3},{s2,0.7}};
    std::map<State,double> distr5 = {{s1,0.0},{s2,1}};
    std::map<State,double> distr6 = {{s0,0.5},{s2,0.5}};

    //Createa the MDP objects
    MDP* mk = new MDP({s0,s1,s2});
    mk->activateDebug();
    //Adding the rewards
    mk->addReward(s0,5);
    mk->addReward(s2,6);
    mk->addReward(s1,10);
    mk->printRewards();

    //Adding the transitions on the MDP
    mk->addTransition(std::make_pair(s0,s0.getAction(0)),distr1);
    mk->addTransition(std::make_pair(s1,s1.getAction(1)),distr2);
    mk->addTransition(std::make_pair(s1,s1.getAction(2)),distr3);
    mk->addTransition(std::make_pair(s1,s1.getAction(3)),distr4);
    mk->addTransition(std::make_pair(s2,s2.getAction(4)),distr5);
    mk->addTransition(std::make_pair(s2,s2.getAction(5)),distr6);
    mk->printTransitions();
    
    //Algorithm for the Policy computing
    mk->computePolicy();
    mk->printPolicy();

    //Setting the current State
    mk->setCurrentState(2);
    
    //step() function called for 10 times
    for(int i = 0; i!= 10; ++i){
        mk->step();
    }

    return 0;
}