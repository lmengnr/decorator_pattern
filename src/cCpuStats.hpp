#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>

///////////////////////////////////////////////////////////////////////////////
/////////////// CLASS DECLARATION /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/**
 * @brief This is a class to read and calculate the cpu usage statistics
*/
class cCpuStats
{
private:
  /// For calculating the CPU percentage
  uint32_t lastTotalUser = 0;
  uint32_t lastTotalUserLow = 0;
  uint32_t lastTotalSys = 0;
  uint32_t lastTotalIdle = 0;

  double m_currCpuUsage = 0.0;

  /// Thread stuff
  std::shared_ptr<std::thread> m_statThread;
  std::mutex m_statMutex;

  void UpdateCpuUsage();

  void LaunchObserver();

  
public:
  cCpuStats(/* args */);
  ~cCpuStats();

  void StartReadThread();

  inline double GetCurrCpuUsage()
  {
    return m_currCpuUsage;
  }

};

///////////////////////////////////////////////////////////////////////////////
////////////////////// METHOD DEFINITIONS /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

cCpuStats::cCpuStats(/* args */)
{

}

cCpuStats::~cCpuStats()
{
  m_statThread->join();
}

///////////////////////////////////////////////////////////////////////////////
void cCpuStats::UpdateCpuUsage()
{
  u_int totalUser, totalUserLow, totalSys, totalIdle, total;
  double percent;

  std::ifstream filestat("/proc/stat");
  std::string stat_line;
  std::getline(filestat, stat_line);

  std::string stat_line2 = stat_line.substr(5, stat_line.find(" 0 0"));

  std::stringstream statstream;
  statstream << stat_line2;

  statstream >> totalUser;
  statstream >> totalUserLow;
  statstream >> totalSys;
  statstream >> totalIdle;
  statstream >> total;

  if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
      totalSys < lastTotalSys || totalIdle < lastTotalIdle)
  {
    // Overflow detection. Just skip this value.
    percent = -1.0;
  }
  else
  {
    total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
    percent = total;
    total += (totalIdle - lastTotalIdle);
    percent /= total;
    percent *= 100;
  }

  std::unique_lock<std::mutex> lock(m_statMutex);
  m_currCpuUsage = percent;
}

///////////////////////////////////////////////////////////////////////////////
void cCpuStats::StartReadThread()
{
  m_statThread = std::make_shared<std::thread>(std::thread(LaunchObserver));
}

///////////////////////////////////////////////////////////////////////////////
void cCpuStats::LaunchObserver()
{
  while(1)
  {
    UpdateCpuUsage();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}