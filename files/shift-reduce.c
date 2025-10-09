#include <stdio.h>
#include <string.h>

char input[20];
char stack[20];
int top = -1;
int ip = 0;

// Function to print current step
void display(const char *action) {
    printf("%-20s%-20s%-20s\n", stack, input + ip, action);
}

// Check if we can reduce
int reduce() {
    if (top >= 2 && stack[top-2] == 'E' && stack[top-1] == '+' && stack[top] == 'E') {
        top -= 2;  // Remove + E
        stack[top] = 'E';  // Replace with E
        stack[top+1] = '\0';
        display("REDUCE E -> E+E");
        return 1;
    } else if (top >= 0 && stack[top] == 'i' && input[ip] == 'd') {
        // handled below in shift normally
        return 0;
    } else if (top >= 1 && stack[top-1] == 'i' && stack[top] == 'd') {
        top -= 1;
        stack[top] = 'E';
        stack[top+1] = '\0';
        display("REDUCE E -> id");
        return 1;
    }
    return 0;
}

// Recursive shift-reduce function
void shift_reduce() {
    // If input fully consumed and stack has E only
    if (input[ip] == '\0' && top == 0 && stack[top] == 'E') {
        display("ACCEPT");
        return;
    }

    // Try to reduce first
    while (reduce());

    // If not finished, shift next symbol
    if (input[ip] != '\0') {
        stack[++top] = input[ip++];
        stack[top+1] = '\0';
        display("SHIFT");
        shift_reduce();  // recursive call
    }
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);
    printf("\n%-20s%-20s%-20s\n", "STACK", "INPUT", "ACTION");
    printf("------------------------------------------------------------\n");
    shift_reduce();
    return 0;
}
