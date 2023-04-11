#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct task{
    char task[50];
    struct tm time;
}TASK;



int main(){
    TASK tareas[100];
    int items=0, seconds=0;
    int i=0, answer=99;
    unsigned patata;
    while(answer){
        system("cls");
        if(items){
            if(items<10) {
                printf("----- Current Items (0%i) -----\n", items);
            }
            else{
                printf("----- Current Items (%i) -----\n", items);
            }
            for(i=0;i<items;i++){
                if(seconds==1){
                    if(i<10){
                        printf("0%i - %i:%i:%i %i/%i/%i - %s\n", i, tareas[i].time.tm_hour, tareas[i].time.tm_min, tareas[i].time.tm_sec, tareas[i].time.tm_mday, tareas[i].time.tm_mon, tareas[i].time.tm_year+1900,  tareas[i].task);

                    }
                    else{
                        printf("%i - %i:%i:%i %i/%i/%i - %s\n", i, tareas[i].time.tm_hour, tareas[i].time.tm_min, tareas[i].time.tm_sec, tareas[i].time.tm_mday, tareas[i].time.tm_mon, tareas[i].time.tm_year+1900,  tareas[i].task);
                    }
                }
                else {
                    if (i < 10) {
                        printf("0%i - %i:%i %i/%i/%i - %s\n", i, tareas[i].time.tm_hour, tareas[i].time.tm_min,
                               tareas[i].time.tm_mday, tareas[i].time.tm_mon, tareas[i].time.tm_year + 1900,
                               tareas[i].task);

                    } else {
                        printf("%i - %i:%i %i/%i/%i - %s\n", i, tareas[i].time.tm_hour, tareas[i].time.tm_min,
                               tareas[i].time.tm_mday, tareas[i].time.tm_mon, tareas[i].time.tm_year + 1900,
                               tareas[i].task);
                    }
                }
            }
        }
        printf("------------ Menu ------------\n1 - Add a task\n2 - Edit a task\n3 - Delete a task\n4 - Toggle seconds in tasks\n0 - Exit\nSelect an option: ");
        fflush(stdin);
        scanf("%i", &answer);
        switch (answer) {
            case 0:
                break;
            case 1:
                //addatask();
                if(items<100){
                    time_t t = time(NULL);
                    tareas[items].time = *localtime(&t);
                    printf("Introduzca what you did: ");
                    fflush(stdin);
                    gets(tareas[items].task);
                    items++;
                }
                else{
                    printf("Cannot add further tasks, please delete some to make room.");
                }
                break;
            case 2:
                //editatask();
                if(items){
                    printf("Select task to edit: ");
                    scanf("%u", &patata);
                    if(patata<=items-1){
                        fflush(stdin);
                        printf("Introduzca nuevo nombre: ");
                        gets(tareas[patata].task);
                        time_t t = time(NULL);
                        tareas[patata].time = *localtime(&t);
                    } else{
                        printf("No item :(\n");
                    }
                }
                else{
                    printf("No tasks to edit.\n");
                }
                break;
            case 3:
                //deleteatask();
                if(items){
                    printf("Select task to delete: ");
                    scanf("%u", &patata);
                    if(patata<=items-1){
                        fflush(stdin);
                        items--;
                        for(i=patata;i<items;i++){
                            tareas[i]=tareas[i+1];
                        }
                    }
                }
                break;
            case 4:
                if(seconds){
                    seconds=0;
                }
                else{
                    seconds=1;
                }
                break;
            default:
                break;
        }
    }
    printf("Thanks for using \"Did I...?\"!");
    return 0;
}