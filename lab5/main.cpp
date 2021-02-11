#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <pthread.h>
#include <cstring>
#include "algo.h"
#include "arguments.h"

using namespace std;

void* calculate(void *args) {
    Arguments *newargs = (Arguments*) args;
    cout<<"Path: "<<" "<<newargs->directory<<endl; 
    result(newargs->directory, newargs->output);
    pthread_mutex_unlock(&(newargs->mutex));   
    return nullptr;
}
int main(int argc, char **argv)
{
    const char* directory = argv[1];
    string output = argv[2];
    Arguments args;
    args.output = output;
    ofstream fout(output);
    fout.close();
    
    vector<pthread_t> threads;
    args.mutex = PTHREAD_MUTEX_INITIALIZER;

    DIR *dp;
    struct dirent *dir;
    dp = opendir(directory);
    if (dp != NULL) {
        while (dir = readdir(dp)) {
            if (dir->d_type != DT_REG) 
                continue;           
            string dir_tmp = directory;
            dir_tmp += "/";
            dir_tmp += dir->d_name;       
            
            pthread_t thread;
            pthread_mutex_lock(&(args.mutex));
            cout<<dir_tmp<<endl;
            args.directory = dir_tmp;
            pthread_create(&thread, NULL, calculate, (void*)&args);
            threads.push_back(thread);            
        }
        closedir(dp);
    }
    else {
        cout<<"Couldn't open the directory!"<<endl;
    }

    void* res;
    for (auto t : threads) {
        pthread_join(t, &res);
    }
    pthread_mutex_destroy(&(args.mutex));
    return 0;
}