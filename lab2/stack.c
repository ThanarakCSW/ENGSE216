/*
Program create PUSH/POP function of Stack and use its.
The program will exit when status are "OVER FLOW" or "UNDER FLOW".
=======================================================================
=========
*/
#include <stdio.h>   // use printf()
#include <termios.h> // for custom getch() on macOS
#include <unistd.h>  // for STDIN_FILENO

#define MaxStack 6   // Set Max Stack

int stack[MaxStack]; // Declare Max Stack 0..5
int x;               // Temporary variable
int SP = 0;          // Initial SP=0
char status = 'N';   // Initial Status = NORMAL
char ch;             // KBD Read variable

// getch() replacement for macOS
int getch(void) {
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);      // get terminal attributes
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);    // disable buffered I/O and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    ch = getchar();                         // read character

    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); // restore settings
    return ch;
}

void push(int x)     // PUSH Function
{
    if (SP == MaxStack - 1)
    { // Check Stack FULL?
        printf("!!!OVER FLOW!!!...\n");
        status = 'O'; // set status = OVER FLOW
    }
    else
    {
        SP = SP + 1;   // Increase SP
        stack[SP] = x; // Put data into Stack
    }
}

int pop() // POP Function
{
    int x;
    if (SP != 0) // Check Stack NOT EMPTY?
    {
        x = stack[SP]; // Get data from Stack
        stack[SP] = 0; // Clear data (optional)
        SP--;          // Decrease SP
        return (x);    // Return data
    }
    else
    {
        printf("\n!!!UNDER FLOW!!!...\n");
        status = 'U'; // set STATUS = "UNDER FLOW"
        return 0;     // avoid warning
    }
}

void ShowAllStack() // Display Function
{
    int i;                              // Counter variable
    printf(" N : %d\n ", MaxStack - 1); // Display N
    printf("Status : %c\n ", status);   // Display STATUS
    printf("SP : %d\n", SP);            // Display SP
    for (i = 1; i < MaxStack; i++)
    {
        printf("%d:%d ", i, stack[i]); // Display all of data in Stack
    }
    printf("\n----------------------------------------------------------\n");
}

int main()
{
    printf("STACK PROGRAM...\n");
    printf("===================\n");

    while (status == 'N')
    {
        printf("[1=PUSH : 2=POP] : "); // Show MENU

        ch = getch();                  // Use custom getch() for macOS
        printf("%c\n", ch);            // echo input manually

        switch (ch)                    // Check ch
        {
        case '1':
            printf("Enter Number : ");
            scanf("%d", &x); // Read data from KBD
            push(x);         // Call PUSH Function
            ShowAllStack();  // Display all data in Stack
            break;

        case '2':
            x = pop();                  // POP data
            printf("Data : %d\n", x);   // Display it
            ShowAllStack();             // Display all data in Stack
            break;
        }
    }

    printf("\n"); // line feed
    return 0;
}