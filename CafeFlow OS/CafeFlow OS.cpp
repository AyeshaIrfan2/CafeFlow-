#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <string> 
#include <map>
using namespace std;

// ==================== COLOR FUNCTIONS ====================
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
}

void printHeader() {
    setColor(11); // Cyan
    cout << "=========================================\n";
    cout << "           CAFEFLOW OS \n";
    cout << "    Restaurant Management System\n";
    cout << "=========================================\n";
}

// ==================== FOOD ITEM CLASS ====================
class FoodItem {
public:
    string name;
    double price;
    string category;

    FoodItem(string n = "", double p = 0.0, string cat = "") : name(n), price(p), category(cat) {}
};

// ==================== USER BASE CLASS ====================
class User {
public:
    virtual void showMenu() = 0;
};

// ==================== CUSTOMER CLASS ====================
class Customer : public User {
    vector<FoodItem> cart;

public:
    void showMenu() override {
        clearScreen();
        printHeader();
        setColor(10); // Green
        cout << "           CUSTOMER MENU\n";
        cout << "=========================================\n";
        setColor(15); // White
        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "0. Exit\n";
        cout << "=========================================\n";
        cout << "Select option: ";
    }

    void viewMenu(const vector<FoodItem>& menu) {
        clearScreen();
        printHeader();
        setColor(14); // Yellow
        cout << "               MENU\n";
        cout << "=========================================\n";
        setColor(15); // White;

        // Group items by category
        map<string, vector<FoodItem>> categories;
        for (const auto& item : menu) {
            categories[item.category].push_back(item);
        }

        // Display by category
        for (const auto& cat : categories) {
            setColor(13); // Magenta for category names
            cout << "\n--- " << cat.first << " ---\n";
            setColor(15); // White for items
            // cat.first: The category name ("Burgers")
            //cat.second: The vector of items in that category

            for (size_t i = 0; i < cat.second.size(); i++) 
                // size_t: SAFE loop counter for sizes - guaranteed non-negative, 
                //  perfectly matches vector.size() return type
                //  prevents overflow/underflow bugs
            {
                cout << "  " << i + 1 << ". " << setw(20) << left << cat.second[i].name
                    << " - Rs." << cat.second[i].price << endl;
            }
        }

        setColor(11); // Cyan
        cout << "\n=========================================\n";
        setColor(15); // White
        cout << "Press any key to continue...";
        _getch();
    }

    void placeOrder(vector<FoodItem>& menu) {
        int choice;
        do {
            clearScreen();
            printHeader();
            setColor(14); // Yellow
            cout << "           ADD TO CART\n";
            cout << "=========================================\n";
            setColor(15); // White;

            // Display menu with numbers
            for (size_t i = 0; i < menu.size(); i++) {
                cout << i + 1 << ". " << setw(20) << left << menu[i].name
                    << " - Rs." << menu[i].price << " (" << menu[i].category << ")" << endl;
            }

            setColor(11); // Cyan
            cout << "=========================================\n";
            setColor(15); // White
            cout << "0. Back to Menu\n";
            cout << "Enter item number: ";
            cin >> choice;

            if (choice > 0 && choice <= menu.size()) {
                cart.push_back(menu[choice - 1]); 
                // Convert 1-based user selection to 0-based vector index;
                // User enters 1 → menu[0] (first item)  
                setColor(10); // Green
                cout << menu[choice - 1].name << " added to cart!\n";
                setColor(15); // White
                Sleep(1000);
            }
        } while (choice != 0);
    }

    void viewCart() {
        clearScreen();
        printHeader();
        setColor(14); // Yellow
        cout << "               CART\n";
        cout << "=========================================\n";
        setColor(15); // White

        double total = 0;
        for (size_t i = 0; i < cart.size(); i++) {
            cout << i + 1 << ". " << setw(20) << left << cart[i].name
                << " - Rs." << cart[i].price << endl;
            total += cart[i].price;
        }

        setColor(11); // Cyan
        cout << "=========================================\n";
        setColor(12); // Red
        cout << "TOTAL: Rs." << total << endl;
        setColor(11); // Cyan
        cout << "=========================================\n";
        setColor(15); // White
        cout << "Press any key to continue...";
        _getch();
    }

    void checkout() {
        clearScreen();
        printHeader();
        setColor(10); // Green
        cout << "            CHECKOUT\n";
        cout << "=========================================\n";
        setColor(15); // White

        double total = 0;
        for (size_t i = 0; i < cart.size(); i++) {
            cout << setw(20) << left << cart[i].name
                << " - Rs." << cart[i].price << endl;
            total += cart[i].price;
        }

        setColor(11); // Cyan
        cout << "=========================================\n";
        setColor(12); // Red
        cout << "GRAND TOTAL: Rs." << total << endl;
        setColor(10); // Green
        cout << "Thank you for your order!\n";
        setColor(11); // Cyan
        cout << "=========================================\n";
        setColor(15); // White
        cout << "Press any key to continue...";
        _getch();
        cart.clear();
    }
};

// ==================== OWNER CLASS ====================
class Owner : public User {
    vector<FoodItem>& menu;

public:
    Owner(vector<FoodItem>& m) : menu(m) {}

    void showMenu() override {
        clearScreen();
        printHeader();
        setColor(12); // Red
        cout << "            OWNER MENU\n";
        cout << "=========================================\n";
        setColor(15); // White
        cout << "1. View Menu\n";
        cout << "2. Add Item\n";
        cout << "3. Remove Item\n";
        cout << "0. Exit\n";
        cout << "=========================================\n";
        cout << "Select option: ";
    }

    void viewMenu() {
        clearScreen();
        printHeader();
        setColor(14); // Yellow
        cout << "            CURRENT MENU\n";
        cout << "=========================================\n";
        setColor(15); // White;

        // Group by category
        map<string, vector<FoodItem>> categories;
        for (const auto& item : menu) {
            categories[item.category].push_back(item);
        }

        for (const auto& cat : categories) {
            setColor(13); // Magenta
            cout << "\n--- " << cat.first << " ---\n";
            setColor(15); // White

            for (size_t i = 0; i < cat.second.size(); i++) {
                cout << "  " << i + 1 << ". " << setw(20) << left << cat.second[i].name
                    << " - Rs." << cat.second[i].price << endl;
            }
        }

        setColor(11); // Cyan
        cout << "\n=========================================\n";
        setColor(15); // White
        cout << "Press any key to continue...";
        _getch();
    }


    void addItem() {
        clearScreen();
        printHeader();
        setColor(10); // Green
        cout << "            ADD ITEM\n";
        cout << "=========================================\n";
        setColor(15); // White;

        string name, category;
        double price;

        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, name);

        // Show available categories and let user choose
        setColor(14); // Yellow
        cout << "\nAvailable Categories:\n";
        cout << "1. Burgers\n";
        cout << "2. Drinks\n";
        cout << "3. Sides\n";
        cout << "4. Desserts\n";
        cout << "5. Main Course\n";
        cout << "6. New Category\n";
        setColor(15); // White;

        int catChoice;
        cout << "Select category (1-6): ";
        cin >> catChoice;

        switch (catChoice) {
        case 1: category = "Burgers"; break;
        case 2: category = "Drinks"; break;
        case 3: category = "Sides"; break;
        case 4: category = "Desserts"; break;
        case 5: category = "Main Course"; break;
        case 6:
            cout << "Enter new category name: ";
            cin.ignore();
            getline(cin, category);
            break;
        default:
            cout << "Invalid choice! Using 'Other' category.\n";
            category = "Other";
            Sleep(1000);
        }

        cout << "Enter price: ";
        cin >> price;

        menu.push_back(FoodItem(name, price, category));
        setColor(10); // Green
        cout << "\n" << name << " added to " << category << " category successfully!\n";
        setColor(15); // White;
        Sleep(2000);
    }


    void removeItem() {
        clearScreen();
        printHeader();
        setColor(12); // Red
        cout << "           REMOVE ITEM\n";
        cout << "=========================================\n";
        setColor(15); // White;

        if (menu.empty()) {
            setColor(12); // Red
            cout << "Menu is already empty!\n";
            setColor(15); // White;
            Sleep(1000);
            return;
        }

        // Display menu with ORIGINAL numbering
        for (size_t i = 0; i < menu.size(); i++) {
            cout << i + 1 << ". " << setw(20) << left << menu[i].name
                << " - Rs." << menu[i].price << " (" << menu[i].category << ")" << endl;
        }

        int choice;
        cout << "=========================================\n";
        cout << "Enter item number to remove (0 to cancel): ";
        cin >> choice;

        if (choice > 0 && choice <= menu.size()) {
            setColor(12); // Red
            cout << "Removed: " << menu[choice - 1].name << endl;
            setColor(15); // White;
            menu.erase(menu.begin() + choice - 1);
            Sleep(1000);
        }
    }
};

// ==================== MAIN FUNCTION ====================
int main() {
    vector<FoodItem> menu = {
        FoodItem("Zinger Burger", 350, "Burgers"),
        FoodItem("Cheese Burger", 300, "Burgers"),
        FoodItem("French Fries", 150, "Sides"),
        FoodItem("Onion Rings", 180, "Sides"),
        FoodItem("Cold Drink", 100, "Drinks"),
        FoodItem("Fresh Juice", 150, "Drinks"),
        FoodItem("Pizza", 800, "Main Course"),
         FoodItem("Biryani", 200, "Main Course"),
        FoodItem("Ice Cream", 200, "Desserts"),
        FoodItem("Chocolate Cake", 250, "Desserts")
    };

    Customer customer;
    Owner owner(menu);
    User* currentUser = nullptr;

    int roleChoice;
    do {
        clearScreen();
        printHeader();
        setColor(15); // White
        cout << "1. Customer Login\n";
        cout << "2. Owner Login\n";
        cout << "0. Exit\n";
        cout << "=========================================\n";
        cout << "Select role: ";
        cin >> roleChoice;

        if (roleChoice == 1) currentUser = &customer;
        else if (roleChoice == 2) currentUser = &owner;
        else if (roleChoice == 0) break;
        else continue;

        int choice;
        do {
            currentUser->showMenu();
            cin >> choice;

            if (roleChoice == 1) { // Customer
                switch (choice) {
                case 1: customer.viewMenu(menu); break;
                case 2: customer.placeOrder(menu); break;
                case 3: customer.viewCart(); break;
                case 4: customer.checkout(); break;
                case 0: break;
                default: cout << "Invalid choice!\n"; Sleep(1000);
                }
            }
            else if (roleChoice == 2) { // Owner
                switch (choice) {
                case 1: owner.viewMenu(); break;
                case 2: owner.addItem(); break;
                case 3: owner.removeItem(); break;
                case 0: break;
                default: cout << "Invalid choice!\n"; Sleep(1000);
                }
            }
        } while (choice != 0);

    } while (roleChoice != 0);

    setColor(10); // Green
    cout << "Thank you for using CafeFlow OS!\n";
    setColor(15); // White
    return 0;
}