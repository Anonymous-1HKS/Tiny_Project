#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include "DataManager.h"
const string DataManager::PRODUCT_FILE = "products.txt";
void DataManager:: saveProducts(const vector<Product>& products) {
    ofstream outFile(PRODUCT_FILE);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    for (const auto& product : products) {
        outFile << product.getId() << "|" 
                << product.getName() << "|" 
                << product.getCategory() << "|" 
                << product.getPrice() << "|" 
                << product.getViewCount() << "|" 
                << product.getPurchaseCount() << endl;
    }
    outFile.close();
    
};
vector<Product> DataManager::loadProduct(){
    ifstream inFile(PRODUCT_FILE);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return vector<Product>();
    }
    vector<Product> result;
    string line;
    
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        getline(ss, token, '|'); int id = stoi(token);
        getline(ss, token, '|'); string name = token;
        getline(ss, token, '|'); string category = token;
        getline(ss, token, '|'); double price = stod(token);
        getline(ss, token, '|'); int viewCount = stoi(token);
        getline(ss, token, '|'); int purchaseCount = stoi(token);

        Product product(id, name, category, price);
        product.setViewCount(viewCount);
        product.setPurchaseCount(purchaseCount);
        result.push_back(product);
    }
    inFile.close();
    return result;
}

