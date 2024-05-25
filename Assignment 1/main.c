//Owais Khan
//202555567
//Lab1 --Process Creation Hierarchy
//Comp 322 - L
//Date: 9/9/2023


#include <stdio.h>
#include <stdlib.h>

// Define structures and global variables
//*************************************************************
struct PCB {

  int oldr_sibling;
  int younger_sibling;
  int parent;
  int first_child;

};

  int max_processes;
  struct PCB *PCB_array;

//*************************************************************

int find_last_child(int parent_index) {
  int last_child = PCB_array[parent_index].first_child;

  // Continue until last found
  while (last_child != -1) {
    int next_sibling = PCB_array[last_child].younger_sibling;
    if (next_sibling != -1) {
      last_child = next_sibling;  //lastedit
    } else {
      break; 
    }
  }

  return last_child;
}

//*************************************************************

void create_child(int parent_index) {

  
  int q;

  for (q = 0; q < max_processes && PCB_array[q].parent != -1; q++)    //Find next
    ;

  if (q == max_processes) {
    
    printf("Error: No more processes can be created. PCB array is full.\n");
    
    return;
  }

  PCB_array[q].parent = parent_index;        //Initialzing all
  PCB_array[q].first_child = -1;
  PCB_array[q].oldr_sibling = -1;
  PCB_array[q].younger_sibling = -1;

  int last_child = find_last_child(parent_index);


  if (last_child != -1) {      //problem resolved
    
    PCB_array[last_child].younger_sibling = q;
  
    PCB_array[q].oldr_sibling = last_child;
  
  
  } else {
    
    PCB_array[parent_index].first_child = q;
  
  }

}


//*************************************************************
void destroy_descendants(int parent_index) {
    int stack[max_processes];
    int top = -1;

    // Push the initial parent index onto the stack
    stack[++top] = parent_index;

    while (top != -1) {
        int current_index = stack[top--];

        // Traverse through the first_child field of PCB[p] and push onto the stack
        int q = PCB_array[current_index].first_child;
        while (q != -1) {
            stack[++top] = q;
            q = PCB_array[q].younger_sibling;
        }

        // Update sibling pointers
        int older_sibling_index = PCB_array[current_index].oldr_sibling;
        if (older_sibling_index != -1) {
            PCB_array[older_sibling_index].younger_sibling = -1;
        }
        int parent_index = PCB_array[current_index].parent;
        if (parent_index != -1) {
            PCB_array[parent_index].first_child = -1;
        }

        // Reset all fields of the current process to -1
        PCB_array[current_index].parent = -1;
        PCB_array[current_index].first_child = -1;
        PCB_array[current_index].oldr_sibling = -1;
        PCB_array[current_index].younger_sibling = -1;
    }
}


//*************************************************************
void printPCBTable() {
    printf("\ni     Parent     First     Older     Younger\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < max_processes; i++) {
        printf("%-2d      ", i);

        if (PCB_array[i].parent != -1) {              // For PArent
            printf("%-6d    ", PCB_array[i].parent);
        } else {
            printf("         ");
        }

        if (PCB_array[i].first_child != -1) {                // For Child
            printf("%-5d     ", PCB_array[i].first_child);
        } else {
            printf("   ");
        }

        if (PCB_array[i].oldr_sibling != -1) {              // For Older
            printf("%-5d      ", PCB_array[i].oldr_sibling);
        } else {
            printf("                  ");
        }

        if (PCB_array[i].younger_sibling != -1) {            // For Younger
            printf("%-5d       ", PCB_array[i].younger_sibling);
        }

        printf("\n");
    }
}


void freeMemory() { free(PCB_array); }      // for freeing the memory [stack overflow]
void create_child(int parent_index);
void destroy_descendants(int parent_index);
void printPCBTable();
void freeMemory();

//******************************************main******************************************
int main() {
  int choice, parent_index;

  do {

    
    printf("\nProcess creation and destruction\n");
    
    printf("--------------------------------\n");
    
    printf("1) Enter parameters\n");
    
    printf("2) Create a new child process\n");
    
    printf("3) Destroy all descendants of a process\n");
    
    printf("4) Quit program and free the memory\n");
  
    printf("Enter selection: ");  
    scanf("%d", &choice);

    // Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure 
    //Options 
    switch (choice) {

    case 1:
      printf("Enter maximum number of processes: ");
      scanf("%d", &max_processes);

      
      PCB_array = (struct PCB *)malloc(max_processes * sizeof(struct PCB));    //allocation
      
      if (PCB_array == NULL) {

        
        printf("Error: Memory allocation error.\n");
        return 1;
      }

      
      for (int i = 0; i < max_processes; i++) {      //init
        PCB_array[i].parent = -1;
        
        PCB_array[i].first_child = -1;
        
        PCB_array[i].oldr_sibling = -1;
        PCB_array[i].younger_sibling = -1;
      }
      PCB_array[0].parent = 0;      //set 0
      printPCBTable();      //issue resolved
      break;
    case 2:

      
      printf("Enter the parent process index: ");
      
      scanf("%d", &parent_index);
      create_child(parent_index);

      
      printPCBTable();
      break;
    case 3:

      
      printf("Enter the process whose descendants are to be destroyed: ");
      
      scanf("%d", &parent_index);
      
      destroy_descendants(parent_index);
      
      printf("Descendants of process %d destroyed.\n", parent_index);


      printPCBTable();      //print
      
      break;
    
    case 4:
      
      freeMemory();
      
      printf("Quitting program...\n");     
      break;
    default:
      printf("Invalid choice. Please try again.\n");
      while (getchar() != '\n');
      break;    
    }
  } while (choice != 4);
  return 0;
}
