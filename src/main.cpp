#include <iostream>
#include <iomanip>
#include <windows.h>
#include <ctime>

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

// FUNCTION DECLARATIONS
void line();
void header();
void loading();
void showMedicines();
void customerFlow();
void adminMenu();
bool adminLogin();
void autoBill();
void viewCart();

// ---------------- LINE ----------------
void line() {
    cout << "\n--------------------------------------------------\n";
}

// ---------------- HEADER ----------------
void header() {
    cout << "\n";
    cout << "############################################################\n";
    cout << "#         AL-SHIFA MEDICAL STORE SYSTEM                    #\n";
    cout << "############################################################\n";
}

// ---------------- LOADING ----------------
void loading() {
    cout << "\nLoading System";
    for(int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(300);
    }
    cout << "\n";
}

// ---------------- SHOW MEDICINES ----------------
void showMedicines() {
    cout << left
         << setw(5) << "ID"
         << setw(25) << "MEDICINE NAME"
         << setw(10) << "PRICE" << endl;

    line();

    for(int i = 0; i < totalMedicines; i++) {
        cout << left
             << setw(5) << i
             << setw(25) << medName[i]
             << setw(10) << medPrice[i]
             << endl;
    }

    line();
}

// ---------------- VIEW CART ----------------
void viewCart() {
    cout << "\n================ YOUR CART ================\n";

    if(cartCount == 0) {
        cout << "Cart is empty!\n";
        return;
    }

    grandTotal = 0;

    for(int i = 0; i < cartCount; i++) {
        int id = cartID[i];
        int qty = cartQty[i];
        int total = medPrice[id] * qty;

        cout << medName[id] << " x " << qty << " = " << total << endl;

        grandTotal += total;
    }

    cout << "------------------------------------------\n";
    cout << "TOTAL BILL: " << grandTotal << endl;
}

// ---------------- FINAL BILL ----------------
void autoBill() {
    if(cartCount == 0) {
        cout << "\nCart is empty!\n";
        return;
    }

    grandTotal = 0;

    cout << "\n=========== FINAL RECEIPT ===========\n";
    line();

    // TIME STAMP
    time_t now = time(0);
    cout << "Date/Time: " << ctime(&now);

    cout << left
         << setw(25) << "MEDICINE"
         << setw(10) << "QTY"
         << setw(10) << "PRICE"
         << setw(10) << "TOTAL" << endl;

    line();

    for(int i = 0; i < cartCount; i++) {
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

    line();
    cout << "GRAND TOTAL: " << grandTotal << endl;
    line();

    cout << "THANK YOU FOR SHOPPING!\n";
    line();

    cartCount = 0;
    grandTotal = 0;
}

// ---------------- CUSTOMER FLOW ----------------
void customerFlow() {
    int choice;

    while(true) {
        cout << "\n===== CUSTOMER PANEL =====\n";
        line();

        cout << "[1] Buy Medicine\n";
        cout << "[2] View Cart\n";
        cout << "[3] Generate Bill\n";
        cout << "[4] Exit\n";

        line();
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {
            int id, qty;

            showMedicines();

            cout << "Enter Medicine ID: ";
            cin >> id;

            if(id < 0 || id >= totalMedicines) {
                cout << "Invalid ID!\n";
                continue;
            }

            cout << "Enter Quantity: ";
            cin >> qty;

            if(medStock[id] >= qty) {

                medStock[id] -= qty;

                if(cartCount < 100) {
                    cartID[cartCount] = id;
                    cartQty[cartCount] = qty;
                    cartCount++;
                } else {
                    cout << "Cart Full!\n";
                }

                cout << "Added to cart!\n";
            }
            else {
                cout << "Not enough stock!\n";
            }
        }

        else if(choice == 2) {
            viewCart();
        }

        else if(choice == 3) {
            autoBill();
            return;
        }

        else if(choice == 4) {
            return;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }
}

// ---------------- ADMIN LOGIN ----------------
bool adminLogin() {
    string user, pass;

    cout << "\nADMIN LOGIN\n";
    line();

    cout << "Username: ";
    cin >> user;

    cout << "Password: ";
    cin >> pass;

    if((user == "admin1" && pass == "1234") ||
       (user == "admin2" && pass == "1234") ||
       (user == "admin3" && pass == "1234")) {
        return true;
    }

    cout << "Invalid Login!\n";
    return false;
}

// ---------------- ADMIN PANEL ----------------
void adminMenu() {
    if(!adminLogin()) return;

    int choice;

    while(true) {
        cout << "\n===== ADMIN DASHBOARD =====\n";
        line();

        cout << "[1] View Medicines\n";
        cout << "[2] Add Stock\n";
        cout << "[3] Low Stock Alert\n";
        cout << "[4] Exit\n";

        line();
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {
            for(int i = 0; i < totalMedicines; i++) {
                cout << i << " | " << medName[i]
                     << " | Stock: " << medStock[i] << endl;
            }
        }

        else if(choice == 2) {
            int id, qty;

            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter Quantity: ";
            cin >> qty;

            if(id >= 0 && id < totalMedicines) {
                medStock[id] += qty;
                cout << "Stock Updated!\n";
            }
        }

        else if(choice == 3) {
            cout << "\nLOW STOCK ITEMS (<60)\n";

            for(int i = 0; i < totalMedicines; i++) {
                if(medStock[i] < 60) {
                    cout << medName[i]
                         << " -> " << medStock[i] << endl;
                }
            }
        }

        else if(choice == 4) {
            return;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }
}

// ---------------- MAIN ----------------
int main() {
    system("color 0A");

    loading();

    int choice;

    while(true) {
        header();

        cout << "\n[1] Customer Panel\n";
        cout << "[2] Admin Panel\n";
        cout << "[3] Exit\n";

        line();
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) customerFlow();
        else if(choice == 2) adminMenu();
        else if(choice == 3) break;
        else cout << "Invalid choice!\n";
    }

    return 0;
}
