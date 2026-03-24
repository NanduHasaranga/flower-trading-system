#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "Enums.h"

struct Order
{
    std::string clientOrderId;
    Instrument instrument;
    Side side;
    double price;
    int quantity;
};

#endif