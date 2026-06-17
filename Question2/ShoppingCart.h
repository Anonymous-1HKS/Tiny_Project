#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <map>

class ShoppingCart {
private:
    std::map<int, int> items;   // productId → quantity

public:
    void addItem(int productId, int qty);
    void removeItem(int productId);
    void updateQuantity(int productId, int qty);
    std::map<int, int> getItems();
    bool isEmpty();
    void clear();
    void display();
};

#endif  // SHOPPINGCART_H