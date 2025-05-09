#include <LockDown/Controller.h>
#include <iostream>

int main()
{
    string key = "motDePasseMaitre";
    
    Controller(key).start();

    return 0;
}