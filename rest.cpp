#include "header.h"

int rest(vector<string> &arg){
    pid_t pid= fork();
    fg_pid=pid;
    if (pid < 0) {
        cerr << "Fork failed." << endl;
        return 1;
    }

    if(pid==0){
        int n=arg.size();
        char* c_arg[n+1];
        for(int i=0;i<n;i++){
            c_arg[i]=const_cast<char*>(arg[i].c_str());  //arg[i].c_str();
            cout<<c_arg[i]<<" ";
        }
        c_arg[n]=NULL;
        if(execvp(c_arg[0], c_arg)==-1){

            cerr<<"Execution failed "<<c_arg[0]<<endl;
            exit(1);
        }
    }
    else{

        int status;
        // cout<<"child pid: "<<pid<<endl;
        wait(&status);
    }
    return 0;
}