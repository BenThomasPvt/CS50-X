#include<stdio.h>
#include<cs50.h>

int main (void)
{
    char c = get_char("Yes(y) or No(n) ? ");
    if (c=='n'||c=='N')
    {
        printf("Not agreed\n");
    }
    else if (c=='y' || c=='Y')
    {
        printf("Agreed\n");
    }
}