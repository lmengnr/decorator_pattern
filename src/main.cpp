#include "cStats.hpp"
#include <iostream>


int main()
{
    std::shared_ptr<cCPUStats> pCPUusage = std::make_shared<cCPUStats>();

    cRamWrapper oRamConfig(pCPUusage);


    std::cout << oRamConfig.getStats() << std::endl;

}