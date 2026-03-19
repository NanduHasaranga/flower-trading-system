#ifndef ORDERBOOKSIDE_H
#define ORDERBOOKSIDE_H

#include <map>
#include <deque>
#include "order.h"

struct BuyComparator
{
    bool operator()(double a, double b) const
    {
        return a > b; // highest first
    }
};

struct SellComparator
{
    bool operator()(double a, double b) const
    {
        return a < b; // lowest first
    }
};

template <typename Comparator>
class OrderBookSide
{
private:
    std::map<double, std::deque<Order>, Comparator> orders;

public:
    OrderBookSide() : orders(Comparator{}) {};

    void insertOrder(const Order &order)
    {
        orders[order.price].push_back(order);
    }

    const Order &getBestOrder() const
    {
        if (orders.empty())
        {
            throw std::runtime_error("OrderBook is empty");
        }
        return orders.begin()->second.front();
    }

    void removeTopOrder()
    {
        if (orders.empty())
            return;

        auto &bestLevelQueue = orders.begin()->second;

        bestLevelQueue.pop_front();

        if (bestLevelQueue.empty())
        {
            orders.erase(orders.begin());
        }
    }

    void updateTopOrderQuantity(int newQty)
    {
        orders.begin()->second.front().quantity = newQty;
    }

    bool isEmpty() const
    {
        return orders.empty();
    }
};

#endif