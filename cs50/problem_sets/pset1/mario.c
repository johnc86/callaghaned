#include <cs50.h>
#include <stdio.h>

void pyramid(int h);
void pyraup(int h, int b);
void pyradown(int h, int b);

int main(void)
{
    printf("height: ");
    int h = get_int();
    while (h < 0 || h > 23) //check user input
    {
        printf("Retry: ");
        h = get_int();
    }
    pyramid(h);
}

void pyramid(int h)
{
    int b = h; // blocks
    for (int r = 0; r < h; r++)
    {
        b--;
        pyraup(h, b);
        printf("  ");
        pyradown(h, b);
        printf("\n");
    }
}

void pyraup(int h, int b)
{
    for (int i = 0; i < b; i++)
        {
            printf(" ");
        }
    for (int i = 0; i < h-b; i++)
        {
            printf("#");
        }
}

void pyradown(int h, int b)
{
    for (int i = 0; i < h-b; i++)
        {
            printf("#");
        }
}