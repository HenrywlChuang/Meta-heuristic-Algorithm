#include "GA.h"
#include "lib.h"

using namespace std;

GA::GA(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function, int num_population, string way_selection, string way_crossover, double crossover_rate, double mutation_rate)
        :
        Algo(name_algo, num_bit, num_evaluation, num_run, name_function), num_population(num_population), way_selection(way_selection), way_crossover(way_crossover), crossover_rate(crossover_rate), mutation_rate(mutation_rate)
{
        srand(time(0));
}

void GA::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Genetic Algorithm."                 << endl;
    cout << "Algo : "               << name_algo         << endl;
    cout << "Bits : "               << num_bit           << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    cout << "Population : "         << num_population    << endl;
    cout << "Crossover rate : "     << crossover_rate    << endl;
    cout << "Mutation rate  : "     << mutation_rate     << endl;
    way_method = "GA" + way_selection + way_crossover;
    way_selection = "GA" + way_selection;
    way_crossover = "GA" + way_crossover;
    // way_selection = "GA_tournament";    // GA_roulette or GA_tournament 
    // way_crossover = "GA_onepoint";    // GA_onepoint

    average_best.assign(num_evaluation, 0);
    // start
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        // initialization
        initialization_population(solution_vec_pop, num_bit, num_population);
        evaluation_population(current_fitness_pop, solution_vec_pop, name_function);
        // see_solution_v2i_vec(solution_vec_pop);
        local_best_population(current_fitness_pop, local_best);
        global_best = local_best;
        // cout << local_best << endl;

        while(current_evaluation < num_evaluation)
        {
            // GA
            v2i temp_solution_vec_pop;
            for(int j = 0; j < num_population; j++)
            {
                selection(way_selection, temp_solution_vec_pop);
                crossover(way_crossover, temp_solution_vec_pop);
                mutation();
            }
            
            evaluation_population(current_fitness_pop, solution_vec_pop, name_function);
            local_best_population(current_fitness_pop, local_best);
            save_global_best(global_best, local_best);
            for(int k = current_evaluation; k < (current_evaluation + num_population); k++)    average_best[k] += global_best;
            current_evaluation += num_population;
        }
        // write_best_file(way_method, global_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run, name_function);
    cout << "---DONE GA.---" << endl;
}

inline void GA::selection(const string& way_selection, v2i& temp_solution_vec_pop)
{
    if(!way_selection.compare("GA_roulette"))            selection_roulette(temp_solution_vec_pop);
    else if(!way_selection.compare("GA_tournament"))     selection_tournament(temp_solution_vec_pop);
    else
    {
        cout << "Please check the selection method." << endl;
        exit(1);
    }
}

inline void GA::selection_roulette(v2i& temp_solution_vec_pop)
{
    double select_random_rate;
    double sum_fitness_base = accumulate(current_fitness_pop.begin(), current_fitness_pop.end(), 0);
    // cout << "sum_fitness_base : " << sum_fitness_base << endl;
    for(int i = 0; i < (int)solution_vec_pop.size(); i++)
    {
        int position = 0;
        select_random_rate = rand() % (int)sum_fitness_base;
        // cout << "select_random_rate : " << select_random_rate << endl;
        while(select_random_rate > current_fitness_pop.back())
        {
            // cout << "Before minus" << endl;
            // cout << position << endl;
            // cout << current_fitness_pop[position] << endl;
            // cout << select_random_rate << endl;
            select_random_rate -= current_fitness_pop[position];
            position++;
            // cout << "after minus" << endl;
            // cout << position << endl;
            // cout << select_random_rate << endl;
        }
        temp_solution_vec_pop.push_back(solution_vec_pop[position]);
    }
}

inline void GA::selection_tournament(v2i& temp_solution_vec_pop)
{
    int select_one;
    int select_two;
    for(int i = 0; i < (int)solution_vec_pop.size(); i++)
    {
        select_one = rand() % num_population;
        select_two = rand() % num_population;
        if(current_fitness_pop[select_one] >= current_fitness_pop[select_two])   temp_solution_vec_pop.push_back(solution_vec_pop[select_one]);
        else    temp_solution_vec_pop.push_back(solution_vec_pop[select_two]);
    }
}

inline void GA::crossover(const string& way_crossover, const v2i& temp_solution_vec_pop)
{
    double random_crossover = (double)rand() / RAND_MAX;
    if(random_crossover > crossover_rate)   return;
    if(!way_crossover.compare("GA_onepoint"))     crossover_one_point(temp_solution_vec_pop);
    else
    {
        cout << "Please check the crossover method." << endl;
        exit(1);
    }
}

inline void GA::crossover_one_point(const v2i& temp_solution_vec_pop)
{
    v1i temp_solution_vec;
    temp_solution_vec.resize(num_bit);
    int select_one;
    int select_two;
    for(int i = 0; i < (int)solution_vec_pop.size(); i++)
    {
        select_one = rand() % num_population;
        select_two = rand() % num_population;
        int random_onepoint = rand() % num_bit;
        for(int j = 0; j < random_onepoint; j++)                 temp_solution_vec[j] = temp_solution_vec_pop[select_one][j];
        for(int j = random_onepoint; j < num_bit; j++)           temp_solution_vec[j] = temp_solution_vec_pop[select_two][j];
        solution_vec_pop[i] = temp_solution_vec;
    }
}

inline void GA::mutation()
{
    double random_mutation = (double)rand() / RAND_MAX;
    if(random_mutation > mutation_rate)   return;
    for(int i = 0; i < (int)solution_vec_pop.size(); i++)
    {
        int random_onepoint = rand() % num_bit;
        if(solution_vec_pop[i][random_onepoint] == 0)   solution_vec_pop[i][random_onepoint] = 1;
        else                                            solution_vec_pop[i][random_onepoint] = 0;
    }
}
