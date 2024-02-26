#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int hash;
    do
    {
        printf("Input an height: ");
        scanf("%d", &hash);
        printf("\n");
        while (getchar() != '\n');
    }
    while (hash <= 0 || hash >= 9);
    int j = 0;
    int i = 0;
    for (i; i < hash; i++)
    {
        for (j = i; j < hash - 1; j++)
        {
            printf(" ");
        }
        for (j = - 1; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (j = - 1; j < i ; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}