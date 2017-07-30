/**
 * Allows the user to input a credit card number and checks the validity using Luhn's algorithm
 * Created by John Callaghan in 2017 for cs50
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>

string get_cardnumber(int argc, string argv[]);
bool check_number(string cardnumber);
string get_brand(string cardnumber);
string err_number(void);

int main(int argc, string argv[])
{
    string cardnumber = get_cardnumber(argc, argv);
    while (check_number(cardnumber) == false)
    {
        printf("Retry: ");
        cardnumber = get_string();
    }
    
    int checksum = 0;
    
    // make a number array
    int digit[strlen(cardnumber)];
    for (int i = 0, n = strlen(cardnumber); i < n; i++)
    {
        digit[i] = (int) cardnumber[i]-48;
    }
    
    // --- apply Luhn's algorithm ---
    
    // Multiply every other digit by 2, starting with the number’s second-to-last digit
    
    // loop that starts with the 2nd to last character and moves backwards 2 at a time
    // multiplying numbers in the array as required
    for (int i = strlen(cardnumber)-2 ; i >= 0; i = i - 2)
    {
        digit[i] = digit[i]*2;
    }
    
    // then add all products' ** digits ** together.
    for (int i = 0, n = strlen(cardnumber); i < n; i++)
    {
        if (digit[i] > 9)
        {
            // if the number is more than 10, add those digits together rather than as a whole number
            checksum = checksum + (digit[i] % 10) + 1;
        }
        else
        {
            // otherwise just add
            checksum += digit[i];
        }
    }
                
    // check which brand the card is and is it the correct length for that brand
    string brandname = get_brand(cardnumber);

    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0)
    
    if (checksum % 10 != 0)	
    {
        brandname = "INVALID";
    }

    // All the checks were successful, success
    printf("%s\n", brandname);
    return 0;
}

// function to check for command line arguments or get string input if none exist
string get_cardnumber(int argc, string argv[])
{
    // check for command line arguments
    if (argc > 1)
    {
        // take argument 2 as the credit card number input
        return argv[1];
    }
    
    else
    {
        // fetch an input from the user
        printf("Number: ");
        return get_string();
    }
}

// check the string is numbers only, not null and not ridiculously short (<13)
bool check_number(string cardnumber)
{
    if (cardnumber == NULL)
    {
        return false;
    }
    else
    {
        for (int i = 0, n = strlen(cardnumber); i < n; i++)
        {
            // check for anything other than numbers
            if (cardnumber[i] < 48 || cardnumber[i] > 57)
            {
                return false;
            }
        }
    }
    return true;
}

// function to ake the first two digits of the string and identify card brand
string get_brand(string cardnumber)
{
    // get the brand number from the string
    int brand =  (int) ((cardnumber[0]-48)*10)+(cardnumber[1]-48);
    
    // compare the length of cardnumber against what we expect for each brand
    switch (brand)
    {
        // card is American Express - 15 digits
        case 34:
        case 37:
            return (strlen(cardnumber) == 15) ? "AMEX" : "INVALID";
            break;
        // card is Visa - 13 or 16 digits
        case 40 ... 49:
            if (strlen(cardnumber) == 13 || strlen(cardnumber) == 16)
            {
                return "VISA";
            }
            else
            {
                return "INVALID";
            }
            
            break;
        // card is Mastercard - 16 digits
        case 51 ... 55:
            return (strlen(cardnumber) == 16) ? "MASTERCARD" : "INVALID";
            break;
        default:
            return "INVALID";
            break;
    }
}

// function to get input again
string err_number(void)
{
    printf("Retry: ");
    return get_string();
}