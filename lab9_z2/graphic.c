#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "arraymanipulation.h"
#include <wchar.h>
#define COLOR_DARK_GREEN 10
/**
 * @brief File manager basement output
 * 
 * @param [in] width Int,The number of strolts of the console
 */
void print_table_basement(int* width)
{
    int Deviation_width;//The initialization of the retreat for the column depends on the combination of the length of the console
    if (*width%2 == 0){
        Deviation_width = 2;
    }
    else
    {
        Deviation_width = 1;
    }
    printw("+");
    for (int i = 0; i< *width/2-Deviation_width; i++ ) printw("-");//Conclusion of the first part of the basement line
    if (*width%2==0) printw("+");
    printw("+");
    for (int i = 0; i< *width/2-Deviation_width; i++ ) printw("-");//Conclusion of the second part of the basement line
    printw("+");
};
/**
 * @brief Conclusion of file manager caps
 * 
 * @param [in] width Int, the number of strolts of the console
 */
void print_table_title(int* width)
{
    int Deviation_width;//The initialization of the retreat for the column depends on the combination of the length of the console
    if (*width%2 == 0){
        Deviation_width = 2;
    }
    else
    {
        Deviation_width = 1;
    }
    printw("+");
    for (int i = 0; i< *width/2-Deviation_width; i++ ) printw("-");//Conclusion of the first part of the basement line
    if (*width%2==0) printw("+");
    printw("+");
    for (int i = 0; i< *width/2-Deviation_width; i++ ) printw("-");//Conclusion of the second part of the basement line
    printw("+");
    printw("|");//Border of the first window
    for (int i = 0; i< *width/2-Deviation_width; i++ ){
        if(i == *width/4-2){//Miscalculation to be NAME in the middle
            printw("Name");
            i+=3;
        }
        else
        {
            printw(" ");
        }
    }
    if (*width%2==0) printw("|");
    printw("|");//Output of the border of the second window and the end of the first
    for (int i = 0; i< *width/2-Deviation_width; i++ ){
        if(i == *width/4-2){//Miscalculation to be NAME in the middle
            printw("Name");
            i+=3;
        }
        else
        {
            printw(" ");
        }
    }
    printw("|");//Border of the second window
    printw("+");
    for (int i = 0; i< *width/2-Deviation_width; i++ ) printw("-");
    if (*width%2==0) printw("+");
    printw("+");
    for (int i = 0; i< *width/2-Deviation_width; i++ ) printw("-");
    printw("+");
}
/**
 * @brief file manager's body output
 * 
 * @param [in] arrayWindowOne File_Directory_name*, an array of current folder files in the first window
 * @param [in] arrayWindowTwo File_Directory_name*, an array of current folder files in the second window
 * @param [in] width Int, the length of the console (number of columns)
 * @param [in] height Int, the height of the console (number of lines)
 * @param [in] y Int, the current coordinate of the folder that was chosen in one of the windows
 * @param [in] tub Int, switch between windows
 * @param [in] NumOne Int, the number of files in the first window
 * @param [in] NumTwo Int, the number of files in the second window
 * @param [in] misalignmentOne Int, the control of the shift of the array in the first window (for example, if the foldmarks and they all do not fit, the array begins to swing the array when we begin to go beyond the console)
 * @param [in] misalignmentTwo Int, control of the shift of the array in the second window (for example, if the foldmarks and they all do not fit, the array begins to be condemned when we start to go beyond the console)
 */
void print_table_body(file_directory_name* arrayWindowOne, file_directory_name* arrayWindowTwo, int* width, int* height, int* y, int* tub,int* NumOne,int* NumTwo, int* misalignmentOne, int* misalignmentTwo)
{
    int Deviation_width; // Variable declaration for column offset, depends on console width
    if (*width % 2 == 0){ // Checking if the width of the console is even
        Deviation_width = 2; // Setting the offset to 2 if width is even
    }
    else
    {
        Deviation_width = 1; // Setting the offset to 1 if width is odd
    }
    attron(COLOR_PAIR(2)); // Enabling color pair 2
    if(*tub == 0) mvhline(*y+3, 1, ' ', *width/2); else mvhline(*y+3, *width/2, ' ', *width/2); // Drawing a part of the folder selection window
    for (int elem_index=0; elem_index<*height-4; elem_index++)
    {   
        if (elem_index == *y && *tub == 0) attron(COLOR_PAIR(2)); else attron(COLOR_PAIR(1)); // Coloring based on conditions
        if (elem_index <= *NumOne){
            mvprintw(elem_index+3, 1,"%s",arrayWindowOne[elem_index+*misalignmentOne].file); // Printing file names from arrayWindowOne
        }
        if (elem_index == *y && *tub == 1) attron(COLOR_PAIR(2)); else attron(COLOR_PAIR(1)); // Coloring based on conditions
        if (elem_index <= *NumTwo){
            mvprintw(elem_index+3, *width/2+1,"%s",arrayWindowTwo[elem_index+*misalignmentTwo].file); // Printing file names from arrayWindowTwo
        }
        attron(COLOR_PAIR(1)); // Enabling color pair 1
        if (Deviation_width % 2 == 0) mvprintw(elem_index+3, *width/2-1, "|"); // Printing '|' if deviation width is even
        mvprintw(elem_index+3, 0, "|"); // Printing '|' at beginning of line
        mvprintw(elem_index+3, *width/2, "|"); // Printing '|' at half of the width
        mvprintw(elem_index+3, *width-1, "|"); // Printing '|' at end of line
    }

}

