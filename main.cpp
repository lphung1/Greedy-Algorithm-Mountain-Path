//
//  main.cpp
//  Greedy algorithm mountain path program
//  Created by Loi Phung on 9/14/2018
//  Copyright © 2018 Loi Phung. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "src/Bridges.h"
#include "src/Color.h"
#include "src/ColorGrid.h"
#include "DrawMap.cpp"

using namespace bridges;

int main() {
    //BRIDGES initializations
    
    Bridges::initialize(3, "lphung1@uncc.edu", "234291986029"); //enter's api credentials
    Bridges::setTitle("Greedy Algorithm");
    
    // call drawmap constructor and set colorgrid canvas

    /*
     set new file and canvas size here.
     constructor will always start with lowest elevation in the first column
     call map.startRandomRow() to reset and start from a random row
     
     will demonstrate algorithm with 3 examples below
     */
    DrawMap map("Colorado_480x480.txt", 480, 480);//file name, row, col
    
    ColorGrid *cg  = new ColorGrid(map.getRow(), map.getCol(), Color("white"));
    Bridges::setDataStructure(cg);
    
    //print map
    for (int i = 0; i < map.getRow(); i++){
        for(int j = 0; j < map.getCol(); j++){
            int color = map.getColorOfArray(i, j);
            cg -> set(i, j, Color(color, color, color, 255));
        }
    }
    
    //draw line from lowest elevation
    for(int i = 0; i < map.getCol(); i++){
        map.calcNextPath();
        cg -> set(map.getIndexOfMinCol(), map.getCurrentCol(), Color("red"));
    }
    Bridges::visualize();
    
    map.resetLine();
    //start from random point
    for(int i = 0; i < map.getCol(); i++){
        map.calcNextPath();
        cg -> set(map.getIndexOfMinCol(), map.getCurrentCol(), Color("red"));
    }
    Bridges::visualize();
    
    //draw another from random point
    map.resetLine();
    for(int i = 0; i < map.getCol(); i++){
        map.calcNextPath();
        cg -> set(map.getIndexOfMinCol(), map.getCurrentCol(), Color("red"));
    }
    Bridges::visualize();
    
    /* comment out below to simulate the line multiple times
    
    int lines = 10;
    for (int i = 0; i < lines; i++){
        map.resetLine();
        for(int i = 0; i < map.getCol(); i++){
            map.calcNextPath();
            cg -> set(map.getIndexOfMinCol(), map.getCurrentCol(), Color("red"));
        }
        //Bridges::visualize(); //comment out to see multiple images
    }
     */
    
    
    //outputs of values for debug purposes
    cout <<"\nMax Value: " << map.getMaxVal() << "\nMin Value: " << map.getMinVal();
    cout <<"\nCurrent Col: " << map.getCurrentCol() << "\nIndexofMinCol: " << map.getIndexOfMinCol();
    cout << "\nCurrent Value: " << map.getCurrentValueOfIndex();
    cout <<"\nScaled Min: " << map.scaleValue(map.getMinVal()) << "\nScaled Max: " <<map.scaleValue(map.getMaxVal()) << "\n";
    
    
    
    
    
    
    return 0;
}
