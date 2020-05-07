#include"MDP.hpp"
#include"MDPFactory.hpp"
#include<iostream>
#include<string>
#include<map>
#include<utility>


int main(){
    //Write our states transitions with probabilities to be used next (We could also declare them in the addTransition)
    std::map<unsigned,double> distr1 = {{0,0.2},{1,0.8}};
    std::map<unsigned,double> distr2 = {{0,0.7},{1,0.3}};
    std::map<unsigned,double> distr3 = {{0,0.0},{1,1.0}};
    std::map<unsigned,double> distr4 = {{1,0.3},{2,0.7}};
    std::map<unsigned,double> distr5 = {{1,0.0},{2,1}};
    std::map<unsigned,double> distr6 = {{0,0.5},{2,0.5}};

    //create a MDP with 3 states
    auto f = MDPFactory::getInstance();
    auto mk = f->createMDP(3);
    
    //Adding Actions to States
    mk->addAction(0,"A",0);
    mk->addAction(1,"B",1);
    mk->addAction(1,"C",2);
    mk->addAction(1,"D",3);
    mk->addAction(2,"E",4);
    mk->addAction(2,"F",5);

    //mk->activateDebug();
    //Adding the rewards
    mk->createReward(0,10);
    mk->createReward(2,6);
    mk->createReward(1,5);

    mk->printRewards();

    //Add the transitions
    mk->createTransition(0,0,distr1);
    mk->createTransition(1,1,distr2);
    mk->createTransition(1,2,distr3);
    mk->createTransition(1,3,distr4);
    mk->createTransition(2,4,distr5);
    mk->createTransition(2,5,distr6);

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

    std::cout << "END" << std::endl;

    return 0;
}