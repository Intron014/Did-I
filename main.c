#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct task{
    char task[50];
    struct tm time;
}TASK;



int main(){
    //TODO: File integration
    //FILE * thefile;
    //if(!thefile==(fopen("savedata.bin", "wb"))){
    //    printf("The file could not be opened");
    //    return 1;
    //}
    TASK tareas[100];
    TASK aux;
    int items=0;
    int i=0, answer=99;
    unsigned patata;
    while(answer){
        system("cls");
        printf("Did I...? vpc1.0\n");
        if(items){
            printf("----- Current Items (%i) -----\n", items);
            for(i=0;i<items;i++){
                printf("%i - %i:%i %i/%i/%i - %s\n", i, tareas[i].time.tm_hour, tareas[i].time.tm_min, tareas[i].time.tm_mday, tareas[i].time.tm_mon, tareas[i].time.tm_year+1900,  tareas[i].task);
            }
        }
        printf("----- Menu -----\n1 - Add a task\n2 - Edit a task\n3 - Delete a task\n0 - Exit\nSelect an option: ");
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
                    gets(&tareas[items].task);
                    items++;
                }
                else{
                    printf("Cannot add further tasks, please delete some to make room.");
                }
                break;
            case 2:
                //editatask();
                if(items){
                    char editanswer='y';
                    while(editanswer=='y'||editanswer=='Y'){
                        printf("Select task to edit: ");
                        scanf("%u", &patata);
                        if(patata<=items-1){
                            fflush(stdin);
                            printf("Introduzca nuevo nombre: ");
                            gets(&tareas[patata].task);
                        } else{
                            printf("No item :(\n");
                        }
                        printf("Desea editar otra tarea? (Y/N)");
                        scanf("%c", &editanswer);
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
            default:
                break;
        }
    }
    printf("Thanks for using \"Did I...?\"!");
    return 0;
}