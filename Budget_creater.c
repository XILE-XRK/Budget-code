#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "BCF.c"
#define INFOLENGTH 60
void printLoop();
void flushInputBuffer(void);
int main() {
    char usrstat[INFOLENGTH] = {};
    char usrname[INFOLENGTH] = {};
    char paswrd[INFOLENGTH] = {};
    char iggy[INFOLENGTH] = "_budgetignore.txt";
    char paswrd2ndcheck[INFOLENGTH] = {};
    char line[1024];
    char passave[INFOLENGTH] = {};
    char confir[INFOLENGTH] = {};
    char temploc[1888] = {};
    char usrname1[INFOLENGTH] = {};
    int attempts = 0, ilios = 0, option = 0,option_x,dependents = 0, carpaymonths = 0,rs = 0,stat = 0,ZTX=0,izo = 0,zila = 0;
    float income = 0,income2 = 0,expenses1,tax_rate = 0.09,income_tax,loan_amount = 0,total_loan = 0,util = 0,carpay = 0,insurance = 0,assets = 0.0,carpayment = 0,groceries = 0,gas = 0, left_over_income = 0, subserv = 0, medical = 0,Emergency_Fund = 1000,car_payment = 0,mortgage = 0;

    printf("Welcome to the budget app.\n");
    printf("After providing some information, I will help you set up a budget to get you out of debt and improve your finances.\n");

    // Ask if the user is new or returning
    printf("\nAre you a returning user. or have you recently created an account? (yes/no): ");
    scanf("%s", usrstat);
    flushInputBuffer();
    while(stat==0){

    if (strcmp(usrstat,"Yes")==0||strcmp(usrstat,"yes")==0) {//compares the user response to the ascii codes. Use Strcmp and string arrays instead
        // Returning user login
        printf("\n\nWelcome back!\n\n");

        printf("Enter username: ");
        fgets(usrname,sizeof(usrname),stdin);
        usrname[strcspn(usrname, "\n")] = '\0';
        FILE *Usr1 = fopen(usrname, "r");
        while(ilios==0){

        while (ZTX!=3) {
            if (Usr1 == NULL) {
                printf("Username not recognized. Please try again or create a new account. Enter Q to exit\n");
                printf("You have %d attempt(s) left\n",3-ZTX);
                printf("Enter username: ");
                fgets(usrname,sizeof(usrname),stdin);
                usrname[strcspn(usrname, "\n")] = '\0';
                if(strncmp(usrname,"Q",1)==0||strncmp(usrname,"q",1)==0)
                {
                    printf("\nExiting");
                    sleep(2);
                    exit(0);
                }
                // Try to reopen with new input
                Usr1 = fopen(usrname, "r");  // reattempt open
                ZTX++;

            }
            else {
                ZTX=3;  // valid file found
                strcpy(usrname1,usrname);
            }
        }

        while (attempts < 3) {
            printf("Enter password: ");
            fgets(paswrd, sizeof(paswrd), stdin);
            paswrd[strcspn(paswrd, "\n")] = '\0';
        
            fscanf(Usr1, "%19s", paswrd2ndcheck); // Load the saved password
            //flushInputBuffer(); // Clean up any trailing characters
            fclose(Usr1);
        
            if (strcmp(paswrd, paswrd2ndcheck) == 0) {
                printf("\nPassword correct. Welcome!\n");
                ilios = 1;
                stat = 1;
                break;
            } else {
                printf("\nIncorrect password. Attempts remaining: %d\n", 2 - attempts);
                attempts++;
                if (attempts == 3) {
                    printf("Too many attempts.\nTry again later.");
                    return 1;
                }
                Usr1 = fopen(usrname, "r");
                if (Usr1 == NULL) {
                    printf("\nError reopening user file.\n");
                    ilios = 2;
                }
            }
        }
        
        }
    }

    else if (strcmp(usrstat,"No")==0||strcmp(usrstat,"no")==0) {
        //Checks to see if a username already exist or not.
        if (access(usrname, F_OK) != -1) {
            printf("\nThat username already exists. Please restart and choose a new one.\n");
            exit(1);
        }
        // New user account creation
        printf("\nLet's create your account.\n");

        printf("Enter a username (max 19 characters): ");
        //scanf("%19s",usrname);
        fgets(usrname,sizeof(usrname),stdin);
        usrname[strcspn(usrname, "\n")] = '\0';

            FILE *Usr = fopen(usrname, "w");
        if (Usr == NULL) {
            printf("\nError: Failed to create account.\n");
            ilios=2;
            exit(0);
            }
            printf("\nEnter a password:\n");
            fgets(paswrd,sizeof(paswrd),stdin);
            paswrd[strcspn(paswrd, "\n")] = '\0';

            fprintf(Usr, "%s\n", paswrd);
            fclose(Usr);//Get rid of in order to continue working with the code later.

            printf("\nAccount successfully created! You can now log in.\n");
            exit(0);

        }
    else {
        printf("\nInvalid input. Please restart the program and enter 'Yes' or 'No'.\n");
        scanf("%s",&usrstat);
        flushInputBuffer();

        }
    }
    if(ilios==1){
        printf("What actions would you like to perform today?\n");
        //Change the following menu into a function in order to clean it up and more easily add extra things in the future.
        printf("\n0 - Create a new budget\n\n1 - Update current budget plan.\n\n2 - Delete current budget plan\n\n3 - Print Your budget\n\n4 - Exit\n\n");//Update current budget plan
        scanf("%d",&option);
        printf("\nYou have chosen option %d",option);
        flushInputBuffer();
        FILE *Rs1 = fopen(usrname, "a");
        if(Rs1==NULL)
        {
            printf("Error 293\nterminating.");
            exit(0);
        }
        switch(option){
            case 0:
            while(rs == 0){
                // Confirmation loop for sensitive information
                while(1) {
                    printf("\nHello, in order to create your new budget plan I will have to collect some sensitive information.\n\nAre you sure you would like to proceed with this process? (Yes/No):\n");
                    fgets(confir, sizeof(confir), stdin);
                    confir[strcspn(confir, "\n")] = '\0';
        
                    if (strcmp(confir, "Yes") == 0 || strcmp(confir, "yes") == 0 || strcmp(confir, "YES") == 0) {
                        break; // valid input, continue
                    } else if (strcmp(confir, "No") == 0 || strcmp(confir, "no") == 0 || strcmp(confir, "NO") == 0) {
                        printf("I understand that you might not be willing to give up this information and that's perfectly fine.\nHave a nice day.");
                        fclose(Rs1);
                        exit(0);
                    } else {
                        printf("\nInvalid input, Try again.\n");
                    }
                }
        
                // Continue collecting budget info
                FILE *Usr1 = fopen(usrname, "r");
                if (Usr1 == NULL) {
                    printf("\nERROR 235\nTerminating");
                    return 1;
                }
                fgets(passave, sizeof(passave), Usr1);
                fclose(Usr1);
        
                FILE *Usr3 = fopen(usrname, "w");
                if (Usr3 == NULL) {
                    printf("\nERROR 234");
                    return 1;
                }
                fprintf(Usr3, "%s", passave);
                fclose(Usr3);
        
                printf("\nLet us continue\n");
        
                printf("\nEnter the total house yearly income (Without commas):\n");
                scanf("%f", &income);
                income2 = income - (income * tax_rate);
                printf("\nYou entered an income value of %.2f.\n", income);
        
                printf("\nDo you currently have any car payments? (Yes/No)\n");
                scanf(" %s", confir);
                flushInputBuffer();
        
                while(rs == 0){
                    if (strcmp(confir, "Yes") == 0 || strcmp(confir, "yes") == 0 || strcmp(confir, "Y") == 0 || strcmp(confir, "y") == 0) {
                        printf("\nHow many payments of what amount do you have left on your vehicle\n");
                        printf("Enter the monthly car payment:\n");
                        scanf("%f", &carpay);
                        flushInputBuffer();
        
                        printf("Enter the amount of months left to pay off the vehicle:\n");
                        scanf("%d", &carpaymonths);
                        flushInputBuffer();
        
                        car_payment = calculate_total_car_loan(carpay, carpaymonths);
                        rs = 1;
                    }
                    else if (strcmp(confir, "No") == 0 || strcmp(confir, "no") == 0 || strcmp(confir, "N") == 0 || strcmp(confir, "n") == 0) {
                        printf("\nThat's amazing, that's one less payment to worry about.\n");
                        rs = 1;
                    }
                    else {
                        printf("\nInvalid input, Try again.\n");
                        scanf(" %s", confir);
                        flushInputBuffer();
                    }
                }
        
                printf("\nEnter your current total loan amount:\n");
                scanf("%f", &loan_amount);
                total_loan = calculate_total_loans(car_payment, loan_amount);
        
                printf("\nEnter approximated amount of monthly utility bills:\n");
                scanf("%f", &util);
        
                printf("\nEnter number of dependents:\n");
                scanf("%d", &dependents);
                while(izo == 0){
                    if(dependents < 0){
                        printf("\nEnter a positive number:\n");
                        scanf("%d", &dependents);
                    } else {
                        izo++;
                    }
                }
        
                printf("\nEnter total expenses per month:\n");
                scanf("%f", &expenses1);
                expenses1 *= 12;
        
                printf("\nEnter your total assets:\n");
                scanf("%f", &assets);
        
                printf("\nEnter monthly grocery bill:\n");
                scanf("%f", &groceries);
        
                printf("\nEnter monthly gas expenses:\n");
                scanf("%f", &gas);
        
                printf("\nEnter your monthly subscription payments:\n");
                scanf("%f", &subserv);
        
                printf("\nEnter your monthly medical payments:\n");
                scanf("%f", &medical);
        
                printf("\nEnter your Emergency Fund:\n");
                scanf("%f", &Emergency_Fund);
                printf("\nEnter your monthly insurance bill.\n");
                scanf("%f",&insurance);
                printf("\nEnter your monthly mortgage bill.\n");
                scanf("%f",&mortgage);
        
                left_over_income = calculate_remaining_balance(income2, expenses1, total_loan, car_payment, Emergency_Fund, dependents, groceries, gas, medical, insurance, mortgage);
        
                printf("\nExcluding Assets, you should currently have %.2f left over considering all of the payments and expenses you have.", left_over_income);
                printf("\nPrinting your information in your file.\n");
                strcat(usrname1,iggy);
                FILE * NZXT = fopen(usrname1,"w");
                if(NZXT==NULL){
                    printf("\nFATAL ERROR 7838");
                    exit(0);
                }
                fprintf(Rs1, "\n+-----------------------+---------------+\n");
                fprintf(Rs1, "| Category              | Value         |\n");
                fprintf(Rs1, "+-----------------------+---------------+\n");
                fprintf(Rs1, "| Income post tax       | %13.2f|\n", income2);
                fprintf(NZXT,"%.2f",income2);
                fprintf(Rs1, "| Total Loans           | %13.2f|\n", loan_amount);
                fprintf(NZXT,"\n%.2f",loan_amount);
                fprintf(Rs1, "| Utilities (Annual)    | %13.2f|\n", util * 12);
                fprintf(NZXT,"\n%.2f",util);
                fprintf(Rs1, "| Dependents            | %13d  |\n", dependents);
                fprintf(NZXT,"\n%d",dependents);
                fprintf(Rs1, "| Total Assets          | %13.2f|\n", assets);
                fprintf(NZXT,"\n%.2f",assets);
                fprintf(Rs1, "| Total Expenses        | %13.2f|\n", expenses1);
                fprintf(NZXT,"\n%.2f",expenses1);
                fprintf(Rs1, "| Emergency Fund        | %13.2f|\n", Emergency_Fund);
                fprintf(NZXT,"\n%.2f",Emergency_Fund);
                fprintf(Rs1, "| Grocery Bill          | %13.2f|\n", groceries * 12);
                fprintf(NZXT,"\n%.2f",groceries);
                fprintf(Rs1, "| Gas Bill              | %13.2f|\n", gas * 12);
                fprintf(NZXT,"\n%.2f",gas);
                fprintf(Rs1, "| Monthly subscriptions | %13.2f|\n", subserv * 12);
                fprintf(NZXT,"\n%.2f",subserv);
                fprintf(Rs1, "| Monthly Medical Bill  | %13.2f|\n", medical * 12);
                fprintf(NZXT,"\n%.2f",medical);
                fprintf(Rs1, "| Monthly Insurance Bill| %13.2f|\n", insurance * 12);
                fprintf(NZXT,"\n%.2f",insurance);
                fprintf(Rs1, "| Monthly Mortgage Bill | %13.2f|\n", mortgage * 12);
                fprintf(NZXT,"\n%.2f",mortgage);
                fprintf(Rs1, "+-----------------------+---------------+\n");
                fprintf(Rs1, "| Money Remaining       | %13.2f|\n",left_over_income);
                fprintf(Rs1, "+-----------------------+---------------+\n");
                fclose(NZXT);
                fclose(Rs1);
                printf("\nExiting\n");
                sleep(2);
                budgetadvise(usrname, income2, left_over_income, loan_amount, util, dependents, assets, expenses1, Emergency_Fund, groceries, gas, subserv, medical,insurance,mortgage);
                exit(0);
            }
            break;
        
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                case 1:
                // Skip the password
                strcat(usrname1,iggy);
                fclose(Rs1);
                Rs1 = fopen(usrname,"r");
                if(Rs1==NULL){
                    printf("\nFile opening failed!");
                    exit(0);
                }
                fgets(passave, sizeof(passave), Rs1); // Read password line

                int hasData = 0;

                // Read the rest of the file, line by line
                while (fgets(temploc, sizeof(temploc), Rs1) != NULL) {
                    // Strip newline
                    temploc[strcspn(temploc, "\n")] = '\0';

                    // Check if line has any actual data (digits or alphabetic content)
                    for (int i = 0; temploc[i] != '\0'; i++) {
                        if ((temploc[i] >= '0' && temploc[i] <= '9') || 
                            (temploc[i] >= 'A' && temploc[i] <= 'Z') ||
                            (temploc[i] >= 'a' && temploc[i] <= 'z')) {
                            hasData = 1;
                            break;
                        }
                    }
                    if (hasData) break;
                }

                if (!hasData) {
                    printf("\nERROR 6575\nYou have no information to update\n");
                    fclose(Rs1);
                    exit(0);
                }
                fclose(Rs1);
                FILE *NZXT = fopen(usrname1,"r");
                if(NZXT==NULL)
                {
                    printf("\nFATAL ERROR 3984\nExiting\n");
                    exit(0);
                }
                fscanf(NZXT,"%f",&income2);
                fscanf(NZXT,"%f",&loan_amount);
                fscanf(NZXT,"%f",&util);
                fscanf(NZXT,"%d",&dependents);
                fscanf(NZXT,"%f",&assets);
                fscanf(NZXT,"%f",&expenses1);
                fscanf(NZXT,"%f",&Emergency_Fund);
                fscanf(NZXT,"%f",&groceries);
                fscanf(NZXT,"%f",&gas);
                fscanf(NZXT,"%f",&subserv);
                fscanf(NZXT,"%f",&medical);
                fscanf(NZXT,"%f",&insurance);
                fscanf(NZXT,"%f",&mortgage);
                fclose(NZXT);
                Rs1 = fopen(usrname,"a");
                    do{
                        printf("\nWhat information would you like to update?\n");
                        printf("5  = Update income\n\n6  = Update expenses\n\n7  = Update Dependants\n\n8  = Update Assets\n\n9  = Update Loan Amount\n\n10 = Update Emergency Fund\n\n11 = Update Grocery Bill\n\n12 = Update Gas Bill\n\n13 = Update Monthly Subscriptions\n\n14 = Update Monthly Medical Bill\n\n15 = Update Monthly Insurance Bill\n\n16 = Update Mortgage Amount\n\n\n17 = Save Changes\n\n\n18 = Exit\n");
                        scanf("%d",&option_x);
                        switch(option_x){
                            case 5:
                                printf("\n What is the new income value you would like to use?\n");
                                flushInputBuffer();
                                scanf("%f",&income2);
                                sleep(2);
                                printf("Income Updated");
                                break;
                            case 6:
                                printf("\nWhat would you like to change your total expenses to?\n");
                                flushInputBuffer();
                                scanf("%f",&expenses1);
                                sleep(2);
                                printf("\nExpenses Successfully Updated\n");
                                break;
                            case 7:
                                printf("What would you like to change your dependent count to?\n");
                                flushInputBuffer();
                                scanf("%d",&dependents);
                                sleep(2);
                                printf("Dependents successfully updated.\n");
                                break;
                            case 8:
                                printf("\nWhat would you like to change your asset amount to?\n");
                                scanf("%f",&assets);
                                sleep(2);
                                printf("\nThe asset amount has been updated successfully!\n");
                                break;
                            case 9:
                                printf("\nWhat would you like to change your loan amount to?\n");
                                scanf("%.2f",&loan_amount);
                                sleep(2);
                                printf("\nThe loan amount has been updated successfully!\n");
                                break;
                            case 10:
                                printf("\nWhat would you like to update your Emergency Fund to?\n");
                                scanf("%f",&Emergency_Fund);
                                sleep(2);
                                printf("\nThe Emergency Fund amount has been updated successfully\n");
                                break;
                            case 11:
                                printf("\nWhat would you like to update your Monthly grocery amount to?\n");
                                scanf("%f",&groceries);
                                sleep(2);
                                printf("\nMonthly Grocery Bill updated successfully\n");
                                break;
                            case 12:
                                printf("\nWhat would you like to update your Monthly gas bill to?\n");
                                scanf("%f",&gas);
                                sleep(2);
                                printf("\nMonthly Gas amount updated successfully\n");
                                break;
                            case 13:
                                printf("\nWhat would you like to update your Monthly Subscriptions to?\n");
                                scanf("%f",&subserv);
                                sleep(2);
                                printf("\nMonthly Subscriptions updated successfully\n");
                                break;
                            case 14:
                                printf("\nWhat would you like to update your Monthly Medical Bill to?\n");
                                scanf("%f",&medical);
                                sleep(2);
                                printf("\nMonthly Medical Bills updated sucessfully\n");
                                break;
                            case 15:
                                printf("\nWhat would you like to update your Monthly Insurance Bill to?\n");
                                scanf("%f",&insurance);
                                sleep(2);
                                printf("\nMonthly Insurance Bill updated successfully\n");
                                break;
                            case 16:
                                printf("\nWhat would you like your Monthly Mortgage Bill to be updated to?\n");
                                scanf("%f",&mortgage);
                                sleep(2);
                                printf("\nMonthly Mortgage Bill updated successfully\n");
                                break;
                            case 17:
                                printf("\nAre you finished making changes?(Yes/No)\n");
                                scanf("%s",confir);
                                if(strncmp(confir,"Yes",3)==0||strncmp(confir,"yes",3)==0){
                                    fclose(Rs1);
                                    Rs1 = fopen(usrname,"r");
                                    if(Rs1==NULL)
                                    {
                                        printf("Fatal error 226");
                                    }
                                    fgets(passave, sizeof(passave), Rs1);
                                    if (passave == NULL) {
                                        printf("Error: Unable to read password line\n");
                                        fclose(Rs1);
                                        exit(1);
                                    }
                                    fclose(Rs1);
                                    left_over_income = calculate_remaining_balance(income2, expenses1, total_loan, car_payment, Emergency_Fund, dependents, groceries, gas, medical, insurance, mortgage);
                                    Rs1 = fopen(usrname,"w");
                                    fprintf(Rs1,"%s\n",passave);
                                    printf("\nChanges complete");
                                    printf("\nPrinting your information\n");
                                    printLoop();
                                    fprintf(Rs1, "\n+-----------------------+---------------+\n");
                                    fprintf(Rs1, "| Category             | Value          |\n");
                                    fprintf(Rs1, "+-----------------------+---------------+\n");
                                    fprintf(Rs1, "| Income post tax       | %13.2f |\n", income2);
                                    fprintf(Rs1, "| Total Loans           | %13.2f |\n", loan_amount);
                                    fprintf(Rs1, "| Utilities (Monthly)   | %13.2f |\n", util);
                                    fprintf(Rs1, "| Dependents            | %13d |\n", dependents);
                                    fprintf(Rs1, "| Total Assets          | %13.2f |\n", assets);
                                    fprintf(Rs1, "| Total Expenses        | %13.2f |\n", expenses1);
                                    fprintf(Rs1, "| Emergency Fund        | %13.2f |\n", Emergency_Fund);
                                    fprintf(Rs1, "| Grocery Bill          | %13.2f |\n", groceries);
                                    fprintf(Rs1, "| Gas Bill              | %13.2f |\n", gas);
                                    fprintf(Rs1, "| Monthly subscriptions | %13.2f |\n", subserv);
                                    fprintf(Rs1, "| Monthly Medical Bill  | %13.2f |\n", medical);
                                    fprintf(Rs1, "| Monthly Insurance Bill| %13.2f |\n", insurance);
                                    fprintf(Rs1, "| Monthly Mortgage Bill | %13.2f |\n", mortgage);
                                    fprintf(Rs1, "+-----------------------+---------------+\n");
                                    fprintf(Rs1, "| Money Remaining       | %13.2f |\n", left_over_income);
                                    fprintf(Rs1, "+-----------------------+---------------+\n");
                                    fclose(Rs1);
                                    budgetadvise(usrname,income2,left_over_income,loan_amount,util,dependents,assets,expenses1,Emergency_Fund,groceries,gas,subserv,medical,insurance,mortgage);
                                    zila++;
                                    NZXT = fopen(usrname1,"w");
                                    if(NZXT==NULL)
                                    {
                                        printf("\nFATAL ERROR 3984\nExiting\n");
                                        exit(0);
                                    }
                                    fprintf(NZXT,"%.2f",income2);
                                    fprintf(NZXT,"\n%.2f",loan_amount);
                                    fprintf(NZXT,"\n%.2f",util);
                                    fprintf(NZXT,"\n%d",dependents);
                                    fprintf(NZXT,"\n%.2f",assets);
                                    fprintf(NZXT,"\n%.2f",expenses1);
                                    fprintf(NZXT,"\n%.2f",Emergency_Fund);
                                    fprintf(NZXT,"\n%.2f",groceries);
                                    fprintf(NZXT,"\n%.2f",gas);
                                    fprintf(NZXT,"\n%.2f",subserv);
                                    fprintf(NZXT,"\n%.2f",medical);
                                    fprintf(NZXT,"\n%.2f",insurance);
                                    fprintf(NZXT,"\n%.2f",mortgage);
                                    fclose(NZXT);
                                    printf("\nThank you for choosing Us to help you budget. Happy budgeting may great success come to you\nAlways feel free to comeback and update your information for a more up to date plan\n");
                                    exit(0);
                                }
                                else{
                                    printf("\nEnter 14, to quit, or 10 when you would like to add your changes.");
                                }
                                break;
                            case 18:
                                printf("\nCancel\n");
                                fclose(Rs1);
                                exit(0);
                                break;
                            default:
                                printf("\n\nERROR CODE 259\nInvalid option, Please select a valid option");
                                break;
                    }
                    }while(option_x!=14||zila==0);// add print function information here
                    fprintf(Rs1,"%s\n",passave);
                    fprintf(Rs1, "\n+-----------------------+---------------+\n");
                    fprintf(Rs1, "| Category              | Value         |\n");
                    fprintf(Rs1, "+-----------------------+---------------+\n");
                    fprintf(Rs1, "| Income post tax       | %13.2f |\n", income2);
                    fprintf(Rs1, "| Total Loans           | %13.2f |\n", loan_amount);
                    fprintf(Rs1, "| Utilities (Monthly)   | %13.2f |\n", util);
                    fprintf(Rs1, "| Dependents            | %13d |\n", dependents);
                    fprintf(Rs1, "| Total Assets          | %13.2f |\n", assets);
                    fprintf(Rs1, "| Total Expenses        | %13.2f |\n", expenses1);
                    fprintf(Rs1, "| Emergency Fund        | %13.2f |\n", Emergency_Fund);
                    fprintf(Rs1, "| Grocery Bill          | %13.2f |\n", groceries);
                    fprintf(Rs1, "| Gas Bill              | %13.2f |\n", gas);
                    fprintf(Rs1, "| Monthly subscriptions | %13.2f |\n", subserv);
                    fprintf(Rs1, "| Monthly Medical Bill  | %13.2f |\n", medical);
                    fprintf(Rs1, "| Monthly Insurance Bill| %13.2f |\n", insurance);
                    fprintf(Rs1, "| Monthly Mortgage Bill | %13.2f |\n", mortgage);
                    fprintf(Rs1, "+-----------------------+---------------+\n");
                    fprintf(Rs1, "| Money Remaining       | %13.2f |\n", left_over_income);
                    fprintf(Rs1, "+-----------------------+---------------+\n");
                    fclose(Rs1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                case 2:
                    printf("\n\nClearing your budget\n");
                    printLoop();
                    FILE *Usr2 = fopen(usrname, "r");
                    if (Usr2 == NULL) {
                        printf("\nERROR 235\nFailed to open file\n");
                        return 1;
                    }
                    fgets(passave, sizeof(passave), Usr2);
                    fclose(Usr2);
                    Usr2 = fopen(usrname, "w");
                    if (Usr2 == NULL)
                    {
                        printf("\nERROR 234");
                        return 1;
                    }
                    fprintf(Usr2,"%s",passave);
                    printf("\nThe budget has been cleared\n");
                    fclose(Usr2);
                    break;
                case 3:
                FILE *Rs2 = fopen(usrname, "r");
                //---------------------Utilize entire file reading
                
                // Skip the first line (password)
                fgets(passave, sizeof(passave), Rs2);
                
                printf("\nPrinting your file.");
                printLoop();
                
                // Check if the file has remaining content
                if (fgets(line, sizeof(line), Rs2) == NULL) {
                    printf("File is empty or error reading.\n");
                } else {
                    // Print the first read line
                    printf("%s", line);
                
                    // Print the remaining lines
                    while (fgets(line, sizeof(line), Rs2) != NULL) {
                        printf("%s", line);
                    }
                }
                
                fclose(Rs2);
                break;
                
                case 4:
                    printf("\nEXITING!");
                    exit(0);
                default:
                    printf("\nInvalid option.");
                    break;
        }
    }
    

return 0;
}
