#include <stdio.h>
#include <string.h>

unsigned long amount = 1000, deposit, withdraw;
int choice, k;
char transaction = 'y';
char pin[5]; // Use a string for the PIN

int main() {
    // Prompt for PIN until correct one is entered
    while (1) {
        printf("ENTER YOUR SECRET PIN NUMBER: ");
        scanf("%s", pin); // Read PIN as a string
        if (strcmp(pin, "1520") == 0) { // Compare as strings
            break; // Exit the loop if PIN is correct
        }
        printf("PLEASE ENTER VALID PASSWORD\n");
    }

    do {
        printf("******** Welcome to ATM Service **************\n");
        printf("1. Check Balance\n");
        printf("2. Withdraw Cash\n");
        printf("3. Deposit Cash\n");
        printf("4. Quit\n");
        printf("******************?****************************\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nYOUR BALANCE IN Rs: %lu\n", amount);
                break;
            case 2:
                printf("\nENTER THE AMOUNT TO WITHDRAW: ");
                scanf("%lu", &withdraw);
                if (withdraw % 100 != 0) {
                    printf("\nPLEASE ENTER THE AMOUNT IN MULTIPLES OF 100\n");
                } else if (withdraw > (amount - 500)) {
                    printf("\nINSUFFICIENT BALANCE\n");
                } else if (withdraw <= 0) {
                    printf("\nPLEASE ENTER A POSITIVE AMOUNT\n");
                } else {
                    amount -= withdraw;
                    printf("\nPLEASE COLLECT CASH\n");
                    printf("YOUR CURRENT BALANCE IS Rs: %lu\n", amount);
                }
                break;
            case 3:
                printf("\nENTER THE AMOUNT TO DEPOSIT: ");
                scanf("%lu", &deposit);
                if (deposit <= 0) {
                    printf("\nPLEASE ENTER A POSITIVE AMOUNT\n");
                } else {
                    amount += deposit;
                    printf("YOUR BALANCE IS Rs: %lu\n", amount);
                }
                break;
            case 4:
                printf("\nTHANK YOU FOR USING ATM\n");
                break;
            default:
                printf("\nINVALID CHOICE\n");
        }

        printf("\n\nDO YOU WISH TO HAVE ANOTHER TRANSACTION? (y/n): \n");
        while (getchar() != '\n'); // Clear the newline character from the buffer
        scanf("%c", &transaction);
        if (transaction == 'n' || transaction == 'N') {
            k = 1; // Set k to 1 to exit the loop
        }
    } while (!k);

    printf("\nTHANKS FOR USING OUR ATM SERVICE\n");
    return 0; // Return 0 to indicate successful termination
}
