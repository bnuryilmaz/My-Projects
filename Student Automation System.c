#include <stdio.h>
#include <stdlib.h>

//Buket Nur Yýlmaz 040200207

typedef struct IDNODE{ //This node is for integer variable.
	int id;
	struct CHNODE* next;
}idNode;

typedef struct CHNODE{ //This node is for name_surname data.
	char ch;
	struct CHNODE* next;
}chNode;

typedef struct{ //Stack is defined. Stack includes 3 integer head, 3 integer id and one integer top pointer variable. This stack can store 3 data.
    int head[3];
    int ID[3];
    int top;
}stack;

typedef struct{ //This variable is used for datas in stack. Using this variable makes access to the variables in stack.
	int ID;
	int head;
}data;

stack *stkHead; //Global variable for stack is defined. 

void addNumber(){ //This function takes number and name.
	int number, i;
	char name_surname[50];
	printf("Enter school number: ");
	scanf("%d",&number);
	printf("Name & Surname: ");
	scanf("%s",name_surname);
	
	idNode *head = malloc(sizeof(idNode));
	head->id = number;
	chNode *node = malloc(sizeof(chNode));
	head->next = node;
	node->ch = name_surname[0];
	node->next = NULL;
	
	for(i=1; i<strlen(name_surname);i++){ //This loop seprates fullname into letters and creates nodes.
		node->next = malloc(sizeof(chNode));
		node = node->next;
		node->ch = name_surname[i];
		node->next = NULL;
	}
	push(head, number%10000, stkHead); //These nodes are pushed into stack.
	sortByID();
}

void push(idNode *head, int number, stack *stk){ // define push function.
    if(stk->top==2){
        printf("\nStack dolu!!!");
    }
    else{
        stk->top++;
        stk->head[stk->top]=head;
        stk->ID[stk->top]=number;
    }
}

data pop(stack *stk){ //Define pop function.
	data poped;
    if(stk->top==-1){
        printf("\nStack bos!!!");
    }
    else{
    	poped.ID = stk->ID[stk->top];
    	poped.head = stk->head[stk->top];
    	stk->top--;
	    return poped;
    }
}

void sortByID(){ //This function sorts all datas by ID numbers. 
	stack *tmpstk = malloc(sizeof(stack)); // Create a temporary stack.
	data topStk;
	data topTmpStk;
	tmpstk->top = -1;
	while(stkHead->top>-1){
		topStk = pop(stkHead);
		int topIDstk = topStk.ID;
		idNode *topHeadstk = topStk.head;

		while(tmpstk->top>-1 && tmpstk->ID[tmpstk->top] > topIDstk){
			topTmpStk = pop(tmpstk);
			int topIDtmpstk =topTmpStk.ID;
			idNode *topHeadtmpstk = topTmpStk.head;
			
			push(topHeadtmpstk, topIDtmpstk, stkHead);
		}
		push(topHeadstk, topIDstk, tmpstk);
	}
	stkHead = tmpstk;
}

void displayStack(){ //This function prints all datas to screen.
	stack *tmpstk = malloc(sizeof(stack));
	tmpstk->top = -1;
	data current;
	
	while(stkHead->top>-1){
		current = pop(stkHead);
		int topIDstk = current.ID;
		idNode *topHeadstk = current.head;
		push(topHeadstk, topIDstk, tmpstk);
	}
	
	while(tmpstk->top>-1){
		char fullName[50] = "";
		chNode *nextNode;
		current = pop(tmpstk);
		int topIDstk = current.ID;
		idNode *topHeadstk = current.head;
		push(topHeadstk, topIDstk, stkHead);
		nextNode = topHeadstk->next;
		while(nextNode!= NULL){
			char cha[2] = {nextNode->ch, '\0'};
			if(nextNode->ch!='_'){
				strcat(fullName, cha);
			}
			else{
				strcat(fullName, " ");
			}
			nextNode = nextNode->next;
		}
		printf("\n%d %s", topHeadstk->id, fullName);
	}
	free(tmpstk);
}

void deleteNumber(){ //Define deleting a number that user enters.
	int numberToDelete;
	printf("Please enter a number to delete: ");
	scanf("%d", &numberToDelete);
	
	stack *tmpstk = malloc(sizeof(stack));
	tmpstk->top = -1;
	data current;
	
	while(stkHead->top>-1){
		current = pop(stkHead);
		idNode *topHeadstk = current.head;
		if(topHeadstk->id != numberToDelete){
			push(current.head, current.ID, tmpstk);
		}
		else{
			free(topHeadstk->next);
		}
	}
	printf("\nNumber %d successfully deleted.", numberToDelete);
	stkHead = tmpstk;
	free(tmpstk);
	sortByID();
}

void sortByYear(){ //This function sorts all datas by year.
	stack *tmpstk = malloc(sizeof(stack));
	idNode *tmphead;
	data topStk;
	data topTmpStk;
	tmpstk->top = -1;
	
	while(stkHead->top>-1){
		topStk = pop(stkHead);
		idNode *topHeadstk = topStk.head;
		int topYear = ((topHeadstk->id/10000))%100;

		while(tmpstk->top>-1){
			tmphead = tmpstk->head[tmpstk->top];
			int tmpYear = ((tmphead->id/10000))%100;
			if(tmpYear > topYear){
				topTmpStk = pop(tmpstk);
				int topIDtmpstk =topTmpStk.ID;
				idNode *topHeadtmpstk = topTmpStk.head;
				push(topHeadtmpstk, topIDtmpstk, stkHead);				
			}
			else{
				break;
			}
		}
		push(topHeadstk, (topHeadstk->id)%10000, tmpstk);

	}
	stkHead = tmpstk;
}

void sortByFcode(){ //This function sorts all data by faculty code.
	stack *tmpstk = malloc(sizeof(stack));
	idNode *tmphead;
	data topStk;
	data topTmpStk;
	tmpstk->top = -1;
	
	while(stkHead->top>-1){
		topStk = pop(stkHead);
		idNode *topHeadstk = topStk.head;
		int topYear = (topHeadstk->id)/1000000;

		while(tmpstk->top>-1){
			tmphead = tmpstk->head[tmpstk->top];
			int tmpYear = (tmphead->id)/1000000;
			if(tmpYear > topYear){
				topTmpStk = pop(tmpstk);
				int topIDtmpstk =topTmpStk.ID;
				idNode *topHeadtmpstk = topTmpStk.head;
				push(topHeadtmpstk, topIDtmpstk, stkHead);				
			}
			else{
				break;
			}
		}
		push(topHeadstk, (topHeadstk->id)%10000, tmpstk);

	}
	stkHead = tmpstk;	

}

int main(){ //Main menu prints and asks a choise from user. Based on chooise, necessary functions starts.
	stkHead = malloc(sizeof(stack));
	stkHead->top = -1;
	
	printf("\n1 - Enter school number");
	printf("\n2 - Display school numbers sorted by ID");
	printf("\n3 - Display school numbers sorted by year");
	printf("\n4 - Display school numbers sorted by faculty codes");
	printf("\n5 - Delete a record by school number");
	printf("\n6 - Exit");

	while(1){
		printf("\nEnter choice: ");
		int choice;
		scanf("%d",&choice);
	
		switch(choice){
			case 1:
				addNumber(stkHead);
				break;
			case 2:
				printf("Sorted by ID: ");
				displayStack();
				break;
			case 3:
				printf("Sorted by Year: ");
				sortByYear();
				displayStack();
				sortByID();				
				break;
			case 4:
				printf("Sorted by Faculty Code: ");
				sortByFcode();
				displayStack();
				sortByID();	
				break;
			case 5:
				deleteNumber();
				break;
			case 6:
				exit(0);
				break;
			default:
				printf("\nPlease enter a valid choice");
		}
	}
	return 0;
}
