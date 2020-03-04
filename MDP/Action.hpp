#ifndef ACTION_HPP

#define ACTION_HPP

#include<string>
#include"MDP.hpp"

class MDP;

class Action{
    protected:
        std::string actionName;
        unsigned int actionId;
    public:
        friend std::ostream& operator<<(std::ostream& os, const Action& a);
        friend std::ostream& operator<<(std::ostream& os,Action* a);
        //Constructor/Destructor
        Action(const std::string actionName, unsigned int actionId);
        virtual ~Action();
        //Overloaded Operators
        Action& operator=(const Action& a);
        bool operator==(const Action& a) const;
        //friend bool operator==(Action* a1, Action*a2) const;
        bool operator<(const Action& a) const;
        bool operator<=(const Action& a) const;
        bool operator>(const Action& a) const;
        bool operator>=(const Action& a) const;
        //Getters
        std::string getName() const;
        unsigned int getId() const;
};


struct HashAction{
    size_t operator()(const Action& a) const ;
};


#endif