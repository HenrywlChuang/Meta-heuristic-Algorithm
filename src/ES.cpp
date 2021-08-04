#include "ES.h"
#include "lib.h"

using namespace std;

ES::ES(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function)
        :
        Algo(name_algo, num_bit, num_evaluation, num_run, name_function)
{
        srand(time(0));
}

void ES::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Exhaustive Search."             << endl;
    cout << "Algo : "               << name_algo         << endl;
    cout << "Bits : "               << num_bit           << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    way_method = "ES";

    average_best.assign(num_evaluation, 0);
    // start
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        // initializtion
        initialization(solution_vec, num_bit);
        // see_solution_v1i_vec(solution_vec);
        evaluation(current_fitness, solution_vec, name_algo);
        global_best = current_fitness;
        // cout << "START FROM number of bit : " << current_fitness << endl;
        // clock_t begin = clock();
        // while(1) // For exhaustive
        while(current_evaluation < num_evaluation)   // For limited times
        {
            v1i temp_solution_vec = solution_vec;
            transition();   // ES
            evaluation(current_fitness, solution_vec, name_function);
            determination(current_fitness, global_best, temp_solution_vec, solution_vec);
            // check time
            // clock_t end = clock();
            // searching_secs = double(end - begin) / CLOCKS_PER_SEC;
            // if(searching_secs >= 10)  // executing time
            // {
            //     cout << "TIME'S UP." << endl;
            //     cout << "The current one." << endl;
            //     see_solution_v1i_vec(solution_vec);
            //     break;
            // }  
            average_best[current_evaluation] += global_best; 
            current_evaluation++;
            if(global_best == num_bit)    break;
        }
        for(int j = current_evaluation; j < num_evaluation; j++)    average_best[j] += global_best; 

        // write into a file
        // write_best_file("ES", global_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run);
    cout << "---DONE ES.---" << endl;
}

void ES::transition()
{
    for(int i = solution_vec.size() - 1; i >= 0; i--)
    {
        if(solution_vec[i] == 0)
        {
            solution_vec[i] = 1;
            break;
        }
        else    solution_vec[i] = 0;
    }
}
