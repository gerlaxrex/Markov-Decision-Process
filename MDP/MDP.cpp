#include<vector>
#include<string>
#include<sstream>
#include<utility>
#include<stdexcept>
#include<random>
#include<iomanip>
#include"MDP.hpp"
#include"Action.hpp"
#include"State.hpp"


//MDP
unsigned MDP::numStates = 0;


MDP::MDP(const std::vector<State>& sts){
    debugMode = false;
    this->states = sts;
    this->currentState = &states[0];
}

MDP::MDP(unsigned int sn){
    this->debugMode = false;
    for(int i = 0; i != sn; ++i){
        this->states.push_back({numStates});
        ++numStates;
    }
    this->currentState = &states[0];
}

MDP::~MDP(){
    /*for(auto& el : this->policy){
        delete el.second;
    }*/
    this->policy.clear();

    /*for(auto& el: this->transitions){
        delete el.first.second;
    }*/
    this->transitions.clear();
}

MDP& MDP::addReward(const State& s, double reward){
    auto conf = this->rewards.insert(std::unordered_map<State,double,HashState>::value_type(s,reward));
    if(conf.second == false){
        std::cout << "Reward for the state already exists." << std::endl;
    }else{
        if(debugMode) std::cout << "Inserted reward." << std::endl;
    }
    return *this;
}

State& MDP::getState(unsigned int i){
    for(auto it = this->states.begin(); it != this->states.end(); ++it){
        if(i == it->getId()){
            return *it;
        }
    }
    throw std::runtime_error("State not found.");
}


MDP& MDP::addTransition(const std::pair<State,std::shared_ptr<Action>>& sa, const std::map<State,double>& distr){
    double norm = 0;
    for(auto el : distr){
        norm += el.second;
    }
    

    auto conf = this->transitions.insert(std::make_pair(sa,distr));
    if(conf.second == false){
        std::cout << "Transition already exists." << std::endl;
    }else{
        std::cout << "Inserted Transition." << std::endl;
        //Normalize the distribution    
        for(auto el : this->transitions[sa]){
            this->transitions[sa][el.first] = el.second/norm;
        }
    }
    return *this;
}

const State& MDP::computeProbability(const std::map<State,double>& distr){
std::random_device rd;
    std::uniform_real_distribution<double> dist(0,1);
    double chosen = dist(rd);
    double prevSum = 0;
    double sum = 0;
    //std::cout << chosen << std::endl;
    for(auto it = distr.begin(); it!= distr.end();++it){
        prevSum = sum;
        sum += it->second;
        //std::cout << "Prev:" <<prevSum << ", sum:" << sum << std::endl;
        if(chosen <= sum && chosen > prevSum){
            return it->first;
        }    
    }
    throw std::runtime_error("No State found for the given probability distribution.\n");
}


double MDP::maxDistance(const std::map<State,double>& u, const std::map<State,double>& v){
    double maxDistance = 0;
    for(auto el : u){
        auto f = v.find(el.first);
        if(f != v.end()){
            double tmp = f->second;
            double actualDistance = std::fabs(el.second - tmp);
            maxDistance = (actualDistance > maxDistance? actualDistance : maxDistance);
        }else{
            throw std::runtime_error("Element not found in the map\n");
        }
    }
    return maxDistance;
}


MDP& MDP::computePolicy(){
    std::map<State,double> u,v; //v is the new computed vector, u is the previous one.
    //Initialize the vectors
    for(auto s : this->states){
        u[s] = 0;
    }
    //Begin the procedure
    double tollerance = 0.01;
    double maxDistance = 0;
    double discountFactor = 0.5;
    do{
        u = v;
        double preceding = 0;
        if(debugMode) std::cout << "ITERATION --------------------" << std::endl; 
        for(auto s : this->states){
            double preceding = 0;
            if(debugMode){
                std::cout << std::endl;
                std::cout << "processing " << s << std::endl;
            }
            for(auto a : s.getActions()){
                if(debugMode) std::cout << "action: "<< a << std::endl;
                for(auto prob : this->transitions){
                    if(prob.first.first == s && *prob.first.second == *a){
                        double sumProb = 0;
                        for(auto d : prob.second){
                            //std::cout <<"distribution: " << d.first << ":" << d.second << std::endl;
                            sumProb += d.second*u[d.first];
                            }    
                        double tmpUtil = this->rewards[s] + discountFactor * sumProb;
                        if(tmpUtil > preceding){
                            preceding = tmpUtil;
                            v[s] = tmpUtil;
                            this->policy[s] = std::make_shared<Action>(a->getName(),a->getId());
                            if(debugMode) std::cout << "Assigned "<< a << " to " << s << " -> "<< v[s] << std::endl;
                        }                        
                    }
                }
            }
        }
        try{
            maxDistance = this->maxDistance(u,v);
        }catch(std::runtime_error e){
            std::cout << e.what() << std::endl;
        }
    if(debugMode) std::cout << "---------------------------------" <<std::endl;
    }while(maxDistance > tollerance);
    return *this;
}

void MDP::printRewards(){
    std::cout << "REWARDS:" << std::endl;
    for(auto r : this->rewards){
        std::cout << r.first << "->" << std::setw(3) << r.second << std::endl;
    }
}

void MDP::printPolicy(){
    std::cout << "POLICY:" << std::endl;
    for(auto p : this->policy){
        std::cout << p.first << " -> " << *p.second << std::endl;
    }
}

void MDP::printTransitions(){
    std::cout << "TRANSITIONS: "<< std::endl;
    for(auto el : this->transitions){
        std::cout << "<" << el.first.first << "," << el.first.second << "> ----> ";
        for(auto d : el.second){
            std::cout << d.first << " : " << std::setw(5) << std::setprecision(3) << d.second << "; ";
        }
        std::cout << std::endl;
    }
}

MDP& MDP::setCurrentState(unsigned int i){
    bool found = false;
    for(auto it = this->states.begin(); it != this->states.end(); ++it){
        if(it->getId() == i){
            this->currentState = &(*it);
            if(debugMode) std::cout << "current State: " << *currentState <<" (id: " << currentState->getId() << ") " << std::endl;
            found = true;
            break;
        }
    }
    if(!found){
        std::cout << "No state with Id " << i << " has been found." << std::endl;
    }
    return *this;
}


MDP& MDP::step(){
    if(this->currentState == NULL){
        std::cout << "Current state has not been selected. Please call 'setCurrentState(unsigned int) method in order to set it." << std::endl;
        return *this;
    }else{
        //Select the next best Action:
        std::shared_ptr<Action> nextAction = this->policy[*currentState];
        std::cout << *nextAction << std::endl;
        for(auto el : this->transitions){
            if(el.first.first == *currentState && *el.first.second == *nextAction){
                this->computeProbability(el.second);
                //std::cout << "Found";  
                State nextState = this->computeProbability(el.second);
                std::cout << "Moving to " << nextState << std::endl;
                this->setCurrentState(nextState.getId()); 
            }
        }
        return *this;
    }
}

void MDP::activateDebug(){
    this->debugMode = true;
}


MDP& MDP::createTransition(unsigned int stateId, unsigned int actionId, const std::map<unsigned int,double>& distr){
    try{
        std::map<State,double> ds;
        for(auto& el : distr){
            ds[this->getState(el.first)] = el.second;
        }

        this->addTransition(std::make_pair(this->getState(stateId),this->getState(stateId).getAction(actionId)),ds);
    }catch(std::runtime_error e){
        std::cout << e.what() << std::endl;
    }
}


MDP& MDP::createReward(unsigned int sn, double reward){
    try{
        this->addReward(this->getState(sn),reward);
        return *this;
    }catch(std::runtime_error e){
        std::cout << e.what() << std::endl;
    }
}

 MDP& MDP::addAction(unsigned state, const std::string actionName, unsigned actionId){
     try{
         this->getState(state).addAction(std::make_shared<Action>(actionName,actionId));
         return *this;
     }catch(std::runtime_error e){
         std::cout << e.what() << std::endl;
     }
 }

