#include <string>
using namespace std;

// --- CONSTANTS ---
const int MAX_CUST = 100;   // Maximum number of customers
const int MAX_ORD = 500;    // Maximum number of orders
const int MAX_USERS = 20;   // Maximum number of users

// File names
const string CUST_FILE = "customers.txt";
const string ORD_FILE = "orders.txt";
const string USER_FILE = "users.txt";

// --- STRUCTURES ---

// Structure to hold customer details
struct Customer {
    int id;
    string name;
    string phone;
    string address;
};

// Structure to hold order details
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

// Structure for user login info
struct User {
    string username;
    string password;
    bool isAdmin;
};

// Structure for laundry services
struct Service {
    int code;
    string name;
    double price;
} services[4] = {
    {1, "Wash & Fold",         150.00},
    {2, "Dry Cleaning",        400.00},
    {3, "Ironing Only",        100.00},
    {4, "Premium Wash + Iron", 250.00}
};

// --- GLOBAL ARRAYS ---
Customer cust[MAX_CUST];
Order ord[MAX_ORD];
User users[MAX_USERS];

// --- GLOBAL VARIABLES ---
int custCnt = 0;
int ordCnt = 0;
int userCnt = 0;

int nextCustId = 1;
int nextOrdId = 1001;

string currentUser = "";
bool isAdmin = false;
