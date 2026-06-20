#include <iostream>
#include <cstring>

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Not enough arguments!\n";
        return 1;
    }

    std::cout << "Total Arguments: " << argc << std::endl;

    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            std::cout << "Welcome to " << argv[i] << std::endl;
        }
        else if (i == 1)
        {
            std::cout << "Hello Dear " << argv[i] << std::endl;
        }
        else if (i == 2)
        {
            if (strcmp(argv[i], "1") == 0)
            {
                std::cout << "WELCOME TO NSE" << std::endl;
            }
            else if (strcmp(argv[i], "2") == 0)
            {
                std::cout << "WELCOME TO BSE" << std::endl;
            }
        }
        else if (i == 3)
        {
            if (strcmp(argv[i], "1") == 0)
            {
                std::cout << "WELCOME TO EQ Market" << std::endl;
            }
            else if (strcmp(argv[i], "2") == 0)
            {
                std::cout << "WELCOME TO FO Market" << std::endl;
            }
        }
    }

    return 0;
}