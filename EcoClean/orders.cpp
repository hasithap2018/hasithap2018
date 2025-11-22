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
int findCust(int id);
void saveOrders();

// ===================== ORDER MANAGEMENT =====================

// Find an order by ID
int findOrd(int id) {
    for(int i = 0; i < ordCnt; i++) {
        if(ord[i].id == id) {
            return i; // Return array index
        }
    }
    return -1; // Not found
}

// Display available services
void viewServices() {
    printHeader("OUR SERVICES");
    cout.precision(2);
    cout << fixed;

    center("CODE     SERVICE NAME               PRICE (per Kg)");
    center("---------------------------------------------------");

    for(int i = 0; i < 4; i++) {
        string line = " " + to_string(services[i].code) + "       " + services[i].name;
        // Padding for alignment
        while(line.length() < 33) {
            line += " ";
        }
        line += "Rs. " + to_string(services[i].price);
        center(line);
    }
    wait();
}

// Place a new order
void placeOrder() {
    printHeader("PLACE NEW ORDER");
    cout.precision(2);
    cout << fixed;

    if(ordCnt >= MAX_ORD) {
        center("Error: Order system is full!");
        wait();
        return;
    }

    int custId;
    cout << string(25,' ') << "Enter Customer ID: ";
    cin >> custId;

    int custIndex = findCust(custId);
    if(custIndex == -1) {
        center("Error: Customer ID not found!");
        wait();
        return;
    }

    Order newOrder;
    newOrder.id = nextOrdId;
    newOrder.custId = custId;
    newOrder.custName = cust[custIndex].name;

    cout << string(25,' ') << "Customer: " << newOrder.custName << endl;

    cout << "\n";
    center("CODE     SERVICE NAME               PRICE (per Kg)");
    center("---------------------------------------------------");
    for(int i = 0; i < 4; i++) {
        string line = " " + to_string(services[i].code) + "       " + services[i].name;
        while(line.length() < 33) line += " ";
        line += "Rs. " + to_string(services[i].price);
        center(line);
    }

    cout << "\n" << string(25,' ') << "Enter Service Code (1-4): ";
    cin >> newOrder.service;

    if(newOrder.service < 1 || newOrder.service > 4) {
        center("Error: Invalid Service Code!");
        wait();
        return;
    }

    cout << string(25,' ') << "Enter Weight (Kg): ";
    cin >> newOrder.kg;

    if(newOrder.kg <= 0) {
        center("Error: Invalid weight!");
        wait();
        return;
    }

    cout << string(25,' ') << "Enter Date (e.g., 18-Nov-2025): ";
    clearInputBuffer();
    getline(cin, newOrder.date);

    newOrder.status = "Pending";
    newOrder.amount = newOrder.kg * services[newOrder.service - 1].price;

    // Add to orders array
    ord[ordCnt] = newOrder;
    ordCnt++;

    nextOrdId++;
    saveOrders();

    printHeader("ORDER RECEIPT");
    cout << string(25,' ') << "Order ID      : " << newOrder.id << endl;
    cout << string(25,' ') << "Customer ID   : " << newOrder.custId << endl;
    cout << string(25,' ') << "Customer Name : " << newOrder.custName << endl;
    cout << string(25,' ') << "Service       : " << services[newOrder.service - 1].name << endl;
    cout << string(25,' ') << "Weight        : " << newOrder.kg << " Kg" << endl;
    cout << string(25,' ') << "Status        : " << newOrder.status << endl;
    cout << string(25,' ') << "Date          : " << newOrder.date << endl;
    cout << string(25,' ') << "TOTAL AMOUNT  : Rs. " << newOrder.amount << endl;

    wait();
}

// View all orders
void viewOrders() {
    printHeader("VIEW ALL ORDERS");
    cout.precision(2);
    cout << fixed;

    if(ordCnt == 0) {
        center("No orders found.");
    } else {
        for(int i = 0; i < ordCnt; i++) {
            cout << string(15, ' ') << "------------------------------------------\n";
            cout << string(15, ' ') << "Order ID : " << ord[i].id << " (" << ord[i].status << ")\n";
            cout << string(15, ' ') << "Cust ID  : " << ord[i].custId << " (" << ord[i].custName << ")\n";
            cout << string(15, ' ') << "Date     : " << ord[i].date << "\n";
            cout << string(15, ' ') << "Service  : " << services[ord[i].service - 1].name << "\n";
            cout << string(15, ' ') << "Details  : " << ord[i].kg << " Kg\n";
            cout << string(15, ' ') << "Amount   : Rs. " << ord[i].amount << "\n";
        }
        cout << string(15, ' ') << "------------------------------------------\n";
        cout << "\n";
        center("Total Orders: " + to_string(ordCnt));
    }
    wait();
}

// Update order status
void updateStatus() {
    printHeader("UPDATE ORDER STATUS");
    cout << "\n" << string(25,' ') << "Enter Order ID to update: ";
    int updateId;
    cin >> updateId;

    int index = findOrd(updateId);
    if(index == -1) {
        center("Order ID not found!");
        wait();
        return;
    }

    cout << "\n" << string(25,' ') << "Current Status: " << ord[index].status << endl;
    cout << string(25,' ') << "Enter New Status (e.g., Processing, Ready, Completed): ";
    string newStatus;
    clearInputBuffer();
    getline(cin, newStatus);

    if(!newStatus.empty()) {
        ord[index].status = newStatus;
        saveOrders();
        center("\nStatus updated successfully!");
    } else {
        center("\nNo change made.");
    }
    wait();
}
