#include "User.h"
#include <iostream>
using namespace std;
User::User(int id, string name)
{
    this->id = id;
    this->name = name;
}

void User::addToViewHistory(int productId)
{
    if (!hasViewed(productId))
    {
        viewHistory.push_back(productId);
    }
}
void User::addToPurchaseHistory(int productId)
{
    if (!hasPurchased(productId))
    {
        purchaseHistory.push_back(productId);
    }
}
bool User::hasPurchased(int productID)
{
    for (int id : purchaseHistory)
    {
        if (id == productID)
        {
            return true;
        }
    }
    return false;
}
bool User::hasViewed(int productID)
{
    for (int id : viewHistory)
    {
        if (id == productID)
        {
            return true;
        }
    }
    return false;
}
int User::getId() { return id; }
string User::getName() { return name; }
vector<int> User::getViewHistory() { return viewHistory; }
vector<int> User::getPurchaseHistory() { return purchaseHistory; }
void User::display()
{
    cout << "User ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "View History: ";
    for (int id : viewHistory)
    {
        cout << id << " ";
    }
    cout << endl;
    cout << "Purchase History: ";
    for (int id : purchaseHistory)
    {
        cout << id << " ";
    }
    cout << endl;
}