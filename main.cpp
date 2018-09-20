//
//  main.cpp
//  bridges_program
//  prints random color squares on a red grid
//  Created by Loi Phung on 8/29bri/18.
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
    
    ColorGrid *cg  = new ColorGrid(480, 480, Color("white"));
    
    
    // draw a green square

    DrawMap map;
    
    
    for (int i = 0; i < 480; i++){
        for(int j = 0; j < 480; j++){
            int color = map.getColorOfArray(i, j);
            cg -> set(i, j, Color(color, color, color, 255));
        }
    }
    
    for(int i = 0; i < 480; i++){
        map.calcNextPath();
        cg -> set(map.getIndexOfMinCol(), map.getCurrentCol(), Color("red"));
    }
    
    cout <<"\nMax Value: " << map.getMaxVal() << "\nMin Value: " << map.getMinVal();
    cout <<"\nCurrent Col: " << map.getCurrentCol() << "\nIndexofMinCol: " << map.getIndexOfMinCol();
    cout << "\nCurrent Value: " << map.getCurrentValueOfIndex();
    cout <<"\nScaled Min: " << map.scaleValue(map.getMinVal()) << "\nScaled Max: " <<map.scaleValue(map.getMaxVal());
    
    
    
    
    Bridges::setDataStructure(cg);
    Bridges::visualize();
    return 0;
}
