#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask height within range : 1 - 8 (do while)
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    //Do a left aligned pyramid
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            printf(" ");
        }
        for (int k = 1; k <= (n - (n - i)); k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
