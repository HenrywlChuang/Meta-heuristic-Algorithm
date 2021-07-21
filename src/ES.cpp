#include "ES.h"
#include "lib.h"

using namespace std;

ES::ES(int name_algo, int num_population, int num_evaluation, int num_run)
        :
        name_algo(name_algo),
        num_population(num_population),
        num_evaluation(num_evaluation),
        num_run(num_run)
{
        srand(time(0));
}

void ES::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Exhaustive Search."             << endl;
    cout << "Algo : "               << name_algo              << endl;
    cout << "Population : "         << num_population        << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    way_method = "ES";

    average_best.assign(num_evaluation, 0);
    // start
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        // initializtion
        initialization(population_vec, num_population);
        current_best = 0;
        // see_population_vec(population_vec);
        evaluation(global_one, population_vec);
        // cout << "START FROM number of bit : " << global_one << endl;
        // clock_t begin = clock();
       while(current_evaluation < num_evaluation)
        {
            transition();   // ES
            evaluation(global_one, population_vec);
            comparison(global_one, current_best);

            // check time
            // clock_t end = clock();
            // searching_secs = double(end - begin) / CLOCKS_PER_SEC;
            // if(searching_secs >= 10)  // executing time
            // {
            //     cout << "TIME'S UP." << endl;
            //     cout << "The current one." << endl;
            //     see_population_vec(population_vec);
            //     break;
            // }  
            average_best[current_evaluation] += current_best; 
            current_evaluation++;
            if(current_best == num_population)    break;
        }
        for(int j = current_evaluation; j < num_evaluation; j++)    average_best[j] += current_best; 

        // write into a file
        // write_best_file("ES", current_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run);
    cout << "---DONE ES.---" << endl;
}

void ES::transition()
{
    for(int i = population_vec.size() - 1; i >= 0; i--)
    {
        if(population_vec[i] == 0)
        {
            population_vec[i] = 1;
            break;
        }
        else    population_vec[i] = 0;
    }
}
