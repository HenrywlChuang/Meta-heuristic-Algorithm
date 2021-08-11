#include "HC.h"
#include "lib.h"

using namespace std;

HC::HC(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function, string way_method)
        :
        Algo(name_algo, num_bit, num_evaluation, num_run, name_function)
{
        this->way_method = way_method;
        srand(time(0));
}

void HC::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Hill Climbing."                 << endl;
    cout << "Algo : "               << name_algo         << endl;
    cout << "Bits : "               << num_bit           << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    way_method = "HC" + way_method;
    cout << way_method << endl;
    // way_method = "HC_rand"; // HC_rand or HC_left_right

    average_best.assign(num_evaluation, 0);
    // start
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        // initialization
        initialization(solution_vec, num_bit);
        // see_solution_v1i_vec(solution_vec);
        evaluation(current_fitness, solution_vec, name_function);
        global_best = current_fitness;
        // cout << "START FROM number of bit : " << current_fitness << endl;

        // HC
        double latest_best = current_fitness;
        while(current_evaluation < num_evaluation)
        {
            v1i temp_solution_vec = solution_vec;
            transition(temp_solution_vec);   // HC
            evaluation(current_fitness, temp_solution_vec, name_function);
            determination(current_fitness, latest_best, temp_solution_vec, solution_vec);
            
            save_global_best(global_best, latest_best);
            average_best[current_evaluation] += global_best;
            current_evaluation++;
        }
        // write_best_file(way_method, global_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run, name_function);
    cout << "---DONE HC.---" << endl;
}

inline void HC::transition(v1i& temp_solution_vec)
{
    // random method
    if(!way_method.compare("HC_rand"))
    {
        int pick_random = rand() % num_bit;  // randomly pick a position to be changed
        if(temp_solution_vec[pick_random] == 0)   temp_solution_vec[pick_random] = 1;
        else temp_solution_vec[pick_random] = 0;
    }
    // left-right method
    else if(!way_method.compare("HC_left_right"))
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
