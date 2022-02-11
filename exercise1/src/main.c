#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

typedef struct alarm_t {
    time_t ring_time;
    char timestamp[20];
    int PID;
} alarm_t;

alarm_t alarms[100];
int alarms_i = 0;

char* cur_timestamp() {
    time_t current_time;
    char* c_time_string;
    
    current_time = time(NULL);
    c_time_string = ctime(&current_time);

    return c_time_string;
}

int main () {
    char* current_time = cur_timestamp();
    printf("Welcome to the alarm clock! It is currently %s", current_time);
    printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)\n");
    
    while (1) {
        char character = getchar();
        while(getchar() != '\n');
        printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)\n");
        switch (character) {
            case 's':
            {
                struct tm user_schedule;
                time_t alarm_time;
                char buffer[20];

                printf("Pressed s\n");
                printf("Schedule alarm at which date and time? ");
                
                //gets user input on format yyyy-mm-dd hh:mm:ss
                scanf("%d-%d-%d %d:%d:%d", &user_schedule.tm_year, &user_schedule.tm_mon, &user_schedule.tm_mday, 
                &user_schedule.tm_hour, &user_schedule.tm_min, &user_schedule.tm_sec );

                //corrects for start of unix time
                user_schedule.tm_year -= 1900;
                user_schedule.tm_mon -=1;
                user_schedule.tm_isdst = -1;
                //user_schedule.tm_hour +=1;
                alarm_time = mktime(&user_schedule);

                //finds time until alarm goes off
                time_t alarm_delay = alarm_time - time(NULL); 

                //converts to user readable format and displays
                strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", localtime(&alarm_time));
                printf("You entered %s \n", buffer);
                printf("Scheduling alarm in %ld seconds \n", alarm_delay);
                
                // create alarm type and update list of alarms
                alarm_t alarm;
                alarm.ring_time = alarm_time;
                strcpy(alarm.timestamp, buffer);
                alarms[alarms_i] = alarm;
                alarms_i += 1;

                //forking processes for alarms, each process handles one alarm
                int pid;
                pid = fork();
                if(pid == 0){
                    int child_pid = getpid();
                    alarm.PID = child_pid;
                    sleep(alarm_delay);
                    printf("RING!!\n");
                    exit(0);
                }

                break;
            }
            case 'l':
            {
                for (int i=0;i<alarms_i;i++) {
                    printf("Alarm %d: %s\n",i, alarms[i].timestamp);
                }
                break;
            }                
            case 'c': 
            {
                int del_index;
                scanf("%d", &del_index);
                printf("%d\n", del_index);

                break;
            }
            case 'x':
                printf("Pressed x\n");
                printf("Goodbye!\n");
                exit(0);
            default: 
                printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)\n");
                break;
        }
    }
    return(0);
}

