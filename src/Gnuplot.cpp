#include "Gnuplot.h"
#include "lib.h"

using namespace std;

Gnuplot::Gnuplot(int name_algo)
        :
        name_algo(name_algo)
{
        srand(time(0));
}

void Gnuplot::main()
{
    cout << "---------------------"                                                   << endl;
    cout << "Start plotting the figure."                                              << endl;
    cout << "Please name the name of figure."        << endl;
    getline(cin, input_filename);
    fstream file;
    string filename = "result/gp/" + input_filename + ".gp";
    file.open(filename,  ios::out | ios::app);    // ios::app // open the existed one, not remove it    // ios::trunc   // remove the same name file, rewrite it again
    if(!file)
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        cout << "Opened file." << endl;
        file << "reset" << endl;
        file << "set output '";
        file << "result/graph/" + input_filename + ".png'" << endl;
        file << "set xlabel \"Evaluation\"" << endl;
        file << "set ylabel \"Number of bit\"" << endl;
        file << "set title \"" + input_filename + "\"" << endl;
        file << "set grid" << endl;
        file << "set term png enhanced font 'Verdana,10'" << endl;
    } 
    cout << "Please name the file name that you want to plot. EXIT to finish."        << endl;
    getline(cin, input_filename);
    if(input_filename.compare("EXIT") != 0)
    {
        file << "plot 'result/txt/" + input_filename +".txt' title \""
            + input_filename + "\" with lines,\\" << endl;
        getline(cin, input_filename);
    }
    while(input_filename.compare("EXIT") != 0)
    {
        file << "'result/txt/" + input_filename +".txt' title \""
            + input_filename + "\" with lines,\\" << endl;
        getline(cin, input_filename);
    }
    file.close();
    cout << "DONE Plotting." << endl;
}
