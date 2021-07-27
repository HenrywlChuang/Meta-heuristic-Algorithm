# Execute this to run the program
# Plotting figures, please using Plot.sh
make

algos=1         #test(0) Exhaustive Search(1) Hill Climbing(2) Plotting (10)
bit=100
evaluation=1000
run=1
RUN=./bin/main

$RUN $algos $bit $evaluation $run