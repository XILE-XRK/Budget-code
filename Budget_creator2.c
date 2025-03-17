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
    
  

