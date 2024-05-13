typedef struct {
    unsigned char d_type; 
    char file[256];
} file_directory_name;
file_directory_name* Add_Array(file_directory_name* array, char *way, int* Number);//<-Used to compare two elements
char* logic_for_path_add(char *StrMain, char *StrExtension);//<-Creating an array along the folder path
char* logic_for_path(char *StrMain, char *StrExtension);//<-Bracing the line is dynamic