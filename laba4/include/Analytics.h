#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <vector>
#include "Pair.h"

class Analytics {
public:

    static std::vector<Pair<std::string, double>> getRevenueByProduct();


    static std::vector<Pair<std::string, int>> getTopSellingProducts(int limit = 3);


    static double getAverageOrderValue();


    static std::vector<Pair<std::string, int>> getOrderCountByProduct();


    static std::vector<Pair<std::string, double>> getDailyRevenue(const std::string& startDate,
                                                                 const std::string& endDate);
    static double getTotalRevenue();


    static bool exportReportToFile(const std::string& filename);
};

#endif