#include "testfile.h"
#include "lib.h"

using namespace std;

testfile::testfile(int algo, int population)
        :
        algo(algo),
        population(population)
{
        srand(time(0));
}

void testfile::algorithm()
{
    cout << "---------------------"                 << endl;
    cout << "This is the Testfile."                 << endl;
    cout << "Algo : "               << algo         << endl;
    cout << "Population : "         << population   << endl;

}
