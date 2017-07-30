#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How long was your shower?: ");
    int m = get_int();
    int b = m * 192 / 16; 
    //1.5g pm (192 ounces), 1 gallon 128 ounces, bottle is 16 ounces
    printf("You used %i bottles of water\n", b);
}