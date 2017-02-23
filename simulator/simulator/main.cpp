//
//  main.cpp
//  simulator
//


#include <iostream>
#include "simulator.h"
using namespace std;


int main(){

    
//    Simulator sim1(5, 0.1, 0.95, 0.01);
//    sim1.train_agent();
//    sim1.playgame();
//    
//    Simulator sim2(5, 0.1, 0.6, 0.2);
//    sim2.train_agent();
//    sim2.playgame();
//    
//    Simulator sim3(5, 0.1, 0.1, 0.1);
//    sim3.train_agent();
//    sim3.playgame();
//    
//    Simulator sim4(5, 0.5, 0.1, 0.1);
//    sim4.train_agent();
//    sim4.playgame();
    
    Simulator sim5(5, 0.9, 0.95, 0);
    sim5.train_agent();
    sim5.playgame();
    return 0;
}
