#include "SA.h"
#include "lib.h"

using namespace std;

SA::SA(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function, string way_method)
        :
        Algo(name_algo, num_bit, num_evaluation, num_run, name_function)
{
        this->way_method = way_method;
        srand(time(0));
}

void SA::main()
{
    cout << "---------------------"                         << endl;
    cout << "This is the Simulated Annealing."              << endl;
    cout << "Algo : "               << name_algo            << endl;
    cout << "Bits : "               << num_bit              << endl;
    cout << "Evaluation : "         << num_evaluation       << endl;
    way_method = "SA" + way_method;
    // way_method = "SA_rand"; // SA_rand or SA_left_right

    /// set by self or from outside
    // cout << "Please input initial temperature"              << endl;
    // if(scanf("%lf", &initial_temperature))  cout << "Initial temperature : " << initial_temperature << endl;
    // else    cout << "Check the input." << endl;
    initial_temperature = 100; 
    ///

    average_best.assign(num_evaluation, 0);
    // start
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        double temperature_run = initial_temperature;
        // initialization
        initialization(solution_vec, num_bit);
        // see_solution_v1i_vec(solution_vec);
        evaluation(current_fitness, solution_vec, name_function);
        global_best = current_fitness;
        // cout << "START FROM number of bit : " << current_fitness << endl;

        // SA
        double latest_best = current_fitness;
        while(current_evaluation < num_evaluation)
        {
            v1i temp_solution_vec = solution_vec;
            transition(temp_solution_vec); 
            evaluation(current_fitness, temp_solution_vec, name_function);
            if(current_fitness > latest_best) determination(current_fitness, latest_best, temp_solution_vec, solution_vec);
            else if(current_fitness == latest_best) solution_vec = temp_solution_vec;
            else
            {
                double rand_annealing_rate = (double)rand() / (RAND_MAX + 1.0);
                double anneal_energy = exp((current_fitness - latest_best) / temperature_run);
                if(anneal_energy > rand_annealing_rate)
                {
                    latest_best = current_fitness;
                    solution_vec = temp_solution_vec;
                }
            }

            save_global_best(global_best, latest_best);
            average_best[current_evaluation] += global_best;
            current_evaluation++;
            // temperature_run = initial_temperature * (double)(num_evaluation - current_evaluation) / (double)num_evaluation;  // annealing
            temperature_run *= 0.9; // annealing
        }
        // write_best_file(way_method, global_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run, name_function);
    cout << "---DONE SA Onemax.---" << endl;
}

inline void SA::transition(v1i& temp_solution_vec)
{
    // random method
    if(!way_method.compare("SA_rand"))
    {
        int pick_random = rand() % num_bit;  // randomly pick a position to be changed
        if(temp_solution_vec[pick_random] == 0)   temp_solution_vec[pick_random] = 1;
        else temp_solution_vec[pick_random] = 0;
    }
    // left-right method
    else if(!way_method.compare("SA_left_right"))
    {
        if(temp_solution_vec[temp_solution_vec.size() - 1] == 0)    temp_solution_vec[temp_solution_vec.size() - 1] = 1;
        else    temp_solution_vec[temp_solution_vec.size() - 1] = 0;
    }
    else
    {
        cout << "Please check the method." << endl;
        exit(1);
    }
}
