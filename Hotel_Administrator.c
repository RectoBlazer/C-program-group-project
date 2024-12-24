#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//def accommodation structure
typedef struct {
    int accommodationID;
    char type[30];
    char description[100];
    double price;
    int Available;
} Accommodation;

//record accommodation info
void record_accommodation(){
    printf("\t\t\t*** Record Accommodation Info ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    Accommodation new_accommodation;

    printf("Enter Accommodation ID: ");
    scanf("%d",&new_accommodation.accommodationID);

    printf("Enter Accommodation Type: ");
    scanf("%s",new_accommodation.type);

    printf("Enter Description: ");
    scanf(" %[^\n]s",new_accommodation.description);

    printf("Enter Price per Night: ");
    scanf("%lf",&new_accommodation.price);

    new_accommodation.Available=1; //the new accommodation exist by default

    //open the binary file to store info
    FILE*file =fopen("accommodations.dat","ab");
    if (file==NULL) {
        printf("Error opening file to save accommodation data!\n");
        return;
    }

    //write new accommodation  to binary file
    fwrite(&new_accommodation,sizeof(Accommodation),1,file);
    fclose(file);

    printf("Accommodation data saved successfully!\n");
}

//view customer info
void view_customer_info() {
    printf("\t\t\t*** View Customer Info ***\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    
    Customer existing_customer;
    FILE*file=fopen("customers.dat","rb");
    if(!file){
        printf("Error opening file!\n");
        return;
    }

    while (fread(&existing_customer,sizeof(Customer), 1, file)== 1){
        printf("First Name: %s\n",existing_customer.first_name);
        printf("Last Name: %s\n",existing_customer.last_name);
        printf("Birthday: %s\n",existing_customer.birthday);
        printf("Email: %s\n",existing_customer.email);
        printf("Passport Number: %s\n",existing_customer.passport_num);
        printf("Phone Number: %s\n",existing_customer.phone_num);
        printf("Address: %s\n",existing_customer.address);
        printf("----------------------------------------------------\n");
    }


    fclose(file);
}

int adm_menu(){
    int choice;
    printf("You selected: Hotel Administrator\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Record Accommodation Information\n");
    printf("4. View Customer Information\n");
    printf("5. Back to main menu\n");
    printf("Please enter your choice: ");
    scanf("%d",&choice);
    while (!(choice>=1 && choice<=5)) {
        printf("Invalid choice, please try again(must be between 1 and 5): ");
        scanf("%d",&choice);
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

int main(){
    int choice;
    MainMenu();
    scanf("%d",&choice);
    while (!(choice>=1 && choice<=4)){
        printf("Invalid choice, please try again(must be between 1 and 4): ");
        scanf("%d",&choice);
    }
    switch (choice){
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