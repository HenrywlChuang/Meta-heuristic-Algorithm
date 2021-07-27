# Onemax Problem

## Onemax problem

This project is for solving one-max problem.  
Exerting to clarify the code and making the structure to be clear and strong.  
If you have any suggestion, feel free to contact me.  
Thx! Have fun.  

Btw, this is the only public project, so if you are interested in other projects, send me correspondence.  

-----  
To **execute** the code  

- ***RUN*** **Name_of_algo Number_of_bit Number_of_evaluation Number_of_run**  

-----

## **Fast link**

- [Exhaustive Search](#Exhaustive-Search-(1))
- [Hill Climbing](#Hill-Climbing-(2))
- [Simulated Annealing](#Simulated-Annealing-(3))
- [Signature](#Best,)

-----

### **Exhaustive Search (1)**  

Trying to search the possible answers as many as possible.  

- Pros : No missing any possible solution.  
- Cons : Wasting the computing capability. If possible solutions are unlimited, couldn't find the best answer anyway.  
- EX :
  - The solution starts from zero. It will be added by one based on decimal. The maximum number depends on user's input. It will be **2^number_of_input**.

-----

### **Hill Climbing (2)**  

Finding a better fitness solution nearby current one, and move toward to it.  

- Pros : Can find a better solution nearby current one.  
- Cons : It might easily trap into a local optimum.  
- EX :

  - There are two ways of transition. One is randonmly pick a position to change,
and another one is only check the left or right position based on decimal.  

-----

### **Simulated Annealing (3)**  

Giving some probabilities to accept worse solution for searching other possible areas.  

- Pros : Can find a better solution if it traps in a local optimum.  
- Cons : It might easily trap into a local optimum.  
- EX :

  - There are two ways of transition. One is randonmly pick a position to change,
and another one is only check the left or right position based on decimal.  
  - The initial temperature is set to 100 or by user input. Temperature will decrease by every iteration.  
  - The anneal energy is calculated by *exp((current_fitness - lastest_fitness) / current_temperature)*
  
### ***Best,***  

### ***Henry Chuang***
