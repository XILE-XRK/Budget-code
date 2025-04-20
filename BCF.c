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
    char il[100] = " Budget Recommendations";
    int debt_payment = 0;
    /*Recalculate medical,gas,groceries,subscription services. by multiplying by 12*/
    strcat(usrname,il);
    FILE *Rdv = fopen(usrname,"w");
    if(Rdv==NULL){
        printf("\nFATAL ERROR\nFile /%s/ failed to open\n",usrname);
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
        fprintf(Rdv,"\nYou have %.2f saved for emergencies and %d dependent(s), this isn't recommended because when something happens when you least expect it your emergency fund of %.2f won't be sufficient for what you would likely need to cover these emergencies.\nWe recommend an Emergency fund exceeding $3,500 for %d dependents",Emergency_Fund,dependents,Emergency_Fund,dependents);
        Emergency_Fund = 4000;
    }
    else{
        fprintf(Rdv,"\nIt seems you have a sufficient amount of money saved up in your emergency fund for the %d dependent(s) you have",dependents);
    }
    if(income2<loan_amount){
        fprintf(Rdv,"\nMajor problem here, You are in more debt than money you make a year, You'll need to start allocating at least 15%% of your income to paying off this debt starting with the smallest current loan. That puts you at %.2f payments per month towards this debt.",(income2*.15)/12);
        debt_payment = (income2*.15)/12;
        fprintf(Rdv,"\nSince this is the case, you will have to go without any fun expenses such as eating out and more until we get this situation under control. Your expenses should be as close to 0 as you can get them.");
        expenses1 = expenses1*0;
    }
    else if(income2*.5<loan_amount){
        fprintf(Rdv,"\nYour total loan amount seems to be more that 50%% of your income, which is an issue, its not as bad as you having more loans than your income, but it's not ideal. We can manage by dedicating, 17%% of your yearly income which is %.2f to trying to pay off this debt. If the debt is resulting form car payments.",income2*.17);
        fprintf(Rdv,"Then I'd recommend you trade in that car for a cheaper car that you can afford, as long as you have something that gets you from point a to point b That should be good enough to work.");
        debt_payment = (income2*.17)/12;
    }
    else if(income2*.5>loan_amount)
    {
        fprintf(Rdv,"\nYour total loan amount seems to be under 50 percent of your total income which is good. But its not zero, so lets get that paid off.\nI recommend you start allocating 20%% of your income to paying this debt off, as the close you get to being debt free, the more you will be able to dedicate some of your income to saving");
        debt_payment = (income2*.20)/12;//calculates the amount you should put towards debt monthly 
    }

    fclose(Rdv);
}
