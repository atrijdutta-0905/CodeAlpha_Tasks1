#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a bank account
struct Account {
    int acc_no;
    char name[100];
    float balance;
};

// Function prototypes
void create_account();
void deposit();
void withdraw();
void balance_enquiry();
void view_all_accounts();
void update_account_file(struct Account acc);
struct Account find_account(int acc_no);

int main() {
    int choice;

    do {
        // Menu interface
        printf("\n*** High Banking Account Management System ***\n");
        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("5. View All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                balance_enquiry();
                break;
            case 5:
                view_all_accounts();
                break;
            case 6:
                printf("Thank you for using the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to create a new account and save to TEXT file
void create_account() {
    struct Account acc;
    FILE *fp;

    printf("\nEnter the account number: ");
    scanf("%d", &acc.acc_no);

    // Consume the newline left by scanf so fgets works
    getchar();

    printf("Enter the account holder's name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0; // Remove trailing newline

    printf("Enter the initial deposit amount (min 500): ");
    scanf("%f", &acc.balance);

    if (acc.balance < 500) {
        printf("Minimum initial deposit is 500. Account creation failed.\n");
        return;
    }

    // Open file in append mode (text)
    fp = fopen("accounts.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write to file in readable text format
    // Format: AccountNumber [Newline] Name [Newline] Balance [Newline]
    fprintf(fp, "%d\n%s\n%f\n", acc.acc_no, acc.name, acc.balance);
    
    fclose(fp);
    printf("\nAccount created successfully!\n");
}

// Function to find an account by reading the TEXT file
struct Account find_account(int acc_no) {
    struct Account acc;
    FILE *fp;
    int found = 0;

    fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        return (struct Account){0, "", 0.0};
    }

    // Read loop: scans 3 items (Int, String line, Float)
    // %[^\n] means "read everything until a newline" (handles spaces in names)
    while (fscanf(fp, "%d\n%[^\n]\n%f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        if (acc.acc_no == acc_no) {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found) {
        return acc;
    } else {
        return (struct Account){0, "", 0.0};
    }
}

// Function to update an account in the TEXT file
void update_account_file(struct Account acc) {
    struct Account temp_acc;
    FILE *fp1, *fp2;

    fp1 = fopen("accounts.txt", "r");
    fp2 = fopen("temp.txt", "w"); // Write mode for temp file

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error updating file.\n");
        return;
    }

    // Read all accounts, update the matching one, write all to temp
    while (fscanf(fp1, "%d\n%[^\n]\n%f", &temp_acc.acc_no, temp_acc.name, &temp_acc.balance) != EOF) {
        if (temp_acc.acc_no == acc.acc_no) {
            // Write the NEW updated data
            fprintf(fp2, "%d\n%s\n%f\n", acc.acc_no, acc.name, acc.balance);
        } else {
            // Write the OLD existing data
            fprintf(fp2, "%d\n%s\n%f\n", temp_acc.acc_no, temp_acc.name, temp_acc.balance);
        }
    }

    fclose(fp1);
    fclose(fp2);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}
// Function to deposit money into an account
void deposit() {
    int acc_no;
    float amount;
    struct Account acc;

    printf("\nEnter the account number to deposit into: ");
    scanf("%d", &acc_no);
    acc = find_account(acc_no);

    if (acc.acc_no == 0) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter the amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {
        acc.balance += amount;
        update_account_file(acc);
        printf("Successfully deposited %.2f. New balance is %.2f.\n", amount, acc.balance);
    } else {
        printf("Invalid amount.\n");
    }
}
// Function to withdraw money from an account
void withdraw() {
    int acc_no;
    float amount;
    struct Account acc;

    printf("\nEnter the account number to withdraw from: ");
    scanf("%d", &acc_no);
    acc = find_account(acc_no);

    if (acc.acc_no == 0) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= acc.balance) {
        acc.balance -= amount;
        update_account_file(acc);
        printf("Successfully withdrew %.2f. New balance is %.2f.\n", amount, acc.balance);
    } else if (amount > acc.balance) {
        printf("Insufficient balance.\n");
    } else {
        printf("Invalid amount.\n");
    }
}
// Function for balance enquiry
void balance_enquiry() {
    int acc_no;
    struct Account acc;

    printf("\nEnter the account number for balance enquiry: ");
    scanf("%d", &acc_no);
    acc = find_account(acc_no);

    if (acc.acc_no == 0) {
        printf("Account not found.\n");
        return;
    }

    printf("\nAccount Details:\n");
    printf("Account Number: %d\n", acc.acc_no);
    printf("Account Holder Name: %s\n", acc.name);
    printf("Current Balance: %.2f\n", acc.balance);
}

// Function to view all accounts reading from TEXT file
void view_all_accounts() {
    struct Account acc;
    FILE *fp;

    fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("No accounts found.\n");
        return;
    }

    printf("\n*** All Accounts List ***\n");
    printf("%-15s %-20s %-10s\n", "Account No.", "Name", "Balance");
    printf("--------------------------------------------------\n");

    while (fscanf(fp, "%d\n%[^\n]\n%f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        printf("%-15d %-20s %-10.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
}
