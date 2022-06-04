// Banker's Algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "BankerAlgorithm.h"

int main()
{
    BankerAlgorithm test(5, 3);

    test.add_allocation(0, 0, 0);
    test.add_allocation(0, 1, 1);
    test.add_allocation(0, 2, 0);
    test.add_allocation(1, 0, 2);
    test.add_allocation(1, 1, 0);
    test.add_allocation(1, 2, 0);    
    test.add_allocation(2, 0, 3);
    test.add_allocation(2, 1, 0);
    test.add_allocation(2, 2, 2);    
    test.add_allocation(3, 0, 2);
    test.add_allocation(3, 1, 1);
    test.add_allocation(3, 2, 1);    
    test.add_allocation(4, 0, 0);
    test.add_allocation(4, 1, 0);
    test.add_allocation(4, 2, 2);

    test.add_max(0, 0, 7);
    test.add_max(0, 1, 5);
    test.add_max(0, 2, 3);
    test.add_max(1, 0, 3);
    test.add_max(1, 1, 2);
    test.add_max(1, 2, 2);
    test.add_max(2, 0, 9);
    test.add_max(2, 1, 0);
    test.add_max(2, 2, 2);
    test.add_max(3, 0, 2);
    test.add_max(3, 1, 2);
    test.add_max(3, 2, 2);
    test.add_max(4, 0, 4);
    test.add_max(4, 1, 3);
    test.add_max(4, 2, 3);

    test.add_available(0, 3);
    test.add_available(1, 3);
    test.add_available(2, 2);

    bool res = test.request(2, {3,0,0});
    if (res)
    {
        cout << "This request can be granted.";
        return 0;
    }
    cout << "Request denied.";
    return 0;
}