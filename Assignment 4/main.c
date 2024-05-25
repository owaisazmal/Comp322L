// Owais Khan
//Comp 322L
//04/20/24
//Assignment 4 -- Hole Fitting Algorithms

#include <stdio.h>
#include <stdlib.h>

// decalare global variables including linked list of blocks containing
// id, starting address, ending address, link to nxt node in list

//********************************************************************

typedef struct block {
  int id;
  int End_Add;
  int Start_Add;
  struct block *nxt;

} blck_type;
blck_type *head = NULL;
int pm_size;

//********************************************************************

void print_allocation_table() {
  
  printf("ID Start End\n");
  printf("-------------------\n");
  
  blck_type *curr = head;
  while (curr != NULL) {
  
    printf("%d %d %d\n", curr->id, curr->Start_Add,
           curr->End_Add);
    
    curr = curr->nxt;
  }
}

//************************PROCEDURE FOR OPTION1********************************************

void enter_param() {
  
  printf("Enter size of physical memory: ");
  scanf("%d", &pm_size);
  
  while (head != NULL) {
    
    blck_type *temp = head;
    head = head->nxt;
    
    free(temp);
  
  }
}

//********************************************************************

void insrt_blck(int id, int size, int Start_Add) {
  blck_type *new_blck = malloc(sizeof(blck_type));
  
  new_blck->id = id;
  new_blck->Start_Add = Start_Add;
  new_blck->End_Add = Start_Add + size;
  new_blck->nxt = NULL;

  if (head == NULL || Start_Add < head->Start_Add) {
    
    new_blck->nxt = head;
    head = new_blck;
    
  } else {
    blck_type *curr = head;
    while (curr->nxt != NULL &&
           curr->nxt->Start_Add < Start_Add) {
      curr = curr->nxt;
    }
    new_blck->nxt = curr->nxt;
    curr->nxt = new_blck;
  }
}


//********************************************************************

void allocate_memory(int id, int size, char mode) {

  
  if (size > pm_size) {
    printf("Error: Memory block size exceeds physical memory size.\n");
    return;
  }

  blck_type *curr = head, *prev = NULL;
  blck_type *best = NULL, *worst = NULL;
  int best_size = pm_size + 1, worst_size = 0;
  int start = 0;


  while (curr != NULL) {
    if (curr->id == id) {
      printf("Error: Block ID %d already exists.\n", id);
      return;
    }
    curr = curr->nxt;
  }//Checking ID

  curr = head;
  while (curr != NULL || start < pm_size) {
    
    int end = (curr ? curr->Start_Add : pm_size);
    
    int gap = end - start;

    if (gap >= size) {
      
      if (mode == 'F') { 
        insrt_blck(id, size, start);
        print_allocation_table();
        return;
      }
      if (mode == 'B' && gap < best_size) { 
        best = prev;
        best_size = gap;
      }
      if (mode == 'W' && gap > worst_size) { 
        worst = prev;
        worst_size = gap;
      }
    }
    start = (curr ? curr->End_Add : pm_size);
    prev = curr;
    curr = (curr ? curr->nxt : NULL);
  }

  if ((mode == 'B' && best_size != pm_size + 1) ||
      (mode == 'W' && worst_size != 0)) {
    blck_type *fit = (mode == 'B') ? best : worst;
    int fit_start = (fit ? fit->End_Add : 0);
    insrt_blck(id, size, fit_start);
    print_allocation_table();
    return;
  }

  printf("No suitable hole found for block %d of size %d.\n", id, size);
}

//********************************************************************

void deallocate_memory(int id) {
  blck_type *prev = NULL, *curr = head;
  while (curr != NULL && curr->id != id) {
    prev = curr;
    curr = curr->nxt;
  }

  if (curr == NULL) {
    printf("Error: Block ID %d not found.\n", id);
    return;
  }

  if (prev) {
    prev->nxt = curr->nxt;
  } else {
    head = curr->nxt;
  }

  free(curr);
  
  print_allocation_table();
  
}

//********************************************************************

void defragment_memory() {
  
  if (head == NULL) {
    
    printf("Memory is empty, no blocksto defragment.\n");
    
    return;
  }

  blck_type *new_head = NULL;
  blck_type *new_curr = NULL;

  blck_type *curr = head;
  int curr_address = 0;

  while (curr != NULL) {
    blck_type *new_blck = malloc(sizeof(blck_type));//new
    new_blck->id = curr->id;
    new_blck->Start_Add = curr_address;
    
    new_blck->End_Add = curr_address + (curr->End_Add - curr->Start_Add);
    new_blck->nxt = NULL;

    if (new_head == NULL) {
      new_head = new_blck;
      new_curr = new_blck;
    } else {
      new_curr->nxt = new_blck;
      new_curr = new_blck;
    }

    curr_address = new_blck->End_Add;

    // curr = curr->next;
    // blck_type *temp = curr;
    //free(temporary);
    
    blck_type *temp = curr;
    curr = curr->nxt;
    free(temp);
  }

  head = new_head;

  printf("Memory has been defragmented.\n");
  print_allocation_table();
}

//********************************************************************

//********************************************************************

void free_memory() {
  
  blck_type *curr = head;
  
  while (curr != NULL) {
    blck_type *temp = curr;
    curr = curr->nxt;
    
    free(temp);
  
  }
  
  head = NULL;
}

//*******************************MAIN********************************************

int main() {
  int choice, id, size;
  char mode;

  while (1) {
    printf("\nHole-fitting Algorithms\n");
    printf("-----------------\n");
    printf("1) Enter parameters\n");
    printf("2) Allocate memory for block using First-fit\n");
    printf("3) Allocate memory for block using Best-fit\n");
    printf("4) Allocate memory for block using Worst-fit\n");
    
    printf("5) Deallocate memory for block\n");
    printf("6) Defragment memory\n");
    printf("7) Quit program\n");
    
    printf("Enter selection: ");
    scanf("%d", &choice);

    switch (choice) {
      
    case 1:
      
      enter_param();
      
      break;
    
    case 2:
    
    case 3:
    
    case 4:
    
      printf("Enter block id: ");
      scanf("%d", &id);
      printf("Enter block size: ");
      
      scanf("%d", &size);
      mode = (choice == 2) ? 'F' : ((choice == 3) ? 'B' : 'W');
      allocate_memory(id, size, mode);
      
      break;
    case 5:
      
      printf("Enter block id: ");
      scanf("%d", &id);
      deallocate_memory(id);
      
      break;
    
    case 6:
      
      defragment_memory();
      
      break;
    case 7:
      
      free_memory();
      printf("Quitting program...\n");
      return 0;
    
    default:
      printf("Invalid option, please try again.\n");
    }
  }

  return 0;
}
