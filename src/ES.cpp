#include "ES.h"
#include "lib.h"

using namespace std;

ES::ES(int algo, int population)
        :
        algo(algo),
        population(population)
{
        srand(time(0));
}

void ES::algorithm()
{
    cout << "---------------------"                 << endl;
    cout << "This is the Exhaustive Search."        << endl;
    cout << "Algo : "               << algo         << endl;
    cout << "Population : "         << population   << endl;

    pop_vec.assign(population, 0);
    n_best = 0;
    see_popvec(pop_vec);
    evaluation(c_one, pop_vec);
    cout << "START FROM number of bit : " << c_one << endl;

    // start
    clock_t begin = clock();
    while(n_best < population)
    {
        for(int i = pop_vec.size() - 1; i >= 0; i--)
        {
            if(pop_vec[i] == 0)
            {
                pop_vec[i] = 1;
                break;
            }
            else    pop_vec[i] = 0;
        }
        evaluation(c_one, pop_vec);

        // compare
        if(c_one > n_best)
        {
            n_best = c_one;
            // clock_t end = clock();
            // see_popvec(pop_vec);
            // searching_secs = double(end - begin) / CLOCKS_PER_SEC;
            cout << c_one << endl;
            // cout << searching_secs << " sec." << endl;
        }

        // check time
        clock_t end = clock();
        searching_secs = double(end - begin) / CLOCKS_PER_SEC;
        if(searching_secs >= 10)  // executing time
        {
            cout << "TIME'S UP." << endl;
            cout << "The current one." << endl;
            see_popvec(pop_vec);
            break;
        }   
    }

    // write into a file
    w_file("ES", n_best);
    cout << "---DONE ES.---" << endl;
}