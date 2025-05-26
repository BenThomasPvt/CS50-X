#include <cs50.h>
#include <stdio.h>

int main(void)
{
    unsigned long number = get_long("Number: ");
    unsigned long copy = number;
    int tenn, onee;
    int ten = 0, one = 0, length = 0;
    while (copy > 0)
    {
        onee = copy % 10;
        copy = copy / 10;
        one = one + onee;
        length++;
        tenn = 2 * (copy % 10);
        if (copy > 0)
            length++;
        if (tenn >= 10)
            tenn = (tenn % 10) + 1;
        copy = copy / 10;
        ten = ten + tenn;
    }
    int sum = ten + one;
    if (sum % 10 == 0)
    {
        unsigned long copy2 = number;
        while (copy2 >= 100)
        {
            copy2 = copy2 / 10;
        }
        if ((copy2 == 34 || copy2 == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else if ((copy2 / 10 == 4) && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else if ((copy2 >= 51 && copy2 <= 55) && (length == 16))
        {
            printf("MASTERCARD\n");
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
