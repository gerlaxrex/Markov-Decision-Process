#include"Action.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<utility>

Action::Action(std::string actionName, unsigned int actionId) : actionName(actionName),actionId(actionId){}

Action::~Action(){}

Action& Action::operator=(const Action& a){
    this->actionName = a.actionName;
    this->actionId = a.actionId;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Action& a){
    os << "[Action (id: " << a.actionId << ") " << a.actionName << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os,Action* a){
    os << "[Action (id: " << a->actionId << ") " << a->actionName << "]";
    return os;
}

bool Action::operator==(const Action& a) const {
    return (this->actionId == a.actionId? true : false);
}

bool Action::operator<(const Action& a) const {
    return (this->actionId < a.actionId? true : false);
}

bool Action::operator<=(const Action& a) const {
    return (this->actionId <= a.actionId? true : false);
}

bool Action::operator>(const Action& a) const {
    return (this->actionId > a.actionId? true : false);
}

bool Action::operator>=(const Action& a) const {
    return (this->actionId >= a.actionId? true : false);
}

std::string Action::getName() const{
    return this->actionName;
}

unsigned int Action::getId() const {
    return this->actionId;
}

