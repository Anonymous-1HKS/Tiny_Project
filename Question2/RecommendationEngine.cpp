#include "RecommendationEngine.h"
#include <iostream>
#include <algorithm>
using namespace std;

double RecommendationEngine::calculateScore(Product p, User u, const vector<Product> &allProducts)
{
    double score = p.getViewCount() * 0.2 + p.getPurchaseCount() * 0.8;
    double category_bonus = 0.0;
    string category = p.getCategory();
    for (const auto &productID : u.getPurchaseHistory())
    {
        for (const auto &product : allProducts)
        {
            if (product.getId() == productID && product.getCategory() == category)
            {
                category_bonus = 1.0;
                break;
            }
        }
        if (category_bonus > 0)
            break;
    }
    return score + category_bonus;
}

vector<Product> RecommendationEngine::recommend(User u, const vector<Product> &allProducts, int topN)
{
    vector<pair<Product, double>> scoredList;
    for (const auto &product : allProducts)
    {
        double score = calculateScore(product, u, allProducts);
        scoredList.push_back({product, score});
    }
    sort(scoredList.begin(), scoredList.end(), [](const pair<Product, double> &a, const pair<Product, double> &b)
         { return a.second > b.second; });
    vector<Product> recommendations;
    for (int i = 0; i < min(topN, (int)scoredList.size()); i++)
    {
        recommendations.push_back(scoredList[i].first);
    }
    return recommendations;
}