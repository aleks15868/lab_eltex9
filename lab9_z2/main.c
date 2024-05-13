#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include "arraymanipulation.h"
#include "graphic.h"
#include <string.h>
#define COLOR_DARK_GREEN 10

int main(void) {
    setlocale(LC_ALL, ""); // Installation of the current local

    // The initialization of the screen
    initscr();
    
    // Do not display the introduced symbols
    curs_set(0); // Turning off the cursor
    noecho();
    
    // allow the use of arrows
    keypad(stdscr, TRUE);

    int Input, max_y;
    int misalignmentOne = 0, misalignmentTwo = 0;
    int y = 0;
    int tub = 0;

    // Demonstration of memory and initialization of variables for the first window
    char *directoryWindowOne = malloc(sizeof(char) * (strlen("/.") + 1));
    strcpy(directoryWindowOne, "/.");

    file_directory_name* arrayWindowOne = NULL;
    int NumWindowOne = 0;
    arrayWindowOne = Add_Array(arrayWindowOne, directoryWindowOne, &NumWindowOne);
    (NumWindowOne)--;

    // Demonstration of memory and initialization of variables for the second window
    char *directoryWindowTwo = malloc(sizeof(char) * (strlen("/.") + 1));
    strcpy(directoryWindowTwo, "/.");

    file_directory_name* arrayWindowTwo = NULL;
    int NumWindowTwo = 0;
    arrayWindowTwo = Add_Array(arrayWindowTwo, directoryWindowTwo, &NumWindowTwo);
    (NumWindowTwo)--;

    // Getting the size of the window
    int max_width, max_height;
    getmaxyx(stdscr, max_height, max_width);
    start_color();

    // Initialization of the color scheme
    init_color(COLOR_DARK_GREEN, 0, 149, 86); // rgb value for light green
    init_pair(2, COLOR_BLACK, COLOR_GREEN);   // dark green background
    init_pair(1, COLOR_WHITE, COLOR_DARK_GREEN); // light green background

    // endless cycle for reading keys
    do {
        // screen cleaning and table output
        wbkgd(stdscr, COLOR_PAIR(1));
        attron(COLOR_PAIR(1));
        clear();
        print_table_title(&max_width);
        print_table_body(arrayWindowOne, arrayWindowTwo, &max_width, &max_height, &y, &tub, &NumWindowOne, &NumWindowTwo, &misalignmentOne, &misalignmentTwo);
        print_table_basement(&max_width);

        Input = getch(); // Getting user input

        // Processing of pressing the key "Up"
        if (Input == KEY_UP) {
            if (y == 0) {
                if (tub == 0) {
                    if (misalignmentOne != 0) misalignmentOne--; 
                } else {
                    if (misalignmentTwo != 0) misalignmentTwo--; 
                }
            } else {
                y--;
            }
        }

        // Processing of pressing the key "down"
        if (Input == KEY_DOWN) {
            if (y != max_height - 5) {
                if (tub == 0) {
                    if (y >= NumWindowOne) y = NumWindowOne; else y++;
                } else {
                    if (y >= NumWindowTwo) y = NumWindowTwo; else y++;
                }
            } else {
                if (tub == 0) {
                    if ((y + misalignmentOne) < NumWindowOne - 1) misalignmentOne++; 
                } else {
                    if ((y + misalignmentTwo) < NumWindowTwo - 1) misalignmentTwo++; 
                }
            }
        }

        // Processing the key "Tab"
        if (Input == 9) tub = (tub + 1) % 2; 

        // Processing the key "Enter"
        if (Input == 10) {
            if (tub == 0) {
                directoryWindowOne = logic_for_path_add(directoryWindowOne, arrayWindowOne[y + misalignmentOne].file);
                arrayWindowOne = Add_Array(arrayWindowOne, directoryWindowOne, &NumWindowOne);
                misalignmentOne = 0;
            } else {
                directoryWindowTwo = logic_for_path_add(directoryWindowTwo, arrayWindowTwo[y + misalignmentTwo].file);
                arrayWindowTwo = Add_Array(arrayWindowTwo, directoryWindowTwo, &NumWindowTwo);   
                misalignmentTwo = 0;
            }
            y = 0;
        }
    } while (Input != 27); // Exit from the cycle when pressing the ESC key

    // Completion of work with ncurses and the release of memory
    endwin();
    free(arrayWindowOne);
    free(arrayWindowTwo);    
    free(directoryWindowOne);    
    free(directoryWindowTwo);
    return 0;
}

