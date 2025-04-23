#include <cstdlib>
#include <iostream>

int main()
{
    int result = system("sudo /etc/init.d/ethercat start");
    if (result == 0)
    {
        std::cout << "Success: " << result << std::endl;
    }
    else
    {
        std::cout << "Failed: " << result << std::endl;
    }

    return 0;
}
