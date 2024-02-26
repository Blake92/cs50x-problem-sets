#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit = get_long("Number: ");
    int y = 1;
    long i = 10;
    int firstN;
    while (credit % i != credit)
    {
        i = i * 10;
        y++;
    }
    int x [y];
    i = 10;
    long loop;
    for (int z = 0; z < y; z++)
    {
        loop = credit % i;
        long deloop = i / 10;
        x[z] = loop / deloop;
        i = i * 10;
    }
    firstN = (x[y - 1] * 10) + x[y - 2];
    int chksum = 0;
    for (int z = 1; z < y; z = z + 2)
    {
        i = x[z] * 2;
        if (i >= 10)
        {
            i = (i % 10) + (i / 10);
        }
        chksum = i + chksum;
    }
    for (int z = 0; z < y; z = z + 2)
    {
        chksum = x[z] + chksum;
    }
    if (chksum % 10 == 0)
    {
        if (y == 15)
        {
            switch (firstN)
            {
                case 34:
                    printf("AMEX\n");
                    break;
                case 37:
                    printf("AMEX\n");
                    break;
                default:
                    printf("INVALID\n");
                    break;
            }
        }
        else if (y == 16)
        {
            if (firstN / 10 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                switch (firstN)
                {
                    case 51:
                        printf("MASTERCARD\n");
                        break;
                    case 52:
                        printf("MASTERCARD\n");
                        break;
                    case 53:
                        printf("MASTERCARD\n");
                        break;
                    case 54:
                        printf("MASTERCARD\n");
                        break;
                    case 55:
                        printf("MASTERCARD\n");
                        break;
                    default:
                        printf("INVALID\n");
                        break;
                }
            }
        }
        else if (y == 13)
        {
            if (firstN / 10 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}