// Sum of car loan
#include <stdio.h>
#include <string.h>
#include <unistd.h>
float calculate_total_car_loan(float car_payment, int months_left) {
    return car_payment * months_left;
}

// Combine existing loan and car loan
float calculate_total_loans(float existing_loan, float car_loan) {
    return existing_loan + car_loan;
}
float calculate_remaining_balance(float income, float expenses, float total_loans,
    float car_payment, int Emergency_Fund, int dependents,
    float groceries, float gas, float medical,float insurance,float mortgage) {
float total_expenses = expenses + total_loans + car_payment + Emergency_Fund +
(groceries * 12) + (gas * 12) + (medical * 12)+(insurance*12)+(mortgage*12);
return income - total_expenses;
}

// Expense as a percentage of income
float calculate_expense_percentage(float income, float expenses) {
    if (income == 0) return 0;
    return (expenses / income) * 100;
}
void budgetadvise(char usrname[],float income2,float left_over_income,float loan_amount,float util,int dependents,float assets,float expenses1,float Emergency_Fund,float groceries,float gas, float subserv/*Subscription services*/,float medical,float insurance,float mortgage){
    char il[100] = " Budget Recommendations";
    int debt_payment = 0;
    float savings = 0,post_col_sav = 0;
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
    fprintf(Rdv,"Considering all of the information you have filled in for the budget app, Here is a plan, tailor made for you\n");
    fprintf(Rdv,"\nAfter subtracting all of the expenses loans etc that was entered, you have $%.2f left over ",left_over_income);
    if(inda == 1){
        fprintf(Rdv,"\nConsidering you are spending over the what we recommend you allocate towards spending, which is around 26%% its recommended you start allocating $%.2f to expenses instead",expense_limit);
    }
    else if(inda ==0)
    {
        fprintf(Rdv,"\nConsidering you are spending under or exactly at the percentage of spending that we recommend which is 26%%, your spending amount of $%.2f seems in line with what's recommended\n",expenses1);
    }
    if((dependents==0)&&(Emergency_Fund>=1000))
    {
        fprintf(Rdv,"\nBased on the statement that you have zero dependents its advised that you continue to keep the $%.2f dollars or above that you have saved for emergencies.",Emergency_Fund);
    }
    else if(dependents>0&&Emergency_Fund<=1000)
    {
        fprintf(Rdv,"\nYou have %.2f saved for emergencies and %d dependent(s), this isn't recommended because when something happens when you least expect it your emergency fund of %.2f won't be sufficient for what you would likely need to cover these emergencies.\nWe recommend an Emergency fund exceeding $3,500 for %d dependents",Emergency_Fund,dependents,Emergency_Fund,dependents);
        Emergency_Fund = 3500;
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
    else if((income2*.5>loan_amount)&&loan_amount>0)
    {
        fprintf(Rdv,"\nYour total loan amount seems to be under 50%% of your total income which is good. But its not zero, so lets get that paid off.\nI recommend you start allocating 20%% of your income to paying this debt off, as the close you get to being debt free, the more you will be able to dedicate some of your income to saving");
        debt_payment = (income2*.20)/12;//calculates the amount you should put towards debt monthly 
    }
    else{
        fprintf(Rdv,"\nSince it seems you are on the right track and have no debt to speak of I suggest you keep up the good work.");
        
        if(loan_amount==0){
            debt_payment = 0;
        } 
        else
        {
            debt_payment = (income2*.20)/12;
        }
    }
    if (((income2*.15)>=groceries*12)&&dependents<=1)
    {
        fprintf(Rdv,"\nFor Groceries, your spending is reasonable considering how many dependents you have. Keep up the good work.");
    }
    else if(((income2*.15)<=groceries*12)&&dependents<=1)
    {
        fprintf(Rdv,"\nYou are spending a little more than necessary for groceries considering you have one dependent but if your spending is under %.2f then it isn't a real issue",income2*.25);
        groceries = income2*.20;
    }
    else if (((income2*.15)<=groceries*12)&&dependents>=1)
    {
        fprintf(Rdv,"\nYou are over the recommended spending of 15%% for groceries, but considering you have %d dependents its understandable",dependents);
        if(groceries*12>(income2*.25)){
            fprintf(Rdv,"\nEven through you have %d dependents, you shouldn't really be spending over 25 percent of your yearly income on groceries alone, lets try to get that down to 25%%.",dependents);
            groceries = income2*.25;
        }
    }
    else if (((income2*.15)>=groceries*12)&&dependents>=1)
    {
        fprintf(Rdv,"\nConsidering you have %d dependents and you are not spending over the recommended amount of money per year for 1 dependent, its save to say you and your dependents aren't eating enough, its recommended that with the increasing dependent count that you increase your grocery spending up to 20-25 percent, in your case, we will raise the grocery spending to around that 20%% mark",dependents);
        groceries = income2*.20;
        if(groceries*12>(income2*.25)){
            fprintf(Rdv,"\nEven through you have %d dependents, you shouldn't really be spending over 25 percent of your yearly income on groceries alone, lets try to get that down to 25%%.",dependents);
            groceries = income2*.25;
        }
    }
    else{
        fprintf(Rdv,"\nYour spending overall is to much considering its over 15%% of your total income, and it seems like you have no dependents to justify this overspending. Your groceries should go down to 20%% since it seems you'd still would like to be on the higher end of the grocery spending ladder");
        groceries = income2*.20;
    }
    if((income2*.30)<loan_amount)
    {
        if(subserv>0)
        {
            fprintf(Rdv,"\nYour loan amount is greater than 30 percent of your income, which means we need to start cutting off things in order to pay for these loans, and I have an idea for something that we can cut off. That subscription services, lets go ahead and set those to zero because you don't really need them.");
            subserv = subserv*0;
        }
        else{
            fprintf(Rdv,"\nGood on you for not having any subscription services while you are in debt, you are one step closer to getting out of debt by having a way to reallocate money towards your debt.");
        }
        
    }
    fprintf(Rdv,"\nYou should be saving around 20%% of your income. So in your case around %.2f",income2*.25);
    savings = income2*.20;
    fprintf(Rdv,"\n\nMonthly Budget\n");
    fprintf(Rdv, "\n+-----------------------+---------------+\n");
    fprintf(Rdv, "| Category             | Value          |\n");
    fprintf(Rdv, "+-----------------------+---------------+\n");
    fprintf(Rdv, "| Income post tax       | %13.2f |\n", income2);
    fprintf(Rdv, "| Total Loans           | %13.2f |\n", loan_amount);
    fprintf(Rdv, "| Utilities (Monthly)   | %13.2f |\n", util);
    fprintf(Rdv, "| Dependents            | %13d |\n", dependents);
    fprintf(Rdv, "| Total Assets          | %13.2f |\n", assets);
    fprintf(Rdv, "| Total Expenses        | %13.2f |\n", expense_limit);
    fprintf(Rdv, "| Emergency Fund        | %13.2f |\n", Emergency_Fund);
    fprintf(Rdv, "| Grocery Bill          | %13.2f |\n", groceries);
    fprintf(Rdv, "| Gas Bill              | %13.2f |\n", gas);
    fprintf(Rdv, "| Monthly subscriptions | %13.2f |\n", subserv);
    fprintf(Rdv, "| Monthly Medical Bill  | %13.2f |\n", medical);
    fprintf(Rdv, "| Savings               | %13.2f |\n", savings);
    fprintf(Rdv, "| Monthly Insurance Bill| %13.2f |\n", insurance);
    fprintf(Rdv, "| Monthly Mortgage  Bill| %13.2f |\n", mortgage);
    fprintf(Rdv, "| Debt payments(Monthly)| %13.2f |\n", debt_payment);
    fprintf(Rdv, "+-----------------------+---------------+\n");
    fprintf(Rdv, "| Money Remaining       | %13.2f |\n", left_over_income);
    fprintf(Rdv, "+-----------------------+---------------+\n");
    if(left_over_income>1000)
    {
    fprintf(Rdv,"\n\nWith the $%.2f dollars that you have left over, Consider investing, giving to charity or",left_over_income);
    if(dependents>0)
    {
        fprintf(Rdv," if your dependents are children, consider putting 40%% of that towards their college fund. Which is %.2f per month",(left_over_income*.40)/12);
        post_col_sav = left_over_income - (left_over_income*.40);
        fprintf(Rdv," if you are feeling mighty gracious, you could take 15%% of that and dedicate that towards their marriage. Which is %.2f per month.\n",(post_col_sav*15)/12);
    }
    else{
        fprintf(Rdv," since you have have zero dependents, think about investing into a 401k, Roth IRA, Mutual Fund etc Make your money work for you we'd recommend you put 30%% towards that, which would put you at %.2f per month.",(left_over_income*.30)/12);
    }
}
    fclose(Rdv);
}
void flushInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
void printLoop(){
    int art =0;
    printf("\n");
    while(art<20)
    {
        printf("#");
        sleep(1);
        art++;
    }
    printf("\n");
    }
