// D5F9AC

#include <stdio.h>
#include <ctype.h>

int main()
{
    const float cola_price = 0.75;
    const float candy_price = 1.25;
    const float popcorn_price = 0.5;

    int num_cola = 5;
    int num_candy = 5;
    int num_popcorn = 5;

    float total_profit = 0.0;
    float change = 0.0;
    float cash_amt = 0.0;
    int choice_num = 0;

    int value_scanf = 0;

    // Menu options printed
    printf("Welcome to the Vending Machine!\n");
    printf("Enter your choice by # and input cash amount, repeatedly (^d to end).\n");
    printf("[0] %d cola left: cost is $0.75\n", num_cola);
    printf("[1] %d candybar left: cost is $1.25\n", num_candy);
    printf("[2] %d popcorn left: cost is $0.50\n", num_popcorn);
    printf("Money made so far is $%.2f\n", total_profit);

    // collect user input and corresponding output + handling errors
    while ((value_scanf = scanf(" %d %f", &choice_num, &cash_amt)) == 2)
    {
        if (num_cola == 0 || num_candy == 0 || num_popcorn == 0)
        {
            printf("invalid item\n");
            return 1;
        }
        if (cash_amt < 0.0)
        {
            printf("malformed expression\n");
            return 1;
        }
        // identifies user choice
        switch (choice_num)
        {
        case 0:
            change = cash_amt - cola_price;
            if (change < 0)
            {
                printf("Not enough money\n");
                return 1;
            }
            else
            {
                printf("cola is dispensed and $%.2f returned\n", change);
                total_profit += cola_price;
            }
            num_cola--;

            break;
        case 1:
            change = cash_amt - candy_price;
            if (change < 0)
            {
                printf("Not enough money\n");
                return 1;
            }
            else
            {
                printf("candybar is dispensed and $%.2f returned\n", change);
                total_profit += candy_price;
            }
            num_candy--;
            break;
        case 2:
            change = cash_amt - popcorn_price;
            if (change < 0)
            {
                printf("Not enough money\n");
                return 1;
            }
            else
            {
                printf("popcorn is dispensed and $%.2f returned\n", change);
                total_profit += popcorn_price;
            }
            num_popcorn--;
            break;
        default:
            printf("invalid item\n");
            return 1;
        }
        // print updated menu
        printf("[0] %d cola left: cost is $0.75\n", num_cola);
        printf("[1] %d candybar left: cost is $1.25\n", num_candy);
        printf("[2] %d popcorn left: cost is $0.50\n", num_popcorn);
        printf("Money made so far is $%.2f\n", total_profit);
    }

    // if string is entered as input for an int or float, handles corresponding error
    if (value_scanf == 0 || value_scanf == 1)
    {
        printf("malformed expression\n");
        return 1;
    }

    // ending message
    printf("Thanks for your patronage!\n");
    return 0;
}
