#include <iostream>
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
void printHeader(string title);
void center(const string& text);
void wait();
int getChoice();
void clearInputBuffer();
void saveCustomers();

// ===================== CUSTOMER MANAGEMENT =====================

// Find a customer by their ID
int findCust(int id) {
    for(int i = 0; i < custCnt; i++) {
        if(cust[i].id == id) {
            return i; // Return array index if found
        }
    }
    return -1; // Not found
}

// Display all customers
void viewCustomers() {
    printHeader("ALL CUSTOMERS");

    if(custCnt == 0) {
        center("No customers found in the database.");
    } else {
        for(int i = 0; i < custCnt; i++) {
            cout << string(23, ' ') << "----------------------------------\n";
            cout << string(23, ' ') << "ID      : " << cust[i].id << endl;
            cout << string(23, ' ') << "Name    : " << cust[i].name << endl;
            cout << string(23, ' ') << "Phone   : " << cust[i].phone << endl;
            cout << string(23, ' ') << "Address : " << cust[i].address << endl;
        }
        cout << string(23, ' ') << "----------------------------------\n";
        cout << "\n";
        center("Total Customers: " + to_string(custCnt));
    }
    wait();
}

// Internal function to add a customer
void addNewCustomerInternal() {
    printHeader("ADD NEW CUSTOMER");

    if(custCnt >= MAX_CUST) {
        center("Error: Customer database is full!");
        wait();
        return;
    }

    Customer newCustomer;
    newCustomer.id = nextCustId;

    cout << string(25,' ') << "New Customer ID: " << newCustomer.id << endl;

    cout << string(25,' ') << "Name: ";
    clearInputBuffer(); // Clear buffer before getline
    getline(cin, newCustomer.name);

    cout << string(25,' ') << "Phone: ";
    getline(cin, newCustomer.phone);

    cout << string(25,' ') << "Address: ";
    getline(cin, newCustomer.address);

    // Add to global array
    cust[custCnt] = newCustomer;
    custCnt++;

    nextCustId++;
    saveCustomers();

    center("\nCustomer added successfully!");
    wait();
}

// Search for a customer
void searchCustomer() {
    printHeader("SEARCH FOR CUSTOMER");
    int searchId;
    cout << string(25,' ') << "Enter Customer ID to search: ";
    cin >> searchId;

    int index = findCust(searchId);

    if(index == -1) {
        center("Customer not found.");
    } else {
        cout << "\n" << string(20, ' ') << "--- CUSTOMER FOUND ---\n";
        cout << string(20, ' ') << "ID      : " << cust[index].id << endl;
        cout << string(20, ' ') << "Name    : " << cust[index].name << endl;
        cout << string(20, ' ') << "Phone   : " << cust[index].phone << endl;
        cout << string(20, ' ') << "Address : " << cust[index].address << endl;
        cout << string(20, ' ') << "----------------------\n";
    }
    wait();
}

// Update customer details
void updateCustomer() {
    printHeader("UPDATE CUSTOMER DETAILS");
    int updateId;
    cout << string(25,' ') << "Enter Customer ID to update: ";
    cin >> updateId;

    int index = findCust(updateId);

    if(index == -1) {
        center("Customer not found.");
        wait();
        return;
    }

    cout << "\n" << string(20, ' ') << "--- Updating Customer ---\n";
    cout << string(20, ' ') << "ID: " << cust[index].id << endl;
    cout << string(20, ' ') << "Current Name: " << cust[index].name << endl;

    string newName, newPhone, newAddress;

    cout << string(20, ' ') << "Enter new Name (or press Enter to keep): ";
    clearInputBuffer();
    getline(cin, newName);

    cout << string(20, ' ') << "Current Phone: " << cust[index].phone << endl;
    cout << string(20, ' ') << "Enter new Phone (or press Enter to keep): ";
    getline(cin, newPhone);

    cout << string(20, ' ') << "Current Address: " << cust[index].address << endl;
    cout << string(20, ' ') << "Enter new Address (or press Enter to keep): ";
    getline(cin, newAddress);

    // Only update if user entered something
    if(!newName.empty()) {
        cust[index].name = newName;
    }
    if(!newPhone.empty()) {
        cust[index].phone = newPhone;
    }
    if(!newAddress.empty()) {
        cust[index].address = newAddress;
    }

    saveCustomers();
    center("\nCustomer details updated successfully!");
    wait();
}

// Delete a customer
void deleteCustomer() {
    printHeader("DELETE CUSTOMER");
    int deleteId;
    cout << string(25,' ') << "Enter Customer ID to delete: ";
    cin >> deleteId;

    int index = findCust(deleteId);

    if(index == -1) {
        center("Customer not found.");
        wait();
        return;
    }

    cout << "\n" << string(20, ' ') << "Found Customer: " << cust[index].name << endl;
    cout << string(20, ' ') << "Are you sure you want to delete? (Y/N): ";
    char confirm;
    cin >> confirm;

    if(confirm == 'Y' || confirm == 'y') {
        // Shift remaining customers left
        for(int i = index; i < custCnt - 1; i++) {
            cust[i] = cust[i + 1];
        }
        custCnt--;
        saveCustomers();
        center("\nCustomer deleted successfully.");
    } else {
        center("\nOperation cancelled.");
    }
    wait();
}

// Main menu for customer management
void manageCustomers() {
    while(true) {
        printHeader("MANAGE CUSTOMERS");
        center("1. Add New Customer");
        center("2. Search Customer");
        center("3. Update Customer Details");
        center("4. Delete Customer");
        center("5. View All Customers");
        center("6. Back to Main Menu");
        cout << "\n";
        center("--------------------------------------------------");

        int choice = getChoice();

        if(choice == 1) addNewCustomerInternal();
        else if(choice == 2) searchCustomer();
        else if(choice == 3) updateCustomer();
        else if(choice == 4) deleteCustomer();
        else if(choice == 5) viewCustomers();
        else if(choice == 6) return;
        else {
            center("Invalid choice! Please try again.");
            wait();
        }
    }
}
