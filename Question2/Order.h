#ifndef ORDER_H
#define ORDER_H
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include "Product.h"
using namespace std;
class Order {
    private:
        int orderID;
        int userID;
        map<int, int> items; // productId → quantity
        double totalPrice;
        string timestamp; 
        double calculateTotalPrice(const vector<Product>& products);
        
    public:
        Order(const vector<Product>& products, int orderID, int userID, map<int, int> items, time_t orderTime = time(0));
        int getOrderID();
        int getUserID();
        map<int, int> getItems();
        double getTotalPrice();
        string getTimestamp();
        
        void display();
};
#endif // ORDER_H
