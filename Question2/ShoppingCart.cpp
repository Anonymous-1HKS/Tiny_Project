#include "ShoppingCart.h"
#include <iostream>
using namespace std;
void ShoppingCart::addItem(int productID, int qty)
{
    if (qty <= 0)
    {
        cout << "Quantity must be greater than 0." << endl;
        return;
    }
    items[productID] += qty; // If productID doesn't exist, it will be created with initial value 0
}
void ShoppingCart::removeItem(int productID)
{
    if (items.find(productID) != items.end())
    {
        items.erase(productID);
    }
    else
    {
        cout << "Product ID " << productID << " not found in cart." << endl;
    }
}
void ShoppingCart::updateQuantity(int productID, int qty)
{
    if (items.find(productID) == items.end())
    {
        cout << "Product ID " << productID << " not found in cart." << endl;
        return;
    }
    if (qty <= 0)
    {
        removeItem(productID);
    }
    else
    {
        items[productID] = qty;
    }
}
bool ShoppingCart::isEmpty()
{
    return items.empty();
}
void ShoppingCart::clear()
{
    items.clear();
}
void ShoppingCart::display()
{
    if (items.empty())
    {
        cout << "Shopping cart is empty." << endl;
        return;
    }
    cout << "Shopping Cart:" << endl;
    for (const auto &item : items)
    {
        cout << "Product ID: " << item.first << ", Quantity: " << item.second << endl;
    }
}
std::map<int, int> ShoppingCart::getItems()
{
    return items;
}