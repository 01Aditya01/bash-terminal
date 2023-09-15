#include "header.h"

bool tokenize(char* input, vector<string> &command){
    char* token;
    token=strtok(input,"|");
    while(token!=NULL){
        // string s=token;
        command.push_back(token);
        token=strtok(NULL,"|");
    }
    if(command.size()>1) return true;
    return false;
}

void pipeline(char* arg){

    int fd[2];
	pid_t pid;
	int fd_read = 0;

    vector<string> command;
    if(!tokenize(arg, command)){
        redirection(const_cast<char*>(command[0].c_str()));
        return;
    }
    
    int n=command.size();
    int i=0;
    while (i<n){
		pipe(fd);				/* Sharing bidiflow */
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(fd_read, 0);
			if (i<n-1) {
				dup2(fd[1], 1);
			}
			close(fd[0]);
            redirection(const_cast<char*>(command[i].c_str()));
			// execvp((*cmd)[0], *cmd);
			exit(1);
		}
		else {
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			fd_read = fd[0];
			i++;
		}
	}

}


/*
bool pipeline(vector<string> &arg){
    
    int n=arg.size();
    bool flag=false;
    for(int i=0;i<n;i++){
        if(arg[i]=="|"){
            cout<<"inside pipe"<<endl;
            flag =true;
            int pipe_fd[2];
            if(pipe(pipe_fd) == -1){
                perror("pipe");
                return false;
            }

            pid_t pid= fork();
            if (pid == -1) {
                perror("fork");
                return false;
            }
            else if(pid==0){
                close(pipe_fd[1]);
                vector<string> new_arg(arg.begin()+i+1, arg.end());
                dup2(pipe_fd[0],STDIN_FILENO);
                pipeline(new_arg);
                close(pipe_fd[0]);
                exit(1);
            }
            else if(pid>0){
                close(pipe_fd[0]);
                vector<string> new_arg(arg.begin(), arg.begin()+i);
                dup2(pipe_fd[1],STDOUT_FILENO);
                redirection(new_arg);
                close(pipe_fd[1]);
            }
            break;
        }
        else if(i==n-1 && !flag){
            return redirection(arg);
        }
    }
    return flag;
    
}
*/