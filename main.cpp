#include "header.h"

// using namespace std;
void detectCommand(vector<string>&);


    string home_directory_path;
    int home_path_len;
    string prev_dir;
    string history_path;
    int fg_pid=-1;

void c_signalHandler(int signal){
    cout<<endl;
    if(fg_pid==-1){
        return;
    }
    if(fg_pid > 0){
        if(kill(fg_pid, SIGINT) == -1){
            perror("Error killing process");
        }
        fg_pid = -1;
    }
}

int main(int argc, char* argv[]){

    prev_dir=pwd();
    filesystem::path executablePath = argv[0];
    filesystem::path absoluteExecutablePath = filesystem::absolute(executablePath);
    // Get the directory path containing the executable
    filesystem::path executableDirectory = absoluteExecutablePath.parent_path();

    home_directory_path=executableDirectory.string();
    home_path_len=home_directory_path.length()-2;
    home_directory_path=home_directory_path.substr(0,home_path_len);
    history_path = home_directory_path + "/" + ".history.txt";

    signal(SIGINT, c_signalHandler);

    while(true){
        // cout<<"argv[0]: "<<argv[0]<<endl;
        char *username = getlogin();
        if (username != nullptr) {
            cout <<username<<"@";
        } else {
            cerr << "Error getting username.";
        }
        char hostname[256];
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            cout <<hostname<<":";   
        } else {
            cerr << "Error getting hostname.";
        }
        // Get the path of the executable

        printCurrentDir(argv);

        char input[128];
        if(!cin.getline(input,128)){
            exit(1);
        }

        writeHistory(input);

        char* token;
        vector<string> arg;
        token=strtok(input,";");
        while(token!=NULL){
            // string s=token;
            arg.push_back(token);
            token=strtok(NULL,";");
        }

        int n= arg.size();
        for(int i=0;i<n;i++){
            pipeline(const_cast<char*>(arg[i].c_str()));
            
            // detectCommand(arg[i]);
        }

        
    }
    return 0;
}