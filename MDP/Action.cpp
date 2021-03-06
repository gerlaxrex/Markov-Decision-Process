#include"Action.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<functional>

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
    if(typeid(*this) == typeid(a)){
        return (this->actionId == a.actionId? true : false);
    }else{
        return false;
    }
}

bool Action::operator<(const Action& a) const {
    if(typeid(*this) == typeid(a)){
        return (this->actionId < a.actionId? true : false);
    }else{
        return false;
    }
}

bool Action::operator<=(const Action& a) const {
    if(typeid(*this) == typeid(a)){
        return (this->actionId <= a.actionId? true : false);
    }else{
        return false;
    }
}

bool Action::operator>(const Action& a) const {
    if(typeid(*this) == typeid(a)){
        return (this->actionId > a.actionId? true : false);
    }else{
        return false;
    }
}

bool Action::operator>=(const Action& a) const {
    if(typeid(*this) == typeid(a)){
        return (this->actionId >= a.actionId? true : false);
    }else{
        return false;
    }

}

std::string Action::getName() const{
    return this->actionName;
}

unsigned int Action::getId() const {
    return this->actionId;
}

size_t HashAction::operator()(const Action& a) const {
    size_t h1 = std::hash<int>{}(a.getId());
    size_t h2 = std::hash<std::string>{}(a.getName());
    return (h1 ^ h2);
}

