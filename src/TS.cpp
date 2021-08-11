#include "TS.h"
#include "lib.h"

using namespace std;

TS::TS(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function, string way_method)
        :
        Algo(name_algo, num_bit, num_evaluation, num_run, name_function)
{
        this->way_method = way_method;
        srand(time(0));
}

void TS::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Tabu Search."                   << endl;
    cout << "Algo : "               << name_algo         << endl;
    cout << "Bits : "               << num_bit           << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    way_method = "TS" + way_method;
    // way_method = "TS_rand"; // TS_rand or TS_left_right
	length_tabulist = 20;   // set by user
	tabulist_vec.resize(length_tabulist);

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

        // TS
		double latest_best = current_fitness;
        while(current_evaluation < num_evaluation)
        {
            v1i temp_solution_vec = solution_vec;
            transition(temp_solution_vec);
            evaluation(current_fitness, temp_solution_vec, name_function);
            if((current_fitness > latest_best) && (tabulist(temp_solution_vec)))	determination(current_fitness, latest_best, temp_solution_vec, solution_vec);

            save_global_best(global_best, latest_best);
			average_best[current_evaluation] += global_best;
            current_evaluation++;
			tabulist_vec.erase(tabulist_vec.begin());
			tabulist_vec.push_back(temp_solution_vec);
        }
        // write_best_file(way_method, global_best);
		// see_solution_v2i_vec(tabulist_vec);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run, name_function);
    cout << "---DONE TS.---" << endl;
}

inline bool TS::tabulist(const v1i& temp_solution_vec)	// check the current if in the tabulist
{
	for(int i = 0; i < (int)tabulist_vec.size(); i++)
	{
		if(tabulist_vec[i] == temp_solution_vec)	return false;
	}
	return true;
}

inline void TS::transition(v1i& temp_solution_vec)
{
    // random method
    if(!way_method.compare("TS_rand"))
    {
        int pick_random = rand() % num_bit;  // randomly pick a position to be changed
        if(temp_solution_vec[pick_random] == 0)   temp_solution_vec[pick_random] = 1;
        else temp_solution_vec[pick_random] = 0;
    }
    // left-right method
    else if(!way_method.compare("TS_left_right"))
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
