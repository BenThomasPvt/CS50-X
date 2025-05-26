#include<stdio.h>
#include<cs50.h>

int main (void)
{
    int x = get_int("What is the value of x ? ");
    int y = get_int("What is the value of y ? ");

    if (x<y)
    {
        printf("X is less than Y \n");
    }
    else if(y<x)
    {
        printf("Y is less than X\n");
    }
    else
    {
        printf("X and y are equal\n");
    }
}