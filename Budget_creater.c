#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "BCF.c"
#define INFOLENGTH 20
void printLoop();
void flushInputBuffer(void);
int main() {
    char usrstat[INFOLENGTH] = {};
    char usrname[INFOLENGTH] = {};
    char paswrd[INFOLENGTH] = {};
    char paswrd2ndcheck[INFOLENGTH] = {};
    char line[1024];
    char passave[INFOLENGTH] = {};
    char confir[INFOLENGTH] = {};
    char temploc[1888] = {};
    int attempts = 0, ilios = 0, option = 0,option_x,dependents = 0, carpaymonths = 0,rs = 0,stat = 0,ZTX=0,izo = 0,car_payment = 0,Emergency_Fund = 1000,zila = 0;
    float income = 0,income2 = 0,expenses1,tax_rate = 0.09,income_tax,loan_amount,util,carpay = 0,assets = 0.0,carpayment = 0,groceries = 0,gas = 0, left_over_income = 0;

    printf("Welcome to the budget app.\n");
    printf("After providing some information, I will help you set up a budget to get you out of debt and improve your finances.\n");

    // Ask if the user is new or returning
    printf("\nAre you a returning user. or have you recently created an account? (yes/no): ");
    scanf("%s", usrstat);
    while(stat==0){

    if (strcmp(usrstat,"Yes")==0||strcmp(usrstat,"yes")==0) {//compares the user response to the ascii codes. Use Strcmp and string arrays instead
        // Returning user login
        printf("\n\nWelcome back!\n\n");

        printf("Enter username: ");
        scanf("%19s",usrname);
        //flushInputBuffer();
        FILE *Usr1 = fopen(usrname, "r");
        while(ilios==0){

        while (ZTX!=3) {
            if (Usr1 == NULL) {
                printf("Username not recognized. Please try again or create a new account. Enter Q to exit\n");
                printf("You have %d attempt(s) left\n",3-ZTX);
                flushInputBuffer();
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
            }
        }


            while (attempts < 3) {
                flushInputBuffer();
                printf("Enter password: ");
                scanf("%19s", paswrd);

                // Read the stored password from file
                fscanf(Usr1, "%19s", paswrd2ndcheck);
                fclose(Usr1); // Close file after reading

                if (strcmp(paswrd, paswrd2ndcheck) == 0) {
                    printf("\nPassword correct. Welcome!\n");
                    ilios = 1;
                    stat=1;
                    break;
                } else {
                    printf("\nIncorrect password. Attempts remaining: %d\n", 2 - attempts);
                    attempts++;
                    Usr1 = fopen(usrname, "r"); // Reopen file for next attempt
                    if(attempts == 3){
                        printf("Too many attempts.\nTry again later. ");
                        return 1;
                    }
                    if (Usr1 == NULL) {
                        printf("\nError reopening user file.\n");
                        ilios = 2;
                    }

                }
                fclose(Usr1);
            }
        }
    }

    else if (strcmp(usrstat,"No")==0||strcmp(usrstat,"no")==0) {
        // New user account creation
        printf("Let's create your account.\n");

        printf("Enter a username (max 19 characters): ");
        scanf("%19s",usrname);
        flushInputBuffer();

            FILE *Usr = fopen(usrname, "w");
        if (Usr == NULL) {
            printf("\nError: Failed to create account.\n");
            ilios=2;
            exit(0);
            }

            printf("Enter your password: ");
            scanf("%19s", paswrd);

            fprintf(Usr, "%s\n", paswrd);
            fclose(Usr);//Get rid of in order to continue working with the code later.

            printf("\nAccount successfully created! You can now log in.\n");
            exit(0);

        }
    else {
        printf("\nInvalid input. Please restart the program and enter 'Yes' or 'No'.\n");
        flushInputBuffer();
        scanf("%s",&usrstat);

        }
    }
    if(ilios==1){
        printf("What actions would you like to perform today?\n");
        //Change the following menu into a function in order to clean it up and more easily add extra things in the future.
        printf("\n0 - Create a new budget\n\n1 - Update existing information\n\n2 - Delete a current budget plan.\n\n3 - Print current budget plan\n\n4 - Exit\n\n");
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
                    while(rs==0){
                        printf("\nHello, in order to create your new budget plan I will have to collect some sensitive information.\n\nAre you sure you would like to proceed with this process?\nYes/No:\n");
                        scanf("%s",confir);
                        if(strcmp(confir,"Yes")==0||strcmp(confir,"yes")== 0||strcmp(confir,"YES")==0||strcmp(confir,"YEs")==0||strcmp(confir,"yEs")==0||strcmp(confir,"yeS")==0){
                        while (getchar() != '\n');
                        FILE *Usr1 = fopen(usrname, "r");
                        if (Usr1 == NULL) {
                            printf("\nERROR 235\nTerminating");
                            return 1;
                        }
                        fgets(passave, sizeof(passave), Usr1);
                        fclose(Usr1);
                        FILE *Usr3 = fopen(usrname, "w");
                        if (Usr3 == NULL)
                        {
                            printf("\nERROR 234");
                            return 1;
                        }
                        fprintf(Usr3,"%s",passave);
                        fclose(Usr3);
                        printf("\nLet us continue\n");
                        printf("\nEnter the total house yearly income (Enter the income that the entire house makes or just your income if you live alone.(Without commas):\n");
                        scanf("%f",&income);
                        income2= income - (income*tax_rate);
                        printf("\nYou entered an income value of %2.f.\n",income);
                        printf("\nDo you currently have any car payments? (Yes/No)\n");
                        scanf(" %c",confir);
                        flushInputBuffer();
                        while(rs==0){
                            if(strcmp(confir,"Yes")==0||strcmp(confir,"yes")== 0||strcmp(confir,"YES")==0||strcmp(confir,"YEs")==0||strcmp(confir,"yEs")==0||strcmp(confir,"yeS")==0||strcmp(confir,"Y")==0||strcmp(confir,"y")==0)
                            {
                                rs = 0;
                                printf("\nHow many payments of what amount do you have left on your vehicle\n");
                                printf("\nEnter the monthly car payment.\n");
                                scanf("%.2f",&carpay);
                                flushInputBuffer();
                                printf("\nEnter the amount of months left to pay off the vehicle.\n");
                                scanf("%d",&carpaymonths);
                                flushInputBuffer();
                                float car_payment = calculate_total_car_loan(carpay,carpaymonths);////////////////////////////////////////////////////////////////////////////////////////////////////////
                                rs+=1;                                          ////////
                            }
                            else if(strcmp(confir,"No")==0||strcmp(confir,"no")== 0||strcmp(confir,"NO")==0||strcmp(confir,"nO")==0||strcmp(confir,"n")==0||strcmp(confir,"N")==0)
                            {
                                printf("\nThats amazing, Thats one less payment to worry about.\n");
                                rs+=1;
                            }
                            else
                            {
                                printf("\nInvalid input, Try again.\n");
                                scanf("%s",confir);
                            }

                        }
                        printf("\nEnter your current total loan amount.\n");
                        scanf("%f",&loan_amount);
                        int total_loan = calculate_total_loans(car_payment,loan_amount);
                        printf("\nEnter approximated amount of monthly utility bills:\n");
                        scanf("%f",&util);
                        printf("\nEnter number of dependents:\n");
                        scanf("%d",&dependents);                       
                        while(izo==0){
                            if(dependents<0)
                            {
                                printf("\nEnter a positive number ");
                                scanf("%d",&dependents);
                            }
                            else
                            {
                                izo++;
                            }
                            }

                        printf("\nEnter total expenses per month:\n");
                        scanf("%f",&expenses1);
                        expenses1 = expenses1*12;
                        flushInputBuffer();
                        printf("\nEnter your total assets:\n");
                        scanf("%f",&assets);
                        printf("\nEnter monthly grocery bill:\n");
                        scanf("%f",&groceries);
                        printf("\nEnter monthly gas expenses:\n");
                        scanf("%f",&gas);

                        int ija = 0;
                        left_over_income = calculate_remaining_balance(income2,expenses1,total_loan,car_payment,Emergency_Fund)+dependents*500+groceries*12+gas * 12;
                        printf("\nExcluding Assets, you should currently have %.2f left over considering all of the payments and expenses you have.",left_over_income);
                        printf("\nPrinting your information in your file.");
                               fprintf(Rs1, "\n+---------------------+---------------+\n");
                               fprintf(Rs1, "| Category            | Value         |\n");
                               fprintf(Rs1, "+---------------------+---------------+\n");
                               fprintf(Rs1, "| Income post tax     | %13.2f |\n", income2);
                               fprintf(Rs1, "| Total Loans         | %13.2f |\n", loan_amount);
                               fprintf(Rs1, "| Utilities (Annual)  | %13.2f |\n", util * 12);
                               fprintf(Rs1, "| Dependents          | %13d |\n", dependents);
                               fprintf(Rs1, "| Total Assets        | %13.2f |\n", assets);
                               fprintf(Rs1, "| Total Expenses      | %13.2f |\n", expenses1);
                               fprintf(Rs1, "| Emergency Fund      | %13.2f |\n", Emergency_Fund);
                               fprintf(Rs1, "| Grocery Bill        | %13.2f |\n", groceries * 12);
                               fprintf(Rs1, "| Gas Bill            | %13.2f |\n", gas * 12);
                               fprintf(Rs1, "+---------------------+---------------+\n");
                               fprintf(Rs1, "| Money Remaining     | %13.2f |\n",left_over_income);
                               fclose(Rs1);
                               printf("\nExiting");
                               sleep(2);
                               exit(0);
                        }
                        
                        else if(strcmp(confir,"No")==0||strcmp(confir,"no")== 0||strcmp(confir,"NO")==0||strcmp(confir,"nO")==0)
                        {
                            printf("I understand that you might not be willing to give up this information and that's perfectly fine.\nHave a nice day.");
                            exit(0);
                        }
                        else
                        {
                            printf("\nInvalid input, Try again.\n");
                            scanf("%s",confir);
                        }
                        break;
                case 1:
                // Skip the password
                fclose(Rs1);
                Rs1 = fopen(usrname,"r");
                if(Rs1==NULL){
                    printf("\nFile opening failed!");
                    exit(0);
                }
                fgets(temploc, sizeof(temploc), Rs1); // Read password line

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
                    printf("\nPrinting Current information\n");
                    printLoop();
                    fprintf(Rs1, "\n+---------------------+---------------+\n");
                    fprintf(Rs1, "| Category            | Value         |\n");
                    fprintf(Rs1, "+---------------------+---------------+\n");
                    fprintf(Rs1, "| Income post tax     | %13.2f |\n", income2);
                    fprintf(Rs1, "| Total Loans         | %13.2f |\n", loan_amount);
                    fprintf(Rs1, "| Utilities (Annual)  | %13.2f |\n", util * 12);
                    fprintf(Rs1, "| Dependents          | %13d  |\n", dependents);
                    fprintf(Rs1, "| Total Assets        | %13.2f |\n", assets);
                    fprintf(Rs1, "| Total Expenses      | %13.2f |\n", expenses1);
                    fprintf(Rs1, "| Emergency Fund      | %13.2f |\n", Emergency_Fund);
                    fprintf(Rs1, "| Grocery Bill        | %13.2f |\n", groceries * 12);
                    fprintf(Rs1, "| Gas Bill            | %13.2f |\n", gas * 12);
                    fprintf(Rs1, "+---------------------+---------------+\n");
                    fprintf(Rs1, "| Money Remaining     | %13.2f |\n",left_over_income);
                    sleep(1);
                    printf("\nExiting\n");
                    sleep(2);
                    fclose(Rs1);
                    exit(0);
                }
                fclose(Rs1);
                Rs1 = fopen(usrname,"a");
                    do{
                        printf("\nWhat information would you like to update?\n");
                        printf("5 = Update income\n6 = Update expenses\n7 = Update Dependants\n8 = Update Assets\n9 = Loan Amount\n10 = Save Changes\n14 = Exit\n");
                        scanf("%d",&option_x);
                        switch(option_x){
                            case 5:
                                printf("\n What is the new income value you would like to use?\n");
                                flushInputBuffer();
                                scanf("%f",&income2);////////////////////////////////////////////////////////////////////
                                sleep(2);
                                printf("Income Updated");
                                break;
                            case 6:
                                printf("\nWhat would you like to change your total expenses to?\n");
                                flushInputBuffer();
                                scanf("%f",&expenses1);
                                sleep(2);
                                printf("\nExpenses Updated\n");
                                break;
                            case 7:
                                printf("What would you like to change your dependent count to?\n");
                                flushInputBuffer();
                                scanf("%d",&dependents);
                                sleep(2);
                                printf("Dependents successfully updated.");
                                break;
                            case 8:
                                printf("\nWhat would you like to change your asset amount to?");
                                flushInputBuffer();
                                scanf("%f",&assets);
                                sleep(2);
                                printf("\nThe asset amount has been updated successfully!");
                                break;
                            case 9:
                                printf("\nWhat would you like to change your loan amount to?\n");
                                flushInputBuffer();
                                scanf("%.2f",loan_amount);
                                sleep(2);
                                printf("\nThe loan amount has been updated successfully!\n");
                                break;
                            case 10:
                                printf("\nAre you finished making changes?");
                                scanf("%s",confir);
                                if(strncmp(confir,"Yes",3)==0||strncmp(confir,"yes",3)==0){
                                    printf("\nChanges complete");
                                    zila++;
                                }
                                else{
                                    printf("\nEnter 14, to quit, or 10 when you would like to add your changes.");
                                }
                                break;
                            case 14:
                                printf("\nCancel\n");
                                fclose(Rs1);
                                exit(0);
                                break;
                            default:
                                printf("\n\nERROR CODE 259\nInvalid option, Please select a valid option");
                                break;
                                //Make sure to add an exit case
                    }
                    }while(option_x!=14||zila==0);// add print function information here
                    fprintf(Rs1, "\n+---------------------+---------------+\n");
                    fprintf(Rs1, "| Category            | Value         |\n");
                    fprintf(Rs1, "+---------------------+---------------+\n");
                    fprintf(Rs1, "| Income              | %13.2f |\n", income2);
                    fprintf(Rs1, "| Total Loans         | %13.2f |\n", loan_amount);
                    fprintf(Rs1, "| Utilities (Annual)  | %13.2f |\n", util * 12);
                    fprintf(Rs1, "| Dependents          | %13d  |\n", dependents);
                    fprintf(Rs1, "| Total Assets        | %13.2f |\n", assets);
                    fprintf(Rs1, "| Total Expenses      | %13.2f |\n", expenses1);
                    fprintf(Rs1, "| Emergency Fund      | %13.2f |\n", Emergency_Fund);
                    fprintf(Rs1, "| Grocery Bill        | %13.2f |\n", groceries * 12);
                    fprintf(Rs1, "| Gas Bill            | %13.2f |\n", gas * 12);
                    fprintf(Rs1, "+---------------------+---------------+\n");
                    fprintf(Rs1, "| Money Remaining     | %13.2f |\n",left_over_income);

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
                    printf("\nPrinting your file.");
                    FILE *Rs2 = fopen(usrname, "r");
                    printf("\n#");
                    printLoop();
                    //---------------------Utilize entire file reading

                    // Skip the first line
                    if (fgets(line, sizeof(line), Rs2) == NULL) {
                        printf("File is empty or error reading.\n");
                    }

                    // Print the remaining lines
                    while (fgets(line, sizeof(line), Rs2) != NULL) {
                        printf("%s", line);
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
    }

return 0;
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
    }
