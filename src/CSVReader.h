#ifndef CSVREADER_H
#define CSVREADER_H

#include <fstream>
#include <sstream>
#include <vector>
#include "Order.h"

struct OrderData {
    std::string clientOrderId;
    std::string instrument;
    std::string side;     
    std::string price;
    std::string quantity;
    bool isValid;
    std::string rejectReason;
};

class CSVReader
{
private:
    std::string filename;
    std::vector<std::string> tokenize(const std::string& line, char delimiter);

public:
    CSVReader(const std::string &filename);
    std::vector<OrderData> readOrders();
};

#endif