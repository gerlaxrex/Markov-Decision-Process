#include<vector>
#include<string>
#include<utility>
#include<stdexcept>
#include<iomanip>
#include<functional>
#include"Action.hpp"

//STATE
unsigned int State::actual_id = 0;

State::State(){
    std::ostringstream os;
    this->id = actual_id++;
    os << "S" << this->id;
    this->name = os.str();
}

State::State(const std::string& n){
    this->id = actual_id++;
    this->name = n;
}

State::State(const State& s){
    this->id = s.id;
    this->name = s.name;

    for(auto el : this->possibleActions){
        delete el;
    }
    this->possibleActions.clear();
    
    for(auto el : s.possibleActions){
        this->possibleActions.push_back(new Action(el->getName(),el->getId()));
    }
}

State::~State(){
    for(auto el : this->possibleActions){
        delete el;
    }
    this->possibleActions.clear();
}

State& State::operator=(const State& a){
    this->id = a.id;
    this->name = a.name;

    for(auto el : this->possibleActions){
        delete el;
    }
    this->possibleActions.clear();
    
    for(auto el : a.possibleActions){
        this->possibleActions.push_back(new Action(el->getName(),el->getId()));
    }
    return *this;
}

bool State::operator==(const State& a) const {
    return (this->id == a.id? true : false);
}

bool State::operator<(const State& a) const {
    return (this->id < a.id? true : false);
}

bool State::operator<=(const State& a) const {
    return (this->id <= a.id? true : false);
}

bool State::operator>(const State& a) const {
    return (this->id > a.id? true : false);
}

bool State::operator>=(const State& a) const {
    return (this->id >= a.id? true : false);
}

int State::getId() const {
    return this->id;
}

std::string State::getName() const {
    return this->name;
}

std::ostream& operator<<(std::ostream& out, const State& s){
    out << "State " << s.id << " ";
    return out;
}

std::vector<Action*> State::getActions() const {
    return this->possibleActions;
}

State& State::addAction(Action* newAction){
    this->possibleActions.push_back(newAction);
    return *this;
}


Action* State::getAction(unsigned int id) const {
    for(auto action : this->possibleActions){
        if(action->getId() == id){
            return action;
        }
    }
    return NULL;
}

size_t HashState::operator()(const State& s) const{
    size_t h1 = std::hash<std::string>{}(s.getName());
    size_t h2 = std::hash<int>{}(s.getId());
    return h1 ^ h2;
}
