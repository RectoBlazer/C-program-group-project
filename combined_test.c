#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Define common structures and constants
#define MAX_NAME_LENGTH 50
#define MAX_USERS 100
#define D_FIRST_NAME 15
#define D_LAST_NAME 15
#define D_BIRTHDAY 12
#define D_EMAIL 40
#define D_PASSPORT_NUM 10
#define D_PHONE_NUM 11
#define D_ADDRESS 100
#define D_PASSWORD 25

typedef struct {
    char first_name[D_FIRST_NAME];
    char last_name[D_LAST_NAME];
    char birthday[D_BIRTHDAY];
    char email[D_EMAIL];
    char passport_num[D_PASSPORT_NUM];
    char phone_num[D_PHONE_NUM];
    char address[D_ADDRESS];
    char password[D_PASSWORD];
} Customer;

typedef struct {
    int accommodationID;
    char type[30];
    char description[100];
    double price;
    int Available;
} Accommodation;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char contact[MAX_NAME_LENGTH];
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    char role[MAX_NAME_LENGTH];
} User;

User users[MAX_USERS];
int userCount = 0;
Accommodation accommodations[MAX_USERS];
int accommodationCount = 0;

// Function prototypes
void record_accommodation();
void view_customer_info();
void employee_Page();
void viewCustomerList();
void viewAccommodation();
void registerEmployee();
int loginEmployee();
int MainMenu();
void cust_menu();
int login_customer();
void register_customer();
void bill_information();

int main() {
    int choice;
    MainMenu();
    scanf("%d", &choice);
    while (!(choice >= 1 && choice <= 4)) {
        printf("Invalid choice, please try again (must be between 1 and 4): ");
        scanf("%d", &choice);
    }
    switch (choice) {
        case 1:
            adm_menu();
            break;
        case 2:
            empl_menu();
            break;
        case 3:
            cust_menu();
            break;
        case 4:
            printf("Exiting the system. Goodbye!\n");
    }
    return 0;
}

int MainMenu() {
    printf("\t\t\t***Welcome to the Hotel Management System!***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Please select your role:\n");
    printf("1. Hotel Administrator\n");
    printf("2. Employee\n");
    printf("3. Customer\n");
    printf("4. Exit\n");
    printf("Please select a number between 1 and 4: ");
    return 0;
}

int adm_menu() {
    int choice;
    printf("You selected: Hotel Administrator\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Record Accommodation Information\n");
    printf("4. View Customer Information\n");
    printf("5. Back to main menu\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    while (!(choice >= 1 && choice <= 5)) {
        printf("Invalid choice, please try again (must be between 1 and 5): ");
        scanf("%d", &choice);
    }
    switch (choice) {
        case 1:
            // register_Hotel_Administrator();
            break;
        case 2:
            // login_Hotel_Administrator();
            break;
        case 3:
            record_accommodation();
            break;
        case 4:
            view_customer_info();
            break;
        case 5:
            break;
    }
    return 0;
}

int empl_menu() {
    int choice;
    printf("You selected: Employee\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Back to main menu\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    while (!(choice >= 1 && choice <= 3)) {
        printf("Invalid choice, please try again (must be between 1 and 3): ");
        scanf("%d", &choice);
    }
    switch (choice) {
        case 1:
            registerEmployee();
            break;
        case 2:
            loginEmployee();
            break;
        case 3:
            break;
    }
    return 0;
}

void record_accommodation() {
    printf("\t\t\t*** Record Accommodation Info ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    Accommodation new_accommodation;

    printf("Enter Accommodation ID: ");
    scanf("%d", &new_accommodation.accommodationID);

    printf("Enter Accommodation Type: ");
    scanf("%s", new_accommodation.type);

    printf("Enter Description: ");
    scanf(" %[^\n]s", new_accommodation.description);

    printf("Enter Price per Night: ");
    scanf("%lf", &new_accommodation.price);

    new_accommodation.Available = 1; // the new accommodation exists by default

    // open the binary file to store info
    FILE *file = fopen("accommodations.dat", "ab");
    if (file == NULL) {
        printf("Error opening file to save accommodation data!\n");
        return;
    }

    // write new accommodation to binary file
    fwrite(&new_accommodation, sizeof(Accommodation), 1, file);
    fclose(file);

    printf("Accommodation data saved successfully!\n");
}

void view_customer_info() {
    printf("\t\t\t*** View Customer Info ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    Customer existing_customer;
    FILE *file = fopen("customers.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&existing_customer, sizeof(Customer), 1, file) == 1) {
        printf("First Name: %s\n", existing_customer.first_name);
        printf("Last Name: %s\n", existing_customer.last_name);
        printf("Birthday: %s\n", existing_customer.birthday);
        printf("Email: %s\n", existing_customer.email);
        printf("Passport Number: %s\n", existing_customer.passport_num);
        printf("Phone Number: %s\n", existing_customer.phone_num);
        printf("Address: %s\n", existing_customer.address);
        printf("----------------------------------------------------\n");
    }

    fclose(file);
}

void employee_Page() {
    int choice;

    while (1) {
        printf("\n___Employee Page___\n");
        printf("1. View List of Customers\n");
        printf("2. View List of Accommodations\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                viewCustomerList();
                break;
            case 2:
                viewAccommodation();
                break;
            case 3:
                printf("\nLogging out from Employee Page.\n");
                return;
            default:
                printf("\nInvalid choice. Please select a valid option.\n");
        }
    }
}

void viewCustomerList() {
    int found = 0;

    printf("\n--- Customer List ---\n");
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].role, "Customer") == 0) {
            found = 1;
            printf("Name: %s\n", users[i].name);
            printf("Contact: %s\n", users[i].contact);
            printf("--------------------------\n");
        }
    }

    if (!found) {
        printf("\nNo customers found.\n");
    }
}

void viewAccommodation() {
    if (accommodationCount == 0) {
        printf("\nSorry. No accommodations available.\n");
        return;
    }

    printf("\n--- List of Accommodations ---\n");
    for (int i = 0; i < accommodationCount; i++) {
        printf("Room ID: %d\n", accommodations[i].accommodationID);
        printf("Room Type: %s\n", accommodations[i].type);
        printf("Price: %.2f\n", accommodations[i].price);
        printf("Status: %s\n", accommodations[i].Available ? "Available" : "Booked");
        printf("--------------------------\n");
    }
}

void registerEmployee() {
    if (userCount >= MAX_USERS) {
        printf("\nUser limit reached. Cannot register more employees.\n");
        return;
    }

    User newUser;

    printf("\n=== Register Employee ===\n");
    printf("Enter your name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0';

    printf("Enter your contact: ");
    fgets(newUser.contact, sizeof(newUser.contact), stdin);
    newUser.contact[strcspn(newUser.contact, "\n")] = '\0';

    printf("Enter a username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0';

    printf("Enter a password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    newUser.password[strcspn(newUser.password, "\n")] = '\0';

    strcpy(newUser.role, "Employee");
    users[userCount++] = newUser;

    printf("\nEmployee registered successfully!\n");
}

int loginEmployee() {
    char username[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];

    printf("\n__Employee Login __\n");
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            if (strcmp(users[i].role, "Employee") == 0) {
                printf("\nLogin successful. Welcome, %s!\n", users[i].name);
                employee_Page();
                return 1;
            } else {
                printf("\nAccess denied. Only employees are allowed to log in.\n");
                return 0;
            }
        }
    }

    printf("\nInvalid username or password. Please try again.\n");
    return 0;
}

void cust_menu() {
    int choice;
    printf("You selected: Customer\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Back to main menu\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    while (!(choice >= 1 && choice <= 3)) {
        printf("Invalid choice, please try again (must be between 1 and 3): ");
        scanf("%d", &choice);
    }
    switch (choice) {
        case 1:
            register_customer();
            break;
        case 2:
            login_customer();
            break;
        case 3:
            break;
    }
}

void register_customer() {
    printf("\t\t\t*** Register customer ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    Customer new_customer;
    // First name
    printf("Please enter your first name: ");
    scanf("%s", new_customer.first_name);
    while (strlen(new_customer.first_name) < 2 || alphabetical(new_customer.first_name) == 0) {
        if (strlen(new_customer.first_name) < 2) {
            printf("First name is too short! , please enter your first name again: ");
        } else if (alphabetical(new_customer.first_name) == 0) {
            printf("First name must be alphabetical! , please enter your first name again: ");
        }
        scanf("%s", new_customer.first_name);
    }

    // Last name
    printf("Please enter your last name: ");
    scanf("%s", new_customer.last_name);
    while (strlen(new_customer.last_name) < 2 || alphabetical(new_customer.last_name) == 0) {
        if (strlen(new_customer.last_name) < 2) {
            printf("Last name is too short! , please enter your last name again: ");
        } else if (alphabetical(new_customer.last_name) == 0) {
            printf("Last name must be alphabetical! , please enter your last name again: ");
        }
        scanf("%s", new_customer.last_name);
    }

    // Birthday
    printf("Please enter your birthday (DD/MM/YYYY): ");
    scanf("%s", new_customer.birthday);
    while (check_birthday(new_customer.birthday) == 0) {
        printf("Invalid birthday, please enter your birthday again:");
        scanf("%s", new_customer.birthday);
    }

    // Email
    printf("Please enter your email: ");
    scanf("%s", new_customer.email);
    while (check_email(new_customer.email) == 0 || exist_email(new_customer.email) == 1) {
        if (check_email(new_customer.email) == 0) {
            printf("Invalid email, please enter your email again: ");
            scanf("%s", new_customer.email);
        } else if (exist_email(new_customer.email) == 1) {
            printf("Email already used, please enter your email again: ");
            scanf("%s", new_customer.email);
        }
    }

    // Passport number
    printf("Please enter your passport number: ");
    scanf("%s", new_customer.passport_num);
    while (check_passport(new_customer.passport_num) == 0 || exist_passport(new_customer.passport_num) == 1) {
        if (check_passport(new_customer.passport_num) == 0) {
            printf("Invalid passport number, please enter your passport number again: ");
            scanf("%s", new_customer.passport_num);
        } else if (exist_passport(new_customer.passport_num) == 1) {
            printf("Passport already used, please enter your passport number again: ");
            scanf("%s", new_customer.passport_num);
        }
    }

    // Phone number
    printf("Please enter your phone number: ");
    scanf("%s", new_customer.phone_num);
    while (numeric(new_customer.phone_num) == 0 || strlen(new_customer.phone_num) < 10 || strlen(new_customer.phone_num) > 11 || new_customer.phone_num[0] != '0' || new_customer.phone_num[1] != '7') {
        printf("Invalid phone number, please enter your phone number again: ");
        scanf("%s", new_customer.phone_num);
    }

    // Address
    printf("Please enter your address: ");
    scanf(" %[^\n]s", new_customer.address);

    // Password
    printf("Please enter password (it must be at least 8 characters, and contain letters, numbers and at least one special character): ");
    scanf(" %[^\n]s", new_customer.password);
    while (check_password(new_customer.password) == 0 || strlen(new_customer.password) < 8) {
        printf("Invalid password, please enter your password again: ");
        scanf(" %[^\n]s", new_customer.password);
    }

    char password_2[40];
    printf("Please re-enter password: ");
    scanf(" %[^\n]s", &password_2);
    while (strcmp(password_2, new_customer.password) != 0) {
        printf("Incorrect password, Please enter again: ");
        scanf(" %[^\n]s", &password_2);
    }

    // Opening the binary file to store the information
    FILE *file = fopen("customers.dat", "ab");
    if (file == NULL) {
        printf("Error opening file to save customer data!\n");
        return;
    }

    // Writing the new customer data to the binary file
    fwrite(&new_customer, sizeof(Customer), 1, file);
    fclose(file);

    printf("Customer data saved successfully!\n");
}

int login_customer() {
    printf("\t\t\t*** Login Customer ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    char email[40], password[25];
    printf("Please enter your email: ");
    scanf("%s", email);
    while (exist_email(email) == 0) {
        printf("This email does not exist, Please enter your email again: ");
        scanf("%s", email);
    }
    printf("Please enter your password: ");
    scanf(" %[^\n]s", password);
    while (correct_password(email, password) == 0) {
        printf("Incorrect password, Please enter your password again: ");
        scanf("%s", password);
    }
    printf("~~~~~~~~~~~~~~ Login successful! ~~~~~~~~~~~~~~\n");
    int choice;
    printf("1. View list and information of Accommodation\n");
    printf("2. View all reservations\n");
    printf("3. Booking\n");
    printf("4. Bill information\n");
    printf("5. Back to main menu\n");
    printf("Please select a number between 1 and 5: ");
    scanf("%d", &choice);
    while (!(choice >= 1 && choice <= 5)) {
        printf("Invalid choice, please try again (must be between 1 and 5): ");
        scanf("%d", &choice);
    }
    switch (choice) {
        case 1:
            // view_list_information_accommodation();
            break;
        case 2:
            view_reservations();
            break;
        case 3:
            booking();
            break;
        case 4:
            bill_information();
            break;
        case 5:
            MainMenu();
    }
    return 0;
}

void bill_information() {
    printf("\t\t\t*** Bill Information ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    char customer_name[50];
    printf("Enter your name (First Last):