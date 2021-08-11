#include "Gnuplot.h"
#include "lib.h"

using namespace std;

Gnuplot::Gnuplot(int name_algo, int name_function)
        :
        name_algo(name_algo), name_function(name_function)
{
        srand(time(0));
}

void Gnuplot::main()
{
    cout << "---------------------"                  << endl;
    cout << "Start plotting the figure."             << endl;
    cout << "Please name the name of figure."        << endl;
    getline(cin, input_filename);
    fstream file;
    string sh_filename = "Gnuplot.sh";    // for sh file
    file.open(sh_filename,  ios::out | ios::trunc);    // ios::app // open the existed one, not remove it    // ios::trunc   // remove the same name file, rewrite it again
    if(!file)
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        // cout << "Opened file." << endl;
        file << "main=gnuplot"                 << endl;
        file << "filename=" + input_filename   << endl;;
        file << "$main result/gp/$filename.gp" << endl;
    }
    file.close(); 
    string gp_filename = "result/gp/" + input_filename + ".gp";    // for gp file
    file.open(gp_filename,  ios::out | ios::trunc);    // ios::app // open the existed one, not remove it    // ios::trunc   // remove the same name file, rewrite it again
    if(!file)
    {
        cout << "Cannot open file." << endl;
    }
    else
    {
        // cout << "Opened file." << endl;
        file << "reset" << endl;
        file << "set output '";
        file << "result/graph/" + input_filename + ".png'" << endl;
        file << "set xlabel \"Evaluation\"" << endl;
        file << "set ylabel \"Fitness\"" << endl;
        file << "set title \"" + input_filename + "\"" << endl;
        file << "set grid" << endl;
        file << "set term png enhanced font 'Verdana,10'" << endl;
    } 

    struct dirent *ptr;      
    DIR *dir;  
    string PATH = "./result/txt/";      // target file
    string name_function_string;
    if(name_function == 1)
    {
        name_function_string = "onemax/";
        PATH = "./result/txt/" + name_function_string;
    }
    else if(name_function == 2)
    {
        name_function_string = "deception/";
        PATH = "./result/txt/" + name_function_string;
    }
    else
    {
        cout << "Please check the function." << endl;
        exit(0);
    }
    dir = opendir(PATH.c_str());   
    vector<string> files;  
    // cout << "File list: "<< endl;
    while((ptr = readdir(dir)) != NULL)  
    {  
        // skip the two directories'.' and'..'
        if(ptr -> d_name[0] == '.')   continue;  
        //cout << ptr -> d_name << endl;  
        files.push_back(ptr -> d_name);  
    }  
    for (int i = 0; i < (int)files.size(); ++i)  
    {  
        if(i != 0)
        {
            file << "'result/txt/" + name_function_string + files[i] +"' title \"" + files[i] + "\" with lines,\\" << endl;
            // cout << files[i] << endl;  
        }
        else
        {
            file << "plot 'result/txt/" + name_function_string + files[i] +"' title \"" + files[i] + "\" with lines,\\" << endl;
            // cout << files[i] << endl;  
        }
    }  
    closedir(dir); 
    file.close();
    cout << "DONE Plotting." << endl;
}
