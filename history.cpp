#include "header.h"

void history(int n){
    
    const char * history_path_char = history_path.c_str();
    ifstream history_obj;

    history_obj.open(history_path_char);

    if(!history_obj.is_open()){
        cerr << "Error opening history file" << endl;
        return;
    }
    string line;

    vector<string> arr;

    int i=0;

    while(i<n && getline(history_obj, line)){
        arr.push_back(line);
        // cout << line << endl;
        i++;
    }

    history_obj.close();
    int l=arr.size();
    for(i=l-1;i>=0;i--){
        cout<<arr[i]<<endl;
    }

    return;

}

void writeHistory(char input[]){
    // int fd_temp = open("temp_history.txt", O_RDONLY | O_CREAT | O_APPEND, 0777);
    // if(fd_temp == -1){
    //     perror("open");
    //     return;
    // }

    // ofstrem tem_obj;
    // temp_obj.open("temp_history.txt");

    // if(!temp_obj.is_open()){
    //     cerr << "error opening file";
    //     return;
    // }


    const char * history_path_char = history_path.c_str();
    int fd = open(history_path_char, O_RDONLY | O_CREAT | O_APPEND, 0777);
    if(fd==-1){
        perror("open");
        return;
    }

    ifstream history_obj;

    history_obj.open(history_path_char);

    if(!history_obj.is_open()){
        cerr << "Error opening history file" << endl;
        return;
    }

    // temp_obj << input;
    vector<string> arr;
    arr.push_back(input);

    string line;
    int i=0;
    while(i<19 && getline(history_obj, line)) {
        arr.push_back(line);
        i++;
    }

    history_obj.close();

    ofstream history_write;
    history_write.open(history_path_char);

    if(!history_write.is_open()){
        cerr << "Error opening history file" << endl;
        return;
    }

    int arr_size= arr.size();

    for(int i=0;i<arr_size;i++){
        history_write << arr[i]<< '\n';
    }

    history_write.close();
    return;    
    
}
