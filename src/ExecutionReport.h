#ifndef EXECUTIONREPORT_H
#define EXECUTIONREPORT_H

#include <string>
#include "Enums.h"

struct ExecutionReport
{
    std::string clientOrderId;
    std::string orderId;
    Instrument instrument;
    Side side;
    double price;
    int quantity;
    OrderStatus status;
    std::string reason;
    std::string transactionTime; // Format: YYYYMMDD-HHMMSS.sss

    ExecutionReport() = default;

    ExecutionReport(
        const std::string &clientOrderId,
        const std::string &orderId,
        Instrument instrument,
        Side side,
        double price,
        int quantity,
        OrderStatus status) : clientOrderId(clientOrderId), orderId(orderId),
                              instrument(instrument), side(side), price(price),
                              quantity(quantity), status(status), reason(""), transactionTime("")
    {
    }
    ExecutionReport(
        const std::string &clientOrderId,
        const std::string &orderId,
        Instrument instrument,
        Side side,
        double price,
        int quantity,
        const std::string &rejectReason) : clientOrderId(clientOrderId), orderId(orderId),
                                           instrument(instrument), side(side), price(price),
                                           quantity(quantity), status(OrderStatus::Rejected),
                                           reason(rejectReason), transactionTime("")
    {
    }
};

#endif