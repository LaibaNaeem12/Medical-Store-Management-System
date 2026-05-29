
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

// MEDICINES DATABASE

string medName[] = {
    "Panadol","Brufen","Cough Syrup","Disprin","Amoxicillin",
    "Paracetamol","Aspirin","Augmentin","Vicks","Cetirizine",
    "Loratadine","Ibuprofen","Azithromycin","Metformin","Insulin",
    "Omeprazole","ORS","Norflox","Diclofenac","Calpol"
};

int medPrice[] = {
    10,20,15,5,25,
    8,6,30,12,18,
    22,14,35,40,50,
    28,7,33,16,11
};

int medStock[] = {
    120,90,80,150,60,
    100,110,70,130,95,
    85,100,60,75,50,
    88,140,65,115,105
};

int totalMedicines = 20;


// CART SYSTEM

int cartID[100];
int cartQty[100];
int cartCount = 0;
int grandTotal = 0;

// FUNCTIONS

void line();
void header();
void loading();
void showMedicines();
void customerFlow();
void adminMenu();
bool adminLogin();
void autoBill();
void viewCart();


void line() {
    cout << "\n--------------------------------------------------\n";
}


// HEADER DESIGN

void header() {

    cout << "\n";
    cout << "############################################################\n";
    cout << "#                                                          #\n";
    cout << "#         AL-SHIFA MEDICAL STORE SYSTEM                    #\n";
    cout << "#                                                          #\n";
    cout << "############################################################\n";
}


// LOADING EFFECT

void loading() {

    cout << "\nLoading System";

    for(int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(300);
    }

    cout << "\n";
}


// SHOW MEDICINES

void showMedicines() {


    cout << left
         << setw(5)  << "ID"
         << setw(25) << "MEDICINE NAME"
         << setw(10) << "PRICE" << endl;

    line();

    for (int i = 0; i < totalMedicines; i++) {

        cout << left
             << setw(5)  << i
             << setw(25) << medName[i]
             << setw(10) << medPrice[i]
             << endl;
    }

    line();
}


// VIEW CART

void viewCart() {

    cout << "\n==================== YOUR CART ====================\n";

    if (cartCount == 0) {
        cout << "Cart is empty!\n";
        return;
    }

    grandTotal = 0;

    for (int i = 0; i < cartCount; i++) {

        int id = cartID[i];
        int qty = cartQty[i];
        int total = medPrice[id] * qty;

        cout << medName[id]
             << " x " << qty
             << " = " << total << endl;

        grandTotal += total;
    }

    cout << "---------------------------------------------------\n";
    cout << "TOTAL BILL: " << grandTotal << endl;
}

// FINAL BILL RECEIPT

void autoBill() {

    if (cartCount == 0) {
        cout << "\nCart is empty!\n";
        return;
    }

    grandTotal = 0;

    
    cout << "                    FINAL RECEIPT\n";
    line();

    cout << left
         << setw(25) << "MEDICINE"
         << setw(10) << "QTY"
         << setw(10) << "PRICE"
         << setw(10) << "TOTAL" << endl;

    line();

    for (int i = 0; i < cartCount; i++) {

        int id = cartID[i];
        int qty = cartQty[i];
        int total = medPrice[id] * qty;

        cout << left
             << setw(25) << medName[id]
             << setw(10) << qty
             << setw(10) << medPrice[id]
             << setw(10) << total
             << endl;

        grandTotal += total;
    }

    

    cout << "GRAND TOTAL: " << grandTotal << endl;

    line();

    cout << "         THANK YOU FOR SHOPPING!\n";

    line();

    cartCount = 0;
    grandTotal = 0;
}

// CUSTOMER PANEL

void customerFlow() {

    int choice;

    while (true) {

        
        cout << "                CUSTOMER PANEL\n";
        line();

        cout << "\n[1] Buy Medicine\n";
        cout << "[2] View Cart\n";
        cout << "[3] Generate Bill\n";
        cout << "[4] Exit\n";

        line();

        cout << "Enter choice: ";
        cin >> choice;

        // BUY MEDICINE
        if (choice == 1) {

            int id, qty;

            showMedicines();

            cout << "Enter Medicine ID: ";
            cin >> id;

            if (id < 0 || id >= totalMedicines) {
                cout << "\nInvalid Medicine ID!\n";
                continue;
            }

            cout << "Enter Quantity: ";
            cin >> qty;

            if (medStock[id] >= qty) {

                medStock[id] -= qty;

                cartID[cartCount] = id;
                cartQty[cartCount] = qty;

                cartCount++;

                
                cout << "     MEDICINE ADDED TO CART SUCCESSFULLY\n";
                line();

                int next;

                cout << "\n[1] Buy More Medicines\n";
                cout << "[2] Generate Bill\n";

                cout << "Enter choice: ";
                cin >> next;

                if (next == 2) {
                    autoBill();
                    return;
                }
            }

            else {
                cout << "\nNot Enough Stock Available!\n";
            }
        }

        // VIEW CART
        else if (choice == 2) {
            viewCart();
        }

        // GENERATE BILL
        else if (choice == 3) {
            autoBill();
            return;
        }

        // EXIT
        else if (choice == 4) {
            return;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }
}


// ADMIN LOGIN

bool adminLogin() {

    string username, password;

    
    cout << "                  ADMIN LOGIN\n";
    line();

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    if (
        (username == "admin1" && password == "1234") ||
        (username == "admin2" && password == "1234") ||
        (username == "admin3" && password == "1234")
       )
    {
        return true;
    }

    cout << "\nInvalid Login!\n";

    return false;
}


// ADMIN PANEL

void adminMenu() {

    if (!adminLogin()) {
        return;
    }

    int choice;

    while (true) {

        
        cout << "                 ADMIN DASHBOARD\n";
        line();

        cout << "\n[1] View Medicines";
        cout << "\n[2] Add Stock";
        cout << "\n[3] Low Stock Alert";
        cout << "\n[4] Exit";

        line();

        cout << "Enter choice: ";
        cin >> choice;

        // VIEW MEDICINES
        if (choice == 1) {

            line();

            cout << left
                 << setw(5)  << "ID"
                 << setw(25) << "MEDICINE"
                 << setw(10) << "PRICE"
                 << setw(10) << "STOCK" << endl;

            line();

            for (int i = 0; i < totalMedicines; i++) {

                cout << left
                     << setw(5)  << i
                     << setw(25) << medName[i]
                     << setw(10) << medPrice[i]
                     << setw(10) << medStock[i]
                     << endl;
            }

            line();
        }

        // ADD STOCK
        else if (choice == 2) {

            int id, qty;

            line();

            cout << left
                 << setw(5)  << "ID"
                 << setw(25) << "MEDICINE"
                 << setw(10) << "STOCK" << endl;

            line();

            for (int i = 0; i < totalMedicines; i++) {

                cout << left
                     << setw(5)  << i
                     << setw(25) << medName[i]
                     << setw(10) << medStock[i]
                     << endl;
            }

            line();

            cout << "Enter Medicine ID: ";
            cin >> id;

            if (id < 0 || id >= totalMedicines) {
                cout << "Invalid ID!\n";
                continue;
            }

            cout << "Enter Quantity To Add: ";
            cin >> qty;

            medStock[id] += qty;

            
            cout << "            UPDATED MEDICINE DETAILS\n";
            line();

            cout << "Medicine ID     : " << id << endl;
            cout << "Medicine Name   : " << medName[id] << endl;
            cout << "Updated Stock   : " << medStock[id] << endl;

            

            cout << "       STOCK UPDATED SUCCESSFULLY!\n";

            line();
        }

        // LOW STOCK
        else if (choice == 3) {

            cout << "\n============= LOW STOCK MEDICINES =============\n";

            bool found = false;

            for (int i = 0; i < totalMedicines; i++) {

                if (medStock[i] < 60) {

                    cout << medName[i]
                         << " -> Stock: "
                         << medStock[i] << endl;

                    found = true;
                }
            }

            if (!found) {
                cout << "No Low Stock Medicines.\n";
            }
        }

        // EXIT
        else if (choice == 4) {
            return;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }
}


// MAIN FUNCTION

int main() {

    // CONSOLE COLOR
    system("color 0A");

    loading();

    int choice;

    while (true) {

        header();

        cout << "\n";
        cout << "         Fast Billing | Smart Stock\n";

        line();

        cout << "\n[1] Customer Panel\n";
        cout << "[2] Admin Panel\n";
        cout << "[3] Exit\n";

        line();

        cout << "Enter choice: ";
        cin >> choice;

        // CUSTOMER
        if (choice == 1) {
            customerFlow();
        }

        // ADMIN
        else if (choice == 2) {
            adminMenu();
        }

        // EXIT
        else if (choice == 3) {

            line();

            cout << "      THANK YOU FOR USING THE SYSTEM!\n";

            line();

            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}


