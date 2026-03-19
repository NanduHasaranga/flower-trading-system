#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include "OrderBookSide.h"
#include "ExecutionReport.h"

class OrderBook
{
private:
    OrderBookSide<SellComparator> sellOrders;
    OrderBookSide<BuyComparator> buyOrders;
public:
    OrderBook() = default;
    std::vector<ExecutionReport> processOrder(const Order& order);
};

#endif