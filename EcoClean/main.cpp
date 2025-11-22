// ECO-CLEAN LAUNDRY SYSTEM - MODULARIZED
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// --- CONSTANTS ---
const int MAX_CUST = 100;
const int MAX_ORD = 500;
const int MAX_USERS = 20;
const string CUST_FILE = "customers.txt";
const string ORD_FILE = "orders.txt";
const string USER_FILE = "users.txt";

// --- STRUCTURES ---
struct Customer {
    int id;
    string name;
    string phone;
    string address;
};

struct Order {
    int id;
    int custId;
    int service;
    string custName;
    string status;
    string date;
    double kg;
    double amount;
};

struct User {
    string username;
    string password;
    bool isAdmin;
};

struct Service {
    int code;
    string name;
    double price;
};

// --- EXTERN GLOBALS ---
extern Customer cust[MAX_CUST];
extern Order ord[MAX_ORD];
extern User users[MAX_USERS];
extern Service services[4];

extern int custCnt;
extern int ordCnt;
extern int userCnt;

extern int nextCustId;
extern int nextOrdId;

extern string currentUser;
extern bool isAdmin;

// --- FUNCTION PROTOTYPES ---
void center(const string& text);
void clearInputBuffer();
void wait();
void printHeader(string title);
int getChoice();

void loadUsers();
void loadCustomers();
void loadOrders();

bool login();

void viewServices();
void manageCustomers();
void viewCustomers();
void placeOrder();
void viewOrders();
void updateStatus();
void manageUsers();


int main() {
    // Load data from files at startup
    loadCustomers();
    loadOrders();

    // Perform login
    // Perform login
    bool loggedIn = false;
    while(!loggedIn) {
        if(login()) {
            loggedIn = true;
        } else {
            printHeader("Access Denied! Invalid credentials.");
            cout << "\n";
            center("1. Try Again");
            center("2. Exit Program");
            cout << "\n";
            center("--------------------------------------------------");

            int retryChoice = getChoice();
            if(retryChoice == 2) {
                return 0;
            }
        }
    }

    // Main Menu Loop
    while(true) {
        printHeader("ECO - CLEAN LAUNDRY SYSTEM");

        string roleStr;
        if(isAdmin) {
            roleStr = " (ADMIN)";
        } else {
            roleStr = " (EMPLOYEE)";
        }

        center("Logged in as: " + currentUser + roleStr);
        cout << "\n";

        center("1. View Services");
        center("2. Manage Customers");
        center("3. View Customers");
        center("4. Place Order");
        center("5. View Orders");
        center("6. Update Order Status");

        if(isAdmin) {
            center("7. Manage Users");
        }

        // Adjust menu numbers based on role
        if(isAdmin) {
            center("8. Logout");
            center("9. Exit");
        } else {
            center("7. Logout");
            center("8. Exit");
        }

        cout << "\n";
        center("==================================================");

        int choice = getChoice();

        if(choice == 1) {
            viewServices();
        }
        else if(choice == 2) {
            manageCustomers();
        }
        else if(choice == 3) {
            viewCustomers();
        }
        else if(choice == 4) {
            placeOrder();
        }
        else if(choice == 5) {
            viewOrders();
        }
        else if(choice == 6) {
            updateStatus();
        }
        else if(isAdmin && choice == 7) {
            manageUsers();
        }
        else if(choice == (isAdmin ? 8 : 7)) {
            // Logout
            center("Logged out successfully!");
            currentUser = "";
            isAdmin = false;
            wait();

            // Ask for login again
            if(!login()) {
                printHeader("Access Denied!");
                cout << "\n\n\t\t\tPress Enter to exit...";
                cin.get();
                return 0;
            }
        }
        else if(choice == (isAdmin ? 9 : 8)) {
            // Exit
            center("Thank you for using EcoClean! Goodbye!");
            wait();
            return 0;
        }
        else {
            center("Invalid choice! Please try again.");
            wait();
        }
    }
    return 0;
}
