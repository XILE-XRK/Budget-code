#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INFOLENGTH 20

int main() {
    char usrstat[INFOLENGTH] = {};
    char usrname[INFOLENGTH] = {};
    char paswrd[INFOLENGTH] = {};
    char paswrd2ndcheck[INFOLENGTH] = {};
    char line[1024];
    char passave[INFOLENGTH] = {};
    int attempts = 0, ilios = 0, option = 0, option_x, dependents = 0, carpaymonths = 0, rs = 0, stat = 0, ZTX = 0;
    float income = 0, incomeCEL, expenses1, tax_rate = 0.09, income_tax, loan_amount, util, carpay = 0, assets = 0.0;
    char confir[INFOLENGTH];
    int login_attempts = 0; 
    void flushInputBuffer(void);

    printf("Welcome to the budget app.\n");
    printf("After providing some information, I will help you set up a budget to get you out of debt and improve your finances.\n");

    // Ask if the user is new or returning
    while(stat == 0) {
        printf("\nAre you a returning user? (Yes/No): ");
        scanf("%s", usrstat);

        if (strcmp(usrstat, "Yes") == 0 || strcmp(usrstat, "yes") == 0) {
            // Returning user login
            printf("\nWelcome back!\n\n");

            int login_attempts = 0;  // Declare login_attempts here
            while (login_attempts < 3) {
                printf("Enter username: ");
                scanf("%19s", usrname);

                FILE *Usr1 = fopen(usrname, "r");

                if (Usr1 == NULL) {
                    printf("\nUsername not recognized. Please try again or create a new account.\n");
                    login_attempts++;
                } else {
                    printf("Enter password: ");
                    scanf("%19s", paswrd);

                    fscanf(Usr1, "%19s", paswrd2ndcheck);
                    fclose(Usr1);

                    if (strcmp(paswrd, paswrd2ndcheck) == 0) {
                        printf("\nPassword correct. \nWelcome!\n\n");
                        stat = 1;  
                        ilios = 1;
                        break;
                    } else {
                        printf("\nIncorrect password. Attempts remaining: %d\n", 2 - login_attempts);
                        login_attempts++;
                    }
                }

                if (login_attempts == 3) {
                    printf("\nToo many failed attempts. Please try again later.\n");
                    break; 
                }
            }
        } else if (strcmp(usrstat, "No") == 0 || strcmp(usrstat, "no") == 0) {
      
            printf("\nLet's create your account.\n\n");

            printf("Enter a username (max 19 characters): ");
            scanf("%19s", usrname);
            flushInputBuffer();

            FILE *Usr = fopen(usrname, "w");
            if (Usr == NULL) {
                printf("\nError: Failed to create account.\n");
                ilios = 2;
                exit(0);
            }

            printf("Enter your password: ");
            scanf("%19s", paswrd);

            fprintf(Usr, "%s", paswrd);
            fclose(Usr);

            printf("\nAccount successfully created! You can now log in.\n\n");
            stat = 1;  // User is now registered and logged in
        } else {
            printf("\nInvalid input. Please restart the program and enter 'Yes' or 'No'.\n");
        }

        // If the user has failed 3 times, reset and ask again
        if (login_attempts == 3 || stat == 0) {
            printf("\n*Returning to the main menu.*\n");
            continue;  
        }
    }

    if (ilios == 1) {
        printf("What actions would you like to perform today?\n");
        printf("\n0 - Create a new budget\n\n1 - Update existing information\n\n2 - Delete a current budget plan.\n\n3 - Print current budget plan\n\n4 - Exit\n\n");
        scanf("%d", &option);
        printf("\nYou have chosen option %d", option);
        flushInputBuffer();
        FILE *Rs1 = fopen(usrname, "a");
        if (Rs1 == NULL) {
            printf("Error 293\nterminating.");
            exit(0);
        }
        switch (option) {
            case 0:
                while (rs == 0) {
                    printf("\nHello, in order to create your new budget plan I will have to collect some information.\nSome information might be sensitive.\nAre you sure you would like to proceed with this process?\nYes/No: ");
                    scanf("%s", confir);
                    if (strcmp(confir, "Yes") == 0 || strcmp(confir, "yes") == 0 || strcmp(confir, "YES") == 0 || strcmp(confir, "YEs") == 0 || strcmp(confir, "yEs") == 0 || strcmp(confir, "yeS") == 0) {
                        while (getchar() != '\n');
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
                        printf("\nEnter your yearly income (Without commas): ");
                        scanf("%f", &income);
                        income_tax = income / tax_rate;
                        fprintf(Rs1, "\n\n|         Income      |");
                        fprintf(Rs1, "\n         %.2f", income);
                        fprintf(Rs1, "\n---------------------------");
                        printf("\nYou entered an income value of %2.f.\n", income);
                        printf("\nDo you currently have any car payments? (Yes/No): ");
                        scanf(" %c", confir);
                        while (rs == 0) {
                            if (strcmp(confir, "Yes") == 0 || strcmp(confir, "yes") == 0 || strcmp(confir, "YES") == 0 || strcmp(confir, "YEs") == 0 || strcmp(confir, "yEs") == 0 || strcmp(confir, "yeS") == 0 || strcmp(confir, "Y") == 0 || strcmp(confir, "y") == 0) {
                                rs = 0;
                                printf("\nHow many payments of what amount do you have left on your vehicle\n");
                                printf("\nEnter the car payment amount followed by the total months left.");
                                scanf("%f%d", &carpay, &carpaymonths);
                                /////////////////////////////////////////////////////////
                                ////////////RedFlagAreaBelow                    /////////
                                loan_amount = loan_amount + (carpay * carpaymonths);////////
                                rs += 1;                                          ////////
                                ////////////////////////////////////////////////////////
                            } else if (strcmp(confir, "No") == 0 || strcmp(confir, "no") == 0 || strcmp(confir, "NO") == 0 || strcmp(confir, "nO") == 0 || strcmp(confir, "n") == 0 || strcmp(confir, "N") == 0) {
                                printf("\nThats amazing, That's one less payment to worry about.\n");
                                rs += 1;
                            } else {
                                printf("\nInvalid input, Try again.\n");
                                scanf("%s", confir);
                            }
                        }
                        printf("\nEnter your current total loan amount.\n");
                        scanf("%f", &loan_amount);
                        printf("You entered a total loan amount of %.2f", loan_amount);
                        fprintf(Rs1, "\n\n|      Total Loans      |\n");
                        fprintf(Rs1, "\n---------------------------");
                        fprintf(Rs1, "%10.2f\n", loan_amount);
                        printf("\nEnter approximated amount of monthly utility bills:\n");
                        scanf("%f", &util);
                        fprintf(Rs1, "\n|        Utilities       |\n");
                        fprintf(Rs1, "\n%10.2f\n", util);
                        printf("\nEnter number of dependents:\n");
                        scanf("%d", &dependents);
                        fprintf(Rs1, "\n|        Dependents      |\n");
                        fprintf(Rs1, "\n%10d", dependents);
                        printf("\nEnter your total assets:\n");
                        scanf("%f", &assets);
                        fprintf(Rs1, "\n|        Total Assets    |\n");
                        fprintf(Rs1, "\n|%10.2f", assets);
                        fclose(Rs1);
                        rs += 1;
                        break;
                    } else if (strcmp(confir, "No") == 0 || strcmp(confir, "no") == 0 || strcmp(confir, "NO") == 0 || strcmp(confir, "nO") == 0) {
                        printf("I understand that you might not be willing to give up this information and that's perfectly fine.\nHave a nice day.");
                        exit(0);
                    } else {
                        printf("\nInvalid input, Try again.\n");
                        scanf("%s", confir);
                    }
                }
                break;
            // Rest of the cases ...
        }
    }

    return 0;
}

void flushInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
