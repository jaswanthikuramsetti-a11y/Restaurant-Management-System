#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

struct Order
{
    string item;
    int quantity;
    double price;
};

class Restaurant
{
private:
    vector<Order> orders;

    bool readInteger(int &value)
    {
        if (cin >> value)
            return true;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

public:
    void displayMenu()
    {
        cout << "\n===== RESTAURANT MENU =====\n";
        cout << "1. Burger      - Rs.120\n";
        cout << "2. Pizza       - Rs.200\n";
        cout << "3. Biryani     - Rs.180\n";
        cout << "4. Fried Rice  - Rs.150\n";
        cout << "5. Noodles     - Rs.130\n";
        cout << "6. Chicken 65  - Rs.250\n";
    }

    void addItem()
    {
        if (orders.size() >= 4)
        {
            cout << "Maximum 4 food entries allowed!\n";
            return;
        }

        displayMenu();

        int choice, quantity;

        cout << "Enter food choice: ";
        if (!readInteger(choice))
        {
            cout << "Invalid input! Enter a number.\n";
            return;
        }

        if (choice < 1 || choice > 6)
        {
            cout << "Invalid food choice!\n";
            return;
        }

        cout << "Enter quantity: ";
        if (!readInteger(quantity) || quantity <= 0)
        {
            cout << "Invalid quantity!\n";
            return;
        }

        Order o;

        switch (choice)
        {
            case 1:
                o.item = "Burger";
                o.price = 120;
                break;

            case 2:
                o.item = "Pizza";
                o.price = 200;
                break;

            case 3:
                o.item = "Biryani";
                o.price = 180;
                break;

            case 4:
                o.item = "Fried Rice";
                o.price = 150;
                break;

            case 5:
                o.item = "Noodles";
                o.price = 130;
                break;

            case 6:
                o.item = "Chicken 65";
                o.price = 250;
                break;
        }

        o.quantity = quantity;
        orders.push_back(o);

        cout << o.item << " added successfully!\n";
    }

    void viewOrder()
    {
        if (orders.empty())
        {
            cout << "No items in the order!\n";
            return;
        }

        cout << "\n========== YOUR ORDER ==========\n";
        cout << left << setw(15) << "Item"
             << setw(10) << "Quantity"
             << setw(12) << "Price"
             << "Amount\n";

        double total = 0;

        for (size_t i = 0; i < orders.size(); i++)
        {
            double amount =
                orders[i].quantity * orders[i].price;

            cout << left << setw(15) << orders[i].item
                 << setw(10) << orders[i].quantity
                 << setw(12) << orders[i].price
                 << amount << '\n';

            total += amount;
        }

        cout << "Total: Rs. " << fixed << setprecision(2)
             << total << '\n';
    }

    void removeItem()
    {
        if (orders.empty())
        {
            cout << "No items to remove!\n";
            return;
        }

        viewOrder();

        int number;
        cout << "Enter item number to remove (1-"
             << orders.size() << "): ";

        if (!readInteger(number))
        {
            cout << "Invalid input!\n";
            return;
        }

        if (number < 1 ||
            number > static_cast<int>(orders.size()))
        {
            cout << "Invalid item number!\n";
            return;
        }

        orders.erase(orders.begin() + number - 1);
        cout << "Item removed successfully!\n";
    }

    void calculateBill()
    {
        double total = 0;

        for (size_t i = 0; i < orders.size(); i++)
        {
            total += orders[i].quantity * orders[i].price;
        }

        cout << fixed << setprecision(2);
        cout << "\nTotal Bill: Rs. " << total << '\n';
    }

    void saveOrder(int orderID)
    {
        if (orders.empty())
        {
            cout << "No items to save!\n";
            return;
        }

        ofstream file("orders.csv", ios::app);

        if (!file)
        {
            cout << "Error opening file!\n";
            return;
        }

        for (size_t i = 0; i < orders.size(); i++)
        {
            file << orderID << ","
                 << orders[i].item << ","
                 << orders[i].quantity << ","
                 << orders[i].price << '\n';
        }

        file.close();
        cout << "Order saved successfully!\n";
    }

    void cancelOrder()
    {
        if (orders.empty())
        {
            cout << "No current order to cancel!\n";
            return;
        }

        char confirm;
        cout << "Are you sure you want to cancel? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y')
        {
            orders.clear();
            cout << "Current order cancelled!\n";
        }
        else
        {
            cout << "Cancellation stopped.\n";
        }
    }
};

int main()
{
    Restaurant restaurant;
    int orderID, choice;

    cout << "Enter Order ID: ";

    if (!(cin >> orderID))
    {
        cout << "Invalid Order ID!\n";
        return 1;
    }

    do
    {
        cout << "\n===== RESTAURANT MANAGEMENT SYSTEM =====\n";
        cout << "1. View Menu\n";
        cout << "2. Add Item\n";
        cout << "3. Remove Item\n";
        cout << "4. View Order\n";
        cout << "5. Calculate Bill\n";
        cout << "6. Save Order\n";
        cout << "7. Cancel Order\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );

            cout << "Invalid choice! Enter a number.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                restaurant.displayMenu();
                break;

            case 2:
                restaurant.addItem();
                break;

            case 3:
                restaurant.removeItem();
                break;

            case 4:
                restaurant.viewOrder();
                break;

            case 5:
                restaurant.calculateBill();
                break;

            case 6:
                restaurant.saveOrder(orderID);
                break;

            case 7:
                restaurant.cancelOrder();
                break;

            case 8:
                cout << "Thank you! Visit again.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
