#include <vector>
#include "OrderBook.h"

long OrderBook::nextOrderId = 1;

std::string OrderBook::generateOrderId()
{
    return "ord" + std::to_string(nextOrderId++);
}

std::vector<ExecutionReport> OrderBook::processOrder(const Order &order)
{
    std::vector<ExecutionReport> reports;
    int remainingQty = order.quantity;
    if (order.side == Side::Buy)
    {
        while (!sellOrders.isEmpty() && sellOrders.getBestOrder().price <= order.price && remainingQty > 0)
        {
            // match
            Order sellOrder = sellOrders.getBestOrder();
            double execPrice = sellOrder.price;
            int execQty = std::min(sellOrder.quantity, remainingQty);

            reports.push_back(ExecutionReport(
                order.clientOrderId,
                generateOrderId(),
                order.instrument,
                order.side,
                execPrice,
                execQty,
                (remainingQty - execQty == 0) ? OrderStatus::Fill : OrderStatus::PFill));

            reports.push_back(ExecutionReport(
                sellOrder.clientOrderId,
                generateOrderId(),
                sellOrder.instrument,
                sellOrder.side,
                execPrice,
                execQty,
                (sellOrder.quantity - execQty == 0) ? OrderStatus::Fill : OrderStatus::PFill));

            remainingQty -= execQty;

            if (execQty == sellOrder.quantity)
                sellOrders.removeTopOrder();
            else
                sellOrders.updateTopOrderQuantity(sellOrder.quantity - execQty);
        }
        if (remainingQty > 0)
        {
            Order remainingOrder = order;
            remainingOrder.quantity = remainingQty;
            buyOrders.insertOrder(remainingOrder);

            reports.push_back(ExecutionReport(
                order.clientOrderId,
                generateOrderId(),
                order.instrument,
                order.side,
                order.price,
                remainingQty,
                OrderStatus::New));
        }
    }
    else
    {
        while (!buyOrders.isEmpty() && buyOrders.getBestOrder().price >= order.price && remainingQty > 0)
        {
            // match
            Order buyOrder = buyOrders.getBestOrder();
            double execPrice = buyOrder.price;
            int execQty = std::min(buyOrder.quantity, remainingQty);

            reports.push_back(ExecutionReport(
                order.clientOrderId,
                generateOrderId(),
                order.instrument,
                order.side,
                execPrice,
                execQty,
                (remainingQty - execQty == 0) ? OrderStatus::Fill : OrderStatus::PFill));

            reports.push_back(ExecutionReport(
                buyOrder.clientOrderId,
                generateOrderId(),
                buyOrder.instrument,
                buyOrder.side,
                execPrice,
                execQty,
                (buyOrder.quantity - execQty == 0) ? OrderStatus::Fill : OrderStatus::PFill));

            remainingQty -= execQty;

            if (execQty == buyOrder.quantity)
                buyOrders.removeTopOrder();
            else
                buyOrders.updateTopOrderQuantity(buyOrder.quantity - execQty);
        }
        if (remainingQty > 0)
        {
            Order remainingOrder = order;
            remainingOrder.quantity = remainingQty;
            sellOrders.insertOrder(remainingOrder);

            reports.push_back(ExecutionReport(
                order.clientOrderId,
                generateOrderId(),
                order.instrument,
                order.side,
                order.price,
                remainingQty,
                OrderStatus::New));
        }
    }
    return reports;
}
