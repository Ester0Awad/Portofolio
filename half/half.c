// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: \n "  );
    float tax_percent = get_float("Sale Tax Percent:  \n");
    int tip_percent = get_int("Tip percent:  \n ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
     ? float e = get_float (tax + bill);
    ? float t = get_float (ester + tip);
    ? float h = (1/2 * t);
    return 0.0;
}
