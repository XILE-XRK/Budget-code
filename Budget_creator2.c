#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INFOLENGTH 20
#define TAX_RATE 0.09

// Function prototypes
float calculate_tax(float income);
float calculate_savings(float income);
float calculate_free_spending(float income);
float calculate_debt_payment(float loan_amount, int months);
float calculate_utilities(float util);

int main() {
    char usrname[INFOLENGTH];
    char paswrd[INFOLENGTH];
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
    printf("Yearly Income: $%.2f\n", income);
    printf("Tax Deduction: $%.2f\n", tax);
    printf("Suggested Savings: $%.2f\n", savings);
    printf("Free Spending Allowance: $%.2f\n", free_spending);
    printf("Debt Payments (monthly): $%.2f\n", debt_payment);
    printf("Utility Bills (monthly): $%.2f\n", utilities);
    printf("Number of Dependents: %d\n", dependents);
    printf("=================================\n");
    
    return 0;
}

// Function definitions
float calculate_tax(float income) {
    return income * TAX_RATE;
}

float calculate_savings(float income) {
    return income * 0.20; // 20% savings recommendation
}
  

