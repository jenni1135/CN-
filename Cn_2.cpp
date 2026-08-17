#include <stdio.h>

int main()
{
    int data[20], hamming[30];
    int m, r = 0, i, j, p, parity;
    int received[30], syndrome = 0;

    printf("Enter number of data bits: ");
    scanf("%d", &m);
    while ((1 << r) < (m + r + 1))
        r++;

    printf("Enter data bits:\n");
    for (i = m; i >= 1; i--)
        scanf("%d", &data[i]);

    j = 1;

    for (i = 1; i <= m + r; i++)
    {
        if ((i & (i - 1)) == 0)
            hamming[i] = 0;
        else
            hamming[i] = data[j++];
    }

    for (i = 0; i < r; i++)
    {
        p = 1 << i;
        parity = 0;

        for (j = 1; j <= m + r; j++)
        {
            if (j & p)
                parity ^= hamming[j];
        }

        hamming[p] = parity;
    }

    printf("\nGenerated Hamming Code:\n");
    for (i = 1; i <= m + r; i++)
        printf("%d ", hamming[i]);

    printf("\n");

    printf("\nEnter received Hamming code:\n");
    for (i = 1; i <= m + r; i++)
        scanf("%d", &received[i]);

  
    syndrome = 0;

    for (i = 0; i < r; i++)
    {
        p = 1 << i;
        parity = 0;

        for (j = 1; j <= m + r; j++)
        {
            if (j & p)
                parity ^= received[j];
        }

        if (parity != 0)
            syndrome += p;
    }

    if (syndrome == 0)
    {
        printf("\nNo error detected.\n");
    }
    else
    {
        printf("\nError detected at position %d\n", syndrome);

       
        received[syndrome] = !received[syndrome];

        printf("Corrected Hamming Code:\n");
        for (i = 1; i <= m + r; i++)
            printf("%d ", received[i]);

        printf("\n");
    }

    return 0;
}