#include <iostream>
#include "BusStop.h"

using namespace std;

int main(){
    BusStop busStop1;
    BusStop busStop2;
    BusStop busStop3(busStop1);
    BusStop busStop4;

    busStop2=busStop1;

    cout << busStop1 << endl;
    cout << busStop2 << endl;
    cout << busStop3 << endl;
    cout << busStop4 << endl;
}
