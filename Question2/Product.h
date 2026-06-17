#pragma once
#include <string>
using namespace std;
class Product { 
private:
    int id;
    string name;
    string category;
    double price;
    int viewCount;
    int purchaseCount;
public:
    Product(int id, string name, string category, double price);
    int getId() const;
    string getName () const;
    string getCategory() const;
    double getPrice () const;
    int getViewCount() const;
    int getPurchaseCount() const;

    void setName(string name); 
    void setCategory(string category);
    void setPrice(double price);
    void setViewCount(int v);
    void setPurchaseCount(int p);
    
    void incrementView();
    void incrementPurchase();
    void display() const;
};
        