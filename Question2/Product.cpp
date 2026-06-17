#include "Product.h"
#include <iostream>
using namespace std;

Product::Product(int id, string name, string category, double price)
    : id(id), name(name), category(category), price(price), viewCount(0), purchaseCount(0) {}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getViewCount() const { return viewCount; }
int Product::getPurchaseCount() const { return purchaseCount; }

void Product::setName(string name) { this->name = name; }
void Product::setCategory(string category) { this->category = category; }
void Product::setPrice(double price) { this->price = price; }
void Product::setViewCount(int v) { viewCount = v; }
void Product::setPurchaseCount(int p) { purchaseCount = p; }

void Product::incrementView() { viewCount++; }
void Product::incrementPurchase() { purchaseCount++; }

void Product::display() const {
    cout << "ID: "       << id            << endl;
    cout << "Name: "     << name          << endl;
    cout << "Category: " << category      << endl;
    cout << "Price: "    << price         << endl;
    cout << "View: "     << viewCount     << endl;
    cout << "Purchase: " << purchaseCount << endl;
}