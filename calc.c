/** Calc.c
*	Reverse Polish Notation Calculator
*/

/** Include appropriate libraries */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

/** Global Vars */
char compareStringAdd[] = "+";
char compareStringSubtract[] = "-";
char compareStringMultiply[] = "*";
char compareStringDivide[] = "/";
char compareStringSine[] = "sin";
char compareStringCosine[] = "cos";
char compareStringRand[] = "rand";
char compareStringSQRT[] = "sqrt";
char compareStringPower[] = "pow";
char compareStringNegate[] = "neg";
char compareStringSwap[] = "swap";
char compareStringPop[] = "pop";
char compareStringPrint[] = "print";
char compareStringQuit[] = "quit";
char compareStringDef[] = "def";
char compareStringPrintFunc[] = "print_func";
char compareStringCallFunc[] = "call_func";
char compareStringAppendFunc[] = "append_func";

/** To start off, functions to establish a linked list */
typedef struct {
	float floatVal;
	struct Node* next;
} Node;

typedef struct {
	char *stringVal;
	struct StringNode* next;
} StringNode;

/** Establish a stack and a queue */
typedef struct {
	Node* head;
	Node* tail;
} Stack;

typedef struct {
	Node* head;
	Node* tail;
} Queue;

Stack stackCalculator;
Queue functionQueue;
Queue queueForAppending;

/** Functions for a stack */
void push(float inputVal) {
	Node* tempNode = (Node*) malloc(sizeof(Node));
    if(tempNode == NULL) {
        exit(0);
    }
    tempNode->floatVal = inputVal;
    tempNode->next = stackCalculator.head;
    stackCalculator.head = tempNode;
    return;
}

float pop() {
	Node* tempNode = stackCalculator.head;
	float returnVal = tempNode->floatVal;
    stackCalculator.head = stackCalculator.head->next;
    free(tempNode);
    return returnVal;
}

/** Functions for a queue */
void enqueue(char* command) {
	StringNode* tempNode = (StringNode*) malloc(sizeof(StringNode));
	tempNode->stringVal = malloc(strlen(command) + 1);
    if (functionQueue.head == NULL && functionQueue.tail == NULL) {
    	strcpy(tempNode->stringVal, command);
		functionQueue.head = tempNode;
		functionQueue.tail = tempNode;
		return;
	}
	strcpy(tempNode->stringVal, command);
	functionQueue.tail -> next = tempNode;
	functionQueue.tail = tempNode;
	return;
}

char* dequeue() {
	static char* returnString[6];
	StringNode* tempNode = functionQueue.head;
	strcpy(returnString, tempNode->stringVal);
    functionQueue.head = functionQueue.head->next;
    free(tempNode);
    return returnString;
}

/** Modified enqueue/dequeue for the extra credit queue */
void enqueueEC(char* command) {
	StringNode* tempNode = (StringNode*) malloc(sizeof(StringNode));
	tempNode->stringVal = malloc(strlen(command) + 1);
    if (queueForAppending.head == NULL && queueForAppending.tail == NULL) {
    	strcpy(tempNode->stringVal, command);
		queueForAppending.head = tempNode;
		queueForAppending.tail = tempNode;
		return;
	}
	strcpy(tempNode->stringVal, command);
	queueForAppending.tail -> next = tempNode;
	queueForAppending.tail = tempNode;
	return;
}

char* dequeueEC() {
	static char* returnString[6];
	StringNode* tempNode = queueForAppending.head;
	strcpy(returnString, tempNode->stringVal);
    queueForAppending.head = queueForAppending.head->next;
    free(tempNode);
    return returnString;
}

/** Function to check to see if input is a number 
	if zero, then false */
int isNumeric (char* s) {
    if (s == NULL || *s == '\0' || isspace(*s)) {
      return 0;
    }
    char* p;
    strtod (s, &p);
    return *p == '\0';
}

/** Math Functions for Part 1 */

/** Push the number to top of stack. */
void inputNumber(float inputVal) {
	push(inputVal);
	printf("%.6f\n", inputVal);
	return;
}

/**	Pop the top two numbers, sum the numbers, and 
	place result to top of stack. */
void addTwoVals() {
	float valA;
	float valB;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valB = pop();
	result = valA + valB;
	push(result);
	printf("%.6f\n", result);
	return;

}

/**	Pop the top two numbers, subtract the numbers, and 
	place result to top of stack. */
void subtractTwoVals() {
	float valA;
	float valB;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valB = pop();
	result = valA - valB;
	push(result);
	printf("%.6f\n", result);
	return;

}

/**	Pop the top two numbers, multiply the numbers, and 
	place result to top of stack. */
void multiplyTwoVals() {
	float valA;
	float valB;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valB = pop();
	result = valA * valB;
	push(result);
	printf("%.6f\n", result);
	return;

}

/**	Pop the top two numbers, divide the numbers, and 
	place result to top of stack. */
void divideTwoVals() {
	float valA;
	float valB;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valB = pop();
	result = valA / valB;
	push(result);
	printf("%.6f\n", result);
	return;

}

/** Pop the top entry off the stack, compute the sine,
	and push it back to top */
void getSine() {
	float valA;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	result = sinf(valA);
	push(result);
	printf("%.6f\n", result);
	return;
}

/** Pop the top entry off the stack, compute the cosine,
	and push it back to top */
void getCosine() {
	float valA;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	result = cosf(valA);
	push(result);
	printf("%.6f\n", result);
	return;
}

/** Compute a random number between 0 and 1 to the 
	top of the stack */
void getRandom() {
	float randVal;
	randVal = rand() / (RAND_MAX + 1.0);
	push(randVal);
  	printf("%.6f\n", randVal);
  	return;
}

/** Pop the top entry off the stack, compute the square root,
	and push it back to top */
void getSquareRoot() {
	float valA;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	result = sqrt(valA);
	push(result);
	printf("%.6f\n", result);
	return;
}

/** Pop the top two entries. First entry is a; second is b.
	Compute b^a */
void getPower() {
	float valA;
	float valB;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valB = pop();
	result = powf(valB, valA);
	push(result);
	printf("%.6f\n", result);
	return;

}

/** Pop first value, negate it, push it */
void getNegative() {
	float valA;
	float result;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	result = valA * -1;
	push(result);
	printf("%.6f\n", result);
	return;
}

/** Swap the first two numbers on the stack */
void swapTwoVals() {
	float valA;
	float valB;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valA = pop();
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	valB = pop();
	push(valA);
	printf("%.6f\n", valA);
	push(valB);
	printf("%.6f\n", valB);
	return;

}

/** Pop the top value */
void popRPN() {
	float returnVal;
	if (stackCalculator.head == NULL) {
		printf("STACK ERROR\n");
		return;
	}
	returnVal = pop();
	printf("%.6f\n", returnVal);
	return;
}

/** Print the stack from top to bottom */
void printStack() {
	Node* current;
    current = stackCalculator.head;
    if (current != NULL) {
        printf("Stack: \n");
        do {
            printf("%.6f\n", current -> floatVal);
            current = current -> next;
        } while (current != NULL);
    } else {
        printf("The Stack is empty\n");
    }
    return;
}

/** Empty the stack, then quit */
void quitStack() {
	while (stackCalculator.head != NULL) {
		pop();
	}
	return;
}

/** Math Functions for Part 2 */
void parseCommand(char* command) {
	int i;
	const char delim[2] = " ";
	char* token;
	if (strlen(command) > 100) {
		printf("INVALID DEF\n");
		return;
	}
	while (functionQueue.head != NULL) {
		dequeue();
	}

	token = strtok(command, delim);
	token = strtok(NULL, delim);

	while (token != NULL) {
		if (strcmp(token, compareStringAdd) == 0 ||
			strcmp(token, compareStringSubtract) == 0 ||
			strcmp(token, compareStringMultiply) == 0 ||
			strcmp(token, compareStringDivide) == 0 ||
			strcmp(token, compareStringSine) == 0 ||
			strcmp(token, compareStringCosine) == 0 ||
			strcmp(token, compareStringRand) == 0 ||
			strcmp(token, compareStringSQRT) == 0 ||
			strcmp(token, compareStringPower) == 0 ||
			strcmp(token, compareStringNegate) == 0 ||
			strcmp(token, compareStringSwap) == 0 ||
			strcmp(token, compareStringPop) == 0 ||
			strcmp(token, compareStringPrint) == 0 ||
			isNumeric(token) != 0) {
				enqueue(token);
		} else {
			while (functionQueue.head != NULL) {
				dequeue();
			}
			printf("INVALID DEF\n");
			break;
		}
		token = strtok(NULL, delim); 	
	}

	
	return;
}

void printQueue() {
	StringNode* current;
	char printVal[10];
    current = functionQueue.head;
    if (current != NULL) {
        printf("Queue: \n");
        do {
        	/* Something is up with the strcpy line */
        	//strcpy(printVal, current->stringVal);
            printf("%s\n", current->stringVal);
            current = current -> next;
        }
        while (current != NULL);
    }
    else {
        printf("NO FUNCTION DEFINED\n");
    }
    return;
}

void useQueue() {
	StringNode* current;
	float convertFloat;
	char useVal[6];
    current = functionQueue.head;
    if (current != NULL) {
        do {
        	strcpy(useVal, current->stringVal);
            if (strcmp(useVal, compareStringAdd) == 0) {
				addTwoVals();
			} else if (strcmp(useVal, compareStringSubtract) == 0) {
				subtractTwoVals();
			} else if (strcmp(useVal, compareStringMultiply) == 0) {
				multiplyTwoVals();
			} else if (strcmp(useVal, compareStringDivide) == 0) {
				divideTwoVals();
			} else if (strcmp(useVal, compareStringSine) == 0) {
				getSine();
			} else if (strcmp(useVal, compareStringCosine) == 0) {
				getCosine();
			} else if (strcmp(useVal, compareStringRand) == 0) {
				getRandom();
			} else if (strcmp(useVal, compareStringSQRT) == 0) {
				getSquareRoot();
			} else if (strcmp(useVal, compareStringPower) == 0) {
				getPower();
			} else if (strcmp(useVal, compareStringNegate) == 0) {
				getNegative();
			} else if (strcmp(useVal, compareStringSwap) == 0) {
				swapTwoVals();
			} else if (strcmp(useVal, compareStringPop) == 0) {
				popRPN();
			} else if (strcmp(useVal, compareStringPrint) == 0) {
				printStack();
			} else if (isNumeric(useVal) != 0) {
				convertFloat = atof(useVal);
				inputNumber(convertFloat);
			}
            current = current -> next;
        } while (current != NULL);
    }
    else {
        printf("NO FUNCTION DEFINED\n");
    }
    return;
}

/** Math Functions for Extra Credit */
void appendQueue(char* command) {
	int i;
	const char delim[2] = " ";
	char* token;
	if (strlen(command) > 100) {
		printf("INVALID DEF\n");
		return;
	}
	while (queueForAppending.head != NULL) {
		dequeueEC();
	}

	token = strtok(command, delim);
	token = strtok(NULL, delim);

	while (token != NULL) {
		if (strcmp(token, compareStringAdd) == 0 ||
			strcmp(token, compareStringSubtract) == 0 ||
			strcmp(token, compareStringMultiply) == 0 ||
			strcmp(token, compareStringDivide) == 0 ||
			strcmp(token, compareStringSine) == 0 ||
			strcmp(token, compareStringCosine) == 0 ||
			strcmp(token, compareStringRand) == 0 ||
			strcmp(token, compareStringSQRT) == 0 ||
			strcmp(token, compareStringPower) == 0 ||
			strcmp(token, compareStringNegate) == 0 ||
			strcmp(token, compareStringSwap) == 0 ||
			strcmp(token, compareStringPop) == 0 ||
			strcmp(token, compareStringPrint) == 0 ||
			isNumeric(token) != 0) {
				enqueueEC(token);
		} else {
			while (queueForAppending.head != NULL) {
				dequeueEC();
			}
			printf("INVALID DEF\n");
			break;
		}
		token = strtok(NULL, delim); 	
	}
	StringNode* endNode = functionQueue.tail;
	endNode->next = queueForAppending.head;

	
	return;
}


/** Main function
* 	Utilizes an infinite loop for the calculator 
*/

int main() {
	char inputString[100];
	
	int i;
	float convertFloat;
	printf("Input Stuff Here:\n");
	while (1) {
		char commandArray[3][10];
		gets(inputString);
		sscanf(inputString, "%s", commandArray[0]);

		for (i = 0; commandArray[0][i]; i++) {
			commandArray[0][i] = tolower(commandArray[0][i]);
		}
		if (strcmp(commandArray[0], compareStringAdd) == 0) {
			addTwoVals();
		} else if (strcmp(commandArray[0], compareStringSubtract) == 0) {
			subtractTwoVals();
		} else if (strcmp(commandArray[0], compareStringMultiply) == 0) {
			multiplyTwoVals();
		} else if (strcmp(commandArray[0], compareStringDivide) == 0) {
			divideTwoVals();
		} else if (strcmp(commandArray[0], compareStringSine) == 0) {
			getSine();
		} else if (strcmp(commandArray[0], compareStringCosine) == 0) {
			getCosine();
		} else if (strcmp(commandArray[0], compareStringRand) == 0) {
			getRandom();
		} else if (strcmp(commandArray[0], compareStringSQRT) == 0) {
			getSquareRoot();
		} else if (strcmp(commandArray[0], compareStringPower) == 0) {
			getPower();
		} else if (strcmp(commandArray[0], compareStringNegate) == 0) {
			getNegative();
		} else if (strcmp(commandArray[0], compareStringSwap) == 0) {
			swapTwoVals();
		} else if (strcmp(commandArray[0], compareStringPop) == 0) {
			popRPN();
		} else if (strcmp(commandArray[0], compareStringPrint) == 0) {
			printStack();
		} else if (strcmp(commandArray[0], compareStringQuit) == 0) {
			quitStack();
			break;
		} else if (strcmp(commandArray[0], compareStringPrintFunc) == 0) {
			printQueue();
		} else if (strcmp(commandArray[0], compareStringCallFunc) == 0) {
			useQueue();
		} else if (strcmp(commandArray[0], compareStringDef) == 0) {
			parseCommand(inputString);
		} else if (strcmp(commandArray[0], compareStringAppendFunc) == 0) {
			appendQueue(inputString);
		} else if (isNumeric(commandArray[0]) != 0) {
			convertFloat = atof(commandArray[0]);
			inputNumber(convertFloat);
		} else {
			printf("INVALID DEF\n");
		}

	}

	return 0;
}