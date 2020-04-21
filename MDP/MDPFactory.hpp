#ifndef MDPFACT_HPP
#define MDPFACT_HPP

#include"MDP.hpp"
#include<iostream>
#include<memory>


class MDPFactory{
private:
    static std::shared_ptr<MDPFactory> instance;
protected:
    MDPFactory();
public:
    ~MDPFactory();
    static std::shared_ptr<MDPFactory> getInstance();
    std::shared_ptr<MDP> createMDP(unsigned int sn);
};


#endif