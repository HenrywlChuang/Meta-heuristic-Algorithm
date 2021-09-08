#include "ACO.h"
#include "lib.h"

using namespace std;

ACO::ACO(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function, int num_population, double alpha, double beta, double rho, double q, string dataset)
        :
        Algo(name_algo, num_bit, num_evaluation, num_run, name_function), num_population(num_population), alpha(alpha), beta(beta), rho(rho), q(q), dataset(dataset)
{
        srand(time(0));
}

void ACO::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Ant colony system."             << endl;
    cout << "Algo : "               << name_algo         << endl;
    cout << "Ants : "               << num_population    << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    cout << "Alpha   : "            << alpha             << endl;
    cout << "Beta    : "            << beta              << endl;
    cout << "Rho     : "            << rho               << endl;   // the rate that how fast the pheromones decrease
    cout << "Q       : "            << q                 << endl;   // the total amount of the pheromones that will be assigned
    cout << "Dataset : "            << dataset           << endl;
    way_method = "ACO";

    average_best.assign(num_evaluation, 0);
    calculate_map();
    // check coordinate and map distance infomation.
    // see_solution_v2d_vec(coordinate);
    // see_solution_v2d_vec(map_distance);
    // start
    real_global_best = DBL_MAX;
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        // initialization
        initialization_pheromones();
        // see_solution_v2d_vec(table_pheromones);
        initialization_population_TSP(solution_vec_pop, num_population, coordinate.size());
        evaluation_TSP(current_fitness_pop, solution_vec_pop, map_distance);
        // see_solution_v2i_vec(solution_vec_pop);
        local_best_smallest(current_fitness_pop, local_best);
        f_local_best_route();
        global_best_route = local_best_route;
        global_best = local_best;
        update_global_pheromones();

        while(current_evaluation < num_evaluation)
        {
            // ACO
            for(int no_ant = 0; no_ant < num_population; no_ant++)
            {
                v1i ant_route;
                walking(ant_route);
                update_local_pheromones(ant_route);
                solution_vec_pop[no_ant] = ant_route;
            }

            // record information
            evaluation_TSP(current_fitness_pop, solution_vec_pop, map_distance);
            local_best_smallest(current_fitness_pop, local_best);
            f_local_best_route();
            save_global_best_TSP(global_best, local_best, global_best_route, local_best_route);
            for(int k = current_evaluation; k < (current_evaluation + num_population); k++)    average_best[k] += global_best;
            current_evaluation += num_population;

            // ACO
            update_global_pheromones();
        }
        save_global_best_TSP(real_global_best, global_best, real_global_best_vector, global_best_route);    // for all runs
        cout << "Best : " << global_best << endl;
        // see_solution_v1i_vec(global_best_route);
        // write_best_file(way_method, global_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run, name_function);
    // see_solution_v1i_vec(real_global_best_vector);
    plot_the_best_route();
    cout << "ALL Best : " << real_global_best << endl;
    cout << "---DONE ACO.---" << endl;
}

inline void ACO::calculate_map()
{
    string buffer;
    fstream file;
    string filename = "dataset/" + dataset;
    file.open(filename, ios::in);
    if(file)
    {
        double doubleFromFile = 0.0;
        do
        {
            getline(file, buffer);
            stringstream ss(buffer);
            v1d temp_coordinate;
            while(ss >> doubleFromFile) temp_coordinate.push_back(doubleFromFile);  // if ss is the double
            if(temp_coordinate.size() > 0)  coordinate.push_back(temp_coordinate);
            temp_coordinate.clear();
        }while(!file.eof());
        file.close();
    } 
    else 
    {
        cout << "Please check the dataset." << endl; 
        exit(0);
    }
    for(int i = 0; i < (int)coordinate.size(); i++)
    {
        v1d temp_map_distance;
        for(int j = 0; j < (int)coordinate.size(); j++)
        {
            double distance;
            if(i != j)
            {
                double x1 = coordinate[i][1];
                double y1 = coordinate[i][2];
                double x2 = coordinate[j][1];
                double y2 = coordinate[j][2];
                distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
            }
            else    distance = DBL_MAX;
            temp_map_distance.push_back(distance);
        }
        map_distance.push_back(temp_map_distance);
        temp_map_distance.clear();
    }
}

inline void ACO::initialization_pheromones()
{
    table_pheromones.resize(coordinate.size());
    for(int i = 0; i < (int)coordinate.size(); i++)
    {
        v1d temp_pheromones;
        for(int j = 0; j < (int)coordinate.size(); j++)
        {
            if(i == j)  temp_pheromones.push_back(DBL_MAX);
            else    temp_pheromones.push_back(0.00001);
        }
        table_pheromones[i] = temp_pheromones;
    }
}

inline void ACO::update_local_pheromones(const v1i& ant_route)
{
    // the pheromones of the each route will be focused

    for(int i = 1; i < (int)coordinate.size(); i++)
    { 
        table_pheromones[ant_route[i - 1]][ant_route[i]] = (1 - rho) * table_pheromones[ant_route[i - 1]][ant_route[i]] + rho * 0.00001;
        table_pheromones[ant_route[i]][ant_route[i - 1]] = (1 - rho) * table_pheromones[ant_route[i]][ant_route[i - 1]] + rho * 0.00001;
    }
    table_pheromones[ant_route[coordinate.size() - 1]][ant_route[0]] = (1 - rho) * table_pheromones[ant_route[coordinate.size() - 1]][ant_route[0]] + rho * 0.00001;
    table_pheromones[ant_route[0]][ant_route[coordinate.size() - 1]] = (1 - rho) * table_pheromones[ant_route[0]][ant_route[coordinate.size() - 1]] + rho * 0.00001;
}

inline void ACO::update_global_pheromones()
{
    // the pheromones will decrease through every iteration
    // the pheromones of the global best route will be focused

    for(int i = 0; i < (int)coordinate.size(); i++)
    {
        for(int j = 0; j < (int)coordinate.size(); j++) table_pheromones[i][j] = table_pheromones[i][j] * (1 - rho);
        if(i != 0)
        {
            table_pheromones[global_best_route[i - 1]][global_best_route[i]] = (1 - rho) * table_pheromones[global_best_route[i - 1]][global_best_route[i]] + rho * pow(global_best, -1);
            table_pheromones[global_best_route[i]][global_best_route[i - 1]] = (1 - rho) * table_pheromones[global_best_route[i]][global_best_route[i - 1]] + rho * pow(global_best, -1);
        }
    }
    table_pheromones[global_best_route[coordinate.size() - 1]][global_best_route[0]] = (1 - rho) * table_pheromones[global_best_route[coordinate.size() - 1]][global_best_route[0]] + rho * pow(global_best, -1);
    table_pheromones[global_best_route[0]][global_best_route[coordinate.size() - 1]] = (1 - rho) * table_pheromones[global_best_route[0]][global_best_route[coordinate.size() - 1]] + rho * pow(global_best, -1);
}

inline void ACO::f_local_best_route()
{
    int local_best_route_position = 0;
    for(int i = 0; i < (int)current_fitness_pop.size(); i++)
    {
        if(local_best == current_fitness_pop[i])
        {
            local_best_route_position = i;
            break;
        }
    }
    local_best_route = solution_vec_pop[local_best_route_position];
}

inline void ACO::walking(v1i& ant_route)
{
    v1b have_been_city;
    have_been_city.resize(coordinate.size(), false);
    int first_city = rand() % coordinate.size();
    ant_route.push_back(first_city);
    have_been_city[first_city] = true;
    int count_cities = 1;
    while(count_cities < (int)coordinate.size())
    {
        double total_probability = 0;
        // count the total base
        for(int i = 0; i < (int)coordinate.size(); i++)
        {
            if(!have_been_city[i])  total_probability += pow(table_pheromones[ant_route.back()][i], alpha) * pow((1 / map_distance[ant_route.back()][i]), beta);
        }
        // check which is picked
        double rand_rate = (double)total_probability * rand() / RAND_MAX;
        int next_city = 0;
        while(rand_rate >= 0)
        {
            if(!have_been_city[next_city])  rand_rate -= pow(table_pheromones[ant_route.back()][next_city], alpha) * pow((1 / map_distance[ant_route.back()][next_city]), beta);
            next_city++;
        }
        next_city--;
        // save the what it is picked
        ant_route.push_back(next_city);
        have_been_city[next_city] = true;
        count_cities++;
    }
}

inline void ACO::plot_the_best_route()
{
    fstream file;
    string route_filename = "result/txt/tsp/ACO_route.txt";    
    file.open(route_filename,  ios::out | ios::trunc);    // ios::app // open the existed one, not remove it    // ios::trunc   // remove the same name file, rewrite it again
    if(!file)
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        // cout << "Opened file." << endl;
        file << "### The best route, " << "the distance is " << real_global_best << " ###" << endl;
        for(int i = 0; i < (int)real_global_best_vector.size(); i++)    file << coordinate[real_global_best_vector[i]][1] << " " << coordinate[real_global_best_vector[i]][2] << endl;
        file << coordinate[real_global_best_vector[0]][1] << " " << coordinate[real_global_best_vector[0]][2] << endl;
    }
    file.close(); 
}
