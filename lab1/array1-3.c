#include <stdio.h>
#include <stdlib.h>

#define l 1
#define u 5

#define l1 1
#define u1 3

#define l2 1
#define u2 4

#define l3 1
#define u3 5

int *BA1, *BA2, *BA3, *p;
int i, j, k;

/* ---------- 1D ---------- */
void Create1DArray()
{
    int element = (u - l + 1);
    int c = sizeof(*BA1);
    int total_mem = element * c;
    BA1 = (int *)malloc(total_mem);
    if (!BA1)
    {
        perror("malloc BA1");
        exit(EXIT_FAILURE);
    }
}

void A1(int i, int x)
{
    p = BA1 + (i - l);
    *p = x;
}

int ReadA1(int i)
{
    p = BA1 + (i - l);
    return *p;
}

/* ---------- 2D ---------- */
void Create2DArray()
{
    int element = (u1 - l1 + 1) * (u2 - l2 + 1);
    int c = sizeof(*BA2);
    int total_mem = element * c;
    BA2 = (int *)malloc(total_mem);
    if (!BA2)
    {
        perror("malloc BA2");
        exit(EXIT_FAILURE);
    }
}

void A2(int i, int j, int x)
{
    p = BA2 + ((i - l1) * (u2 - l2 + 1) + (j - l2));
    *p = x;
}

int ReadA2(int i, int j)
{
    p = BA2 + ((i - l1) * (u2 - l2 + 1) + (j - l2));
    return *p;
}

/* ---------- 3D ---------- */
/* Create same memory buffer for 3D (linearized) */
void Create3DArray()
{
    int element = (u1 - l1 + 1) * (u2 - l2 + 1) * (u3 - l3 + 1);
    int c = sizeof(*BA3);
    int total_mem = element * c;
    BA3 = (int *)malloc(total_mem);
    if (!BA3)
    {
        perror("malloc BA3");
        exit(EXIT_FAILURE);
    }
}

/* Method 1 (เดิม) - row-major แบบ i เป็น major (i เปลี่ยนช้าที่สุด) */
void A3_rowMajor(int i, int j, int k, int x)
{
    int n2 = (u2 - l2 + 1);
    int n3 = (u3 - l3 + 1);
    p = BA3 + ((i - l1) * n2 * n3 + (j - l2) * n3 + (k - l3));
    *p = x;
}

int ReadA3_rowMajor(int i, int j, int k)
{
    int n2 = (u2 - l2 + 1);
    int n3 = (u3 - l3 + 1);
    p = BA3 + ((i - l1) * n2 * n3 + (j - l2) * n3 + (k - l3));
    return *p;
}

/* Method 2 (ใหม่) - column-major แบบ i เป็น fastest (i เปลี่ยนเร็วสุด)
   mapping index = (k-l3) * (n1*n2) + (j-l2) * n1 + (i-l1)
   โดย n1 = u1-l1+1, n2 = u2-l2+1, n3 = u3-l3+1
*/
void A3_colMajor(int i, int j, int k, int x)
{
    int n1 = (u1 - l1 + 1);
    int n2 = (u2 - l2 + 1);
    /* index = (k-l3)*n1*n2 + (j-l2)*n1 + (i-l1) */
    p = BA3 + ((k - l3) * n1 * n2 + (j - l2) * n1 + (i - l1));
    *p = x;
}

int ReadA3_colMajor(int i, int j, int k)
{
    int n1 = (u1 - l1 + 1);
    int n2 = (u2 - l2 + 1);
    p = BA3 + ((k - l3) * n1 * n2 + (j - l2) * n1 + (i - l1));
    return *p;
}

int main()
{
    printf("1-3 DIMENSION ARRAY FUNCTION (with 2 methods for 3D)...\n");
    printf("========================================================\n");

    Create1DArray();
    Create2DArray();
    Create3DArray();

    /* 1D test */
    i = 2;
    A1(i, 9);
    printf("\nA1(%d) = %d\n", i, ReadA1(i));

    /* 2D test */
    i = 2;
    j = 3;
    A2(i, j, 99);
    printf("A2(%d,%d) = %d\n", i, j, ReadA2(i, j));

    /* 3D test - method 1 (เดิม row-major) */
    i = 3;
    j = 4;
    k = 5;
    A3_rowMajor(i, j, k, 999);
    printf("A3_rowMajor(%d,%d,%d) = %d\n", i, j, k, ReadA3_rowMajor(i, j, k));

    /* 3D test - method 2 (ใหม่ col-major) */
    /* note: เราเขียนตำแหน่งอื่นเพื่อไม่ให้ทับค่าเดิมของตัวอย่างข้างบน
       ตัวอย่างนี้แสดงการเขียนและอ่านโดยใช้วิธีใหม่ */
    i = 1;
    j = 1;
    k = 1;
    A3_colMajor(i, j, k, 111);
    printf("A3_colMajor(%d,%d,%d) = %d\n", i, j, k, ReadA3_colMajor(i, j, k));

    /* แสดงว่า ถ้าเขียนด้วยวิธีหนึ่ง แล้วอ่านด้วยอีกวิธีก็จะได้ค่าต่างกัน (เพราะ mapping ต่างกัน) */
    printf("\n(หมายเหตุ: BA3 เป็น buffer เดียวกัน — mapping สองแบบต่างกันจะเข้าถึงตำแหน่งต่างกัน)\n");

    printf("\nPress ENTER to exit...");
    getchar();

    free(BA1);
    free(BA2);
    free(BA3);

    return 0;
}