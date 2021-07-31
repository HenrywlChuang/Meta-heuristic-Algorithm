# Execute this to run the program
# Plotting figures, please using Plot.sh
# Before running the program, plz do "make cleanall".
make

algos=1         #test(0) Exhaustive Search(1) Hill Climbing(2) Simulated Annealing(3) Tabu Search (4) Plotting (10)
bit=100
evaluation=1000
run=51
function=1      #Onemax (1) Deception (2)
RUN=./bin/main

$RUN $algos $bit $evaluation $run $function

# LOOP
# for((algos=2;algos<4;algos++))
# do
#     $RUN ${algos} $bit $evaluation $run
# done