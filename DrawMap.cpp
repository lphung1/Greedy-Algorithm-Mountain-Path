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
#include <cstdlib>
#include <ctime>

using namespace std;

class DrawMap
{
    
private:
    int row, col;
    int map[1000][1000]; //row, col
    string fileName = "Colorado_480x480.txt";
    int maxValue; //max value
    int minValue; //min value
    int indexOfMinColm; //row of the min value in that colum
    int currentColm; //index of current place in path (current colm)
    ifstream file;
    string fileSize; //size of file
    int currentValue; //current value of path
    
    
    
public:
    /* default class constructor
        string fname - file name
        int r - row
        int c - column
        opens and reads file and puts into array and finds min and max values.
        starts from lowest elevation initially
     */
    DrawMap(string fname, int r, int c){
        //initialize bridges
        //Bridges::initialize(3, "lphung1@uncc.edu", "234291986029"); //enter's api credentials
        //Bridges::setTitle("A Color Grid Example");
        
        row = r;
        col = c;
        
        if(row < 1000 || col < 1000){ //checks if dimentions are in bounds
            fileName = fname;
            
            file.open(fileName);
            
            cout << fileName << "\n" ;
            
            if (file.is_open()){
                cout << "File open\n";
                getline(file, fileSize); //to skip first line. there is an extra 480 480 line in Colorado_480x480.txt file
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < col; j++) {
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
            for(int i = currentColm; i < row; i++){ //finds lowest value of first col
                if(map[currentColm][i] < currentValue){
                    currentValue = map[currentColm][i];
                    indexOfMinColm = i; //assigns index of where lowest value is at
                }
            }
        
        }//end if statement
        else{
            cout << "Dimentions are out of bounds";
        }
        
    }//end constructor
    
    
    void showArray(){
        
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << map[i][j] << " ";
            }
        }
    }//end showarray
    
    
    //finds lowest value in array
    void findMinVal(){
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (map[i][j] < minValue){
                    minValue = map[i][j];
                }
            }
        }
        
    }//end findMinVal
    
    //finds highest value in array
    void findMaxVal(){
        
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
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
        currentValue = map[indexOfMinColm][currentColm];
        return currentValue;
    }
    
    
    int calcNextPath(){
        
        int x1, x2, x3 = 0;
        int e1, e2, e3 = 0;
        int random = 0;
        //(rand() % 10) + 1
        
        //if line is out of bounds, end function
        if(currentColm + 1 > col){
            cout << "Line out of bounds";
            return 0;
        }
        
        x1 = map[currentColm + 1][indexOfMinColm + 1];
        x2 = map[currentColm + 1][indexOfMinColm];
        x3 = map[currentColm + 1][indexOfMinColm - 1];
        
        //get elevation
        e1 = abs(currentValue - x1);
        e2 = abs(currentValue - x2);
        e3 = abs(currentValue - x3);
        
        if(compareTo(e1, e2) == -1 && compareTo(e1, e3) == -1){ //go up if top is lowest num
            indexOfMinColm++;
            currentColm++;
        }
        else if(compareTo(e2, e1) == -1 && compareTo(e2, e3) == -1){ //go straight if middle is lowest num
            currentColm++;
        }
        else if(compareTo(e3, e2) == -1 && compareTo(e3, e1) == -1){ // go down if bottom is lowest num
            indexOfMinColm--;
            currentColm++;
        }
        else if(compareTo(e1, e2) == 0){ //if top and middle are same and lowest num
                currentColm++;
                currentValue = map[currentColm][indexOfMinColm];
        }
        else if(compareTo(e3, e2) == 0){ //if bottom and middle are same and lowest num
                currentColm++;
                currentValue = map[currentColm][indexOfMinColm];
        }
        else if(compareTo(e3, e1) == 0){ //if bottom and top are same and lowest num, non straight tie so flip coin
            srand(time(0));
            random = (rand() % 2) + 1;
            if(random == 1){//go down
                indexOfMinColm--;
                currentColm++;
            }
            else{//go up
                indexOfMinColm++;
                currentColm++;
            }
            
        }
        
        else{ //failsafe, go straight
            currentColm++;
            currentValue = map[currentColm][indexOfMinColm];
        }
        
        
        return 0;
    }//end calc next path
    
    int drawNextPath(){
        
        return scaleValue(currentValue);
        
    }
    
    int getColorOfArray(int row, int col){
        
        return scaleValue(map[row][col]);
        
    }
    
    int getRow(){//return row size
        return row;
    }
    
    int getCol(){// return col size
        return col;
    }
    void resetLine(){
        currentColm = 0;
            int random;
            srand(time(0));
            random = (rand() % row);
            indexOfMinColm = random;
        

    }
    
    
private: //compare numbers if lower or greater
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
