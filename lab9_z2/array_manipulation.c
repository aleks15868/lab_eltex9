#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    unsigned char d_type;// file type (folder, file, etc.)
    char file[256];// File name
} file_directory_name;

/**
 * @brief Used to compare two elements
 * 
 * @param [in] file_one Const VOID, array elements
 * @param [in] file_two Const VOID, array elements
 * @return int Int(strcmp(file1->file, file2->file)), -1, if the first element is less than the second, 1, if the first element is greater than the second, 0 if they are equal
 */
int compare(const void *file_one, const void *file_two) {
    const file_directory_name *file1 = (const file_directory_name *)file_one;
    const file_directory_name *file2 = (const file_directory_name *)file_two;

    // first sorting by type (directory or files)
    if (file1->d_type != file2->d_type) {
        // If File1 is a directory, and File2 is a file, we place File1 in front of File2
        return (file1->d_type == DT_DIR) ? -1 : 1;
    }
    // If the types are the same, sort by alphabet
    return strcmp(file1->file, file2->file);
}
/**
 * @brief Creating an array along the folder path
 * 
 * @param [in,out] array file_directory_name*, an array of folders in the folder of the path
 * @param [in] way Char,the path to the folder
 * @param [in] Number int, code-in files in the folder
 */
file_directory_name* Add_Array(file_directory_name* array, char *way, int* Number)
{
    DIR *dir;
    struct dirent *entry;
    dir = opendir(way);// Record of all folder files
    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }
    *Number = 0;
    while ((entry = readdir(dir)) != NULL){// Record of all file files in array
        array = (file_directory_name*)realloc(array, (*Number + 1) * sizeof(file_directory_name));
        if (entry->d_type == DT_DIR){// if the element is the folder-> true
            strcpy(array[*Number].file, "/"); 
            strcat(array[*Number].file, entry->d_name);
        }
        else{
            strcpy(array[*Number].file, entry->d_name);
        }
        array[*Number].d_type = entry->d_type; 
        (*Number)++; // increase the value indicated by the pointer
    }

    array = (file_directory_name*)realloc(array, (*Number + 1) * sizeof(file_directory_name));

    closedir(dir);// Close the dirrotory
    // Sort an array using the compar comparison function
    qsort(array, *Number, sizeof(file_directory_name), compare);
    return array;
}
/**
 * @brief Bracing the line is dynamic
 * 
 * @param [in, out] StrMain Char, main line
 * @param [in] StrExtension Char, side line
 */
char* logic_for_path_add(char *StrMain, char *StrExtension){
    int StrMainLength = strlen(StrMain);// main line length
    int StrExtensionLength = strlen(StrExtension);// side line length
    StrMain = (char*)realloc(StrMain, (StrMainLength + StrExtensionLength + 1) * sizeof(char));// Selection of memory
    strcat(StrMain, StrExtension);// gluing lines
    return StrMain;
}
