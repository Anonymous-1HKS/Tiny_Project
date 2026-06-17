#include "Order.h"
#include <iostream>
using namespace std;
//Constructor
Order::Order(const vector<Product>& products, int orderID, int userID, map<int, int> items, time_t orderTime) 
    : orderID(orderID), userID(userID), items(items) {
    totalPrice = calculateTotalPrice(products);
    timestamp = ctime(&orderTime);
}
double Order::calculateTotalPrice(const vector<Product>& products) {
    double total = 0.0;
    for (const auto& item : items) {
        int productId = item.first;
        int quantity = item.second;
        for (const auto& product : products) {
            if (product.getId() == productId) {
                total += product.getPrice() * quantity;
                break;
            }
        }
    }
    return total;
}
//Getters
int Order::getOrderID() {
    return orderID;
}
int Order::getUserID() {
    return userID;
}
map<int, int> Order::getItems() {
    return items;
}
double Order::getTotalPrice() {
    return totalPrice;
}
string Order::getTimestamp() {
    return timestamp;
}
void Order::display() {
    cout << "Order ID: " << orderID << endl;
    cout << "User ID: " << userID << endl;
    cout << "Items:" << endl;
    for (const auto& item : items) {
        cout << "  Product ID: " << item.first << ", Quantity: " << item.second << endl;
    }
    cout << "Total Price: $" << totalPrice << endl;
    cout << "Timestamp: " << timestamp;
}