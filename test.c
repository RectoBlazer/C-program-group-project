#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define D_FIRST_NAME 15
#define D_LAST_NAME 15
#define D_BIRTHDAY 12
#define D_EMAIL 40
#define D_PASSPORT_NUM 10
#define D_PHONE_NUM 11
#define D_ADDRESS 100
#define D_PASSWORD 25

// Define customer structure
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


//registering a customer
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
    while (check_email(new_customer.email) == 0 || exist_email(new_customer.email)==1) {
        if(check_email(new_customer.email) == 0){
            printf("Invalid email, please enter your email again: ");
            scanf("%s", new_customer.email);
        }
        else if(exist_email(new_customer.email)==1){
            printf("Email already used, please enter your email again: ");
            scanf("%s", new_customer.email);
        }
    }

    // Passport number
    printf("Please enter your passport number: ");
    scanf("%s", new_customer.passport_num);
    while (check_passport(new_customer.passport_num)==0 || exist_passport(new_customer.passport_num)==1 ) {
        if(check_passport(new_customer.passport_num)==0){
            printf("Invalid passport number, please enter your passport number again: ");
            scanf("%s", new_customer.passport_num);
        }
        else if (exist_passport(new_customer.passport_num)==1){
            printf("Passport already used, please enter your passport number again: ");
            scanf("%s", new_customer.passport_num);
        }
    }

    // Phone number
    printf("Please enter your phone number: ");
    scanf("%s", new_customer.phone_num);
    while (numeric(new_customer.phone_num) == 0 || strlen(new_customer.phone_num) < 10 || strlen(new_customer.phone_num) > 11 || new_customer.phone_num[0] != '0' || new_customer.phone_num[1] != '1') {
        printf("Invalid phone number, please enter your phone number again: ");
        scanf("%s", new_customer.phone_num);
    }

    // Address
    printf("Please enter your address: ");
    scanf(" %[^\n]s", new_customer.address);

    //password
    printf("Please enter password (it must be at least 8 characters, and contain letters, numbers and at least one special character): ");
    scanf(" %[^\n]s",new_customer.password);
    while(check_password(new_customer.password)==0 || strlen(new_customer.password)<8){
        printf("Invalid password, pleaser enter your password again: ");
        scanf(" %[^\n]s",new_customer.password);
    }

    char password_2[40];
    printf("Please re-enter password: ");
    scanf(" %[^\n]s",&password_2);
    while(strcmp(password_2,new_customer.password)!=0){
        printf("Incorrect password, Please enter again: ");
        scanf(" %[^\n]s",&password_2);
    }

    // Opening the binary file to store the informations
    FILE *file = fopen("customers.dat", "ab");
    if (file == NULL) {
        printf("Error opening file to save customer data!\n");
        return;}

    // Writing the new customer data to the binary file
    fwrite(&new_customer, sizeof(Customer), 1, file);
    fclose(file);

    printf("Customer data saved successfully!\n");
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

int login_customer(){
    printf("\t\t\t*** login customer ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    char email[40], password[25];
    printf("Please enter your email: ");
    scanf("%s",&email);
    while (exist_email(email)==0){
        printf("This email does not exist, Please enter your email again: ");
        scanf("%s",&email);
    }
    printf("Please enter your password: ");
    scanf(" %[^\n]s",&password);
    while (correct_password(email,password)==0){
        printf("Incorrect password, Please enter your password again: ");
        scanf("%s",&password);
    }
    printf("~~~~~~~~~~~~~~ login successful ! ~~~~~~~~~~~~~~\n");
    int choice;
    printf("1. View list and information of Accommodation\n");
    printf("2. Booking\n");
    printf("3. Bill information\n");
    printf("4. back to main menu\n");
    printf("Please select a number between 1 and 4: ");
    scanf("%d", &choice);
    while(!(choice>=1 && choice<=4)){
         printf("Invalid choice, please try again(must be between 1 and 4): ");
        scanf("%d",&choice);}
    switch (choice){
    case 1:
    //view_list_information_accommodation();
    break;
    case 2:
    //booking();
    break;
    case 3:
    //bill_information();
    break;
    case 4:
    return 0;
    }
}

//main menu
int main(){
    int choice1, choice2;
    while(1){
        printf("\t\t\t*** Welcome to the Hotel Management System! ***\n");
        printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Please select your role:\n");
        printf("1. Hotel Administrator\n");
        printf("2. Employee\n");
        printf("3. Customer\n");
        printf("4. Exit\n");
        printf("Please select a number between 1 and 4: ");
        scanf("%d", &choice1);
        while(!(choice1>=1 && choice1<=4)){
            printf("Invalid choice, please try again(must be between 1 and 4): ");
            scanf("%d",&choice1);
        }
         switch (choice1) {
                case 1:
                printf("You selected: Hotel Administrator\n");
                printf("1. Register\n");
                printf("2. Login\n");
                printf("3. Back to main menu\n");
                printf("Please enter your choice: :");
                scanf("%d", &choice2);
                while(!(choice2>=1 && choice2<=3)){
                printf("Invalid choice, please try again(must be between 1 and 3): ");
                scanf("%d",&choice2);}
                switch (choice2)
                {
                    case 1:
                    //register_Hotel_Administrator();
                    break;
                    case 2:
                    //login_Hotel_Administrator();
                    break;
                    case 3:
                    break;
                }
                break;
                case 2:
                printf("========== Employee Menu ==========\n");
                printf("1. Register\n");
                printf("2. Login\n");
                printf("3. Back to main menu.\n");
                printf("Please enter your choice: ");
                scanf("%d", &choice2);
                while(!(choice2>=1 && choice2<=3)){
                printf("Invalid choice, please try again(must be between 1 and 3): ");
                scanf("%d",&choice2);}
                switch (choice2) {
                    case 1:
                        printf("\nYou selected: Register\n");
                        // register_employee();
                        break;
                    case 2:
                        printf("\nYou selected: Login\n");
                        // Call the function to log in as an employee
                        // login_employee();
                        break;
                    case 3:
                        printf("\nReturning to the Main Menu..\n");
                        break;
                }
               break;
               case 3:
               printf("You selected: Customer\n");
                printf("1. Register\n");
                printf("2. Login\n");
                printf("3. Back to main menu\n");
                printf("Please enter your choice: :");
                scanf("%d", &choice2);
                while(!(choice2>=1 && choice2<=3)){
                printf("Invalid choice, please try again(must be between 1 and 3): ");
                scanf("%d",&choice2);}
                switch (choice2)
                {
                    case 1:
                    register_customer();
                    break;
                    case 2:
                    login_customer();
                    break;
                    case 3:
                    break;
                }
               break;
               case 4:
               printf("Exiting the system. Goodbye!\n");
               return 0;
        }
    }
}
