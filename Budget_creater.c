#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INFOLENGTH 20

int main() {
    char usrstat;
    char usrname[INFOLENGTH] = {};
    char paswrd[INFOLENGTH] = {};
    char paswrd2ndcheck[INFOLENGTH] = {};
    char line[1024];
    char passave[INFOLENGTH] = {};
    int attempts = 0, ilios = 0, option = 0,option_x;
    float income = 0,incomeCEL,expenses1,tax_rate = 0.0,income_tax=income/tax_rate;
    char confir;

    printf("Welcome to the budget app.\n");
    printf("After providing some information, I will help you set up a budget to get you out of debt and improve your finances.\n");

    // Ask if the user is new or returning
    printf("\nAre you a returning user? (Y/N): ");
    scanf(" %c", &usrstat);

    if (usrstat == 'Y' || usrstat == 'y') {//compares the user response to the ascii codes.
        // Returning user login
        printf("Welcome back!\n");

        printf("Enter username: ");
        scanf(" %19s", usrname);//collects the username
        while(ilios==0){

            FILE *Usr1 = fopen(usrname, "r");//looks for a file with a similar name to the users, username given.
            if (Usr1 == NULL) {//if the username/ file doesn't exist this will return null allowing the code to exit.
                printf("\nUsername not recognized. Please try again or create a new account.\n");
                ilios = 2;
                return 1;
            }

            while (attempts < 3) {
                printf("Enter password: ");
                scanf("%19s", paswrd);

                // Read the stored password from file
                fscanf(Usr1, "%19s", paswrd2ndcheck);
                fclose(Usr1); // Close file after reading

                if (strcmp(paswrd, paswrd2ndcheck) == 0) {
                    printf("\nPassword correct. Welcome!\n");
                    ilios = 1;
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
            }
            fclose(Usr1);

    }
}
        else if (usrstat == 'N' || usrstat == 'n') {
            // New user account creation
            printf("Let's create your account.\n");

            printf("Enter a username (max 19 characters): ");
            scanf("%19s", usrname);

            FILE *Usr = fopen(usrname, "w");
        if (Usr == NULL) {
            printf("\nError: Failed to create account.\n");
            ilios=2;
            exit(0);
            }

            printf("Enter your password: ");
            scanf("%19s", paswrd);

            fprintf(Usr, "%s", paswrd);
            fclose(Usr);//Get rid of in order to continue working with the code later.

            printf("\nAccount successfully created! You can now log in.\n");

        }
        else {
            printf("\nInvalid input. Please restart the program and enter 'Y' or 'N'.\n");
            ilios=2;
        }
    if(ilios==1){
        printf("What actions would you like to perform today?\n");
        printf("\n0 - Create a new budget\n\n1 - update existing information\n\n2 - Delete a current budget plan.\n\n3 - Print current budget plan\n\n4 - Exit\n\n");
        scanf("%d",&option);
        printf("\nYou have chosen option %d",option);
        FILE *Rs1 = fopen(usrname, "a");
        if(Rs1==NULL)
        {
            printf("There seems to have been a problem, terminating.");
        }
        while(option!=4){
            switch(option){
                case 0:
                    printf("\nHello, in order to create your new budget plan I will have to collect some sensitive information.\n\nAre you sure you would like to proceed with this process?\nY/N:\n");
                    scanf(" %c",&confir);
                    if(confir == 'Y'||confir == 'y'){
                        printf("\nLet us continue\n");
                        printf("\nEnter your yearly income (Without commas):\n");
                        scanf("%f",&income);
                        fprintf(Rs1,"\n\n|         Income      |");
                        fprintf(Rs1,"\n%8d",income);
                        printf("\nYou entered an income value of %2.f.\n",income);
                        printf("With a tax rate of %d%% your income after taxes should be around %f\n",tax_rate,income_tax);
                        fclose(Rs1);
                        break;//Continue from here-------------------------------
                    }
                    else if(confir == 'n'|| confir == 'N')
                    {
                        printf("I understand that you might not be willing to give up this information and that's perfectly fine.\nHave a nice day.");
                        exit(0);
                    }
                    break;
                case 1:
                    printf("\nWhat information would you like to update?\n");
                    printf("5 = Update income\n6 = Change expenses\n7 = Cancel\n");
                    scanf("%d",option_x);
                    do{
                        switch(option_x){
                            case 5:
                                printf("\n What is the new income value you would like to use?\n");
                                scanf("%f",&incomeCEL);
                                sleep(2);
                                printf("Value Updated");
                                break;
                            case 6:
                                printf("\nWhat would you like to change your total expenses to?\n");
                                scanf("%f",&expenses1);
                                sleep(2);
                                printf("\nValue Updated\n");
                                break;
                            case 7:
                                printf("\nCancel\n");
                                break;
                    }
                    }while(option_x!=7);

                case 2:
                    printf("\n\nClearing your budget\n");
                    sleep(5);
                    FILE *Usr2 = fopen(usrname, "r");
                    if (Usr2 == NULL) {
                        printf("\nERROR 235");
                        return 1;
                    }
                    fgets(passave, sizeof(passave), Usr2);
                    fclose(Usr2);
                    FILE *Usr3 = fopen(usrname, "w");
                    if (Usr3 == NULL)
                    {
                        printf("\nERROR 234");
                        return 1;
                    }
                    fprintf(Usr3,"%s",passave);
                    printf("\nThe budget has been cleared\n");
                    fclose(Usr3);
                    return 0;
                case 3:
                    printf("\nPrinting your file.");
                    FILE *Rs2 = fopen(usrname, "r");
                    sleep(8);

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

