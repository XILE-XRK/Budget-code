// Sum of multiple incomes
/*
float calculate_total_income(float incomes[], int count) {
    float total = 0.0;
    for (int i = 0; i < count; i++) {
        total += incomes[i];
    }
    return total;
}
*/

// Sum of car loan
float calculate_total_car_loan(float car_payment, int months_left) {
    return car_payment * months_left;
}

// Combine existing loan and car loan
float calculate_total_loans(float existing_loan, float car_loan) {
    return existing_loan + car_loan;
}

// Utility sum (can be updated for multiple utility types if needed)
/*
float calculate_utility_total(float utilities[], int count) {
    float total = 0.0;
    for (int i = 0; i < count; i++) {
        total += utilities[i];
    }
    return total;
}
    */

// Asset reporting

// Balance calculation (Income - Total Expenses)
float calculate_remaining_balance(float income, float expenses, float total_loans,float car_payment,int Emergency_Fund) {
    return income - (expenses+total_loans+car_payment+Emergency_Fund);
}


// Expense as a percentage of income
float calculate_expense_percentage(float income, float expenses) {
    if (income == 0) return 0;
    return (expenses / income) * 100;
}
