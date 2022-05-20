#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>


class cCpuStats
{
private:
  uint32_t lastTotalUser = 0;
  uint32_t lastTotalUserLow = 0;
  uint32_t lastTotalSys = 0;
  uint32_t lastTotalIdle = 0;

  std::thread statThread;

  
public:
  cCpuStats(/* args */);
  ~cCpuStats();

  double getCurrVal();

};

cCpuStats::cCpuStats(/* args */)
{

}

cCpuStats::~cCpuStats()
{
}


double cCpuStats::getCurrVal()
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
      totalSys < lastTotalSys || totalIdle < lastTotalIdle) {
    // Overflow detection. Just skip this value.
    percent = -1.0;
  } else {
    total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
    percent = total;
    total += (totalIdle - lastTotalIdle);
    percent /= total;
    percent *= 100;
  }

  return percent;
}