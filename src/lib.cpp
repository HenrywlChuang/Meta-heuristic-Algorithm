#include "lib.h"
// Class
Algo::Algo(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function)
        :
        name_algo(name_algo), num_bit(num_bit), num_evaluation(num_evaluation), num_run(num_run), name_function(name_function)
{
        srand(time(0));
}

// Function
void see_solution_v1i_vec(const v1i& solution_vec)
{
    for(int i = 0; i < (int)solution_vec.size(); i++)    cout << solution_vec[i];
    cout << endl;
}

void see_solution_v2i_vec(const v2i& solution_vec)
{
    cout << "Tabu list : " << endl;
    for(int i = 0; i < (int)solution_vec.size(); i++)
    {
        for(int j = 0; j < (int)solution_vec[i].size(); j++)    cout << solution_vec[i][j];
        cout << endl;
    }
}

int binary_to_decimal(const v1i& temp_solution_vec)
{
    int count = 0;  // decimal
    int solution_index = 0; // index of solution
    // cout << "---" << endl;
    // see_solution_v1i_vec(temp_solution_vec);
    for(int i = temp_solution_vec.size() - 1; i>= 0; i--)
    {
        count += temp_solution_vec[i] * pow(2, solution_index);
        solution_index++;
    }
    // cout << "Count : " << count << endl;
    return count;
}

void evaluation(int& current_fitness, const v1i& temp_solution_vec, const int& name_algo)
{
    if(name_algo == 1)  evaluation_onemax(current_fitness, temp_solution_vec);
    else if(name_algo == 2) evaluation_decption(current_fitness, temp_solution_vec);
    else
    {
        cout << "Please check the function." << endl;
        exit(0);
    }
}

void evaluation_onemax(int& current_fitness, const v1i& temp_solution_vec)
{
    current_fitness = 0;
    for(int i = 0; i < (int)temp_solution_vec.size(); i++)    if(temp_solution_vec[i] == 1) current_fitness++;
}

void evaluation_decption(int& current_fitness, const v1i& temp_solution_vec)
{
    current_fitness = 0;
    current_fitness = fabs(binary_to_decimal(temp_solution_vec) - pow(2, (temp_solution_vec.size() - 2)));
    // see_solution_v1i_vec(temp_solution_vec);
    // cout << current_fitness << endl; // check current_fitness
}

void write_best_file(const string& name_algo, const int& global_best)
{
    fstream file;
    string filename;
    filename = "result/txt/" + name_algo + ".txt";
    file.open(filename,  ios::out | ios::app);    // ios::app // open the existed one, not remove it    // ios::trunc   // remove the same name file, rewrite it again
    if(file.fail()) cout << "open failed" << endl;
    else
    {
        // file << "---" << endl;
        file << "### The maximum number of bit : " << global_best << " ###" <<endl;
    }    

    file << "---" << endl;
    file.close();
    cout << "---DONE Writing.---" << endl;
}

void write_average_file(const string& name_algo, const v1d& average_best, const int& num_run)
{
    fstream file;
    string filename;
    filename = "result/txt/" + name_algo + ".txt";
    file.open(filename,  ios::out | ios::app);    // ios::app // open the existed one, not remove it    // ios::trunc   // remove the same name file, rewrite it again
    if(file.fail()) cout << "open failed" << endl;
    else
    {
        // file << "---" << endl;
        file << "### The average number of bit in each evaluation ###" << endl;
		for(int i = 0; i < (int)average_best.size(); i++)	file << average_best[i] / num_run << endl;
    }    

    file << "---" << endl;
    file.close();
    cout << "---DONE Writing.---" << endl;
}

void initialization(v1i& solution_vec, const int& num_bit)
{
    solution_vec.assign(num_bit, 0);   // initial from all 0
    for(int i = 0; i < num_bit; i++)    solution_vec[i] = rand() % 2;		// initial by random
}

void determination(int& current_fitness, int& best_so_far, const v1i& temp_solution_vec, v1i& solution_vec)
{
    // compare
	if(current_fitness > best_so_far)
	{
		best_so_far = current_fitness;
        solution_vec = temp_solution_vec;
		// clock_t end = clock();
		// see_solution_v1i_vec(solution_vec);
		// searching_secs = double(end - begin) / CLOCKS_PER_SEC;
		// cout << current_fitness << endl;
        // cout << "yooooooo----" << endl;
		// cout << best_so_far << endl;
		// cout << searching_secs << " sec." << endl;
	}
}

void save_global_best(int& global_best, int& lastest_best)
{
    if(lastest_best >= global_best) global_best = lastest_best;
}
