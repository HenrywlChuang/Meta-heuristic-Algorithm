#include "lib.h"
void see_population_vec(v1i population_vec)
{
    for(int i = 0; i < (int)population_vec.size(); i++)    cout << population_vec[i];
    cout << endl;
}

void evaluation(int& current_one, v1i temp_population_vec)
{
    current_one = 0;
    for(int i = 0; i < (int)temp_population_vec.size(); i++)    if(temp_population_vec[i] == 1) current_one++;
}

void write_best_file(string name_algo, int global_best)
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

void write_average_file(string name_algo, v1d average_best, int num_run)
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

void initialization(v1i& population_vec, int num_bit)
{
    population_vec.assign(num_bit, 0);   // initial from all 0
    for(int i = 0; i < num_bit; i++)    population_vec[i] = rand() % 2;		// initial by random
}

void determination(int& current_one, int& global_best, v1i temp_population_vec, v1i& population_vec)
{
    // compare
	if(current_one > global_best)
	{
		global_best = current_one;
        population_vec = temp_population_vec;
		// clock_t end = clock();
		// see_population_vec(population_vec);
		// searching_secs = double(end - begin) / CLOCKS_PER_SEC;
		// cout << current_one << endl;
		cout << global_best << endl;
		// cout << searching_secs << " sec." << endl;
	}
}
