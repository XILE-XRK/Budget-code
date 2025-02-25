#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFOLENGTH 20

int main() {
    char usrstat;
    char usrname[INFOLENGTH] = {};
    char paswrd[INFOLENGTH] = {};
    char paswrd2ndcheck[INFOLENGTH] = {};
    int attempts = 0;

    printf("Welcome to the budget app.\n");
    printf("After providing some information, I will help you set up a budget to get you out of debt and improve your finances.\n");

    // Ask if the user is new or returning
    printf("\nAre you a returning user? (Y/N): ");
    scanf(" %c", &usrstat);

    if (usrstat == 'Y' || usrstat == 'y') {//compares the user response to the ascii codes.
        // Returning user login
        printf("Welcome back!\n");

        printf("Enter username: ");
        scanf("%19s", usrname);//collects the username

        FILE *Usr1 = fopen(usrname, "r");//looks for a file with a similar name to the users, username given.
        if (Usr1 == NULL) {//if the username/ file doesn't exist this will return null allowing the code to exit.
            printf("\nUsername not recognized. Please try again or create a new account.\n");
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
                return 0;
            } else {
                printf("\nIncorrect password. Attempts remaining: %d\n", 2 - attempts);
                attempts++;
                Usr1 = fopen(usrname, "r"); // Reopen file for next attempt
                if (Usr1 == NULL) {
                    printf("\nError reopening user file.\n");
                    return 1;
                }
            }
        }
        printf("Too many incorrect attempts. Please try again later.\n");
        return 1;

    } else if (usrstat == 'N' || usrstat == 'n') {
        // New user account creation
        printf("Let's create your account.\n");

        printf("Enter a username (max 19 characters): ");
        scanf("%19s", usrname);

        FILE *Usr = fopen(usrname, "w");
        if (Usr == NULL) {
            printf("\nError: Failed to create account.\n");
            return 1;
        }

        printf("Enter your password: ");
        scanf("%19s", paswrd);

        fprintf(Usr, "%s", paswrd);
        fclose(Usr);

        printf("\nAccount successfully created! You can now log in.\n");

    } else {
        printf("\nInvalid input. Please restart the program and enter 'Y' or 'N'.\n");
        return 1;
    }

    return 0;
}
