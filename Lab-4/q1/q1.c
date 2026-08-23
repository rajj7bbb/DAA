#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Item
{
    int number;
    char color;
} Item;


typedef enum Colors 
{
    RED, 
    BLUE,
    YELLOW
} Colors;

void Display(Item* a, int length);
void SortedSort(Item* array, int length);

int main(){
    
    int n;
    printf("How many pairs do you want in the array?: ");
    scanf("%d", &n);

    printf("Now enter the items, number followed by color's initial.\n");

    Item* array;
    // printf("%lu\n", sizeof(Item)); // 8 in both sequences
    array = calloc(n, sizeof(Item));
    if (array == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return 1;
    }
    

    for (int i = 0; i < n; i++)
    {
        printf("Item %d: ", i + 1);
        scanf("%d", &(array[i].number));
        scanf(" %c", &(array[i].color));
        array[i].color = toupper(array[i].color);

        while ( (array[i].color != 'R') 
                && (array[i].color != 'Y')
                && (array[i].color != 'B'))
        {
            printf("\tInvalid input, try again!\n");
            printf("Item %d: ", i + 1);
            scanf("%d", &(array[i].number));
            scanf(" %c", &(array[i].color));
            array[i].color = toupper(array[i].color);
        }
    }
    printf("Unsorted: ");
    Display(array, n);

    printf("\nSorted: ");
    SortedSort(array, n);
    Display(array, n);
    free(array);
    return 0;
}

void Display(Item* a, int length)
{
    printf("{");
    for (int i = 0; i < length; i++)
    {
        printf("(%d, %c)", a[i].number, a[i].color);
        if (i < length - 1)
        {
            printf(", ");
        }
    }
    printf("}");
}


void SortedSort(Item* array, int length)
{
    int r_count = 0, b_count = 0;
    for (int i = 0; i < length; i++)
    {
        if(array[i].color == 'R')
        {
            r_count++;
        }
        else if (array[i].color == 'B')
        {
            b_count++;
        }
    }
    Item* result = calloc(length, sizeof(Item));
    if (result == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }
    
    int r = 0, b = r_count, y = b_count + r_count;
    for (int i = 0; i < length; i++)
    {
        if (array[i].color == 'R')
        {
            result[r++] = array[i]; 
        }
        else if (array[i].color == 'B')
        {
            result[b++] = array[i];
        }
        else
        {
            result[y++] = array[i];
        }
    }
    for (int i = 0; i < length; i++)
    {
        array[i] = result[i];
    }    
    free(result);
}