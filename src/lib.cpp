#include "lib.h"
void see_popvec(v1i pop_vec)
{
    for(int i = 0; i < (int)pop_vec.size(); i++)    cout << pop_vec[i];
    cout << endl;
}

void evaluation(int& c_one, v1i pop_vec)
{
    c_one = 0;
    for(int i = 0; i < (int)pop_vec.size(); i++)    if(pop_vec[i] == 1) c_one++;
}

void w_file(string algo, int best)
{
    fstream file;
    string filename;
    filename = "result/" + algo + ".txt";
    file.open(filename,  ios::out | ios::trunc);    // ios::app // open the existed one, not remove it
    if(file.fail()) cout << "open failed" << endl;
    else
    {
        file << "---" << endl;
        file << "The maximum number of bit : " << best << endl;
    }    

    file << "---" << endl;
    file.close();
}
