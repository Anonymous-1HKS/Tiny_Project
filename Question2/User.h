#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;
class User {
private:
    int id;
    string name;
    vector<int> viewHistory;
    vector<int> purchaseHistory;

public:
    // Constructor
    User(int id, std::string name);

    // Getters
    int getId();
    string getName();
    vector<int> getViewHistory();
    vector<int> getPurchaseHistory();

    // Methods
    void addToViewHistory(int productId);
    void addToPurchaseHistory(int productId);
    bool hasPurchased(int productId);     
    bool hasViewed(int productId);        
    void display();
};

#endif