#include "PSO.h"
#include "lib.h"

using namespace std;

PSO::PSO(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function, int num_population, double w, double c1, double c2, int dimension)
        :
        Algo(name_algo, num_bit, num_evaluation, num_run, name_function), num_population(num_population), w(w), c1(c1), c2(c2), dimension(dimension)
{
        srand(time(0));
}

void PSO::main()
{
    cout << "---------------------"                      << endl;
    cout << "This is the Particle Swarm Optimization."   << endl;
    cout << "Algo : "               << name_algo         << endl;
    cout << "Particles : "               << num_population    << endl;
    cout << "Evaluation : "         << num_evaluation    << endl;
    cout << "W    : "               << w                 << endl;
    cout << "C1   : "               << c1                << endl;
    cout << "C2   : "               << c2                << endl;
    cout << "Dimension   : "        << dimension         << endl;
    way_method = "PSO";

    average_best.assign(num_evaluation, 0);
    set_boundary(upper_bound, lower_bound, name_function);
    real_global_best = DBL_MAX;
    /// start
    for(int i = 0; i < num_run; i++)
    {
        cout << "RUN : " << (i + 1) << endl;
        int current_evaluation = 0;
        // initialization
        initialization_PSO();
        evaluation_population_d(current_fitness_pop, solution_vec_pop_d, name_function);
        // see_solution_v2d_vec(solution_vec_pop_d);
        // see_solution_v1d_vec(current_fitness_pop);
        update_best();
        // see_solution_v1d_vec(global_best_particle);

        while(current_evaluation < num_evaluation)
        {
            // PSO
            movement();
            check_boundary();

            evaluation_population_d(current_fitness_pop, solution_vec_pop_d, name_function);
            update_best();
            for(int k = current_evaluation; k < (current_evaluation + num_population); k++)    average_best[k] += global_best;
            current_evaluation += num_population;
        }
        save_global_best_smallest(real_global_best, global_best);
        cout << "Best : " << global_best << endl;
        // write_best_file(way_method, global_best);
    }

    // write average into a file
    write_average_file(way_method, average_best, num_run, name_function);
    cout << "ALL Best : " << real_global_best << endl;
    cout << "---DONE PSO.---" << endl;
}

inline void PSO::initialization_PSO()
{
    solution_vec_pop_d.resize(num_population);
    velocity.resize(num_population);
    local_best_particle.clear();
    local_best_particle.resize(num_population, DBL_MAX);
    local_best_particle_pos.resize(num_population);
    global_best_particle_pos.resize(dimension);
    global_best = DBL_MAX;
    for(int i = 0; i < num_population; i++)
    {
        solution_vec_pop_d[i].resize(dimension);
        velocity[i].resize(dimension);
        local_best_particle_pos[i].resize(dimension);
        for(int j = 0; j < dimension; j++)
        {
            solution_vec_pop_d[i][j] = (double)rand() * (upper_bound - lower_bound) / (RAND_MAX) + lower_bound;
            velocity[i][j] = (double)rand() * (upper_bound - lower_bound) / (RAND_MAX) + lower_bound;
        }
    }
}

inline void PSO::update_best()
{
    for(int i = 0; i < (int)current_fitness_pop.size(); i++)
    {
        // each particle
        if(local_best_particle[i] > current_fitness_pop[i])
        {
            local_best_particle[i] = current_fitness_pop[i];
            local_best_particle_pos[i] = solution_vec_pop_d[i];
        }
        // global best
        if(global_best > local_best_particle[i])
        {
            global_best = local_best_particle[i];
            global_best_particle_pos = local_best_particle_pos[i];
        }
    }
}

inline void PSO::movement()
{
    for(int i = 0; i < num_population; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            velocity[i][j] = w * velocity[i][j] 
                            + c1 * ((double)rand() / (RAND_MAX)) * (local_best_particle_pos[i][j] - solution_vec_pop_d[i][j])
                            + c2 * ((double)rand() / (RAND_MAX)) * (global_best_particle_pos[j] - solution_vec_pop_d[i][j]);
            solution_vec_pop_d[i][j] = solution_vec_pop_d[i][j] + velocity[i][j];
        }
    }
}

inline void PSO::check_boundary()
{
    for(int i = 0; i < num_population; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            while(solution_vec_pop_d[i][j] > upper_bound)   solution_vec_pop_d[i][j] -= upper_bound;
            while(solution_vec_pop_d[i][j] < lower_bound)   solution_vec_pop_d[i][j] -= lower_bound;
        }
    }
}
