#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h> // ต้องใช้สำหรับฟังก์ชัน pow (ยกกำลัง)

#define MAX 100

// ==========================================
// ส่วนที่ 1: GLOBAL STACK & UTILITIES
// ==========================================

// Stack สำหรับเก็บ Operator (ใช้ใน Infix -> Postfix)
char opStack[MAX];
int opTop = -1;

// Stack สำหรับเก็บค่าตัวเลข (ใช้ใน Postfix Evaluation)
float valStack[MAX];
int valTop = -1;

// --- ฟังก์ชันจัดการ Stack ตัวอักษร ---
void pushOp(char ch) {
    if (opTop >= MAX - 1) printf("Stack Overflow\n");
    else opStack[++opTop] = ch;
}

char popOp() {
    if (opTop == -1) return -1;
    else return opStack[opTop--];
}

// --- ฟังก์ชันจัดการ Stack ตัวเลข ---
void pushVal(float val) {
    if (valTop >= MAX - 1) printf("Val Stack Overflow\n");
    else valStack[++valTop] = val;
}

float popVal() {
    if (valTop == -1) return 0;
    else return valStack[valTop--];
}

// ตรวจสอบว่าเป็นตัวดำเนินการหรือไม่
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// ตรวจสอบว่าเป็นตัวแปร (A-Z, a-z)
int isOperand(char ch) {
    return (isalpha(ch)); 
}

// ==========================================
// ส่วนที่ 2: INFIX -> POSTFIX (Logic แก้ไขจากเอกสาร)
// ==========================================

int precedenceIP(char op) { // ความสำคัญขาเข้า (Incoming)
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 4; // แก้ไข: เพิ่ม ^ และให้ค่าสูงสุด
        case '(': return 4;
        default: return 0;
    }
}

int precedenceST(char op) { // ความสำคัญใน Stack (In-Stack)
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3; // แก้ไข: น้อยกว่าขาเข้า (Right Associative)
        case '(': return 0;
        default: return 0;
    }
}

void infixToPostfix() {
    char infix[MAX], postfix[MAX];
    int i = 0, j = 0;
    char ch;
    
    opTop = -1; // Reset Stack

    printf("\n--- 1. INFIX TO POSTFIX ---\n");
    printf("Enter Infix Expression (e.g., A+B*C): ");
    scanf("%s", infix);

    int len = strlen(infix);
    for (i = 0; i < len; i++) {
        ch = infix[i];

        if (isOperand(ch) || isdigit(ch)) { // รองรับทั้งตัวแปรและตัวเลข
            postfix[j++] = ch;
        } else if (ch == '(') {
            pushOp(ch);
        } else if (ch == ')') {
            while (opTop != -1 && opStack[opTop] != '(') {
                postfix[j++] = popOp();
            }
            popOp(); // ทิ้ง '('
        } else if (isOperator(ch)) {
            while (opTop != -1 && precedenceIP(ch) <= precedenceST(opStack[opTop])) {
                postfix[j++] = popOp();
            }
            pushOp(ch);
        }
    }

    while (opTop != -1) {
        postfix[j++] = popOp();
    }
    postfix[j] = '\0';
    printf("Result Postfix: %s\n\n", postfix);
}

// ==========================================
// ส่วนที่ 3: POSTFIX EVALUATION (Logic แก้ไขจากเอกสาร)
// ==========================================

float calculate(float op1, float op2, char operator) {
    switch(operator) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        case '^': return pow(op1, op2);
        default: return 0;
    }
}

void evaluatePostfix() {
    char postfix[MAX];
    int i, len;
    float val, op1, op2, result;

    valTop = -1; // Reset Stack

    printf("\n--- 2. EVALUATE POSTFIX ---\n");
    printf("Enter Postfix Expression (e.g., AB+C*): ");
    scanf("%s", postfix);

    len = strlen(postfix);
    for (i = 0; i < len; i++) {
        char ch = postfix[i];

        // 1. ถ้าเป็นตัวแปร (A, B, C...) ให้ถามค่าจากผู้ใช้ (ตามแบบฝึกหัดในเอกสาร)
        if (isOperand(ch)) {
            printf("Enter value for %c: ", ch);
            scanf("%f", &val);
            pushVal(val);
        }
        // 2. ถ้าเป็นตัวเลข (0-9) ให้แปลงเป็น int แล้ว Push (เผื่อผู้ใช้กรอกตัวเลขตรงๆ)
        else if (isdigit(ch)) {
            pushVal((float)(ch - '0'));
        }
        // 3. ถ้าเป็น Operator ให้ Pop 2 ค่ามาคำนวณ
        else if (isOperator(ch)) {
            op2 = popVal(); // ตัวที่ Pop ครั้งแรกคือตัวกระทำ (ตัวหลัง)
            op1 = popVal(); // ตัวที่ Pop ครั้งที่สองคือตัวตั้ง (ตัวหน้า)
            
            result = calculate(op1, op2, ch);
            pushVal(result);
        }
    }

    printf("Final Result: %.2f\n\n", popVal());
}

// ==========================================
// MAIN MENU
// ==========================================
int main() {
    int choice;
    do {
        printf("=================================\n");
        printf("      DATA STRUCTURE MENU        \n");
        printf("=================================\n");
        printf("1. Convert Infix -> Postfix\n");
        printf("2. Calculate Postfix Result\n");
        printf("0. Exit\n");
        printf("Select menu: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: infixToPostfix(); break;
            case 2: evaluatePostfix(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
    return 0;
}