#include "cStats.hpp"
#include <iostream>

int main()
{
    std::shared_ptr<cCPUStats> pCPUusage = std::make_shared<cCPUStats>();

    cRamWrapper oRamConfig(pCPUusage);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << oRamConfig.getStats() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << oRamConfig.getStats() << std::endl;

    return 0;
}