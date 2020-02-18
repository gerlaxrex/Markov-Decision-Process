<h1>Markov-Decision-Process</h1>

C++ code implementing a Markov Decision Process.
ATTENTION: This is not the final version, it will be subject to changes and adjustments in the code and eventually organization of the classes.

<h2>Classes</h2>

For this code I created three classes:
  - **Action**: It represents an Action that an agent can execute. This class may be inherited in order to create more specific actions (     (for example, we can create Up, Down, Left, Right classes for a robot agent acting in a certain environment.)
  
  - **State**: It represents a simple state in the MDP containg a vector of pointer to Actions, a Name and an Id.
  
  - **MDP**: This is the main class, containing various data structures representing the states of the MDP, the rewards for every state,      the transition function, the optimal policy. The main methods for this class are 'computePolicy()', that is needed in order to compute    the optimal policy for the MDP using a Dynamic Programming algorithm, and 'step()', that executes a probabilistical step for the MDP.

The *main.cpp* file initializes, computes the optimal policy and takes 10 steps of the MDP represented in the image below.

![alt-text](/MDP.png)

(_In this example rewards are chosen in this way: S0->5, S1->10, S2->6)_)

<h2>Compile</h2>

``g++ main.cpp Action.cpp MDP.cpp -std=c++11 -o MDP``

(A makefile will be added ASAP)


