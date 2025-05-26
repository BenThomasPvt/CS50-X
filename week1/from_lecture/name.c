#include <stdio.h>
#include <cs50.h>
int main(void)
{
    printf("Hello, World\n");
    string answer = get_string("What is your name ? ");
    printf("Hello %s\n",answer);
}