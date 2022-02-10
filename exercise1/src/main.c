#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* cur_timestamp() {
    time_t current_time;
    char* c_time_string;
    
    current_time = time(NULL);
    c_time_string = ctime(&current_time);

    return c_time_string;
}
int main () {
    char* time = cur_timestamp();
    printf("Welcome to the alarm clock! It is currently %s", time);
    printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)\n");
    
    while (1) {
        char character = getchar();
        while(getchar() != '\n');
        switch (character) {
            case 's':
                printf("Pressed s\n");
                break;
            case 'l':
                printf("Pressed l\n");
                break;
            case 'c':
                printf("Pressed c\n");
                break;
            case 'x':
                printf("Pressed x\n");
                printf("Goodbye!");
                exit(0);
            default: 
                printf("DEFAULT");
                break;
        }
    }
    return(0);
}

