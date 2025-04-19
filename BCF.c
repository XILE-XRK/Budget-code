// Sum of car loan
float calculate_total_car_loan(float car_payment, int months_left) {
    return car_payment * months_left;
}

// Combine existing loan and car loan
float calculate_total_loans(float existing_loan, float car_loan) {
    return existing_loan + car_loan;
}
float calculate_remaining_balance(float income, float expenses, float total_loans,
    float car_payment, int Emergency_Fund, int dependents,
    float groceries, float gas, float medical) {
float total_expenses = expenses + total_loans + car_payment + Emergency_Fund +
(groceries * 12) + (gas * 12) + (medical * 12);
return income - total_expenses;
}

// Expense as a percentage of income
float calculate_expense_percentage(float income, float expenses) {
    if (income == 0) return 0;
    return (expenses / income) * 100;
}
void budgetadvise(char usrname[],float income2,float left_over_income,float loan_amount,float util,int dependents,float assets,float expenses1,float Emergency_Fund,float groceries,float gas, float subserv/*Subscription services*/,float medical){
    char il[100] = "Budget Recommendations";
    /*Recalculate medical,gas,groceries,subscription services. by multiplying by 12*/
    strcat(usrname,il);
    FILE *Rdv = fopen(usrname,"W");
    if(Rdv==NULL){
        printf("\nFATAL ERROR\n\nFile /%s/ failed to open",usrname);
    }
    int inda = 0;
    float expense_limit = income2*.26;
    if(expense_limit<=expenses1){
        inda++;
    }
    else{
        inda = 0;
    }
    fprintf(Rdv,"Considering all of the information you have filled in for the budget app, Here is a plan, talor made for you\n");
    fprintf(Rdv,"\nAfter subtracting all of the expenses loans etc that was entered, you have $%.2f left over ",left_over_income);
    if(inda == 1){
        fprintf(Rdv,"\nConsidering you are spending over the what we reccomend you allocate towards spending, which is around 26%% its recommended you start allocating $%.2f to expenses instead",expense_limit);
    }
    else if(inda ==0)
    {
        fprintf(Rdv,"\nConsidering you are spending under or exactly at the percentage of spending that we reccomend which is 26%%, your spending amount of $%.2f seems in line with whats recommended\n",expenses1);
    }
    if(dependents==0&&Emergency_Fund>=1000)
    {
        fprintf(Rdv,"\nBased on the statement that you have Zero dependents its advised that you continue to keep the $%.2f dollars or above that you have saved for emergencies.",Emergency_Fund);
    }
    else if(dependents>0&&Emergency_Fund<=1000)
    {
        fprintf(Rdv,"\nYou have %f saved for emergencies and %d dependents, this isn't recommended because when something happens when you least expect it your emergency fund of %.2f won't be sufficient for what you would likely need to cover these emergencies.\nWe recommend an Emergency fund exceeding $4,000 for %d dependents",Emergency_Fund,dependents,Emergency_Fund,dependents);
    }
    else{

    }

}
