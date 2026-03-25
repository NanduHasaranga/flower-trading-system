#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <string>
#include "ExecutionReport.h"

class CSVWriter
{
private:
    std::string filename;
public:
    CSVWriter(const std::string& filename);
    void write(const ExecutionReport& report);
    void writeHeader();
};

#endif