#include <iostream> //declares objects that control reading from and writing to the standard streams
#include <fstream> //library provides functions for files
#include <string>
#include <iomanip> // used to manage input and output formatting
#include <cstdlib> //including memory allocation, random number generation, and other standard library


using namespace std;

//functions
void login();
void login1();
void login2();
void logout();
void addBitem();
void addBitemCashier();
void delBitem();
void upBitem();
void itemD();
void itemDcashier();
void itemDcustomer();
void addsales();
void addsalescashier();
void viewsales();
void sub();
void sub1();
void sub2();
void Cdetail();
void Cdetailcashier();
void Cdetailscustomer();
void exit();
void choiceMCC();



int main() 
{
    cout << "\t\t************AMBER'S BAKERY SYSTEM************\n";

    choiceMCC();
    system("pause");
    return 0;
}

// Function to choose the user type (Manager, Cashier, Customer)
void choiceMCC()
{
    string choiceStr;


    cout << "\nManager    (Press 1)";
    cout << "\nCashier    (Press 2)";
    cout << "\nCustomer   (Press 3)";
    cout << "\n\nPress 4 to Exit";

    cout << "\n\nEnter User Choice :";
    
    cin >> choiceStr;

    if (choiceStr == "1") {
        system("CLS");
        login();
    } else if (choiceStr == "2") {
        // Call cashier options
        system("CLS");
        login1();
       
    } else if (choiceStr == "3") {
        // Call customer options
        system("CLS");
        login2();

    } else if (choiceStr == "4"){
        //Exit from the promt
        exit(0);
    
       
    } else {
        system("CLS");
        cout << "\nInvalid choice. Please select a valid option.\n";
        choiceMCC(); // Re-prompt for choice
    }
}

void login()
{
    cout << "\t\t************AMBER'S BAKERY SYSTEM************\n";
    cout << "\n\nManager";

    ifstream credentialsFile("credentials.txt");
    if (!credentialsFile.is_open()) {
        cout << "Error opening credentials file\n";
        return; // Exit the function if the file cannot be opened
    }

    string enteredUsername, enteredPassword;
    bool loginSuccessful = false;

    cout << "\n\nEnter username: ";
    cin >> enteredUsername;
    cout << "Enter password: ";
    cin >> enteredPassword;

    string line;
    while (getline(credentialsFile, line)) {
        // Split the line into username and password
        stringstream ss(line);
        string correctUsername, correctPassword;
        ss >> correctUsername >> correctPassword;

        if (enteredUsername == correctUsername && enteredPassword == correctPassword) {
            loginSuccessful = true;
            break;
        }
    }

    credentialsFile.close();

    if (loginSuccessful) {
        cout << "\n\nLOGIN SUCCESSFUL, THANK YOU\n";
        sub();
    } else {
        system("CLS");
        cout << "\n\nYOUR USERNAME OR PASSWORD IS INCORRECT, PLEASE TRY AGAIN\n\n";
        login();
    }
}

void sub()
{
    
    int userchoice;

    cout << "\n\t\tPress 1 to add new bakery items" << endl;
    cout << "\t\tPress 2 to delete bakery items" << endl;
    cout << "\t\tPress 3 to update bakery items" << endl;
    cout << "\t\tPress 4 to view bakery items" << endl;
    cout << "\t\tPress 5 to manage sales details" << endl;
    cout << "\t\tPress 6 to view sales details" << endl;
    cout << "\t\tPress 7 to Company Details" << endl;
    cout << "\t\tPress 8 to Log Out" << endl;
    cout << "\t\tPress 9 Exit" << endl << endl;
    
    
    cout<<"\t ENTER YOUR CHOICE....";
    cin>>userchoice;

    switch (userchoice) {
        case 1:
            addBitem();
            break;

        case 2:
            delBitem();
            break;

        case 3:
            upBitem();
            break;

        case 4:
            system("CLS");
            itemD();
            break;

        case 5:
            addsales();
            break;

        case 6:
            viewsales();
            break;

        case 7:
            Cdetail();
            break;

        case 8:
            system("CLS");
            logout();
            break;
  
        case 9:
            exit(0);

        
            
        default:
            cout << "\nInvalid choice. Please select a valid option.\n";
            sub(); // Re-prompt for choice
            break;
    }

    
}

void addBitem() 
{
    fstream bakerydata("BakeryData.txt", ios::out | ios::app); // Open the file in append mode
    string bName, bType, bNumber;
    int bQuantity = 0;
    char choice;
    cout << "\nEnter Name of the Bakery Item : ";
    cin.ignore(); // Clear the newline left in the input buffer
    getline(cin, bName);

    cout << "Enter Type of the Item (Bakery/Beverage): ";
    getline(cin, bType);

    cout << "Enter Bakery Item ID : ";
    getline(cin, bNumber);

    cout << "Enter quantity of the bakery item : ";
    cin >> bQuantity;

    bakerydata << bName << "  " << bType << "   " << bNumber << "   " << bQuantity << endl;
    bakerydata.close();

    cout << "Do you want to add new bakery items? (Y/N) : ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
        addBitem();
    else {
        system("CLS");
        cout << endl << endl << "**********AMBER'S BAKERY SYSTEM**********" << endl << endl;
        sub();
    }
}

void delBitem()
{
    {
    fstream bakerydata, update;
    string bName, bType, bNumber, choice;
    int bQuantity = 0;
    char choice2;
    bool delp = true;

    bakerydata.open("BakeryData.txt", ios::in);
    update.open("Update.txt", ios::out);

    cout << "\t Enter the Bakery Item Name to Delete : ";
    cin.ignore();
    getline(cin, choice);

    while (bakerydata >> bName >> bType >> bNumber >> bQuantity)
    {
        if (choice != bName)
        {
            update << bName << "  " << bType << "   " << bNumber << "   " << bQuantity << endl;
        }
        else
            delp = false;
    }

    if (delp == false)
        cout << "\t Bakery Item Deleted Successfully!";
    else
        cout << "\t Bakery Item Not Found!";

    bakerydata.close();
    update.close();

    bakerydata.open("BakeryData.txt", ios::out);
    update.open("Update.txt", ios::in);

    while (update >> bName >> bType >> bNumber >> bQuantity)
    {
        bakerydata << bName << "  " << bType << "   " << bNumber << "   " << bQuantity << endl;
    }

    bakerydata.close();
    update.close();

    cout << "\n\t Do you want to delete another bakery item? (Y/N) : ";
    cin >> choice2;

    if (choice2 == 'Y' || choice2 == 'y')
        delBitem();
    else
    {
        system("CLS");
        cout << "\t\t************AMBER'S BAKERY SYSTEM************\n";
        sub();
    }
}
}

void upBitem()
{
    fstream update, bakerydata;
    string bName, bType, bNumber, choice, text;
    char choice2;
    int bQuantity = 0;
    bool found = false;

    cout << "\t Enter the name of the bakery item to update : ";
    cin.ignore();
    getline(cin, choice);

    update.open("Update.txt", ios::out); // Open the updating file
    text = "";
    update << text;
    update.close();

    bakerydata.open("BakeryData.txt", ios::in); // Open the bakery data file
    update.open("Update.txt", ios::app);

    while (bakerydata >> bName >> bType >> bNumber >> bQuantity)
    {
        if (choice == bName)
        {
            found = true;
            cout << "\n\t Enter New Name : "; // New bakery item name
            getline(cin, bName);

            cout << "\t Enter New Type : "; // New type of the updated bakery item
            getline(cin, bType);

            cout << "\t Enter New bakery item number : ";
            getline(cin, bNumber);

            cout << "\t Enter New quantity : ";
            cin >> bQuantity;

            update << bName << "  " << bType << "  " << bNumber << "  " << bQuantity << endl;
            cout << "\n \t Successfully Bakery Item Updated!" << endl;
        }
        else
        {
            update << bName << "  " << bType << "  " << bNumber << "  " << bQuantity << endl;
        }
    }
    if (found == false)
        cout << "\n \t Bakery Item Not Found!" << endl;

    bakerydata.close();
    update.close();

    bakerydata.open("BakeryData.txt", ios::out);
    update.open("Update.txt", ios::in);

    while (update >> bName >> bType >> bNumber >> bQuantity)
    {
        bakerydata << bName << "  " << bType << "  " << bNumber << "  " << bQuantity << endl;
    }
    bakerydata.close();
    update.close();

    update.open("Update.txt", ios::out);
    text = "";
    update << text;
    update.close();

    cout << "\n\t Do you want to update another bakery item? (Y/N) : ";
    cin >> choice2;

    if (choice2 == 'Y' || choice2 == 'y')
        upBitem();
    else
    {
        system("CLS");
        cout << "\t\t************AMBER'S BAKERY SYSTEM************\n";
        sub();
    }
}


void itemD()
{
    ifstream bakerydata("BakeryData.txt");
    if (!bakerydata.is_open()) {
        cout << "Error opening BakeryData.txt\n";
        return; // Exit the function if file cannot be opened
    }

    cout << "\n\t************ Bakery Items ************\n";
    cout << "\nName\t\tType\t\tItem Number\tQuantity\n";
    cout << "-----------------------------------------------------------\n";

    string bName, bType, bNumber;
    int bQuantity;

    while (bakerydata >> bName >> bType >> bNumber >> bQuantity) {
        cout << setw(15) << left << bName << setw(15) << left << bType << setw(15) << left << bNumber << setw(10) << left << bQuantity << endl;
    }

    bakerydata.close();

    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get(); // Wait for user input before returning to the main menu

    system("CLS");
        cout << "\n\n\t\t************AMBER'S BAKERY SYSTEM************\n";
        sub();
}

void addsales()
{
    fstream salesdetials("sales.txt", ios::out | ios::app); // Open the file in append mode
    string name, type, itemnumber;
    int Quantity = 0;
    double price;
    char choice;
    
    cout << "\n\tEnter Item Name : ";
    cin.ignore(); // Clear the newline left in the input buffer
    getline(cin, name);

    cout << "\tEnter quantity sold : ";
    cin>> Quantity;

    cout << "\tEnter price per item : ";
    cin>> price;


    salesdetials << name << "  " << Quantity << "   " << price << "   "<< endl;
    salesdetials.close();

    cout << "\nSale recorded successfully.\n";
    cout << "\nDo you want to add new Sale? (Y/N) : ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
        addsales();
    else {
        system("CLS");
        cout << endl << endl << "**********AMBER'S BAKERY SYSTEM**********" << endl << endl;
        sub();
    }
}

void viewsales()
{
    ifstream salesdetials("sales.txt");
    if(!salesdetials.is_open())
    {
        cout<< "Error opening sales.txt\n";
        return; // exit the function if file cannot be opened
    }
    cout << "\n\t************ Sales Details ************\n";
    cout << "\nName\t\tQuantity\tPrice\n";
    cout << "---------------------------------------\n";

    string name, total;
    double price;
    int Quantity;

    

    while (salesdetials >> name >> Quantity >> price)
    {
        cout << setw(15) << left << name << setw(15) << left << Quantity << setw(15) << left << price << endl;

    }
    salesdetials.close();

    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get(); // Wait for user input before returning to the main menu

    system("CLS");
        cout << endl << endl << "**********AMBER'S BAKERY SYSTEM**********" << endl << endl;
        sub();
}

void Cdetail()
{   
    system("CLS");
    cout << "\n\t************ Company Details ************\n";

    cout << "\n\nCompany name : The Amber's Bakery";
    cout << "\nAddress : 49 Featherstone Street,London";
    cout << "\n\nContact Details";
    cout << "\n\nHotline : 081 32566##";
    cout << "\nEmail : amnersbakeryinfo@gmail.com";

    cout << "\n\nPress any key to continue...";
    cin.ignore();
    cin.get(); // Wait for user input before returning to the main menu

    system("CLS");
        cout << endl << endl << "**********AMBER'S BAKERY SYSTEM**********" << endl << endl;
        sub();
}

void logout()
{
    choiceMCC();
}



// cashier login process


void login1() 
{
    cout << "\t\t************AMBER'S BAKERY SYSTEM************\n";
    cout << "\n\nCashier"; //user choosed option

    ifstream loginfile1("cashierlogin.txt");
    if (!loginfile1.is_open()) {
        cout << "Error opening credentials file\n";
        return; // Exit the function if the file cannot be opened
    }

    string enteredUsername, enteredPassword;
    bool loginSuccessful = false;

    cout << "\n\nEnter username: ";
    cin >> enteredUsername;
    cout << "Enter password: ";
    cin >> enteredPassword;

    string line;
    while (getline(loginfile1, line)) {
        // Split the line into username and password
        stringstream ss(line);
        string correctUsername, correctPassword;
        ss >> correctUsername >> correctPassword;

        if (enteredUsername == correctUsername && enteredPassword == correctPassword) {
            loginSuccessful = true;
            break;
        }
    }

    loginfile1.close();

    if (loginSuccessful) {
        cout << "\n\nLOGIN SUCCESSFUL, THANK YOU\n";
        sub1();
    } else {
        system("CLS");
        cout << "\n\nYOUR USERNAME OR PASSWORD IS INCORRECT, PLEASE TRY AGAIN\n\n";
        login1();
    }
}

void sub1()
{
    int userchoice;

    cout << "\n\t\tPress 1 to add new bakery items" << endl;
    cout << "\t\tPress 2 to view bakery items" << endl;
    cout << "\t\tPress 3 to manage sales details" << endl;
    cout << "\t\tPress 4 to Company Details" << endl;
    cout << "\t\tPress 5 to Log Out" << endl;
    cout << "\t\tPress 6 Exit" << endl << endl;

    cout << "\t ENTER YOUR CHOICE....";
    cin >> userchoice;

    switch (userchoice) {
        case 1:
            addBitemCashier(); 
            break;

        case 2:
            system("CLS");
            itemDcashier();
            break;

        case 3:
            addsalescashier();
            break;

        case 4:
            Cdetailcashier();
            break;

        case 5:
            system("CLS");
            logout();
            break;

        case 6:
            exit(0);

        default:
            cout << "\nInvalid choice. Please select a valid option.\n";
            sub1(); // Re-prompt for choice
            break;
    }
}

// To add bakery items (cashier)
void addBitemCashier() 
{
    fstream bakerydata("BakeryData.txt", ios::out | ios::app); // Open the file in append mode
    string bName, bType, bNumber;
    int bQuantity = 0;
    char choice = 'N'; // Initialize choice with 'N'

    cout << "\nEnter Name of the Bakery Item : ";
    cin.ignore(); // Clear the newline left in the input buffer
    getline(cin, bName);

    cout << "Enter Type of the Item (Bakery/Beverage): ";
    getline(cin, bType);

    cout << "Enter Bakery Item ID : ";
    getline(cin, bNumber);

    cout << "Enter quantity of the bakery item : ";
    cin >> bQuantity;

    bakerydata << bName << "  " << bType << "   " << bNumber << "   " << bQuantity << endl;
    bakerydata.close();

    cout << "\nNew bakery item added successfully.\n";

    cout << "Do you want to add another bakery item? (Y/N) : ";
    cin >> choice; // Update choice based on user input

    if (choice == 'Y' || choice == 'y')
    {
        system("CLS");
        addBitemCashier(); 
    }
    else {
        system("CLS");
        cout << endl << endl << "**********AMBER'S BAKERY SYSTEM**********" << endl << endl;
        sub1();
    }

    cout << "Press any key to continue...";
    cin.ignore();
    cin.get(); // Wait for user input

    system("CLS");
    cout << "\n\n\t\t************AMBER'S BAKERY SYSTEM************\n";
    sub1(); // Return to the cashier menu
}

// viewing bakery items in cashier option
void itemDcashier()
{
    ifstream bakerydata("BakeryData.txt");
    if (!bakerydata.is_open()) {
        cout << "Error opening BakeryData.txt\n";
        return; // Exit the function if file cannot be opened
    }

    cout << "\n\t************ Bakery Items ************\n";
    cout << "\nName\t\tType\t\tItem Number\tQuantity\n";
    cout << "-----------------------------------------------------------\n";

    string bName, bType, bNumber;
    int bQuantity;

    while (bakerydata >> bName >> bType >> bNumber >> bQuantity) {
        cout << setw(15) << left << bName << setw(15) << left << bType << setw(15) << left << bNumber << setw(10) << left << bQuantity << endl;
    }

    bakerydata.close();

    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get(); // Wait for user input before returning to the main menu

    system("CLS");
        cout << "\n\n\t\t************AMBER'S BAKERY SYSTEM************\n";
        sub1();
}


void addsalescashier()
{
    fstream salesdetials("sales.txt", ios::out | ios::app); // Open the file in append mode
    string name, type, itemnumber;
    int Quantity = 0;
    double price;
    char choice;
    
    cout << "\n\tEnter Item Name : ";
    cin.ignore(); // Clear the newline left in the input buffer
    getline(cin, name);

    cout << "\tEnter quantity sold : ";
    cin>> Quantity;

    cout << "\tEnter price per item : ";
    cin>> price;


    salesdetials << name << "  " << Quantity << "   " << price << "   "<< endl;
    salesdetials.close();

    cout << "\nSale recorded successfully.\n";
    cout << "\nDo you want to add new Sale? (Y/N) : ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
        addsalescashier();
    else {
        system("CLS");
        cout << endl << endl << "**********AMBER'S BAKERY SYSTEM**********" << endl << endl;
        sub1();
    }
}

void Cdetailcashier()
{
    system("CLS");
    cout << "\n\t************ Company Details ************\n";

    cout << "\n\nCompany name : The Amber's Bakery";
    cout << "\nAddress : 49 Featherstone Street,London";
    cout << "\n\nContact Details";
    cout << "\n\nHotline : 081 32566##";
    cout << "\nEmail : amnersbakeryinfo@gmail.com";

    cout << "\n\nPress any key to continue...";
    cin.ignore();
    cin.get(); // Wait for user input before returning to the main menu

    system("CLS");
        cout << endl << endl << "**********AMBER'S BAKERY SYSTEM**********" << endl << endl;
        sub1();
}  

//customer login process

void login2 ()
{
    cout << "\t\t************AMBER'S BAKERY SYSTEM************\n";
    cout << "\n\nCustomer\n\n"; 
    sub2();
}

void sub2()
{
    int userchoice;

    cout << "\t\tPress 1 to view bakery items" << endl;
    cout << "\t\tPress 2 to Company Details" << endl;
    cout << "\t\tPress 3 to Log Out" << endl;
    cout << "\t\tPress 4 Exit" << endl << endl;

    cout << "\t ENTER YOUR CHOICE....";
    cin >> userchoice;

    switch (userchoice) {
        case 1:
            itemDcustomer();
            break;

        case 2:
            Cdetailscustomer();
            break;

        case 3:
            system("CLS");
            logout();
            break;

        case 4:
            exit(0);

        default:
            cout << "\nInvalid choice. Please select a valid option.\n";
            sub2(); // Re-prompt for choice
            break;
    }
}

// view item details for customer
void itemDcustomer()
{
    ifstream bakerydata("BakeryData.txt");
    if (!bakerydata.is_open()) {
        cout << "Error opening BakeryData.txt\n";
        return; // Exit the function if file cannot be opened
    }

    cout << "\n\t************ Bakery Items ************\n";
    cout << "\nName\t\tType\t\tItem Number\tQuantity\n";
    cout << "-----------------------------------------------------------\n";

    string bName, bType, bNumber;
    int bQuantity;

    while (bakerydata >> bName >> bType >> bNumber >> bQuantity) {
        cout << setw(15) << left << bName << setw(15) << left << bType << setw(15) << left << bNumber << setw(10) << left << bQuantity << endl;
    }

    bakerydata.close();

    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get(); // Wait for user input before returning to the main menu

    system("CLS");
        cout << "\n\n\t\t************AMBER'S BAKERY SYSTEM************\n";
        sub2();
}

// view company details for customer
void Cdetailscustomer()
{
    
    cout << "\n\t************ Company Details ************\n";

    cout << "\n\n\tCompany name : The Amber's Bakery";
    cout << "\n\tAddress : 49 Featherstone Street,London";
    cout << "\n\n\tContact Details";
    cout << "\n\t------------------";
    cout << "\n\n\tHotline : 081 32566##";
    cout << "\n\tEmail : amnersbakeryinfo@gmail.com";

    cout << "\n\nPress any key to continue...";
    cin.ignore();
    cin.get(); // Wait for user input before returning to the main menu

    system("CLS");
        cout << endl << endl << "**********AMBER'S BAKERY SYSTEM**********" << endl << endl;
        sub2();
}
//system End.