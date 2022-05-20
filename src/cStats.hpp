#include <string>
#include <memory>
#include "cCpuStats.hpp"

/**
 * @file cStats.hpp
 * @author your name (you@domain.com)
 * @brief holds the stats classes. The class's basic objective is to return the specific statistics it's 
 *        observing
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief virtual interface class for statistics.
 *        The class will hold and provide certain pc stats read from the OS
 * 
 */
class IStats
{
private:
    /* data */
public:
    IStats(/* args */){}
    ~IStats(){}

    virtual std::string getStats() = 0;
};

 class cCPUStats : public IStats
 {
 private:
    /* data */
 public:
    cCPUStats(/* args */){}
    ~cCPUStats(){}

    std::string getStats() override
    {
        //TODO: Place holder for now, retrun proper statistic later
        return "CPU usage: No. of Processes: ";
    }

 };
 


 /**
  * @brief Wrapper or Decorator class for stats allowing changing the provide stats dynamically.
  * 
  */

class IStatsWrapper : public IStats
{
protected:
    std::shared_ptr<IStats> oStatObj;
public:
    IStatsWrapper(std::shared_ptr<IStats> pSource)
    {
        oStatObj = pSource;

    }
    ~IStatsWrapper(){}
};

class cRamWrapper : public IStatsWrapper
{
private:
    /* data */
public:
    cRamWrapper(std::shared_ptr<IStats> pSource)
    : IStatsWrapper(pSource)
    {}
    ~cRamWrapper(){}

    std::string getStats() override
    {
        return oStatObj->getStats() + " RAM usage: ";
    }
};


