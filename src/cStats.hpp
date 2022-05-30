#include <string>
#include <memory>
#include "cCpuStats.hpp"

/**
 * @file cStats.hpp
 * @author lmengnr
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
    cCpuStatObserver m_oCpuStats;
 public:
    cCPUStats(/* args */)
    {
        m_oCpuStats.StartReadThread();

    }
    ~cCPUStats(){}

    std::string getStats() override
    {
        //TODO: Place holder for now, retrun proper statistic later
        return "CPU usage: " + std::to_string(m_oCpuStats.GetCurrCpuUsage());
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
    double getRam()
    {
        std::ifstream filestat("/proc/meminfo");
        std::string stat_line;
        std::getline(filestat, stat_line);

        uint32_t nTotalMemory;
        std::string label;
        uint32_t nAvailableMem;

        std::stringstream ramStream;

        ramStream << stat_line;

        ramStream >> label;
        ramStream >> nTotalMemory;

        std::getline(filestat, stat_line);
        std::getline(filestat, stat_line);

        ramStream.clear();
        label.clear();
        ramStream << stat_line;
        ramStream >> label;
        ramStream >> nAvailableMem;

        return ((nTotalMemory - nAvailableMem)/(double)nTotalMemory) * 100;
    }
public:
    cRamWrapper(std::shared_ptr<IStats> pSource)
    : IStatsWrapper(pSource)
    {}
    ~cRamWrapper(){}

    std::string getStats() override
    {
        return oStatObj->getStats() + " RAM usage: " + std::to_string(getRam());
    }
};


