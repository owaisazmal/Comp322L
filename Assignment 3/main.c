#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Owais Khan
// Comp 322L
// Assignment 3
// April 10, 2024

// Declare dynamic arrays/vectors and global variables
#define MAX_RES 3
#define MAX_PROC 10

int resVect[MAX_RES];
int availableVector[MAX_RES];
int maxClaims[MAX_PROC][MAX_RES];
int allocated[MAX_PROC][MAX_RES];
int need[MAX_PROC][MAX_RES];
bool finished[MAX_PROC];
int safeSequence[MAX_PROC];

 int numRes;
 int numProc;


void printVector(int *vector, int size);
void printMatrix(int matrix[][MAX_RES], int rows, int cols, const char *title);
void option1();
void option2();
void option3();
void option4();
void option5();
bool isSafe();

//************************************************************
// PROCEDURE TO PRINT VECTOR"
void printVector(int *vector, int size) {
  for (int j = 0; j < size; j++) {
    printf("    %d ", vector[j]);
  }
  printf("\n");
}
void printMatrix(int matrix[][MAX_RES], int rows, int cols, const char *title) {
  printf("%s\n", title);
  for (int i = 0; i < rows; i++) {
    printf("p%d ", i);
    for (int j = 0; j < cols; j++) {
      printf("  %d   ", matrix[i][j]);
    }
    printf("\n");
  }
}

//************************************************************

// void "OPTION #1"()
void option1() {
  printf("Enter number of resources: ");
  scanf("%d", &numRes);

  printf("Enter number of units for resources (r0 to r%d): ", numRes - 1);
  for (int j = 0; j < numRes; j++) {
    scanf("%d", &resVect[j]);
    availableVector[j] = resVect[j];
  }

  printf("Enter number of processes: ");
  scanf("%d", &numProc);
  // glitch here probably
  for (int i = 0; i < numProc; i++) {
    for (int j = 0; j < numRes; j++) {
      allocated[i][j] = 0;
      need[i][j] = 0;
    }
  }

  for (int i = 0; i < numProc; i++) {
    printf("Enter maximum number of units process p%d will claim from each "
           "resource (r0 to r%d): ",
           i, numRes - 1);
    for (int j = 0; j < numRes; j++) {
      scanf("%d", &maxClaims[i][j]);
      need[i][j] = maxClaims[i][j];
    }
  }

  for (int i = 0; i < numProc; i++) {
    printf("Enter number of units of each resource (r0 to r%d) currently "
           "allocated to process p%d: ",
           numRes - 1, i);

    for (int j = 0; j < numRes; j++) {

      scanf("%d", &allocated[i][j]);
      availableVector[j] -= allocated[i][j];
      need[i][j] -= allocated[i][j];
    }
  }

  // printing the above
  printf("\nResources:\n");
  printf("    r0    r1    r2\n");
  printVector(resVect, numRes);

  printf("\nAvailable:\n");
  printf("    r0    r1    r2\n");
  printVector(availableVector, numRes);

  printf("\nMax Claim:\n");
  printf("    r0    r1    r2\n");
  printMatrix(maxClaims, numProc, numRes, " ");

  printf("\nAllocated:\n");
  printf("    r0    r1    r2\n");
  printMatrix(allocated, numProc, numRes, " ");

  printf("\nNeed:\n");
  printf("    r0    r1    r2\n");
  printMatrix(need, numProc, numRes, " ");
}

//************************************************************
// void "OPTION #2"()

void option2() {

  int process;
  printf("Enter requesting process: p");
  scanf("%d", &process);

  char resource[MAX_RES];
  printf("Enter requested resource: r");
  scanf("%s", resource);

  int resourceIndex = atoi(&resource[1]);

  int request;
  printf("Enter number of units process p%d is requesting from resource r%s: ",
         process, resource);
  scanf("%d", &request);

  // make sure to check
  if (request <= need[process][resourceIndex] &&
      request <= availableVector[resourceIndex]) {

    availableVector[resourceIndex] -= request;
    allocated[process][resourceIndex] += request;
    need[process][resourceIndex] -= request;
    // pointer here for backtracking
    printf("\nAvailable:\n");
    printf("    r0    r1    r2\n");
    printVector(availableVector, numRes);

    printf("\n");
    printf("Allocated:\n");
    printf("    r0    r1    r2\n");
    printMatrix(allocated, numProc, numRes, " ");
    printf("\n");
    printf("Need:\n");
    printf("    r0    r1    r2\n");
    printMatrix(need, numProc, numRes, " ");

  } else {

    printf("Request denied. Not enough resources available.\n");
  }
}

//************************************************************
// void "OPTION #3"

void option3() {
  int process;
  printf("Enter releasing processor: p");
  scanf("%d", &process);

  int releasedResource;
  printf("Enter released resource: r");
  scanf("%d", &releasedResource);

  int release;
  printf("Enter number of units process p%d is releasing from resource r%d: ",
         process, releasedResource);
  scanf("%d", &release);

  if (release > allocated[process][releasedResource]) {
    printf("Release denied. Process p%d does not have enough allocated "
           "resources of type r%d.\n",
           process, releasedResource);
    return;
  }

  availableVector[releasedResource] += release;
  allocated[process][releasedResource] -= release;
  need[process][releasedResource] += release;

  printf("\n");
  printf("Available:\n");

  printf("    r0    r1    r2\n");
  printVector(availableVector, numRes);

  printf("\n");
  printMatrix(allocated, numProc, numRes, "Allocated:\n    r0    r1    r2\n");

  printf("\n");
  printMatrix(need, numProc, numRes, "Need:\n    r0    r1    r2\n");

  printf("\n");
}

//************************************************************
// void "OPTION #4"()

void executeSafeSequence();
int safeSequence[MAX_PROC];
void option4() {
  // init

  availableVector[0] = 3;
  availableVector[1] = 3;
  availableVector[2] = 2;

  allocated[0][0] = 0;
  allocated[0][1] = 1;
  allocated[0][2] = 0;
  allocated[1][0] = 2;
  allocated[1][1] = 0;
  allocated[1][2] = 0;

  allocated[2][0] = 3;
  allocated[2][1] = 0;
  allocated[2][2] = 2;
  allocated[3][0] = 0;
  allocated[3][1] = 1;
  allocated[3][2] = 1;
  allocated[4][0] = 4;
  allocated[4][1] = 3;
  allocated[4][2] = 1;

  need[0][0] = 7;
  need[0][1] = 4;
  need[0][2] = 3;
  need[1][0] = 1;
  need[1][1] = 2;
  need[1][2] = 2;
  need[2][0] = 6;
  need[2][1] = 0;
  need[2][2] = 0;
  need[3][0] = 0;
  need[3][1] = 1;
  need[3][2] = 1;
  need[4][0] = 4;
  need[4][1] = 3;
  need[4][2] = 1;

  for (int i = 0; i <= 4; i++) {
    printf("Comparing: <");
    for (int j = 0; j < MAX_RES; j++) {
      printf(" %d", need[i][j]);
    }
    printf(" > <= <");
    for (int j = 0; j < MAX_RES; j++) {
      printf(" %d", availableVector[j]);
    }
    printf(" > : ");

    int tempAvailable[MAX_RES];

    for (int j = 0; j < MAX_RES; j++) {
      tempAvailable[j] = availableVector[j] - need[i][j];
    }

    bool safe = true;

    for (int j = 0; j < MAX_RES; j++) {
      if (tempAvailable[j] < 0) {
        safe = false;
        break;
      }
    }

    if (safe) {

      for (int j = 0; j < MAX_RES; j++) {
        availableVector[j] += allocated[i][j];
      }
      printf("Safe to process p%d\n", i);
      safeSequence[i] = i;
    } else {
      printf("Not safe to process p%d\n", i);
      safeSequence[i] = -1;
    }
  }

  executeSafeSequence();
}

void executeSafeSequence() {
  printf("Safe sequence of processes: ");
  for (int i = 0; i <= 4; i++) {
    if (safeSequence[i] != -1) {
      printf("p%d ", safeSequence[i]);
    }
  }
  printf("\n");
}

//************************************************************
// void Option 5: Quit program and free memory ez
void option5() {

  printf("Quitting program...\n");
  exit(0);
}

bool isSafe() {
  int work[MAX_RES];
  bool finish;

  for (int i = 0; i < numRes; i++) {
    work[i] = availableVector[i];
    finished[i] = false;
  }

  for (int i = 0; i < numProc; i++) {
    finish = false;
    for (int j = 0; j < numProc; j++) {
      if (!finished[j]) {
        bool canFinish = true;
        for (int k = 0; k < numRes; k++) {
          if (need[j][k] > work[k]) {
            canFinish = false;
            break;
          }
        }

        if (canFinish) {

          for (int k = 0; k < numRes; k++) {
            work[k] += allocated[j][k];
          }
          finished[j] = true;
          finish = true;
        }
      }
    }
    if (!finish) {
      return false;
    }
  }
  return true;
}

//***************************main*********************************

int main() {

  int selection;

  do {
    printf("\nBanker's Algorithm\n------------------\n");

    printf("1) Enter resource claim graph data\n");

    printf("2) Request resource by a process\n");

    printf("3) Release resource from a process\n");

    printf("4) Determine safe sequence of processes\n");

    printf("5) Quit program\n");

    printf("\n");

    printf("Enter selection: ");

    scanf("%d", &selection);

    switch (selection) {
    case 1:

      option1();
      break;
    case 2:

      option2();
      break;
    case 3:

      option3();
      break;
    case 4:

      option4();
      break;
    case 5:

      option5();
      break;
    default:

      printf("Invalid selection!\n");
    }
  } while (1);

  return 0;
}

//***************************main*********************************