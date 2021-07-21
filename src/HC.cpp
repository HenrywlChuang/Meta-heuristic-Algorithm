#include "HC.h"
#include "lib.h"

using namespace std;

HC::HC(int name_algo, int num_population, int num_evaluation, int num_run)
        :
        name_algo(name_algo),
        num_population(num_population),
        num_evaluation(num_evaluation),
        num_run(num_run)
{
        srand(time(0));
}

void HC::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Hill Climbing."                 << endl;
    cout << "Algo : "               << name_algo              << endl;
    cout << "Population : "         << num_population        << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    way_method = "HC_left_right"; // HC_rand or HC_left_right

    average_best.assign(num_evaluation, 0);
    // start
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        // initialization
        initialization(population_vec, num_population);
        global_best = 0;
        // see_population_vec(population_vec);
        evaluation(current_one, population_vec);
        // cout << "START FROM number of bit : " << current_one << endl;

        // HC
        while(current_evaluation < num_evaluation)
        {
            transition();
            evaluation(current_one, population_vec);
            comparison(current_one, global_best);
            average_best[current_evaluation] += global_best;
            current_evaluation++;
        }
        // write_best_file(way_method, global_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run);
    cout << "---DONE HC.---" << endl;
}

void HC::transition()
{
    // random method
    if(way_method.compare("HC_rand"))
    {
        int pick_random = rand() % num_population;  // randomly pick a position to be changed
        if(population_vec[pick_random] == 0)   population_vec[pick_random] = 1;
        else population_vec[pick_random] = 0;
    }
    // left-right method
    else if(way_method.compare("HC_left_right"))
    {
        if(population_vec[population_vec.size() - 1] == 0)    population_vec[population_vec.size() - 1] = 1;
        else    population_vec[population_vec.size() - 1] = 0;
    }
    else
    {
        cout << "Please check the method." << endl;
        exit(1);
    }
}
