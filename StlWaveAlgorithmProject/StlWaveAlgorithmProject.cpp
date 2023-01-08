#include <iostream>
#include "Map.h"

int main()
{
    Map map("map1.txt");

    
    cout << "\n";
    map.Print();
    cout << boolalpha << map.CreateWave() << "\n";
    map.Print();
    map.CreatePath();
    map.Print();
    return 0;
}
