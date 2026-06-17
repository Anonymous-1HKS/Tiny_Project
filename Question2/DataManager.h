#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <vector>
#include <string>
#include "Product.h"

class DataManager {
public:
    static void saveProducts (const vector<Product>& products);
    static vector <Product> loadProduct();
private:
    static const string PRODUCT_FILE; //products.txt
};

#endif