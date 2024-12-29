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
#define MAX_ACCESS_CODE_LENGTH 15
#define MAX_DEPARTMENT_LENGTH 30
#define MAX_ACCOMMODATIONS 100


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
    char type[50];
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

typedef struct {
    char name_E[MAX_NAME_LENGTH];
    char phoneNumber_E[MAX_CONTACT_LENGTH];
    char email_E[MAX_CONTACT_LENGTH];
    char username_E[MAX_USERNAME_LENGTH];
    char password_E[MAX_PASSWORD_LENGTH];
    char accessCode_E[MAX_ACCESS_CODE_LENGTH];
    char department_E[MAX_DEPARTMENT_LENGTH];
} Employee;

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
     int totalNights;
 };

User users[MAX_USERS];
int userCount = 0;
Accommodation accommodations[MAX_ACCOMMODATIONS];
int accommodationCount = 0;
Employee employees[MAX_USERS];
int employeeCount = 0;
Customer customers[MAX_USERS];
int customerCount = 0;


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
void admin_dashboard();
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
void booking();
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
int validatePassword_Employee(const char *password);
int validatePhoneNumber_Employee(const char *phoneNumber);
int validateEmail_Employee(const char *email);
void generateAccessCode(char *accessCode, const char *department, int id);
int doesAccommodationExist(const char *fileName, int id); // Placeholder.
void debug_print_accommodations();
void save_employees();
int validateName_Employee(const char *name); // Function to validate employee name
#include <stdio.h>

int ValidateEmail(const char *email); // Function prototype
int validatePassword(const char *password); // Function prototype

void empl_menu(); // Forward declaration for the employee menu
void adm_menu(); // Forward declaration for the admin menu
void cust_menu(); // Forward declaration for the customer menu

int MainMenu() {
    int choice;

    while (1) {
        // Display header
        printf("\n============================================\n");
        printf("   Welcome to the Hotel Management System!   \n");
        printf("============================================\n\n");

        // Display menu options
        printf("Please select your role:\n");
        printf("1. Hotel Administrator\n");
        printf("2. Employee\n");
        printf("3. Customer\n");
        printf("4. Exit\n\n");
        printf("Enter your choice (1-4): ");

        // Input validation for choice
        while (1) {
            if (scanf("%d", &choice) != 1) {
                printf("\n[ERROR] Invalid input. Please enter a number between 1 and 4: ");
                while (getchar() != '\n'); // Clear invalid input
            } else if (choice < 1 || choice > 4) {
                printf("\n[ERROR] Invalid choice. Please select a valid option (1-4): ");
            } else {
                break; // Valid input
            }
        }
        getchar(); // Consume newline

        printf("\n[LOG] User selected option: %d\n", choice);

        // Handle user choice
        switch (choice) {
            case 1:
                printf("\n[LOG] Redirecting to Administrator Menu...\n\n");
                adm_menu();
                break;

            case 2:
                printf("\n[LOG] Redirecting to Employee Menu...\n\n");
                empl_menu();
                break;

            case 3:
                printf("\n[LOG] Redirecting to Customer Menu...\n\n");
                cust_menu();
                break;

            case 4:
                printf("\n============================================\n");
                printf("   Thank you for using the Hotel Management System!\n");
                printf("   Have a great day! Goodbye!\n");
                printf("============================================\n\n");
                return 0;

            default:
                printf("\n[ERROR] Unexpected error occurred. Please try again.\n");
        }
    }
}

void adm_menu() {
    int choice;
    printf("===============================================\n");
    printf("\tYou selected: Hotel Administrator\n");
    printf("===============================================\n");
    printf("\n1. Register\n");
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
            register_Hotel_Administrator();
            break;
        case 2:
            login_Hotel_Administrator();
            break;
        case 3:
            MainMenu();
            break;
    }
}

void admin_dashboard() {
    int choice;
    while (1) {
        printf("1. Record Accommodation Information\n");
        printf("2. View Customer Information\n");
        printf("3. Logout\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        while (!(choice>=1 && choice<=3)) {
            printf("Invalid choice, please try again (must be between 1 and 3): ");
            scanf("%d", &choice);
        }
        switch (choice) {
            case 1:
                record_accommodation();
                break;
            case 2:
                view_customer_info();
                break;
            case 3:
                MainMenu();
                return;
        }
    }
}

void empl_menu() {
    int choice; // Variable to store the user's menu choice.

    while (1) { // Infinite loop to keep the menu running until the user exits.
        // Display a user-friendly menu layout
        printf("\n===============================================\n");
        printf("             === Employee Management ===        \n");
        printf("===============================================\n");
        printf("1. Register Employee\n"); // Option to register a new employee.
        printf("2. Employee Login\n");    // Option to log in as an employee.
        printf("3. Exit\n");             // Option to exit to the main menu.
        printf("Enter your choice: ");

        // Read the user's input and validate it.
        if (scanf("%d", &choice) != 1) {
            // If the input is not a number, clear the input buffer.
            while (getchar() != '\n');
            printf("\nInvalid input. Please enter a number.\n");
            continue; // Restart the loop to prompt the user again.
        }
        getchar(); // Clear any extra newline character left in the input buffer.

        // Process the user's menu choice using a switch-case structure.
        switch (choice) {
            case 1:
                // Register a new employee by calling the corresponding function.
                registerEmployee();
                break;
            case 2:
                // Attempt to log in and navigate to the employee page upon success.
                if (loginEmployee()) {
                    employee_Page(); // Open the employee-specific interface.
                } else {
                    // Inform the user if login fails.
                    printf("\nLogin failed. Please try again.\n");
                }
                break;
            case 3:
                // Exit the menu and return control to the main program.
                printf("\nReturning to Main Menu...\n");
                return; // Exit the loop and end the function.
            default:
                // Handle invalid menu choices gracefully.
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

// Helper function to check if a string contains only letters
int is_alpha_string(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0; // Non-letter character found
        }
        str++;
    }
    return 1; // All characters are letters
}

void register_Hotel_Administrator() {
    if (userCount >= MAX_USERS) {
        printf("\nUser limit reached. Cannot register more administrators.\n");
        MainMenu();
        return;
    }

    User newUser;

    printf("\n=== Register Hotel Administrator ===\n");

    while (getchar() != '\n'); // Clear the input buffer

    // Name validation
    do {
        printf("Enter your name: ");
        fgets(newUser.name, sizeof(newUser.name), stdin);
        newUser.name[strcspn(newUser.name, "\n")] = '\0'; // Remove newline character

        if (!is_alpha_string(newUser.name)) {
            printf("Invalid name. Please enter a name with letters only.\n");
        }
    } while (!is_alpha_string(newUser.name));

    // Email validation
    do {
        printf("Enter your email address: ");
        fgets(newUser.contact, sizeof(newUser.contact), stdin);
        newUser.contact[strcspn(newUser.contact, "\n")] = '\0';

        if (!ValidateEmail(newUser.contact)) {
            printf("\nInvalid email. Please enter a valid email address.\n");
        }
    } while (!ValidateEmail(newUser.contact));

    printf("Enter a username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0';

    // Password validation
    do {
        printf("Enter a password (at least 8 characters, including uppercase letters and digits): ");
        fgets(newUser.password, sizeof(newUser.password), stdin);
        newUser.password[strcspn(newUser.password, "\n")] = '\0';

        if (!validatePassword(newUser.password)) {
            printf("\nInvalid password. Please follow the password requirements.\n");
        }
    } while (!validatePassword(newUser.password));

    strcpy(newUser.role, "Hotel Administrator");
    users[userCount++] = newUser;

    // Save the new user to HotelAdmin.dat
    FILE *file = fopen("HotelAdmin.dat", "ab");
    if (file == NULL) {
        printf("Error opening file to save hotel administrator data!\n");
        MainMenu();
        return;
    }
    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);

    printf("\n--> Hotel Administrator registered successfully!\n");

    MainMenu();
}

int ValidateEmail(const char *email) {
    int count_at = 0; // To count the occurrence of '@'
    int count_dot = 0; // To check if '.' exists after '@'
    int length = strlen(email);

    if (length < 5) {
        printf("Email must be at least 5 characters long.\n");
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {
            count_at++;
        }
        if (count_at > 0 && email[i] == '.') {
            count_dot++;
        }
    }

    if (count_at != 1 || count_dot == 0) {
        printf("Email must contain one '@' and at least one '.' after '@'.\n");
        return 0;
    }

    return 1;
}

void login_Hotel_Administrator() {
    char username[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];

    printf("\n=== Hotel Administrator Login ===\n");

    while (getchar() != '\n');

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    // Open the HotelAdmin.dat file for reading
    FILE *file = fopen("HotelAdmin.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        MainMenu();
        return;
    }
    User storedUser;
    int loginSuccessful = 0;
    // Read user data from the file and validate credentials
    while (fread(&storedUser, sizeof(User), 1, file) == 1) {
        if (strcmp(storedUser.username, username) == 0 && strcmp(storedUser.password, password) == 0) {
            if (strcmp(storedUser.role, "Hotel Administrator") == 0) {
                printf("==============================\n");
                printf("\n\tLogin successful. Welcome, %s!\n\n", storedUser.name);
                printf("==============================\n");
                admin_dashboard();
                loginSuccessful = 1;
                break;
            } else {
                printf("\n--> Access denied. Only Hotel Administrators are allowed to log in.\n");
                break;
            }
        }
    }
    fclose(file);
    if (!loginSuccessful) {
        printf("\n--> Invalid username or password. Please try again.\n");
    }
    MainMenu();
}
void record_accommodation() {
    printf("\t\t\t*** Record Accommodation Info ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    Accommodation new_accommodation;

    // Input accommodation details with validation
    printf("Enter Accommodation ID: ");
    while (scanf("%d", &new_accommodation.accommodationID) != 1 || new_accommodation.accommodationID <= 0) {
        printf("Invalid input. Please enter a positive integer for ID: ");
        while (getchar() != '\n'); // Clear invalid input
    }

    printf("Enter Accommodation Type (max 49 characters): ");
    scanf("%49s", new_accommodation.type);

    printf("Enter Description (max 99 characters): ");
    scanf(" %99[^\n]", new_accommodation.description);

    printf("Enter Price per Night: ");
    while (scanf("%f", &new_accommodation.price) != 1 || new_accommodation.price <= 0.0) {
        printf("Invalid input. Please enter a positive price: ");
        while (getchar() != '\n'); // Clear invalid input
    }

    new_accommodation.Available = 1; // The new accommodation is available by default

    // Open the binary file to store info
    FILE *file = fopen("accommodations.dat", "ab");
    if (file == NULL) {
        perror("Error opening file to save accommodation data");
        return;
    }

    // Write the new accommodation to the file
    size_t written = fwrite(&new_accommodation, sizeof(Accommodation), 1, file);
    if (written != 1) {
        perror("Error writing accommodation data to file");
    } else {
        printf("--> Accommodation recorded successfully!\n");
        printf("----------------------------------------------------\n\n");
    }

    // Close the file
    fclose(file);
}

void view_customer_info() {
    printf("\n\t\t\t*** View Customer Info ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    Customer existing_customer;
    FILE *file = fopen("customers.dat","rb");
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

// Password validation: checks length, uppercase, and digit
int validatePassword_Employee(const char *password) {
    int hasUpper = 0, hasDigit = 0;

    if (strlen(password) < 8) return 0;

    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) hasUpper = 1;
        if (isdigit(password[i])) hasDigit = 1;
    }

    return hasUpper && hasDigit;
}

// Validate phone number (digits only, length 10-15)
int validatePhoneNumber_Employee(const char *phoneNumber) {
    int length = strlen(phoneNumber);
    if (length < 10 || length > 15) return 0;

    for (int i = 0; i < length; i++) {
        if (!isdigit(phoneNumber[i])) return 0;
    }

    return 1;
}

// Validate email format
int validateEmail_Employee(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    return at && dot && at < dot && strlen(dot) > 1;
}

// Generate an access code based on the department and employee ID
void generateAccessCode(char *accessCode, const char *department, int id) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    snprintf(accessCode, MAX_ACCESS_CODE_LENGTH, "%.3s-%04d-", department, id);

    size_t len = strlen(accessCode);
    for (int i = 0; i < 3 && len + i < MAX_ACCESS_CODE_LENGTH - 1; i++) {
        accessCode[len + i] = charset[rand() % (sizeof(charset) - 1)];
    }
    accessCode[len + 3] = '\0';
}

// Register a new employee
void registerEmployee() {
    if (employeeCount >= MAX_USERS) {
        printf("\nEmployee limit reached. Cannot register more employees.\n");
        return;
    }

    Employee newEmployee;
    printf("\n===============================================\n");
    printf("         === Register a New Employee ===        \n");
    printf("===============================================\n");

    // Name
    do {
        printf("Enter name: ");
        fgets(newEmployee.name_E, MAX_NAME_LENGTH, stdin);
        newEmployee.name_E[strcspn(newEmployee.name_E, "\n")] = '\0';

        if (!validateName_Employee(newEmployee.name_E)) {
            printf("\n[Error] Invalid name. Please enter a valid name (Real name, only letters, spaces, and hyphens are allowed).\n");
        }
    } while (!validateName_Employee(newEmployee.name_E));

    // Phone number
    do {
        printf("Enter phone number (10-15 digits): ");
        fgets(newEmployee.phoneNumber_E, MAX_CONTACT_LENGTH, stdin);
        newEmployee.phoneNumber_E[strcspn(newEmployee.phoneNumber_E, "\n")] = '\0';

        if (!validatePhoneNumber_Employee(newEmployee.phoneNumber_E)) {
            printf("\n[Error] Invalid phone number. Please enter a valid phone number with 10-15 digits.\n");
        }
    } while (!validatePhoneNumber_Employee(newEmployee.phoneNumber_E));

    // Email
    do {
        printf("Enter email: ");
        fgets(newEmployee.email_E, MAX_CONTACT_LENGTH, stdin);
        newEmployee.email_E[strcspn(newEmployee.email_E, "\n")] = '\0';

        if (!validateEmail_Employee(newEmployee.email_E)) {
            printf("\n[Error] Invalid email format. Please enter a valid email address.\n");
        }
    } while (!validateEmail_Employee(newEmployee.email_E));

    // Department
    printf("\nSelect Department:\n");
    printf("1. Human Resources\n");
    printf("2. IT\n");
    printf("3. Finance\n");
    printf("4. Marketing\n");
    printf("5. Sales\n");
    printf("Enter your choice (1-5): ");

    int departmentChoice;
    scanf("%d", &departmentChoice);
   getchar(); // Clear buffer

    const char *departments[] = {"Human Resources", "IT", "Finance", "Marketing", "Sales"};
    if (departmentChoice < 1 || departmentChoice > 5) {
        printf("\n[Error] Invalid department choice. Defaulting to General.\n");
        strcpy(newEmployee.department_E, "General");
    } else {
        strcpy(newEmployee.department_E, departments[departmentChoice - 1]);
    }

    // Username
    int usernameExists;
    do {
        printf("Enter username: ");
        fgets(newEmployee.username_E, MAX_USERNAME_LENGTH, stdin);
        newEmployee.username_E[strcspn(newEmployee.username_E, "\n")] = '\0';

        // Check for unique username
        usernameExists = 0;
        for (int i = 0; i < employeeCount; i++) {
            if (strcmp(employees[i].username_E, newEmployee.username_E) == 0) {
                usernameExists = 1;
                break;
            }
        }
        if (usernameExists) {
            printf("\n[Error] Username already exists. Please choose a different username.\n");
        }
    } while (strlen(newEmployee.username_E) == 0 || usernameExists);

    // Password
    do {
        printf("Enter password (at least 8 characters, including uppercase letters and digits): ");
        fgets(newEmployee.password_E, MAX_PASSWORD_LENGTH, stdin);
        newEmployee.password_E[strcspn(newEmployee.password_E, "\n")] = '\0';

        if (!validatePassword_Employee(newEmployee.password_E)) {
            printf("\n[Error] Invalid password. Please follow the password requirements.\n");
        }
    } while (!validatePassword_Employee(newEmployee.password_E));

    // Generate Access Code
    generateAccessCode(newEmployee.accessCode_E, newEmployee.department_E, employeeCount + 1);

    // Store employee
    employees[employeeCount] = newEmployee;
    employeeCount++;

    printf("\n[Success] Employee registered successfully!\n");
    printf("Your Access Code: %s\n", newEmployee.accessCode_E);
    printf("Department: %s\n", newEmployee.department_E);
    printf("Press Enter to continue to the main menu.\n");
    getchar();

    // Save employees to file after registration
    save_employees();
}

int validateName_Employee(const char *name) {
    // Check if the name is empty
    if (strlen(name) == 0) {
        return 0; // Invalid: empty name
    }

    // Check if the name exceeds the maximum length
    if (strlen(name) > MAX_NAME_LENGTH) {
        return 0; // Invalid: name too long
    }

    // Check for valid characters (only letters, spaces, hyphens, and apostrophes)
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '-' && name[i] != '\'') {
            return 0; // Invalid: contains non-alphabetic characters
        }
    }

    // Check for minimum length (optional)
    if (strlen(name) < 2) {
        return 0; // Invalid: name too short
    }

    return 1; // Valid name
}
// Function to save employees to a binary file
void save_employees() {
    FILE *file = fopen("employees.dat", "wb");
    if (file == NULL) {
        printf("Error opening file to save employee data!\n");
        return;
    }
    fwrite(employees, sizeof(Employee), employeeCount, file);
    fclose(file);
    printf("\n[Success] Employee data saved successfully!\n");
}

// Employee login
int loginEmployee() {
    char accessCode[MAX_ACCESS_CODE_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\n===============================================\n");
    printf("             === Employee Login ===             \n");
    printf("===============================================\n");

    // Access Code
    printf("Enter access code: ");
    fgets(accessCode, MAX_ACCESS_CODE_LENGTH, stdin);
    accessCode[strcspn(accessCode, "\n")] = '\0';

    // Username
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    // Password
    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    // Validation
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].accessCode_E, accessCode) == 0 &&
            strcmp(employees[i].username_E, username) == 0 &&
            strcmp(employees[i].password_E, password) == 0) {
            printf("\n[Success] Login successful! Welcome, %s (%s Department).\n", employees[i].name_E, employees[i].department_E);
            return 1;
        }
    }

    printf("\n[Error] Invalid login credentials. Please try again.\n");
    return 0;
}



void employee_Page() {
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("           Welcome to Employee Page       \n");
        printf("========================================\n\n");

        // Display menu options
        printf("What would you like to do?\n\n");
        printf("1. View List of Customers\n");
        printf("2. View List of Accommodations\n");
        printf("3. Logout\n\n");
        printf("Please enter your choice (1-3): ");

        // Input validation for choice
        while (1) {
            if (scanf("%d", &choice) != 1) {
                printf("\nInvalid input. Please enter a valid number: ");
                while (getchar() != '\n'); // Clear invalid input
            } else if (choice < 1 || choice > 3) {
                printf("\nInvalid choice. Please select a valid option (1-3): ");
            } else {
                break; // Valid input
            }
        }
        getchar(); // Consume newline

        printf("\n[LOG] User selected option %d\n", choice);

        // Handle user choice
        switch (choice) {
            case 1:
                printf("\n========================================\n");
                printf("        Redirecting to Customer List      \n");
                printf("========================================\n\n");
                viewCustomerList();
                break;

            case 2:
                printf("\n========================================\n");
                printf("     Redirecting to Accommodation List   \n");
                printf("========================================\n\n");
                viewAccommodation();
                break;

            case 3:
                printf("\n========================================\n");
                printf("       Logging out... Please wait        \n");
                printf("========================================\n\n");
                return; // Exit the loop and end the function.

            default:
                printf("\nUnexpected error. Please try again.\n");
        }
    }
}

// Function to load customers from the binary file
void load_customers() {
    FILE *file = fopen("customers.dat", "rb");
    if (file == NULL) {
        printf("Error opening file to read customer data!\n");
        customerCount = 0; // Reset count if file cannot be opened
        return;
    }

    customerCount = 0; // Reset count before loading
    while (fread(&customers[customerCount], sizeof(Customer), 1, file) == 1) {
        customerCount++;
    }

    fclose(file);
}
void viewCustomerList() {
    // Load customers from file
    load_customers();

    while (1) {
        printf("\n=============================");
        printf("\n       Customer Viewer       ");
        printf("\n=============================\n\n");

        int found = 0; // Flag to check if customers exist

        // Check if there are customers
        if (customerCount == 0) {
            printf("No customers found.\n\n");
        } else {
            printf("--- List of Customers ---\n\n");

            // Iterate through customers and display their details
            for (int i = 0; i < customerCount; i++) {
                found = 1;
                printf("[Customer %d]\n", i + 1);
                printf("----------------------------------\n");
                printf("Name            : %s %s\n", customers[i].first_name, customers[i].last_name);
                printf("Birthday        : %s\n", customers[i].birthday); // Display birthday
                printf("Email           : %s\n", customers[i].email);
                printf("Passport Number : %s\n", customers[i].passport_num); // Display passport number
                printf("Contact         : %s\n", customers[i].phone_num);
                printf("Address         : %s\n", customers[i].address); // Display address
                // Password is typically not displayed for security reasons
                printf("----------------------------------\n\n");
            }
        }

        // Display options after viewing
        printf("========================================\n");
        printf("Options:\n");
        printf("1. Return to Employee Page\n");
        printf("2. Refresh Customer List\n");
        printf("\nEnter your choice: ");

        int choice;

        // Input validation for choice
        while (1) {
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input. Please enter a number: ");
                while (getchar() != '\n'); // Clear invalid input
            } else if (choice < 1 || choice > 2) {
                printf("Invalid choice. Please select a valid option (1 or 2): ");
            } else {
                break; // Valid input
            }
        }
        getchar(); // Consume newline

        printf("\n[LOG] User selected option %d\n", choice);

        // Handle user choice
        if (choice == 1) {
            printf("\n[LOG] Returning to Employee Page\n");
            return;
        } else if (choice == 2) {
            printf("\n[LOG] Refreshing customer list...\n\n");
            load_customers(); // Reload customers from file
            continue;
        }
    }
}
void load_accommodations() {
    FILE *file = fopen("accommodations.dat", "rb");
    if (file == NULL) {
        perror("Error opening file to read accommodation data");
        accommodationCount = 0; // Reset count if file cannot be opened
        return;
    }

    accommodationCount = 0; // Reset count before loading
    while (fread(&accommodations[accommodationCount], sizeof(Accommodation), 1, file) == 1) {
        accommodationCount++;
        if (accommodationCount >= MAX_ACCOMMODATIONS) {
            printf("Warning: Maximum number of accommodations reached. Some records may not be loaded.\n");
            break;
        }
    }

    if (ferror(file)) {
        perror("Error reading accommodation data from file");
    }

    fclose(file);

    // Debug log
    printf("[DEBUG] Loaded %d accommodations from file.\n", accommodationCount);
}
void viewAccommodation() {
    load_accommodations();

    while (1) {
        printf("\n=============================\n");
        printf("     Accommodation List    \n");
        printf("=============================\n\n");

        if (accommodationCount == 0) {
            printf("\nNo accommodations available at the moment.\n");
        } else {
            printf("\n--- List of Available Accommodations ---\n\n");
            for (int i = 0; i < accommodationCount; i++) {
                printf("[Accommodation %d]\n", i + 1);
                printf("----------------------------------\n");
                printf("ID         : %d\n", accommodations[i].accommodationID);
                printf("Type       : %s\n", accommodations[i].type);
                printf("Description: %s\n", accommodations[i].description);
                printf("Price      : $%.2f\n", accommodations[i].price);
                printf("Status     : %s\n", accommodations[i].Available ? "Available" : "Booked");
                printf("----------------------------------\n\n");
            }
        }

        printf("\nOptions:\n");
        printf("1. Return to Employee Page\n");
        printf("2. Refresh Accommodation List\n");
        printf("\nEnter your choice: ");

        int choice;
        while (1) {
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input. Please enter 1 or 2: ");
                while (getchar() != '\n'); // Clear invalid input
            } else if (choice < 1 || choice > 2) {
                printf("Invalid choice. Please select a valid option (1 or 2): ");
            } else {
                break;
            }
        }
        getchar(); // Consume newline

        if (choice == 1) {
            return; // Exit the function
        } else if (choice == 2) {
            printf("\n[LOG] Refreshing accommodation list...\n");
            load_accommodations();
        }
    }
}
void debug_print_accommodations() {
    printf("\n[DEBUG] Current Accommodations:\n");
    for (int i = 0; i < accommodationCount; i++) {
        printf("[Accommodation %d]\n", i + 1);
        printf("ID         : %d\n", accommodations[i].accommodationID);
        printf("Type       : %s\n", accommodations[i].type);
        printf("Description: %s\n", accommodations[i].description);
        printf("Price      : $%.2f\n", accommodations[i].price);
        printf("Status     : %s\n", accommodations[i].Available ? "Available" : "Booked");
        printf("----------------------------------\n");
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
    while (numeric(new_customer.phone_num) == 0 || strlen(new_customer.phone_num) < 10 || strlen(new_customer.phone_num) > 11 || new_customer.phone_num[0] != '0') {
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
    customerCount++;
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
            viewAccommodation();
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
             printf("Total Nights: %d\n", booking.totalNights);

            // Retrieve accommodation details
            Accommodation accommodation;
            if (!doesAccommodationExist("accommodations.dat", booking.accommodationID)) {
                printf("Accommodation details not found.\n");
                fclose(file);
                return;
            }

            FILE *acc_file = fopen("accommodations.dat", "rb");
            while (fread(&accommodation, sizeof(Accommodation), 1, acc_file) == 1) {
                if (accommodation.accommodationID == booking.accommodationID) {
                    double total_price = booking.totalNights * accommodation.price;
                    printf("Total Amount: $%.2f\n", total_price);
                    fclose(acc_file);
                    break;
                }
            }
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
  // Function to check if an accommodation ID exists in the binary file
int doesAccommodationExist(const char *filename, int accommodationID) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file to check accommodation data!\n");
        return 0;
    }

    Accommodation temp;
    while (fread(&temp, sizeof(Accommodation), 1, file)) {
        if (temp.accommodationID == accommodationID) {
            fclose(file);
            return 1; // ID exists
        }
    }

    fclose(file);
    return 0; // ID does not exist
}
 // Booking function 
 // Booking function 
void booking() {
    char customer_name[50];
    printf("\nEnter Booking Details:\n");
    printf("Customer Name (First Last): ");
    scanf(" %[^\n]s", customer_name);

    // Check if the customer is registered
    if (!is_customer_registered(customer_name)) {
        int choice;
        printf("Customer is not registered. Please register before booking.\n");
        printf("1. Customer menu\n");
        printf("2. Main menu\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (!(choice >= 1 && choice <= 3)) {
            printf("Invalid choice, please try again (must be between 1 and 3): ");
            scanf("%d", &choice);
        }
        switch (choice) {
            case 1:
                cust_menu();
                return;
            case 2:
                MainMenu();
                return;
            case 3:
                printf("\nThank you, bye!\n");
                return;
        }
    }

    // Proceed with booking if the customer is registered
    struct Booking new_booking;
    new_booking.bookingID = generate_unique_booking_id();
    strcpy(new_booking.customerName, customer_name);

    do {
        printf("\nEnter Accommodation ID: ");
        scanf("%d", &new_booking.accommodationID);

        if (!doesAccommodationExist("accommodations.dat", new_booking.accommodationID)) {
            printf("Accommodation ID does not exist. Please re-enter.\n");
        }
    } while (!doesAccommodationExist("accommodations.dat", new_booking.accommodationID));

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
    }
    // Calculate total nights and check availability
    int totalNights = 0;
    char current_date[15], next_date[15];
    strcpy(current_date, new_booking.checkInDate);
    // Loop to calculate total nights and check availability
    while (compare_dates(current_date, new_booking.checkOutDate) < 0) {
        if (is_date_reserved(new_booking.accommodationID, current_date)) {
            printf("Sorry, the date %s is already reserved.\n", current_date);
            return;
        }
        totalNights++; // Increment total nights
        get_next_date(current_date, next_date); // Get the next date
        strcpy(current_date, next_date); // Update the current date
    }
    new_booking.totalNights = totalNights; // Store total nights

    // Add all dates to the reservations
    strcpy(current_date, new_booking.checkInDate);
    while (compare_dates(current_date, new_booking.checkOutDate) < 0) {
        add_reservation(new_booking.accommodationID, current_date);
        get_next_date(current_date, next_date);
        strcpy(current_date, next_date);
    }

    // Save the booking
    FILE *file = fopen("bookings.dat", "ab");
    if (!file) {
        printf("Error opening file to save booking data!\n");
        return;
    }

    fwrite(&new_booking, sizeof(struct Booking), 1, file);
    fclose(file);

    printf("Booking saved successfully! Your Booking ID is: %d\n", new_booking.bookingID);
    printf("Total Nights: %d\n", new_booking.totalNights);

    cust_menu();
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
        while (!(choice >= 1 && choice <= 4)) {
        printf("Invalid choice, please try again (must be between 1 and 5): ");
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
}}
