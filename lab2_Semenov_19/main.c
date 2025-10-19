#include <cstdio>

unsigned int gcd(unsigned int num1, unsigned int num2)
{
    while(num2)
    {
        unsigned int tempNum = num1 % num2;
        num1 = num2;
        num2 = tempNum;
    }
    return num1;
}

unsigned int lcm(unsigned int num1, unsigned int num2)
{
    if (num1 == 0 || num2 == 0) return 0;
    unsigned int gcdNum = gcd(num1, num2);
    return (num1*num2) / gcdNum;
}

int main()
{
    unsigned int num1;
    unsigned int num2;
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
            printf("Enter two unsigned integers: ");
            scanf("%u %u", &num1, &num2);

            unsigned int lcmNum = lcm(num1, num2);
            printf("LCM(%u, %u) = %u\n", num1, num2, lcmNum);
        }
        else
        {
            printf("\nInvalid character, try again");
        }
    }
}