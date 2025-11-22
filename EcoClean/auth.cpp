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
void loadUsers();
void printHeader(string title);
void center(const string& text);
void wait();

// ===================== LOGIN SYSTEM =====================

// Function to handle user login
bool login() {
    // Load users from file first
    loadUsers();

    printHeader("ECO-CLEAN LAUNDRY SYSTEM - LOGIN");

    string inputUsername;
    string inputPassword;

    cout << "\n\n";
    cout << string(30,' ') << "Username: ";
    cin >> inputUsername;

    cout << string(30,' ') << "Password: ";
    cin >> inputPassword;

    // Check credentials against loaded users
    for(int i = 0; i < userCnt; i++) {
        if(users[i].username == inputUsername && users[i].password == inputPassword) {
            // Login successful
            currentUser = users[i].username;
            isAdmin = users[i].isAdmin;

            // cls() removed as requested
            center("Welcome, " + currentUser + "!");
            wait();
            return true;
        }
    }

    return false; // No match found
}
