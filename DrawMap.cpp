//
//  DrawMap.cpp
//  bridges_program
//
//  Created by Loi Phung on 9/14/18.
//  Copyright © 2018 Loi Phung. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
//#include "src/Bridges.h"
//#include "src/Color.h"
//#include "src/ColorGrid.h"
//using namespace bridges;


using namespace std;

class DrawMap
{
    
private:
    int row, col;
    int map[480][480];
    string fileName = "Colorado_480x480.txt";
    int maxValue; //max value
    int minValue; //min value
    int indexOfMinColm; //row of the min value in that colum
    int currentColm; //index of current place in path (current colm)
    ifstream file;
    string fileSize; //size of file
    int currentValue; //current value of path
    
    
    
public:
    //default class constructor
    DrawMap(){
        //initialize bridges
        //Bridges::initialize(3, "lphung1@uncc.edu", "234291986029"); //enter's api credentials
        //Bridges::setTitle("A Color Grid Example");
        file.open(fileName);
        
        cout << fileName << "\n" ;
        
        if (file.is_open()){
            cout << "File open\n";
            getline(file, fileSize); //to skip first line
            for (int i = 0; i < 480; i++) {
                for (int j = 0; j < 480; j++) {
                    file >> map[i][j];
                }
            }
        }
        else{
        cout << "Issue opening file";
        }
        file.close();
        //set default values for min/max
        maxValue = map[0][0];
        minValue = map [0][0];
        //find min/max
        findMinVal();
        findMaxVal();
        
        currentValue = map[0][0];
        currentColm = 0;
        
        //setting starting values
        for(int i = currentColm; i < 480; i++){ //finds lowest value of first col
            if(map[currentColm][i] < currentValue){
                currentValue = map[currentColm][i];
                indexOfMinColm = i; //assigns index of where lowest value is at
            }
        }
        
        
        
    }//end constructor
    
    
    void showArray(){
        
        for (int i = 0; i < 480; i++) {
            for (int j = 0; j < 480; j++) {
                cout << map[i][j] << " ";
            }
        }
    }//end showarray
    
    
    
    void findMinVal(){
        for (int i = 0; i < 480; i++) {
            for (int j = 0; j < 480; j++) {
                if (map[i][j] < minValue){
                    minValue = map[i][j];
                }
            }
        }
        
    }//end findMinVal
    
    void findMaxVal(){
        
        for (int i = 0; i < 480; i++) {
            for (int j = 0; j < 480; j++) {
                if (map[i][j] > maxValue){
                    maxValue = map[i][j];
                }
            }
        }
        
    }//end findMaxVal
    
    int scaleValue(int i){
        
        return (255) * (i - minValue) / (maxValue - minValue);
        
    }
    

    int getMinVal(){
        return minValue;
    }//end minVal
    
    int getMaxVal(){
        return maxValue;
    }//end maxVal
    
    
    int getIndexOfMinCol(){
        return indexOfMinColm;
    }
    
    int getCurrentCol(){
        return currentColm;
    }
    
    int getCurrentValueOfIndex(){
        return currentValue;
    }
    
    
    void calcNextPath(){
        
        int x1, x2, x3 = 0;
        int e1, e2, e3 = 0;
        
        x1 = map[currentColm + 1][indexOfMinColm + 1];
        x2 = map[currentColm + 1][indexOfMinColm];
        x3 = map[currentColm + 1][indexOfMinColm - 1];
        
        //get elevation
        e1 = abs(currentValue - x1);
        e2 = abs(currentValue - x2);
        e3 = abs(currentValue - x3);
        
        if(compareTo(e1, e2) == -1 && compareTo(e1, e3) == -1){ //go up
            indexOfMinColm++;
            currentColm++;
            currentValue = map[currentColm][indexOfMinColm];
        }
        else if(compareTo(e2, e1) == -1 && compareTo(e2, e3) == -1){ //go straight
            currentColm++;
            currentValue = map[currentColm][indexOfMinColm];
        }
        else if(compareTo(e3, e2) == -1 && compareTo(e3, e1) == -1){ // go down
            indexOfMinColm--;
            currentColm++;
            currentValue = map[currentColm][indexOfMinColm];
        }
        else{
            currentColm++;
            currentValue = map[currentColm][indexOfMinColm];
        }
        
        
        
        
    }
    
    int drawNextPath(){
        
        return scaleValue(currentValue);
        
    }
    
    int getColorOfArray(int row, int col){
        
        return scaleValue(map[row][col]);
        
    }
    
private:
    int compareTo(int x, int y){
        if (x > y){
            return 1;
        }
        else if (x < y){
            return -1;
        }
        else
            return 0;
    }
    
    
};
