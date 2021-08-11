# Execute this to run the program
# Plotting figures, please using Plot.sh
# Before running the program, plz do "make cleanall".
make

algos=1         #test(0) Exhaustive Search(1) Hill Climbing(2) Simulated Annealing(3) Tabu Search (4) Genetic Algo (5) Plotting (10)
bit=100
evaluation=100000
run=51
function=2                      #Onemax (1) Deception (2)
waymethod=_rand                 #_rand _left_right
wayselection=_roulette          #_roulette _tournament
waycrossover=_onepoint         #_onepoint
waymethod_name=("_rand" "_left_right")
wayselection_name=("_roulette" "_tournament")
waycrossover_name=("_onepoint")
population=10
crossover_rate=0.6
mutation_rate=0.1
RUN=./bin/main

# ES
# $RUN 1 $bit $evaluation $run $function

# HC SA TS
# $RUN $algos $bit $evaluation $run $function $waymethod

# GA
# $RUN 5 $bit $evaluation $run $function $population $wayselection $waycrossover $crossover_rate $mutation_rate

# # LOOP
for((function=1;function<3;function++))
do
    $RUN 1 $bit $evaluation $run ${function}
    for((algos=2;algos<5;algos++))
    do
        for((waymethod=0;waymethod<${#waymethod_name[@]};waymethod++))
        do
            $RUN ${algos} $bit $evaluation $run ${function} ${waymethod_name[$waymethod]}
        done
    done
    for((wayselection=0;wayselection<${#wayselection_name[@]};wayselection++))
    do
        for((waycrossover=0;waycrossover<${#waycrossover_name[@]};waycrossover++))
        do
            $RUN 5 $bit $evaluation $run ${function} $population ${wayselection_name[$wayselection]} ${waycrossover_name[$waycrossover]} $crossover_rate $mutation_rate
        done
    done
done
./Plot.sh
