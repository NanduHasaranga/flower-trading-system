#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include "OrderBookSide.h"
#include "ExecutionReport.h"

class OrderBook
{
private:
    static long nextOrderId;
    OrderBookSide<SellComparator> sellOrders;
    OrderBookSide<BuyComparator> buyOrders;
    std::string generateOrderId();

public:
    OrderBook() = default;
    std::vector<ExecutionReport> processOrder(const Order &order);
};

#endif