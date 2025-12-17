#include <stdio.h>
#include <stdlib.h>

#define N 5   // array size; usable queue capacity is N-1 (indices 1..N-1)

int Q[N];            // queue storage (we use indices 1..N-1)
int x, Qnumber = 0;  // Qnumber: total enqueued count (for display)
int F = 0, R = 0;    // Front and Rear (0 means empty)
char status = 'N';   // 'N' = NORMAL, 'O' = OVERFLOW, 'U' = UNDERFLOW
char ch;             // command input

void insertCQ(int y) {
    // Queue is full when R == F-1 (in modular sense) or special case when F==1 and R==N-1
    if ((F != 0 && R == F - 1) || (R == N - 1 && F == 1)) {
        printf("!!! OVER FLOW !!!\n");
        status = 'O';
        return;
    }

    // advance R (circular 1..N-1)
    if (R == N - 1) {
        R = 1;
    } else {
        R++;
        if (F == 0)   // queue was empty, set front to 1
            F = 1;
    }

    Qnumber++;
    printf("You are queue number : %d\n", Qnumber);
    Q[R] = y;
    status = 'N';
}

int deleteCQ() {
    int y;
    if (F == 0) { // empty
        printf("\n!!! UNDER FLOW !!!\n");
        status = 'U';
        return -1; // sentinel to indicate no data
    }

    y = Q[F];
    if (F == R) { // last element removed -> become empty
        F = 0;
        R = 0;
    } else {
        if (F == N - 1)
            F = 1; // wrap
        else
            F++;
    }
    status = 'N';
    return y;
}

int DataInQueue() {
    int y = 0;
    if (F != 0 && R != 0) {
        if (F <= R)
            y = R - F + 1;                 // normal case
        else
            y = (N - 1) - F + 1 + R;      // wrapped case
    }
    return y;
}

void ShowAllQueue() {
    int i;
    printf("\n--- QUEUE STATUS ---\n");
    printf("Capacity (N-1) : %d\n", N - 1);
    printf("Status = %c\n", status);
    printf("Data waiting in queue = %d\n", DataInQueue());
    printf("F = %d / R = %d\n", F, R);
    printf("All slots (index:value):\n");
    for (i = 1; i < N; i++) {
        printf("%d:%d  ", i, Q[i]);
    }
    printf("\n---------------------\n");
}

int main() {
    printf("CIRCULAR QUEUE PROGRAM...\n");
    printf("=========================\n");

    // initialize Q array to 0 (optional)
    for (int i = 0; i < N; i++) Q[i] = 0;

    ch = ' ';
    while (ch != 'E' && ch != 'e') {
        printf("\n[1=INSERT : 2=DELETE : E=Exit] : ");
        if (scanf(" %c", &ch) != 1) {
            // input failure
            break;
        }

        switch (ch) {
        case '1':
            printf("Insert Number : ");
            if (scanf("%d", &x) == 1) {
                insertCQ(x);
                ShowAllQueue();
            } else {
                printf("Invalid number input.\n");
                // clear invalid token
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { }
            }
            break;

        case '2':
            x = deleteCQ();
            if (x != -1)
                printf("\nData from Queue = %d\n", x);
            ShowAllQueue();
            break;

        case 'E':
        case 'e':
            printf("Exiting...\n");
            break;

        default:
            printf("Unknown command. Use 1, 2 or E.\n");
            break;
        } // end switch
    } // end while

    return 0;
}