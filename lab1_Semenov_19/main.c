#include <stdio.h>
#include <stdbool.h>

double readNumber(const char* prompt)
{
    double number;
    printf("%s", prompt);
    scanf("%lf", &number);
    return number;
}

bool isAscending(double num1, double num2, double num3)
{
    return (num1 < num2 && num2 < num3);
}

int main(void)
{
    double num1;
    double num2;
    double num3;
    char symbol;

    while (true)
    {
        printf("\nPress \"+\" to continue the program or \"-\" to exit.\n");
        scanf("%c", &symbol);
        if (symbol == '-')
        {
            return 0;
        }
        else if (symbol == '+')
        {
            num1 = readNumber("Enter the first number: ");
            num2 = readNumber("\nEnter the second number: ");
            num3 = readNumber("\nEnter the third number: ");

            if (isAscending(num1, num2, num3))
            {
                printf("\nThe numbers form an ascending sequence.");
            }
            else
            {
                printf("\nThe numbers do NOT form an ascending sequence.");
            }
        }
        else
        {
            printf("\nInvalid character, try again");
        }
    }
}
