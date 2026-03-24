#include <vector>
#include <stdexcept>
#include <iostream>
#include "CSVReader.h"

CSVReader::CSVReader(const std::string &filename)
    : filename(filename)
{
}

std::vector<std::string> CSVReader::tokenize(const std::string &line, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(line);

    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<OrderData> CSVReader::readOrders()
{
    std::vector<OrderData> orders;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::vector<std::string> tokens = tokenize(line, ',');

        OrderData orderdata;
        orderdata.isValid = true;

        if (tokens.size() != 5)
        {
            OrderData orderdata;
            orderdata.isValid = false;
            orderdata.rejectReason = "Invalid number of fields";
            orders.push_back(orderdata);
            continue;
        }

        orderdata.clientOrderId = tokens[0];
        orderdata.instrument = tokens[1];

        orderdata.side = tokens[2];
        orderdata.price = tokens[3];
        orderdata.quantity = tokens[4];

        orders.push_back(orderdata);
    }

    file.close();
    return orders;
}