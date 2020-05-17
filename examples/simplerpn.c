#include <stdio.h>
#include <string.h>
#include "../heapstack.c"

#define MAX_LENGTH 100 // MAX_LENGTH OF ARGUMENTS
#define MAX_INPUT 1000

static struct node* outputstack = NULL;
static struct node* expr = NULL;

struct node* processRPN(struct node *l) {
    for ( ;; ) {
        char* cur = l->value;
        double arg1;
        double arg2;
        static char buffer[MAX_LENGTH]; // if not static, value gets deleted from stack
        //puts(l->value);
        if (strcmp(cur, "+") == 0 || strcmp(cur,"-") == 0 || strcmp(cur,"/") == 0 || strcmp(cur,"*") == 0) {
            arg1 = (double)atof(outputstack->value);
            // count number of operators and display error message
            outputstack=pop(outputstack);
            arg2 = (double)atof(outputstack->value);
            float result=0;
            switch (cur[0]) {
                case '+':
                    result=arg1+arg2;
                    break;
                case '-':
                    result=arg2-arg1;
                    break;
                case '*':
                    result=arg1*arg2;
                    break;
                case '/':
                    result=arg2/arg1;
                    break;
                default:
                    fatalerror("This shouldn't happen");
                    break;
            }
            sprintf(buffer, "%f", result);
            outputstack=push(outputstack, buffer);
            // this code is necessary, because this implementation does not support pushing 
            // to an empty list after pop
            // probably a problem with storage classes, same thing happened before I changed buffer
            // to static
            swapnodes(outputstack, outputstack->next);
            outputstack=pop(outputstack);
        } else {
            outputstack=push(outputstack, cur);
        }
    if (l->next==NULL) break;
    else l = l->next;
  }
  return outputstack;
}

int main(int argc, char* argv[]) {
    //struct node* expr = newlist("5", "10", "15" "+", "+", ENDLIST);
    char input[MAX_LENGTH]="";
    printf("Please enter the expression to be evaluated: ");
    fgets(input, MAX_LENGTH+1, stdin);
    input[strcspn(input, "\r\n")] = 0; // works for LF, CR, CRLF, LFCR, ...
    printf("The input was: %s\n", input);
    //char input2[]="4 2 5 + * 2 +";
    
    printf("Parsing the input string '%s'\n", input);
    char *token = strtok(input, " ");
    while (token != NULL) {
        expr=push(expr, token);
        token = strtok(NULL, " ");
    }
    reverselist(expr);
    struct node* result = processRPN(expr);
    printf("The result of the operation is: ");
    displaylist(result);
    return 0;
}