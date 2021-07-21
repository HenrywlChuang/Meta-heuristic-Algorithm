#include "testfile.h"
#include "lib.h"

using namespace std;

testfile::testfile(int name_algo, int num_population)
        :
        name_algo(name_algo),
        num_population(num_population)
{
        srand(time(0));
}

void testfile::main()
{
    cout << "---------------------"                     << endl;
    cout << "This is the Testfile."                     << endl;
    cout << "Algo : "               << name_algo        << endl;
    cout << "Population : "         << num_population   << endl;

}
