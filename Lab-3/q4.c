#include <stdio.h>
#include <stdlib.h>


int **allocateMatrix(int n)
{
    int **matrix = malloc(n * sizeof(int *));

    if (matrix == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        matrix[i] = malloc(n * sizeof(int));

        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    return matrix;
}

void freeMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}


void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}


void strassen(int **A, int **B, int **C, int n)
{
    /* Base case */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }


    int k = n / 2;


    int **A11 = allocateMatrix(k);
    int **A12 = allocateMatrix(k);
    int **A21 = allocateMatrix(k);
    int **A22 = allocateMatrix(k);

    int **B11 = allocateMatrix(k);
    int **B12 = allocateMatrix(k);
    int **B21 = allocateMatrix(k);
    int **B22 = allocateMatrix(k);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];

            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];

            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }


 
    int **M1 = allocateMatrix(k);
    int **M2 = allocateMatrix(k);
    int **M3 = allocateMatrix(k);
    int **M4 = allocateMatrix(k);
    int **M5 = allocateMatrix(k);
    int **M6 = allocateMatrix(k);
    int **M7 = allocateMatrix(k);

    int **T1 = allocateMatrix(k);
    int **T2 = allocateMatrix(k);


    addMatrix(A11, A22, T1, k);
    addMatrix(B11, B22, T2, k);

    strassen(T1, T2, M1, k);


    addMatrix(A21, A22, T1, k);

    strassen(T1, B11, M2, k);


    subtractMatrix(B12, B22, T2, k);

    strassen(A11, T2, M3, k);


    subtractMatrix(B21, B11, T2, k);

    strassen(A22, T2, M4, k);


    addMatrix(A11, A12, T1, k);

    strassen(T1, B22, M5, k);


    subtractMatrix(A21, A11, T1, k);
    addMatrix(B11, B12, T2, k);

    strassen(T1, T2, M6, k);


    subtractMatrix(A12, A22, T1, k);
    addMatrix(B21, B22, T2, k);

    strassen(T1, T2, M7, k);


    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] =
                M1[i][j]
                + M4[i][j]
                - M5[i][j]
                + M7[i][j];
        }
    }


    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j + k] =
                M3[i][j]
                + M5[i][j];
        }
    }


    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i + k][j] =
                M2[i][j]
                + M4[i][j];
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i + k][j + k] =
                M1[i][j]
                - M2[i][j]
                + M3[i][j]
                + M6[i][j];
        }
    }



    freeMatrix(A11, k);
    freeMatrix(A12, k);
    freeMatrix(A21, k);
    freeMatrix(A22, k);

    freeMatrix(B11, k);
    freeMatrix(B12, k);
    freeMatrix(B21, k);
    freeMatrix(B22, k);

    freeMatrix(M1, k);
    freeMatrix(M2, k);
    freeMatrix(M3, k);
    freeMatrix(M4, k);
    freeMatrix(M5, k);
    freeMatrix(M6, k);
    freeMatrix(M7, k);

    freeMatrix(T1, k);
    freeMatrix(T2, k);
}


int nextPowerOfTwo(int n)
{
    int power = 1;

    while (power < n)
        power *= 2;

    return power;
}


void printMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", A[i][j]);
        }

        printf("\n");
    }
}


int main(void)
{
    int n;

    printf("Enter the size of square matrices: ");
    scanf("%d", &n);


    if (n <= 0)
    {
        printf("Invalid matrix size.\n");
        return 1;
    }


    int size = nextPowerOfTwo(n);


    int **A = allocateMatrix(size);
    int **B = allocateMatrix(size);
    int **C = allocateMatrix(size);


    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            A[i][j] = 0;
            B[i][j] = 0;
            C[i][j] = 0;
        }
    }

    printf("\nEnter elements of Matrix A:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }


    printf("\nEnter elements of Matrix B:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }


    strassen(A, B, C, size);


    printf("\nResultant Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", C[i][j]);
        }

        printf("\n");
    }

    freeMatrix(A, size);
    freeMatrix(B, size);
    freeMatrix(C, size);


    return 0;
}