#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_1D  10
#define MAX_2D  5
#define MAX_3D  4

void printBinary(unsigned int value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        unsigned int mask = 1u << i;
        printf(value & mask ? "1" : "0");
        if (i % 4 == 0 && i != 0) printf(" ");
    }
}

int main(void) {
    int menu;

    do {
        printf("\n========== เมนูหลัก ==========\n");
        printf(" 1. short (signed)\n");
        printf(" 2. unsigned short\n");
        printf(" 3. int (signed)\n");
        printf(" 4. unsigned int\n");
        printf(" 5. long (signed)\n");
        printf(" 6. unsigned long\n");
        printf(" 7. float\n");
        printf(" 8. double\n");
        printf(" 9. char\n");
        printf("10. bool\n");
        printf("11. 1D int array\n");
        printf("12. 2D int array\n");
        printf("13. 3D int array\n");
        printf("14. string (char array)\n");
        printf(" 0. ออกจากโปรแกรม\n");
        printf("เลือกเมนู (0-14): ");
        if (scanf("%d", &menu) != 1) {
            printf("อินพุตไม่ถูกต้อง\n");
            return 0;
        }

        if (menu == 0) {
            printf("จบการทำงานของโปรแกรม\n");
            break;
        }

        if (menu == 1) {
            short x;
            printf("\n=== short (signed) ===\n");
            printf("ป้อนค่า short: ");
            scanf("%hd", &x);
            printf("ฐาน 10 : %hd\n", x);
            unsigned short ux = (unsigned short)x;
            printf("ฐาน 16 : 0x%hX\n", ux);
            printf("ฐาน 2  : ");
            printBinary((unsigned int)ux, sizeof(short) * 8);
            printf("\nขนาดข้อมูล : %zu byte\n", sizeof(short));
        }
        else if (menu == 2) {
            unsigned short x;
            printf("\n=== unsigned short ===\n");
            printf("ป้อนค่า unsigned short: ");
            scanf("%hu", &x);
            printf("ฐาน 10 : %hu\n", x);
            printf("ฐาน 16 : 0x%hX\n", x);
            printf("ฐาน 2  : ");
            printBinary((unsigned int)x, sizeof(unsigned short) * 8);
            printf("\nขนาดข้อมูล : %zu byte\n", sizeof(unsigned short));
        }
        else if (menu == 3) {
            int x;
            printf("\n=== int (signed) ===\n");
            printf("ป้อนค่า int: ");
            scanf("%d", &x);
            printf("ฐาน 10 : %d\n", x);
            printf("ฐาน 16 : 0x%X\n", (unsigned int)x);
            printf("ฐาน 2  : ");
            printBinary((unsigned int)x, sizeof(int) * 8);
            printf("\nขนาดข้อมูล : %zu byte\n", sizeof(int));
        }
        else if (menu == 4) {
            unsigned int x;
            printf("\n=== unsigned int ===\n");
            printf("ป้อนค่า unsigned int: ");
            scanf("%u", &x);
            printf("ฐาน 10 : %u\n", x);
            printf("ฐาน 16 : 0x%X\n", x);
            printf("ฐาน 2  : ");
            printBinary(x, sizeof(unsigned int) * 8);
            printf("\nขนาดข้อมูล : %zu byte\n", sizeof(unsigned int));
        }
        else if (menu == 5) {
            long x;
            printf("\n=== long (signed) ===\n");
            printf("ป้อนค่า long: ");
            scanf("%ld", &x);
            printf("ฐาน 10 : %ld\n", x);
            printf("ฐาน 16 : 0x%lX\n", (unsigned long)x);
            printf("ฐาน 2  : ");
            printBinary((unsigned int)x, sizeof(long) * 8);
            printf("\nขนาดข้อมูล : %zu byte\n", sizeof(long));
        }
        else if (menu == 6) {
            unsigned long x;
            printf("\n=== unsigned long ===\n");
            printf("ป้อนค่า unsigned long: ");
            scanf("%lu", &x);
            printf("ฐาน 10 : %lu\n", x);
            printf("ฐาน 16 : 0x%lX\n", x);
            printf("ฐาน 2  : ");
            printBinary((unsigned int)x, sizeof(unsigned long) * 8);
            printf("\nขนาดข้อมูล : %zu byte\n", sizeof(unsigned long));
        }
        else if (menu == 7) {
            float x;
            printf("\n=== float ===\n");
            printf("ป้อนค่า float: ");
            scanf("%f", &x);
            printf("ฐาน 10 : %f\n", x);
            printf("ฐาน 16 (ใช้รูปแบบ %%a ของ C): %a\n", x);
            printf("** ในระดับพื้นฐาน เราเน้นดูฐาน 10/16 ของ float ก่อน\n");
            printf("ขนาดข้อมูล : %zu byte\n", sizeof(float));
        }
        else if (menu == 8) {
            double x;
            printf("\n=== double ===\n");
            printf("ป้อนค่า double: ");
            scanf("%lf", &x);
            printf("ฐาน 10 : %lf\n", x);
            printf("ฐาน 16 (ใช้รูปแบบ %%a ของ C): %a\n", x);
            printf("ขนาดข้อมูล : %zu byte\n", sizeof(double));
        }
        else if (menu == 9) {
            char c;
            printf("\n=== char ===\n");
            printf("ป้อนค่า char 1 ตัว: ");
            scanf(" %c", &c);
            unsigned char uc = (unsigned char)c;
            printf("ตัวอักษร : '%c'\n", c);
            printf("ฐาน 10 (ASCII) : %u\n", (unsigned int)uc);
            printf("ฐาน 16 : 0x%X\n", (unsigned int)uc);
            printf("ฐาน 2  : ");
            printBinary((unsigned int)uc, 8);
            printf("\nขนาดข้อมูล : %zu byte\n", sizeof(char));
        }
        else if (menu == 10) {
            int temp;
            bool b;
            printf("\n=== bool ===\n");
            printf("ป้อนค่า (0 = false, อื่น ๆ = true): ");
            scanf("%d", &temp);
            b = (temp != 0);
            printf("ค่าเชิงตรรกะ : %s\n", b ? "true" : "false");
            unsigned int v = b ? 1u : 0u;
            printf("ฐาน 10 : %u\n", v);
            printf("ฐาน 16 : 0x%X\n", v);
            printf("ฐาน 2  : ");
            printBinary(v, sizeof(bool) * 8);
            printf("\nขนาดข้อมูล : %zu byte\n", sizeof(bool));
        }
        else if (menu == 11) {
            int n, i, arr[MAX_1D];
            printf("\n=== 1D int array ===\n");
            printf("จำนวนสมาชิก (ไม่เกิน %d): ", MAX_1D);
            scanf("%d", &n);
            if (n <= 0 || n > MAX_1D) {
                printf("ขนาดไม่ถูกต้อง\n");
            } else {
                for (i = 0; i < n; i++) {
                    printf("arr[%d] = ", i);
                    scanf("%d", &arr[i]);
                }
                printf("\nแสดงค่าทีละตัว:\n");
                for (i = 0; i < n; i++) {
                    printf("arr[%d] = %d  (dec)\n", i, arr[i]);
                    printf("           0x%X  (hex)\n", (unsigned int)arr[i]);
                    printf("           bin = ");
                    printBinary((unsigned int)arr[i], sizeof(int) * 8);
                    printf("\n");
                }
                printf("ขนาดรวมโดยประมาณ: %zu byte\n", n * sizeof(int));
            }
        }
        else if (menu == 12) {
            int r, c, i, j, arr[MAX_2D][MAX_2D];
            printf("\n=== 2D int array ===\n");
            printf("จำนวนแถว (ไม่เกิน %d): ", MAX_2D);
            scanf("%d", &r);
            printf("จำนวนคอลัมน์ (ไม่เกิน %d): ", MAX_2D);
            scanf("%d", &c);
            if (r <= 0 || r > MAX_2D || c <= 0 || c > MAX_2D) {
                printf("ขนาดไม่ถูกต้อง\n");
            } else {
                for (i = 0; i < r; i++) {
                    for (j = 0; j < c; j++) {
                        printf("arr[%d][%d] = ", i, j);
                        scanf("%d", &arr[i][j]);
                    }
                }
                printf("\nแสดงค่าทีละตำแหน่ง:\n");
                for (i = 0; i < r; i++) {
                    for (j = 0; j < c; j++) {
                        printf("(%d,%d) = %d (dec)\n", i, j, arr[i][j]);
                        printf("          0x%X (hex)\n", (unsigned int)arr[i][j]);
                        printf("          bin = ");
                        printBinary((unsigned int)arr[i][j], sizeof(int) * 8);
                        printf("\n");
                    }
                }
                printf("ขนาดรวมโดยประมาณ: %zu byte\n", (size_t)r * c * sizeof(int));
            }
        }
        else if (menu == 13) {
            int x, y, z, i, j, k, arr[MAX_3D][MAX_3D][MAX_3D];
            printf("\n=== 3D int array ===\n");
            printf("ขนาดมิติที่ 1 (ไม่เกิน %d): ", MAX_3D);
            scanf("%d", &x);
            printf("ขนาดมิติที่ 2 (ไม่เกิน %d): ", MAX_3D);
            scanf("%d", &y);
            printf("ขนาดมิติที่ 3 (ไม่เกิน %d): ", MAX_3D);
            scanf("%d", &z);
            if (x <= 0 || x > MAX_3D || y <= 0 || y > MAX_3D || z <= 0 || z > MAX_3D) {
                printf("ขนาดไม่ถูกต้อง\n");
            } else {
                for (i = 0; i < x; i++)
                    for (j = 0; j < y; j++)
                        for (k = 0; k < z; k++) {
                            printf("arr[%d][%d][%d] = ", i, j, k);
                            scanf("%d", &arr[i][j][k]);
                        }
                printf("\nแสดงค่าทีละตำแหน่ง:\n");
                for (i = 0; i < x; i++)
                    for (j = 0; j < y; j++)
                        for (k = 0; k < z; k++) {
                            int v = arr[i][j][k];
                            printf("(%d,%d,%d) = %d (dec)\n", i, j, k, v);
                            printf("             0x%X (hex)\n", (unsigned int)v);
                            printf("             bin = ");
                            printBinary((unsigned int)v, sizeof(int) * 8);
                            printf("\n");
                        }
                printf("ขนาดรวมโดยประมาณ: %zu byte\n", (size_t)x * y * z * sizeof(int));
            }
        }
        else if (menu == 14) {
            char str[100];
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("\n=== string (char array) ===\n");
            printf("ป้อนข้อความ (ไม่เกิน 99 ตัวอักษร, ไม่มีช่องว่างจะง่ายสุด): ");
            scanf("%99s", str);
            size_t len = strlen(str);
            printf("ข้อความ : %s\n", str);
            printf("ความยาว : %zu ตัวอักษร\n", len);
            printf("ขนาด buffer str : %zu byte\n", sizeof(str));
            printf("\nแสดงรายละเอียดแต่ละตัวอักษร:\n");
            for (size_t i = 0; i < len; i++) {
                unsigned char c = (unsigned char)str[i];
                printf("[%zu] '%c' -> dec=%u, hex=0x%X, bin=", i, c, (unsigned int)c, (unsigned int)c);
                printBinary((unsigned int)c, 8);
                printf("\n");
            }
        }
        else {
            printf("เมนูไม่ถูกต้อง ลองใหม่\n");
        }

    } while (1);

    return 0;
}
