#include"MDPFactory.hpp"
#include"MDP.hpp"
#include<iostream>
#include<memory>

MDPFactory::MDPFactory(){}

MDPFactory::~MDPFactory(){}

std::shared_ptr<MDPFactory> MDPFactory::instance;

std::shared_ptr<MDPFactory> MDPFactory::getInstance(){
    if(!instance){
        instance.reset(new MDPFactory());
    }
    return instance;
}

std::shared_ptr<MDP> MDPFactory::createMDP(unsigned int sn){
    return std::make_shared<MDP>(sn);
}