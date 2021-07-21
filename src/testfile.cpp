#include "testfile.h"
#include "lib.h"

using namespace std;

testfile::testfile(int name_algo, int num_bit)
        :
        name_algo(name_algo),
        num_bit(num_bit)
{
        srand(time(0));
}

void testfile::main()
{
    cout << "---------------------"                     << endl;
    cout << "This is the Testfile."                     << endl;
    cout << "Algo : "               << name_algo        << endl;
    cout << "Population : "         << num_bit          << endl;

}
