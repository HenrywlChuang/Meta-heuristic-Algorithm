# Heuristic Algorithm & Meta-heuristic Algorithm

## **Abstract**

This project is coding for fun. My goal is exerting to clarify the code and making the structure to be clear and strong. I also want to learn the OOP concept. If you have any suggestion, feel free to contact me. Thx! Have fun.  

Btw, this is the only public project, so if you are interested in other projects, send me correspondence.  

-----  
To **execute** the code  

- ***RUN*** **Name_of_algo Number_of_bit Number_of_evaluation Number_of_run Name_of_function**  

-----

## **Fast link**

- [Abstract](#abstract)
- [Problems](#problems)
  - [Onemax](#onemax-problem)
  - [Deception](#deception-problem)
- [Algorithms](#algorithms)
  - [Exhaustive Search](#exhaustive-search-1)
  - [Hill Climbing](#hill-climbing-2)
  - [Simulated Annealing](#simulated-annealing-3)
  - [Tabu Search](#tabu-search-4)
- [Modified Commits](#modified-commits)
- [Signature](#best)

-----

## **Problems**

### **Onemax problem**

- Def : There is a vector that saves "0" or "1". The length of the vactor is defined by user.  
- Goal : The goal of onemax problem is to find **"1"** as many as possible in the vector.

-----

### **Deception problem**

- Def : A function which is difined as **$f(x_{bin}) = |x_{dec} - 2 ^ {(n - 2)}|$**  
The $x$ means a vector that has been input. The $x_{bin}$ means $x$ using binary to show. The $x_{dec}$ means $x$ using decimal to show. The $n$ means the length of $x_{bin}$.  
- Goal : The goal is making the function result as huge as possible.

-----

## **Algorithms**

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
  - The anneal energy is calculated by **exp((current_fitness - lastest_fitness) / current_temperature)**

-----

### **Tabu Search (4)**  

Trying to search a possible solution nearby the certain one which is better and not contained in the tabu list. TS will generate the tabu list to save some solutions at the beginning.

- Pros : To avoid a place where has been visited.  
- Cons : The size of the tabu list might be not enough.  
- EX :

  - The original tabu list is set to size 7.  
  - The tabu list will record the space where has been visited and avoid these areas, so it has more chances to seach the new areas that have not been searched.

-----

### **Modified Commits**

- 07/31/2021 The commit should be **"Fixed bugs. Formatted. The OOP concept"**.
- [BACK TO the TOP](#fast-link)
  
### ***Best,***  

### ***Henry Chuang***
