#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H
#include <vector>

#include "Product.h"
#include "User.h"
#include <vector>
#include <map>
using namespace std;
class RecommendationEngine {
public:
    vector<Product> recommend(User u, const vector<Product>& allProducts, int topN);
    double calculateScore(Product p, User u, const vector<Product>& allProducts);
};
#endif // RECOMMENDATIONENGINE_H 
