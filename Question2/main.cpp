#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <ctime>
#include "Product.h"
#include "User.h"
#include "Order.h"
#include "ShoppingCart.h"
#include "RecommendationEngine.h"
#include "DataManager.h"

using namespace std;

// ─────────────────────────────────────────────
//  Helper utilities
// ─────────────────────────────────────────────

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Product *findProductById(vector<Product> &products, int id)
{
    for (auto &p : products)
        if (p.getId() == id)
            return &p;
    return nullptr;
}

User *findUserById(vector<User> &users, int id)
{
    for (auto &u : users)
        if (u.getId() == id)
            return &u;
    return nullptr;
}

// ─────────────────────────────────────────────
//  Display helpers
// ─────────────────────────────────────────────

void printSeparator()
{
    cout << "========================================" << endl;
}

void displayAllProducts(const vector<Product> &products)
{
    if (products.empty())
    {
        cout << "No products available." << endl;
        return;
    }
    printSeparator();
    cout << "  PRODUCT LIST" << endl;
    printSeparator();
    for (const auto &p : products)
    {
        cout << "[" << p.getId() << "] " << p.getName()
             << " | " << p.getCategory()
             << " | $" << p.getPrice()
             << " | Views: " << p.getViewCount()
             << " | Purchases: " << p.getPurchaseCount() << endl;
    }
    printSeparator();
}

// ─────────────────────────────────────────────
//  Customer menu
// ─────────────────────────────────────────────

void customerMenu(User &user, vector<Product> &products, vector<Order> &orders, int &nextOrderID)
{
    ShoppingCart cart;
    RecommendationEngine engine;
    int choice;

    do
    {
        printSeparator();
        cout << "  CUSTOMER MENU  [" << user.getName() << "]" << endl;
        printSeparator();
        cout << "1. Browse products" << endl;
        cout << "2. View product detail (increments view count)" << endl;
        cout << "3. Add item to cart" << endl;
        cout << "4. Remove item from cart" << endl;
        cout << "5. Update item quantity in cart" << endl;
        cout << "6. View cart" << endl;
        cout << "7. Checkout" << endl;
        cout << "8. View my order history" << endl;
        cout << "9. Get recommendations" << endl;
        cout << "0. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1)
        {
            // Browse products
            displayAllProducts(products);
        }
        else if (choice == 2)
        {
            // View product detail
            displayAllProducts(products);
            cout << "Enter product ID to view: ";
            int pid;
            cin >> pid;
            clearInput();
            Product *p = findProductById(products, pid);
            if (!p)
            {
                cout << "Product not found." << endl;
                continue;
            }
            p->incrementView();
            user.addToViewHistory(pid);
            cout << endl;
            p->display();
            DataManager::saveProducts(products);
        }
        else if (choice == 3)
        {
            // Add to cart
            displayAllProducts(products);
            cout << "Enter product ID: ";
            int pid;
            cin >> pid;
            clearInput();
            if (!findProductById(products, pid))
            {
                cout << "Product not found." << endl;
                continue;
            }
            cout << "Enter quantity: ";
            int qty;
            cin >> qty;
            clearInput();
            cart.addItem(pid, qty);
            cout << "Added to cart." << endl;
        }
        else if (choice == 4)
        {
            // Remove from cart
            cart.display();
            cout << "Enter product ID to remove: ";
            int pid;
            cin >> pid;
            clearInput();
            cart.removeItem(pid);
        }
        else if (choice == 5)
        {
            // Update quantity
            cart.display();
            cout << "Enter product ID: ";
            int pid;
            cin >> pid;
            clearInput();
            cout << "Enter new quantity (0 to remove): ";
            int qty;
            cin >> qty;
            clearInput();
            cart.updateQuantity(pid, qty);
        }
        else if (choice == 6)
        {
            // View cart
            cart.display();
        }
        else if (choice == 7)
        {
            // Checkout
            if (cart.getItems().empty())
            {
                cout << "Cart is empty!" << endl;
                continue;
            }
            cart.display();
            cout << "Confirm checkout? (y/n): ";
            char c;
            cin >> c;
            clearInput();
            if (c != 'y' && c != 'Y')
                continue;

            // Create order
            Order order(products, nextOrderID++, user.getId(), cart.getItems(), time(0));
            orders.push_back(order);

            // Update purchase history & product purchase counts
            for (const auto &item : cart.getItems())
            {
                user.addToPurchaseHistory(item.first);
                Product *p = findProductById(products, item.first);
                if (p)
                {
                    for (int i = 0; i < item.second; i++)
                        p->incrementPurchase();
                }
            }
            DataManager::saveProducts(products);
            cart.clear();

            cout << endl
                 << "  Order placed successfully!" << endl;
            order.display();
        }
        else if (choice == 8)
        {
            // Order history
            printSeparator();
            cout << "  ORDER HISTORY for " << user.getName() << endl;
            printSeparator();
            bool found = false;
            for (auto &o : orders)
            {
                if (o.getUserID() == user.getId())
                {
                    o.display();
                    printSeparator();
                    found = true;
                }
            }
            if (!found)
                cout << "No orders found." << endl;
        }
        else if (choice == 9)
        {
            // Recommendations
            cout << "How many recommendations? ";
            int n;
            cin >> n;
            clearInput();
            vector<Product> recs = engine.recommend(user, products, n);
            if (recs.empty())
            {
                cout << "No recommendations available." << endl;
            }
            else
            {
                printSeparator();
                cout << "  TOP " << n << " RECOMMENDATIONS" << endl;
                printSeparator();
                for (auto &p : recs)
                    p.display(), cout << "---" << endl;
            }
        }
        else if (choice != 0)
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 0);
}

// ─────────────────────────────────────────────
//  Admin menu
// ─────────────────────────────────────────────

void adminMenu(vector<Product> &products, vector<Order> &orders, vector<User> &users, int &nextProductID)
{
    int choice;

    do
    {
        printSeparator();
        cout << "  ADMIN MENU" << endl;
        printSeparator();
        cout << "1. View all products" << endl;
        cout << "2. Add product" << endl;
        cout << "3. Edit product" << endl;
        cout << "4. Delete product" << endl;
        cout << "5. View most viewed products" << endl;
        cout << "6. View best-selling products" << endl;
        cout << "7. View active users (purchase history)" << endl;
        cout << "0. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1)
        {
            displayAllProducts(products);
        }
        else if (choice == 2)
        {
            // Add product
            cout << "Name: ";
            string name;
            getline(cin, name);
            cout << "Category: ";
            string cat;
            getline(cin, cat);
            cout << "Price: $";
            double price;
            cin >> price;
            clearInput();
            products.push_back(Product(nextProductID++, name, cat, price));
            DataManager::saveProducts(products);
            cout << "Product added." << endl;
        }
        else if (choice == 3)
        {
            // Edit product
            displayAllProducts(products);
            cout << "Enter product ID to edit: ";
            int pid;
            cin >> pid;
            clearInput();
            Product *p = findProductById(products, pid);
            if (!p)
            {
                cout << "Product not found." << endl;
                continue;
            }

            cout << "New name (leave blank to keep [" << p->getName() << "]): ";
            string name;
            getline(cin, name);
            if (!name.empty())
                p->setName(name);

            cout << "New category (leave blank to keep [" << p->getCategory() << "]): ";
            string cat;
            getline(cin, cat);
            if (!cat.empty())
                p->setCategory(cat);

            cout << "New price (enter -1 to keep [" << p->getPrice() << "]): ";
            double pr;
            cin >> pr;
            clearInput();
            if (pr >= 0)
                p->setPrice(pr);

            DataManager::saveProducts(products);
            cout << "Product updated." << endl;
        }
        else if (choice == 4)
        {
            // Delete product
            displayAllProducts(products);
            cout << "Enter product ID to delete: ";
            int pid;
            cin >> pid;
            clearInput();
            auto it = products.begin();
            bool found = false;
            while (it != products.end())
            {
                if (it->getId() == pid)
                {
                    it = products.erase(it);
                    found = true;
                    break;
                }
                else
                    ++it;
            }
            if (found)
            {
                DataManager::saveProducts(products);
                cout << "Product deleted." << endl;
            }
            else
                cout << "Product not found." << endl;
        }
        else if (choice == 5)
        {
            // Most viewed
            vector<Product> sorted = products;
            for (int i = 0; i < (int)sorted.size() - 1; i++)
                for (int j = i + 1; j < (int)sorted.size(); j++)
                    if (sorted[j].getViewCount() > sorted[i].getViewCount())
                        swap(sorted[i], sorted[j]);
            printSeparator();
            cout << "  MOST VIEWED PRODUCTS" << endl;
            printSeparator();
            for (int i = 0; i < min(5, (int)sorted.size()); i++)
            {
                cout << (i + 1) << ". [" << sorted[i].getId() << "] "
                     << sorted[i].getName() << " - Views: " << sorted[i].getViewCount() << endl;
            }
        }
        else if (choice == 6)
        {
            // Best selling
            vector<Product> sorted = products;
            for (int i = 0; i < (int)sorted.size() - 1; i++)
                for (int j = i + 1; j < (int)sorted.size(); j++)
                    if (sorted[j].getPurchaseCount() > sorted[i].getPurchaseCount())
                        swap(sorted[i], sorted[j]);
            printSeparator();
            cout << "  BEST-SELLING PRODUCTS" << endl;
            printSeparator();
            for (int i = 0; i < min(5, (int)sorted.size()); i++)
            {
                cout << (i + 1) << ". [" << sorted[i].getId() << "] "
                     << sorted[i].getName() << " - Purchases: " << sorted[i].getPurchaseCount() << endl;
            }
        }
        else if (choice == 7)
        {
            // Active users
            printSeparator();
            cout << "  ACTIVE USERS" << endl;
            printSeparator();
            for (auto &u : users)
            {
                if (!u.getPurchaseHistory().empty())
                {
                    cout << "User [" << u.getId() << "] " << u.getName()
                         << " - Purchases: " << u.getPurchaseHistory().size() << " product(s)" << endl;
                }
            }
        }
        else if (choice != 0)
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 0);
}

// ─────────────────────────────────────────────
//  Main
// ─────────────────────────────────────────────

int main()
{
    // Load products from file
    vector<Product> products = DataManager::loadProduct();

    // Seed products if file was empty
    if (products.empty())
    {
        products.push_back(Product(1, "Laptop Pro 15", "Electronics", 1299.99));
        products.push_back(Product(2, "Wireless Mouse", "Electronics", 29.99));
        products.push_back(Product(3, "Running Shoes", "Sports", 89.99));
        products.push_back(Product(4, "Python Book", "Books", 39.99));
        products.push_back(Product(5, "Coffee Maker", "Kitchen", 59.99));
        products.push_back(Product(6, "Yoga Mat", "Sports", 25.99));
        products.push_back(Product(7, "Noise Headphones", "Electronics", 199.99));
        products.push_back(Product(8, "C++ Book", "Books", 44.99));
        DataManager::saveProducts(products);
    }
    int nextProductID = 0;
    for (const auto &p : products)
        if (p.getId() >= nextProductID)
            nextProductID = p.getId() + 1;

    // Seed users
    vector<User> users;
    users.push_back(User(1, "Alice"));
    users.push_back(User(2, "Bob"));
    users.push_back(User(3, "Admin")); // admin placeholder

    vector<Order> orders;
    int nextOrderID = 1;

    cout << endl;
    printSeparator();
    cout << "  SMART E-COMMERCE SYSTEM" << endl;
    printSeparator();

    int mainChoice;
    do
    {
        cout << endl;
        cout << "1. Login as Customer" << endl;
        cout << "2. Login as Admin" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> mainChoice;
        clearInput();

        if (mainChoice == 1)
        {
            // Customer login
            cout << "Available users:" << endl;
            for (auto &u : users)
                if (u.getId() != 3) // skip admin slot
                    cout << "  [" << u.getId() << "] " << u.getName() << endl;
            cout << "Enter your User ID (or 0 to create new): ";
            int uid;
            cin >> uid;
            clearInput();

            if (uid == 0)
            {
                cout << "Enter your name: ";
                string uname;
                getline(cin, uname);
                int newId = (int)users.size() + 1;
                users.push_back(User(newId, uname));
                uid = newId;
                cout << "Account created! Your ID is " << uid << endl;
            }

            User *u = findUserById(users, uid);
            if (!u)
            {
                cout << "User not found." << endl;
                continue;
            }
            customerMenu(*u, products, orders, nextOrderID);
        }
        else if (mainChoice == 2)
        {
            // Admin login (simple password)
            cout << "Enter admin password: ";
            string pw;
            getline(cin, pw);
            if (pw != "admin123")
            {
                cout << "Wrong password." << endl;
                continue;
            }
            adminMenu(products, orders, users, nextProductID);
        }
        else if (mainChoice != 0)
        {
            cout << "Invalid choice." << endl;
        }

    } while (mainChoice != 0);

    cout << "Goodbye!" << endl;
    return 0;
}