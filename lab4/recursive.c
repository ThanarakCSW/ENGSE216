#include <stdio.h>
#include <stdlib.h>

// ฟังก์ชันหาค่า Factorial แบบ Recursive
int Factorial(int N) {
    int x, y;
    
    // Base Case: จุดหยุดการเรียกตัวเอง
    if (N == 0) {
        printf("Roll Back Point (Base Case Reached)\n");
        return 1;
    } 
    // Recursive Step: การเรียกตัวเอง
    else {
        x = N - 1;
        // แสดงผลขั้นตอนการเรียกไปข้างหน้า (Winding)
        printf("%d! = %d * %d!\n", N, N, x); 
        
        y = Factorial(x); // เรียกฟังก์ชันตัวเองซ้ำ
        
        // แสดงผลขั้นตอนการคำนวณย้อนกลับ (Unwinding)
        printf("%d! = %d * %d = %d\n", N, N, y, N * y); 
        
        return (N * y); // ส่งค่ากลับ
    }
}

int main() {
    int Number = 0, ans; // แก้ไข: ประกาศตัวแปรให้ถูกต้องและกำหนดค่าเริ่มต้น

    printf("RECURSIVE (FACTORIAL) PROGRAM\n");
    printf("=============================\n");

    // วนลูปรับค่าจนกว่าผู้ใช้จะพิมพ์ -999
    while (Number != -999) {
        printf("\nEnter Number (-999 is END): ");
        scanf("%d", &Number);

        if (Number == -999) {
            break; // ออกจากลูปทันทีถ้าใส่ -999
        }

        if (Number >= 0) {
            printf("Formula: N! = N * (N-1)!\n");
            printf("------------------------\n");
            
            ans = Factorial(Number); // เรียกใช้ฟังก์ชัน Recursive
            
            printf("------------------------\n");
            printf("Answer %d! = %d\n", Number, ans);
            printf("------ Finished ------\n");
        } else {
            printf("Error: Please enter a positive number.\n");
        }
    }

    return 0;
}