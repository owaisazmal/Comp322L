//Comp322L
//Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
// declare global variables including a table structure to hold scheduling information
// optional: define a function that finds the maximum of two integers

typedef struct {
    int total_cpu;
    int totalRemainT;
    int arrvl;
    int strtTime;
    int id;
    int trnarndTime;
    int done;
    int endTime;
    int AlrdStarted;
} Process;

Process *processes = NULL;

int num_processes = 0;

//***************************************************************
void ShowCntent() {
    printf("Enter total number of processes: ");
    scanf("%d", &num_processes);
    processes = (Process *)malloc(num_processes * sizeof(Process));

    for (int i = 0; i < num_processes; i++) {
      
      processes[i].id = i;
      
      
      printf("Enter arrival cycle for process %d: ", i);
        scanf("%d", &processes[i].arrvl);
      
      printf("Enter total cycles for process %d: ", i);
      
      scanf("%d", &processes[i].total_cpu);

      processes[i].totalRemainT = processes[i].total_cpu;

      processes[i].done = 0;
      
      processes[i].AlrdStarted = 0;
    }
}
//***************************************************************
// declare local variables ---Done
// print table header  --Done
// for each process    --Done
// print the contents  --Done
void printTable() {
    printf("PID Arrival Total Start End Turnaround\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < num_processes; i++) {
        
      printf("  %d   %d      %d ", processes[i].id, processes[i].arrvl, processes[i].total_cpu);
      
      if (processes[i].done) {
             
          printf("   %d     %d      %d\n", processes[i].strtTime, processes[i].endTime, processes[i].trnarndTime);
      
      } else {
      
        printf("           \n");
        }
    }
}

//***************************************************************
//void "PROCEDURE FOR OPTION #2"()
void scheduleFIFO() {
  
  int currentTime = 0;
    
  for (int i = 0; i < num_processes; i++) {
      
      if (currentTime < processes[i].arrvl) {
      
        currentTime = processes[i].arrvl;
        }
      
      processes[i].strtTime = currentTime;
      
      currentTime += processes[i].total_cpu;
      
      processes[i].endTime = currentTime;

      processes[i].trnarndTime = processes[i].endTime - processes[i].arrvl;
        processes[i].done = 1;
    }
}

//Test case for GDB 
// int compare(const void *a, const void *b) {
//     Process *processA = (Process *)a;
//     Process *processB = (Process *)b;
//     if (processA->arrvl == processB->arrvl) {
        
//         return processA->total_cpu - processB->total_cpu;
//     }
//     // Otherwise
//     return processA->arrvl - processB->arrvl;
// }

//***************************************************************
//void "PROCEDURE FOR OPTION #3"()

void scheduleSJF() {
  
    int completed[num_processes];
    for (int i = 0; i < num_processes; i++) {
        completed[i] = 0; //Error
    }

    int currentTime = 0, totalCompleted = 0;

    while (totalCompleted < num_processes) {
        int shortestJobIndex = -1;
        int shortestTime = INT_MAX;

        
        for (int i = 0; i < num_processes; i++) {
            if (!completed[i] && processes[i].arrvl <= currentTime && processes[i].total_cpu < shortestTime) {
                shortestJobIndex = i;
                shortestTime = processes[i].total_cpu;
            }
        }

       
        if (shortestJobIndex == -1) {
            currentTime++;
            continue;
        }

        Process *p = &processes[shortestJobIndex];
        p->strtTime = currentTime;
        currentTime += p->total_cpu; 
        p->endTime = currentTime;
        p->trnarndTime = p->endTime - p->arrvl;
        completed[shortestJobIndex] = 1;
        totalCompleted++;
    }
}
//***************************************************************
//void "PROCEDURE FOR OPTION #4"()

void scheduleSRT() {

    for (int i = 0; i < num_processes; i++) {
        processes[i].done = 0;
        processes[i].totalRemainT = processes[i].total_cpu;
        processes[i].AlrdStarted = 0;
    }

    int currentTime = 0, completedProcesses = 0;
    while (completedProcesses < num_processes) {
 
        int idx = -1;
        int shortestTime = INT_MAX;
        for (int i = 0; i < num_processes; i++) {
            if (!processes[i].done && processes[i].arrvl <= currentTime && processes[i].totalRemainT < shortestTime) 
            {
                shortestTime = processes[i].totalRemainT;
                idx = i;
            }
        }

        if (idx != -1) {

            if (!processes[idx].AlrdStarted) {
                processes[idx].strtTime = currentTime;
                processes[idx].AlrdStarted = 1;
            }


            processes[idx].totalRemainT--;
            currentTime++;


            if (processes[idx].totalRemainT == 0) {
                processes[idx].done = 1;
                processes[idx].endTime = currentTime;
                processes[idx].trnarndTime = processes[idx].endTime - processes[idx].arrvl;
                completedProcesses++;
            }
        } else {

            currentTime++;
        }
    }
}
//*************************************************************
//void "PROCEDURE FOR OPTION #5"() {

void quitandFreeMem() {
    if (processes != NULL) {
        free(processes);
    }
    printf("Quitting program....\n");
}

//*************************************************************
// Main function
int main() {
  
    int selection;
    do {
        printf("Batch scheduling\n----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Schedule processes with SRT algorithm\n");
        printf("5) Quit and free memory\n");
        printf("Enter selection: ");
        scanf("%d", &selection);

        switch(selection) {
            case 1:
              
                ShowCntent();
                printTable();
                break;
            case 2:
              
                scheduleFIFO();
                printTable();
                break;
            case 3:
              
                scheduleSJF();
                printTable();
                break;
            case 4:
              
                scheduleSRT();
                printTable();
            break;
  
            case 5:
              
                quitandFreeMem();
                break;
            default:
              
                printf("Invalid Number. Please enter a number between 1 and 5.\n");
        }
    } while(selection != 5);

    return 0;
}
//*************************************************************
//End Code
