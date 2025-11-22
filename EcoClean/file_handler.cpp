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

// ===================== FILE HANDLING =====================

// Function to load users from file
void loadUsers() {
    userCnt = 0;
    ifstream file(USER_FILE);

    // If file doesn't exist, create default users
    if (!file.is_open()) {
        users[0].username = "admin";
        users[0].password = "eco123";
        users[0].isAdmin = true;

        users[1].username = "emp";
        users[1].password = "123";
        users[1].isAdmin = false;

        userCnt = 2;
        return;
    }

    string u, p, flag;
    // Read until end of file or max users reached
    while (userCnt < MAX_USERS && file >> u >> p >> flag) {
        users[userCnt].username = u;
        users[userCnt].password = p;
        if (flag == "1") {
            users[userCnt].isAdmin = true;
        } else {
            users[userCnt].isAdmin = false;
        }
        userCnt++;
    }
    file.close();
}

// Function to save users to file
void saveUsers() {
    ofstream file(USER_FILE);
    for(int i = 0; i < userCnt; i++) {
        file << users[i].username << " " << users[i].password << " ";
        if (users[i].isAdmin) {
            file << "1";
        } else {
            file << "0";
        }
        file << "\n";
    }
    file.close();
}

// Function to load customers from file
void loadCustomers() {
    custCnt = 0;
    ifstream file(CUST_FILE);

    if (!file.is_open()) {
        return; // File doesn't exist yet
    }

    int maxId = 0;
    while(custCnt < MAX_CUST && file >> cust[custCnt].id) {
        file.ignore(1, '\n'); // Skip newline after ID
        getline(file, cust[custCnt].name);
        getline(file, cust[custCnt].phone);
        getline(file, cust[custCnt].address);

        // Keep track of the highest ID found
        if(cust[custCnt].id > maxId) {
            maxId = cust[custCnt].id;
        }
        custCnt++;
    }
    file.close();
    nextCustId = maxId + 1; // Set next ID to be one higher
}

// Function to save customers to file
void saveCustomers() {
    ofstream file(CUST_FILE);
    for(int i = 0; i < custCnt; i++) {
        file << cust[i].id << "\n";
        file << cust[i].name << "\n";
        file << cust[i].phone << "\n";
        file << cust[i].address << "\n";
    }
    file.close();
}

// Function to load orders from file
void loadOrders() {
    ordCnt = 0;
    ifstream file(ORD_FILE);

    if (!file.is_open()) {
        return;
    }

    int maxId = 1000;
    while(ordCnt < MAX_ORD && file >> ord[ordCnt].id) {
        file >> ord[ordCnt].custId >> ord[ordCnt].service >> ord[ordCnt].kg >> ord[ordCnt].amount;
        file.ignore(1, '\n'); // Skip newline

        getline(file, ord[ordCnt].custName);
        getline(file, ord[ordCnt].status);
        getline(file, ord[ordCnt].date);

        if(ord[ordCnt].id > maxId) {
            maxId = ord[ordCnt].id;
        }
        ordCnt++;
    }
    file.close();
    nextOrdId = maxId + 1;
}

// Function to save orders to file
void saveOrders() {
    ofstream file(ORD_FILE);
    for(int i = 0; i < ordCnt; i++) {
        file << ord[i].id << " "
             << ord[i].custId << " "
             << ord[i].service << " "
             << ord[i].kg << " "
             << ord[i].amount << "\n"
             << ord[i].custName << "\n"
             << ord[i].status << "\n"
             << ord[i].date << "\n";
    }
    file.close();
}
