
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

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
#define MAX_CONTACT_LENGTH 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

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
    char password2[MAX_PASSWORD_LENGTH];
    char role[MAX_NAME_LENGTH];
} User;

 // Structure that contains the reserved dates of each room
 typedef struct {
     int accommodationID;              // Unique ID for the accommodation
     char reservedDates[100][15];      // An array for reserved dates 
     int reservedCount;                // Number of reserved dates for each room
 } Reservation;

 // Structure for Booking
 struct Booking {
     int bookingID;
     int accommodationID;
     char customerName[50];
     char checkInDate[15];
     char checkOutDate[15];
 };

User users[MAX_USERS];
int userCount = 0;
Accommodation accommodations[MAX_USERS];
int accommodationCount = 0;
User employees[MAX_USERS];
int employeeCount = 0;

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
void register_Hotel_Administrator();
void login_Hotel_Administrator();
int login_customer();
void view_list_information_accommodation();
void register_customer();
void bill_information();
int is_customer_registered(const char *customer_name);
int is_date_reserved(int accommodationID, const char *date);
void add_reservation(int accommodationID, const char *date);
void get_next_date(const char *current_date, char *next_date);
int is_booking_id_exist(int bookingID);
int generate_unique_booking_id();
int booking();
void view_reservations();
int alphabetical(char ch[15]);
int check_birthday(char birthday[12]);
int check_email(char email[40]);
int exist_email(const char *email);
int check_passport(char passport_num[10]);
int exist_passport(char passport[10]);
int numeric(char ch[15]);
int check_password(char password[25]);
int correct_password(const char *email, const char *password);
int compare_dates(const char *date1, const char *date2);
int is_valid_date(const char *date);
void logout();
int validatePassword(const char *password);

#include <stdio.h>

void empl_menu(); // Forward declaration for the employee menu
void admin_menu(); // Forward declaration for the admin menu
void customer_menu(); // Forward declaration for the customer menu

int MainMenu() {
    int choice;

    while (1) {
        printf("\t\t\t***Welcome to the Hotel Management System!***\n");
        printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Please select your role:\n");
        printf("1. Hotel Administrator\n");
        printf("2. Employee\n");
        printf("3. Customer\n");
        printf("4. Exit\n");
        printf("Please select a number between 1 and 4: ");

        // Handle input validation
        if (scanf("%d", &choice) != 1) {
            // Clear the input buffer if the input is invalid
            while (getchar() != '\n');
            printf("\nInvalid input. Please enter a number between 1 and 4.\n");
            continue; // Re-display the menu
        }

        // Handle user choices
        switch (choice) {
            case 1:
                 // Call Hotel Administrator menu
                break;
            case 2:
                empl_menu(); // Call Employee menu
                break;
            case 3:
                // Call Customer menu
                break;
            case 4:
                printf("\nExiting program. Goodbye!\n");
                return 0; // Exit the program
            default:
                printf("\nInvalid choice. Please select a number between 1 and 4.\n");
        }
    }
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
            register_Hotel_Administrator();
            break;
        case 2:
            login_Hotel_Administrator();
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

void empl_menu() {
    int choice;

    while (1) {
        printf("\n=== Employee Main Menu ===\n");
        printf("1. Register a New Employee\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            // Clear the input buffer
            while (getchar() != '\n');
            printf("\nInvalid input. Please enter a number.\n");
            continue;
        }
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                registerEmployee();
                break;
            case 2:
                if (loginEmployee()) {
                    employee_Page();
                } else {
                    printf("\nLogin failed. Please try again.\n");
                }
                break;
            case 3:
                printf("\nReturning to Main Menu...\n");
                return; // Return to the main menu
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void register_Hotel_Administrator() {
    if (userCount >= MAX_USERS) {
        printf("\nUser limit reached. Cannot register more administrators.\n");
        return;
    }

    User newUser;

    printf("\n=== Register Hotel Administrator ===\n");

    // Clear the input buffer
    while (getchar() != '\n');

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

    strcpy(newUser.role, "Hotel Administrator");
    users[userCount++] = newUser;

    printf("\nHotel Administrator registered successfully!\n");
    MainMenu();
}

void login_Hotel_Administrator() {
    char username[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];

    printf("\n__Hotel Administrator Login __\n");

    // Clear the input buffer
    while (getchar() != '\n');

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            if (strcmp(users[i].role, "Hotel Administrator") == 0) {
                printf("\nLogin successful. Welcome, %s!\n", users[i].name);
                // Call the admin-specific functions or menu here
                return;
            } else {
                printf("\nAccess denied. Only Hotel Administrators are allowed to log in.\n");
                return;
            }
        }
    }

    printf("\nInvalid username or password. Please try again.\n");
    MainMenu();
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

void registerEmployee() {
    if (employeeCount >= MAX_USERS) {
        printf("\nEmployee limit reached. Cannot register more employees.\n");
        return;
    }

    User newEmployee;

    printf("\n=== Register a New Employee ===\n");
    printf("Enter name: ");
    fgets(newEmployee.name, MAX_NAME_LENGTH, stdin);
    newEmployee.name[strcspn(newEmployee.name, "\n")] = '\0';

    printf("Enter contact information: ");
    fgets(newEmployee.contact, MAX_CONTACT_LENGTH, stdin);
    newEmployee.contact[strcspn(newEmployee.contact, "\n")] = '\0';

    printf("Enter username: ");
    fgets(newEmployee.username, MAX_USERNAME_LENGTH, stdin);
    newEmployee.username[strcspn(newEmployee.username, "\n")] = '\0';

    do {
        printf("Enter password (at least 8 characters, including uppercase letters and digits): ");
        fgets(newEmployee.password, MAX_PASSWORD_LENGTH, stdin);
        newEmployee.password[strcspn(newEmployee.password, "\n")] = '\0';

        if (!validatePassword(newEmployee.password)) {
            printf("\nInvalid password. Please follow the password requirements.\n");
        }
    } while (!validatePassword(newEmployee.password));

    employees[employeeCount++] = newEmployee;
    printf("\nEmployee registered successfully. Press Enter to continue to Main Menu.\n");
    getchar();
}

int loginEmployee() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("\n=== Login ===\n");
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].username, username) == 0 && strcmp(employees[i].password, password) == 0) {
            printf("\nLogin successful. Welcome, %s!\n", employees[i].name);
            return 1;
        }
    }

    printf("\nInvalid username or password. Please try again.\n");
    return 0;
}

void employee_Page() {
    int choice;

    while (1) {
        printf("\n=== Employee Page ===\n");
        printf("1. View List of Customers\n");
        printf("2. View List of Accommodations\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                viewCustomerList();
                break;
            case 2:
                viewAccommodation();
                break;
            case 3:
                empl_menu(); 
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void viewCustomerList() {
    int found = 0;

    while (1) {
        printf("\n--- Customer List ---\n");

        // Iterate through the users to find customers
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].role, "Customer") == 0) {
                found = 1;
                printf("Name: %s\n", users[i].name);
                printf("Contact: %s\n", users[i].contact);
                printf("--------------------------\n");
            }
        }

        // If no customers found
        if (!found) {
            printf("\nNo customers found.\n");
        }

        // Display options after viewing
        printf("\nOptions:\n");
        printf("1. Return to Employee Page\n");
        printf("2. Refresh Customer List\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        getchar(); // Consume newline

        if (choice == 1) {
            // Return to Employee Page
            return;
        } else if (choice == 2) {
            // Refresh the customer list
            continue;
        } else {
            printf("\nInvalid choice. Try again.\n");
        }
    }
}


void viewAccommodation() {
    while (1) {
        if (accommodationCount == 0) {
            printf("\nNo accommodations available.\n");
        } else {
            printf("\n--- List of Accommodations ---\n");

            // Iterate through accommodations and display their details
            for (int i = 0; i < accommodationCount; i++) {
                printf("Accommodation ID: %d\n", accommodations[i].accommodationID);
                printf("Accommodation Type: %s\n", accommodations[i].type);
                printf("Price: %.2f\n", accommodations[i].price);
                printf("Status: %s\n", accommodations[i].Available ? "Available" : "Booked");
                printf("--------------------------\n");
            }
        }

        // Display options after viewing
        printf("\nOptions:\n");
        printf("1. Return to Employee Page\n");
        printf("2. Refresh Accommodation List\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        getchar(); // Consume newline

        if (choice == 1) {
            // Return to Employee Page
            return;
        } else if (choice == 2) {
            // Refresh the accommodation list
            continue;
        } else {
            printf("\nInvalid choice. Try again.\n");
        }
    }
}




int validatePassword(const char *password) {
    int hasUpper = 0, hasDigit = 0, length = strlen(password);

    if (length < 8) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = 1;
        if (isdigit(password[i])) hasDigit = 1;
    }

    return hasUpper && hasDigit;
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

//checking if a string is numerical or not
int numeric(char ch[15]){
    for (int i = 0; i < strlen(ch); i++) { 
         if (!isdigit(ch[i])){
            return 0;
         }
    }
    return 1;
    
}

//checking if a string is alphabetical or not
int alphabetical(char ch[15]){
    for (int i = 0; i < strlen(ch); i++) { 
         if (!isalpha(ch[i])){
            return 0;
         }
    }
    return 1;
    
}

//checking if email valid or not
int check_email(char email[40]) {
    int count_at = 0; // To count the occurance of '@'
    int count_dot = 0; // To check if '.' exists after '@' or not
    int length = strlen(email);

    if (length < 5) return 0;

    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {
            count_at++;
            // '@' should not be at the start or end
            if (i == 0 || i == length - 1) return 0;
        }
        if (count_at > 0 && email[i] == '.') {
            count_dot = 1; // Found '.' after '@'
        }
    }

    if (count_at == 1 && count_dot) {
        return 1;
    }
    return 0;
}

//checking if birthday is valid or not
int check_birthday(char birthday[12]){
    if (strlen(birthday) != 10) {
        return 0;
    }

    char DD[3] = {birthday[0], birthday[1], '\0'};
    char MM[3] = {birthday[3], birthday[4], '\0'};
    char YYYY[5] = {birthday[6], birthday[7], birthday[8], birthday[9], '\0'};

    if (numeric(DD) == 0 || numeric(MM) == 0 || numeric(YYYY) == 0 ||
        birthday[2] != '/' || birthday[5] != '/') {
        return 0;
    }

    int day = atoi(DD);
    int month = atoi(MM);
    int year = atoi(YYYY);

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        return 0;
    }
    return 1;
}

//checking passport number if it's valid or not
int check_passport(char passport_num[10]){
    if (strlen(passport_num)<6 || strlen(passport_num)>9){
        return 0;
    }
    for (int i=0; i<strlen(passport_num); i++){
        if(!isalnum(passport_num[i])){
            return 0;
        }
    }
    return 1;
}

//checking password if it's valid or not
int check_password(char password[25]){
    int s=0;
    for (int i=0; i<strlen(password);i++){
        if(!isalnum(password[i])){
            s++;
        }
    }
    if (s!=0){return 1;}
    else return 0;
}

// Checking if email exists or not
int exist_email(const char *email) {
    Customer existing_customer;
    FILE *file = fopen("customers.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return 0;
    }

    while (fread(&existing_customer, sizeof(Customer), 1, file) == 1) {
        if (strcmp(existing_customer.email, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Checking if the entered password is correct or not
int correct_password(const char *email, const char *password) {
    Customer existing_customer;
    FILE *file = fopen("customers.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return 0;
    }

    while (fread(&existing_customer, sizeof(Customer), 1, file) == 1) {
        if (strcmp(existing_customer.email, email) == 0) {
            fclose(file);
            return strcmp(existing_customer.password, password) == 0;
        }
    }

    fclose(file);
    return 0;
}

// Checking if passport number exists or not
int exist_passport(char passport[10]) {
    Customer existing_customer;
    FILE *file = fopen("customers.dat", "rb");
    

    while (fread(&existing_customer, sizeof(Customer), 1, file) == 1) {
        if (strcmp(existing_customer.passport_num, passport) == 0) {
            fclose(file);
            return 1;  }

    fclose(file);
    return 0; }}

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
            view_list_information_accommodation();
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

void view_list_information_accommodation() {
    if (accommodationCount == 0) {
        printf("\nSorry. No accommodations available.\n");
        return;
    }

    printf("\n--- List of Accommodations ---\n");
    for (int i = 0; i < accommodationCount; i++) {
        printf("Accommodation ID: %d\n", accommodations[i].accommodationID);
        printf("Type: %s\n", accommodations[i].type);
        printf("Description: %s\n", accommodations[i].description);
        printf("Price per Night: %.2f\n", accommodations[i].price);
        printf("Status: %s\n", accommodations[i].Available ? "Available" : "Booked");
        printf("--------------------------\n");
    }
}

void bill_information() {
    printf("\t\t\t*** Bill Information ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

     char customer_name[50];
     printf("Enter your name (First Last): ");
     scanf(" %[^\n]s", customer_name);
 
     struct Booking booking;
     int found = 0;
 
     FILE *file = fopen("bookings.dat", "rb");
     if (!file) {
         printf("Error opening booking file!\n");
         return;
     }
 
     // Search for the customer's booking
     while (fread(&booking, sizeof(struct Booking), 1, file) == 1) {
         if (strcmp(booking.customerName, customer_name) == 0) {
             printf("\n~~~~~ Booking Details ~~~~~\n");
             printf("Booking ID: %d\n", booking.bookingID);
             printf("Accommodation ID: %d\n", booking.accommodationID);
             printf("Check-In Date: %s\n", booking.checkInDate);
             printf("Check-Out Date: %s\n", booking.checkOutDate);
             //printf("Total Amount: $%.2f\n", booking.totalAmount); // the total amount should be calculated per night
             found = 1;
             break;
         }
     }
 
     fclose(file);
 
     if (!found) {
         printf("You have not booked any accommodation.\n");
     }
 }

 int is_customer_registered(const char *customer_name) {
     Customer existing_customer;
     FILE *file = fopen("customers.dat", "rb");
     if (!file) {
         printf("Error opening file!\n");
         return 0;
     }
 
     while (fread(&existing_customer, sizeof(Customer), 1, file) == 1) {
         char full_name[D_FIRST_NAME + D_LAST_NAME + 2];
         sprintf(full_name, "%s %s", existing_customer.first_name, existing_customer.last_name);
         if (strcmp(full_name, customer_name) == 0) {
             fclose(file);
             return 1;
         }
     }
 
     fclose(file);
     return 0;
 }
 
 // Function to validate date format
 int is_valid_date(const char *date) {
     int day, month, year;
 
     // Check if the date matches the format "DD/MM/YYYY"
     if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
         return 0; // Invalid format
     }
 
     // Validate year
     if (year < 1900 || year > 2100) {
         return 0;
     }
 
     // Validate month
     if (month < 1 || month > 12) {
         return 0;
     }
 
     return 1; // Date is valid
 }
 
 // Function to compare two dates in DD/MM/YYYY format
 // Returns -1 if date1 < date2, 0 if date1 == date2, 1 if date1 > date2
 int compare_dates(const char *date1, const char *date2) {
     int day1, month1, year1, day2, month2, year2;
 
     sscanf(date1, "%d/%d/%d", &day1, &month1, &year1);
     sscanf(date2, "%d/%d/%d", &day2, &month2, &year2);
 
     if (year1 != year2) {
         return (year1 < year2) ? -1 : 1;
     }
     if (month1 != month2) {
         return (month1 < month2) ? -1 : 1;
     }
     if (day1 != day2) {
         return (day1 < day2) ? -1 : 1;
     }
     return 0; // Dates are equal
 }
 
 int is_date_reserved(int accommodationID, const char *date) {
     FILE *file = fopen("reservations.dat", "rb");
     if (!file) {
         return 0; // No reservations exist
     }
 
     Reservation reservation;
     while (fread(&reservation, sizeof(Reservation), 1, file) == 1) {
         if (reservation.accommodationID == accommodationID) {
             for (int i = 0; i < reservation.reservedCount; i++) {
                 if (strcmp(reservation.reservedDates[i], date) == 0) {
                     fclose(file);
                     return 1; // Date is reserved
                 }
             }
             break;
         }
     }
 
     fclose(file);
     return 0; // Date is not reserved
 }
 
 void add_reservation(int accommodationID, const char *date) {
     FILE *file = fopen("reservations.dat", "rb+");
     if (!file) {
         printf("Creating a new reservations file.\n");
         file = fopen("reservations.dat", "wb+");
     }
 
     Reservation reservation;
     int found = 0;
 
     while (fread(&reservation, sizeof(Reservation), 1, file) == 1) {
         if (reservation.accommodationID == accommodationID) {
             found = 1;
 
             // Check if date is already reserved
             for (int i = 0; i < reservation.reservedCount; i++) {
                 if (strcmp(reservation.reservedDates[i], date) == 0) {
                     printf("Date %s is already reserved for Accommodation ID %d.\n", date, accommodationID);
                     fclose(file);
                     return;
                 }
             }
 
             // Add the new date
             strcpy(reservation.reservedDates[reservation.reservedCount], date);
             reservation.reservedCount++;
 
             // Update the file
             fseek(file, -sizeof(Reservation), SEEK_CUR);
             fwrite(&reservation, sizeof(Reservation), 1, file);
 
             fclose(file);
             return;
         }
     }
 
     // If no reservation record exists for the accommodation, create a new one
     if (!found) {
         Reservation new_reservation;
         new_reservation.accommodationID = accommodationID;
         new_reservation.reservedCount = 1;
         strcpy(new_reservation.reservedDates[0], date);
 
         fwrite(&new_reservation, sizeof(Reservation), 1, file);
     }
 
     fclose(file);
 }
 
 void get_next_date(const char *current_date, char *next_date) {
     int day, month, year;
     sscanf(current_date, "%d/%d/%d", &day, &month, &year);
 
     // Advance the day
     day++;

     // Adjust for month-end
     if ((month == 2 && day > 28) || 
         (month == 4 || month == 6 || month == 9 || month == 11) && day > 30 || // 30-day months
         day > 31) {  // 31-day months
         day = 1;
         month++;
     }
 
     // Adjust for year-end
     if (month > 12) {
         month = 1;
         year++;
     }
 
     sprintf(next_date, "%02d/%02d/%04d", day, month, year);
 }
 
 int is_booking_id_exist(int bookingID) {
     struct Booking existing_booking;
     FILE *file = fopen("bookings.dat", "rb");
     if (!file) {
         return 0; // File doesn't exist, so ID cannot exist
     }
 
     while (fread(&existing_booking, sizeof(struct Booking), 1, file) == 1) {
         if (existing_booking.bookingID == bookingID) {
             fclose(file);
             return 1; // ID exists
         }
     }
 
     fclose(file);
     return 0; // ID does not exist
 }
 
 int generate_unique_booking_id() {
     int new_id;
     srand(time(NULL)); // Seed for random number generation
 
     do {
         new_id = rand() % 100000; // Generate a random ID (5 digits max)
     } while (is_booking_id_exist(new_id));
 
     return new_id;
 }
 
 // Booking function 
 int booking() {
     char customer_name[50];
     printf("\nEnter Booking Details:\n");
     printf("Customer Name (First Last): ");
     scanf(" %[^\n]s", customer_name);
 
     // Check if the customer is registered
     if (!is_customer_registered(customer_name)) {
         int choice;
         printf("Customer is not registered. Please register before booking.\n");
         printf("1. customer menu \n");
         printf("2. main menu\n"); 
         printf("3. exit");
         printf("\n enter your choice: ");
         scanf("%d", &choice);
         while(!(choice >= 1 && choice <= 4)){
             printf("Invalid choice, please try again (must be between 1 and 4): ");
             scanf("%d", &choice);
         }
         switch (choice) {
             case 1:
                 cust_menu();
                 break;
             case 2:
                 MainMenu();
                 break;
             case 3:
                 printf("\nThank you, bye!\n");
                 break;
         }
     }
 
     // Proceed with booking if the customer is registered
     struct Booking new_booking;
 
     new_booking.bookingID = generate_unique_booking_id();
     strcpy(new_booking.customerName, customer_name);

     printf("\nEnter Accommodation ID: ");
     scanf("%d", &new_booking.accommodationID);
 
     // Input and validate check-in date
     printf("\nEnter Check-In Date (DD/MM/YYYY): ");
     scanf("%s", new_booking.checkInDate);
     while (!is_valid_date(new_booking.checkInDate)) {
         printf("Invalid date format! Please enter a valid Check-In Date (DD/MM/YYYY): ");
         scanf("%s", new_booking.checkInDate);
     }

    // Input and validate check-out date
     printf("\nEnter Check-Out Date (DD/MM/YYYY): ");
     scanf("%s", new_booking.checkOutDate);
     while (!is_valid_date(new_booking.checkOutDate)) {
         printf("Invalid date format! Please enter a valid Check-Out Date (DD/MM/YYYY): ");
         scanf("%s", new_booking.checkOutDate);
     }
 
     // Ensure check-in date is before check-out date
     while (compare_dates(new_booking.checkInDate, new_booking.checkOutDate) >= 0) {
         printf("Check-Out Date must be later than Check-In Date!\n");
         printf("\nRe-enter Check-Out Date (DD/MM/YYYY): ");
         scanf("%s", new_booking.checkOutDate);
 
         while (!is_valid_date(new_booking.checkOutDate)) {
             printf("Invalid date format! Please enter a valid Check-Out Date (DD/MM/YYYY): ");
             scanf("%s", new_booking.checkOutDate);
         }
     }
     // Check if the dates are available
     char current_date[15], next_date[15];
     strcpy(current_date, new_booking.checkInDate);
 
     while (strcmp(current_date, new_booking.checkOutDate) <= 0) {
         if (is_date_reserved(new_booking.accommodationID, current_date)) {
             printf("Sorry, the date %s is already reserved.\n", current_date);
             return 0;  
         }
         get_next_date(current_date, next_date);
         strcpy(current_date, next_date);
     }
 
     // Add all dates to the reservations
     strcpy(current_date, new_booking.checkInDate);
     while (strcmp(current_date, new_booking.checkOutDate) <= 0) {
         add_reservation(new_booking.accommodationID, current_date);
         get_next_date(current_date, next_date);
         strcpy(current_date, next_date);
     }
 
     // Save the booking
     FILE *file = fopen("bookings.dat", "ab");
     if (!file) {
         printf("Error opening file to save booking data!\n");
         return 0;
     }
 
     fwrite(&new_booking, sizeof(struct Booking), 1, file);
     fclose(file);
 
     printf("Booking saved successfully! Your Booking ID is: %d\n", new_booking.bookingID);
     return 1;
 }
 
 // Function to view all reservations
 void view_reservations() {
     FILE *file = fopen("reservations.dat", "rb");
     if (!file) {
         printf("No reservations found.\n");
         return;
     }
 
     Reservation reservation;
     printf("\t\t\t*** Reservations ***\n");
     printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
 
     while (fread(&reservation, sizeof(Reservation), 1, file) == 1) {
         printf("Accommodation ID: %d\n", reservation.accommodationID);
         printf("Reserved Dates: ");
         for (int i = 0; i < reservation.reservedCount; i++) {
             printf("%s ", reservation.reservedDates[i]);
         }
         printf("\n\n");
     }
 
     fclose(file);
 }

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
