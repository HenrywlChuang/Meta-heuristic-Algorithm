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
    for(int i = 0; i < (int)solution_vec.size(); i++)    cout << solution_vec[i] << " ";
    cout << endl;
}

void see_solution_v1d_vec(const v1d& solution_vec)
{
    for(int i = 0; i < (int)solution_vec.size(); i++)    cout << solution_vec[i] << " ";
    cout << endl;
}

void see_solution_v2i_vec(const v2i& solution_vec)
{
    for(int i = 0; i < (int)solution_vec.size(); i++)
    {
        for(int j = 0; j < (int)solution_vec[i].size(); j++)    cout << solution_vec[i][j] << " ";
        cout << endl;
    }
}

void see_solution_v2d_vec(const v2d& solution_vec)
{
    for(int i = 0; i < (int)solution_vec.size(); i++)
    {
        for(int j = 0; j < (int)solution_vec[i].size(); j++)    cout << solution_vec[i][j] << " ";
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

void evaluation_population(v1d& current_fitness_pop, const v2i& solution_vec_pop, const int& name_function)
{
    current_fitness_pop.resize(solution_vec_pop.size());
    for(int i = 0; i < (int)solution_vec_pop.size(); i++)    evaluation(current_fitness_pop[i], solution_vec_pop[i], name_function);
}

void evaluation_population_d(v1d& current_fitness_pop, const v2d& solution_vec_pop, const int& name_function)
{
    current_fitness_pop.resize(solution_vec_pop.size());
    for(int i = 0; i < (int)solution_vec_pop.size(); i++)    evaluation_d(current_fitness_pop[i], solution_vec_pop[i], name_function);
}

void evaluation_TSP(v1d& current_fitness_pop, const v2i& solution_vec_pop, const v2d& map_distance)
{
    current_fitness_pop.resize(solution_vec_pop.size());
    for(int i = 0; i < (int)solution_vec_pop.size(); i++)
    {
        double distance = 0;
        for(int j = 1; j < (int)solution_vec_pop[i].size(); j++)    distance += map_distance[solution_vec_pop[i][j - 1]][solution_vec_pop[i][j]];
        distance = distance + map_distance[solution_vec_pop[i][solution_vec_pop[i].size() - 1]][solution_vec_pop[i][0]];
        // cout << distance << endl;
        current_fitness_pop[i] = distance;
    }
}

void evaluation(double& current_fitness, const v1i& temp_solution_vec, const int& name_function)
{
    if(name_function == 1)  evaluation_onemax(current_fitness, temp_solution_vec);
    else if(name_function == 2) evaluation_deception(current_fitness, temp_solution_vec);
    else
    {
        cout << "Please check the function." << endl;
        exit(0);
    }
}

void evaluation_d(double& current_fitness, const v1d& temp_solution_vec, const int& name_function)
{
    if(name_function == 4)  evaluation_ackley(current_fitness, temp_solution_vec);
    else
    {
        cout << "Please check the function." << endl;
        exit(0);
    }
}

void evaluation_onemax(double& current_fitness, const v1i& temp_solution_vec)
{
    current_fitness = 0;
    for(int i = 0; i < (int)temp_solution_vec.size(); i++)    if(temp_solution_vec[i] == 1) current_fitness++;
    // cout << current_fitness << endl;
}

void evaluation_deception(double& current_fitness, const v1i& temp_solution_vec)
{
    current_fitness = 0;
    current_fitness = fabs(binary_to_decimal(temp_solution_vec) - pow(2, (temp_solution_vec.size() - 2)));
    // see_solution_v1i_vec(temp_solution_vec);
    // cout << current_fitness << endl; // check current_fitness
}

void evaluation_ackley(double& current_fitness, const v1d& temp_solution_vec)
{
    double result    = 0;
    double sig_x     = 0;
    double sig_cos_x = 0;
    for(int i = 0; i < (int)temp_solution_vec.size(); i++)
    {
        sig_x = sig_x + pow(temp_solution_vec[i], 2);
        sig_cos_x = sig_cos_x + cos(2 * M_PI * temp_solution_vec[i]);
    }
    // cout << i << ": " << endl;
    // cout << "Sig_x : " << sig_x << endl;
    // cout << "Sig_cos_x : " << sig_cos_x << endl;
    result = -20.0 * exp(-0.2 * sqrt((1.0 / (double)temp_solution_vec.size()) * sig_x))
                   - exp((1.0 / (double)temp_solution_vec.size()) * sig_cos_x)
                   + exp(1.0) + 20.0;
    // cout << "Result : " << result << endl;
    current_fitness = result;
}

void write_best_file(const string& name_algo, const double& global_best)
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

void write_average_file(const string& name_algo, const v1d& average_best, const int& num_run, const int& name_function)
{
    fstream file;
    string filename;
    if(name_function == 1)
    {
        filename = "result/txt/onemax/";
    }
    else if(name_function == 2)
    {
        filename = "result/txt/deception/";
    }
    else if(name_function == 3)
    {
        filename = "result/txt/tsp/";
    }
    else if(name_function == 4)
    {
        filename = "result/txt/ackley/";
    }
    else
    {
        cout << "Please check the function." << endl;
        exit(0);
    }
    filename = filename + name_algo + ".txt";
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

void initialization_population(v2i& solution_vec_pop, const int& num_bit, const int& num_population)
{
    solution_vec_pop.resize(num_population);
    for(int i = 0; i < num_population; i++)    initialization(solution_vec_pop[i], num_bit);
}

void initialization(v1i& solution_vec, const int& num_bit)
{
    solution_vec.assign(num_bit, 0);   // initial from all 0
    for(int i = 0; i < num_bit; i++)    solution_vec[i] = rand() % 2;		// initial by random
}

void initialization_population_TSP(v2i& solution_vec_pop, const int& num_population, const int& cities)
{
    solution_vec_pop.resize(num_population);
    for(int i = 0; i < num_population; i++)
    {
        v1i temp_solution_vec;
        v1b citiesHaveBeen;
        citiesHaveBeen.resize(cities, false);
        int cities_count = 0;
        while(cities_count < cities)
        {
            int city_position = rand() % cities;
            if(!citiesHaveBeen[city_position])
            {
                temp_solution_vec.push_back(city_position);
                citiesHaveBeen[city_position] = true;
                cities_count++;
            }
        }
        solution_vec_pop[i] = temp_solution_vec;
        temp_solution_vec.clear();
    }
}

void determination(double& current_fitness, double& best_so_far, const v1i& temp_solution_vec, v1i& solution_vec)
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
		// cout << best_so_far << endl;
		// cout << searching_secs << " sec." << endl;
	}
}

void save_global_best(double& global_best, double& latest_best)
{
    if(latest_best >= global_best) global_best = latest_best;
}

void save_global_best_smallest(double& global_best, double& latest_best)
{
    if(global_best >= latest_best) global_best = latest_best;
}

void save_global_best_TSP(double& global_best, double& latest_best, v1i& global_best_route, v1i& local_best_route) // check if the latest is shorter
{
    if(global_best >= latest_best)
    {
        global_best = latest_best;
        global_best_route = local_best_route;
    } 
}

void local_best_largest(const v1d& current_fitness_pop, double& local_best)  // find the best in this iteration
{
    local_best = *max_element(current_fitness_pop.begin(), current_fitness_pop.end());
}

void local_best_smallest(const v1d& current_fitness_pop, double& local_best)  // find the shortest route in this iteration
{
    local_best = *min_element(current_fitness_pop.begin(), current_fitness_pop.end());
}

void set_boundary(double& upper_bound, double& lower_bound, const int& name_function)
{
    if(name_function == 4)  // Ackley
    {
        upper_bound = 32.0;
        lower_bound = -32.0;
    }
}
