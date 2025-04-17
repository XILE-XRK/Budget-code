#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAX_RATE 0.09

// Function prototypes
float calculate_tax(float income);
float calculate_savings(float income);
float calculate_free_spending(float income);
float calculate_debt_payment(float loan_amount, int months);
float calculate_utilities(float util);

int main() {
    float income = 0, tax, savings, free_spending, debt_payment, utilities;
    float loan_amount = 0, util = 0;
    int carpaymonths = 0, dependents = 0;
    char confir;

    printf("Welcome to the budget app.\n");
    printf("Let's set up your budget.\n");

    printf("Enter your yearly income (without commas): ");
    scanf("%f", &income);

    tax = calculate_tax(income);
    savings = calculate_savings(income);
    free_spending = calculate_free_spending(income);

    printf("\nDo you have any outstanding loans? (Y/N): ");
    scanf(" %c", &confir);

    if (confir == 'Y' || confir == 'y') {
        printf("Enter your total loan amount: ");
        scanf("%f", &loan_amount);
        printf("Enter remaining months for repayment: ");
        scanf("%d", &carpaymonths);
        debt_payment = calculate_debt_payment(loan_amount, carpaymonths);
    } else {
        debt_payment = 0;
    }

    printf("Enter estimated monthly utility bills: ");
    scanf("%f", &util);
    utilities = calculate_utilities(util);

    printf("Enter number of dependents: ");
    scanf("%d", &dependents);

    // Display budget summary
    printf("\n========= Budget Summary =========\n");

