#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EXPENSES 50
#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    float amount;
} Expense;

void write_report(const char* filename, float gross, float taxRate, float net, Expense expenses[], int count, float total, float remaining, float percent) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error writing report file.\n");
        return;
    }

    fprintf(file, "===== Monthly Budget Report =====\n");
    fprintf(file, "Gross Income      : $%.2f\n", gross);
    fprintf(file, "Tax Deduction     : %.2f%%\n", taxRate);
    fprintf(file, "Net Income        : $%.2f\n\n", net);

    fprintf(file, "Expenses:\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, " - %s: $%.2f\n", expenses[i].name, expenses[i].amount);
    }

    fprintf(file, "\nTotal Expenses    : $%.2f\n", total);
    fprintf(file, "Remaining Balance : $%.2f\n", remaining);
    fprintf(file, "Budget Used       : %.2f%%\n", percent);

    fclose(file);
    printf("Report saved to '%s'\n", filename);
}

void append_history(const char* filename, float gross, float taxRate, float net, float total, float remaining, float percent) {
    FILE* file = fopen(filename, "a");
    if (!file) {
        printf("Error appending history file.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "[%d-%02d-%02d %02d:%02d] Income: $%.2f, Tax: %.2f%%, Net: $%.2f, Expenses: $%.2f, Remaining: $%.2f, Used: %.2f%%\n",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min,
            gross, taxRate, net, total, remaining, percent);

    fclose(file);
}

int main() {
    float income, netIncome, taxRate;
    Expense expenses[MAX_EXPENSES];
    int expenseCount;
    char repeat;

    do {
        printf("Enter gross monthly income: $");
        scanf("%f", &income);

        printf(" Enter tax percentage (e.g. 20 for 20%%): ");
        scanf("%f", &taxRate);

        netIncome = income - (income * (taxRate / 100.0));

        printf(" Enter number of expense categories: ");
        scanf("%d", &expenseCount);
        if (expenseCount > MAX_EXPENSES) {
            printf("Too many expenses. Max allowed: %d\n", MAX_EXPENSES);
            continue;
        }

        float totalExpenses = 0.0;
        for (int i = 0; i < expenseCount; i++) {
            printf(" Enter name of expense #%d: ", i + 1);
            scanf(" %[^\n]%*c", expenses[i].name); // to read strings with spaces

            printf("   Amount for %s: $", expenses[i].name);
            scanf("%f", &expenses[i].amount);
            totalExpenses += expenses[i].amount;
        }

        float remaining = netIncome - totalExpenses;
        float percentUsed = (totalExpenses / netIncome) * 100.0;

        printf("\n====== Budget Summary ======\n");
        printf("Net Income        : $%.2f\n", netIncome);
        printf("Total Expenses    : $%.2f\n", totalExpenses);
        printf("Remaining Balance : $%.2f\n", remaining);
        printf("Budget Used       : %.2f%%\n", percentUsed);
        printf("================================\n");

        write_report("budget_report.txt", income, taxRate, netIncome, expenses, expenseCount, totalExpenses, remaining, percentUsed);
        append_history("budget_history.txt", income, taxRate, netIncome, totalExpenses, remaining, percentUsed);

        printf(" Would you like to enter another month's budget? (Y/N): ");
        scanf(" %c", &repeat);

    } while (repeat == 'Y' || repeat == 'y');

    printf(" Exiting Budget Calculator. Stay financially stable! \n");
    return 0;
}
