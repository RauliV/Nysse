#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "interfaces/istatistics.hh"

class statistics : public Interface::IStatistics
{
public:
    statistics();

    void startTimer();

    void stopTimer();


};

#endif // STATISTICS_HH
