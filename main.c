#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store account details
struct Account {
    char accountNumber[20];
    char pin[5];
    float balance;
};

// Function declarations
void displayMenu();
void balanceInquiry(struct Account *account);
void cashDeposit(struct Account *account);
void cashWithdrawal(struct Account *account);
void updateAccount(struct Account account);
struct Account loadAccount(char *accountNumber, char *pin);
int authenticate(char *accountNumber, char *pin);

int main() {
    char accountNumber[20];
    char pin[5];
    struct Account account;
    
    // Authentication process
    printf("Enter your account number: ");
    scanf("%s", accountNumber);
    printf("Enter your PIN: ");
    scanf("%s", pin);

    // Check if account exists and pin matches
    if (!authenticate(accountNumber, pin)) {
        printf("Invalid account number or PIN.\n");
        return 0;
    }

    // Load the account details
    account = loadAccount(accountNumber, pin);
    
    int choice;
    while (1) {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                balanceInquiry(&account);
                break;
            case 2:
                cashDeposit(&account);
                break;
            case 3:
                cashWithdrawal(&account);
                break;
            case 4:
                printf("Exiting...\n");
                updateAccount(account); // Save account details before exit
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    
    return 0;
}

// Function to display the ATM menu
void displayMenu() {
    printf("\n--- ATM Menu ---\n");
    printf("1. Balance Inquiry\n");
    printf("2. Cash Deposit\n");
    printf("3. Cash Withdrawal\n");
    printf("4. Exit\n");
}

// Function to check account balance
void balanceInquiry(struct Account *account) {
    printf("Your current balance is: $%.2f\n", account->balance);
}

// Function to deposit cash into the account
void cashDeposit(struct Account *account) {
    float depositAmount;
    printf("Enter the amount to deposit: $");
    scanf("%f", &depositAmount);
    
    if (depositAmount > 0) {
        account->balance += depositAmount;
        printf("Deposit successful. Your new balance is: $%.2f\n", account->balance);
    } else {
        printf("Invalid amount. Please try again.\n");
    }
}

// Function to withdraw cash from the account
void cashWithdrawal(struct Account *account) {
    float withdrawalAmount;
    printf("Enter the amount to withdraw: $");
    scanf("%f", &withdrawalAmount);
    
    if (withdrawalAmount > 0 && withdrawalAmount <= account->balance) {
        account->balance -= withdrawalAmount;
        printf("Withdrawal successful. Your new balance is: $%.2f\n", account->balance);
    } else if (withdrawalAmount > account->balance) {
        printf("Insufficient balance.\n");
    } else {
        printf("Invalid amount. Please try again.\n");
    }
}

// Function to update the account file after a transaction
void updateAccount(struct Account account) {
    FILE *file;
    char filename[30];
    sprintf(filename, "%s.txt", account.accountNumber);
    
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error updating account details.\n");
        return;
    }
    
    fprintf(file, "%s %s %.2f\n", account.accountNumber, account.pin, account.balance);
    fclose(file);
}

// Function to load account details from file
struct Account loadAccount(char *accountNumber, char *pin) {
    struct Account account;
    FILE *file;
    char filename[30];
    sprintf(filename, "%s.txt", accountNumber);
    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error loading account details.\n");
        exit(1);
    }
    
    fscanf(file, "%s %s %f", account.accountNumber, account.pin, &account.balance);
    fclose(file);
    
    return account;
}

// Function to authenticate user based on account number and PIN
int authenticate(char *accountNumber, char *pin) {
    FILE *file;
    char filename[30];
    char storedAccountNumber[20], storedPin[5];
    
    sprintf(filename, "%s.txt", accountNumber);
    file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // Account doesn't exist
    }
    
    fscanf(file, "%s %s", storedAccountNumber, storedPin);
    fclose(file);
    
    if (strcmp(storedAccountNumber, accountNumber) == 0 && strcmp(storedPin, pin) == 0) {
        return 1; // Authentication successful
    }
    
    return 0; // Authentication failed
}
