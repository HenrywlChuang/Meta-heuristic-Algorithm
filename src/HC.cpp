#include "HC.h"
#include "lib.h"

using namespace std;

HC::HC(int name_algo, int num_bit, int num_evaluation, int num_run)
        :
        name_algo(name_algo),
        num_bit(num_bit),
        num_evaluation(num_evaluation),
        num_run(num_run)
{
        srand(time(0));
}

void HC::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Hill Climbing."                 << endl;
    cout << "Algo : "               << name_algo         << endl;
    cout << "Population : "         << num_bit           << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    way_method = "HC_rand"; // HC_rand or HC_left_right

    average_best.assign(num_evaluation, 0);
    // start
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        // initialization
        initialization(population_vec, num_bit);
        global_best = 0;
        // see_population_vec(population_vec);
        evaluation(current_one, population_vec);
        // cout << "START FROM number of bit : " << current_one << endl;

        // HC
        while(current_evaluation < num_evaluation)
        {
            v1i temp_population_vec = population_vec;
            transition(temp_population_vec);   // HC
            evaluation(current_one, temp_population_vec);
            determination(current_one, global_best, temp_population_vec, population_vec);
            average_best[current_evaluation] += global_best;
            current_evaluation++;
        }
        // write_best_file(way_method, global_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run);
    cout << "---DONE HC.---" << endl;
}

void HC::transition(v1i& temp_population_vec)
{
    // random method
    if(way_method.compare("HC_rand"))
    {
        int pick_random = rand() % num_bit;  // randomly pick a position to be changed
        if(temp_population_vec[pick_random] == 0)   temp_population_vec[pick_random] = 1;
        else temp_population_vec[pick_random] = 0;
    }
    // left-right method
    else if(way_method.compare("HC_left_right"))
    {
        if(temp_population_vec[temp_population_vec.size() - 1] == 0)    temp_population_vec[temp_population_vec.size() - 1] = 1;
        else    temp_population_vec[temp_population_vec.size() - 1] = 0;
    }
    else
    {
        cout << "Please check the method." << endl;
        exit(1);
    }
}
