/*
 File: maze.cpp
 Project: Recursive Maze Walk
 Created by Aleksandr Golovin on 11/11/17.
 Copyright © 2017 Aleksandr Golovin. All rights reserved.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "node.h"

using namespace std;

//void printMaze(node *ar, int rows, int col)
void printMaze(const vector<vector<node> > &ar)
{
    for(int lvl=0; lvl<ar.size();lvl++)
    {
        for(int elmnt=0;elmnt<ar[lvl].size();elmnt++)
        {
            cout<<ar[lvl][elmnt];
        }
        cout<<endl;
    }
}

//Prints path followed to find way out
void printPath(const vector<node> &path)
{
    for (int elmnt=0;elmnt<path.size();elmnt++)
    {
        cout<<"["<<path[elmnt].getX()<<","<<path[elmnt].getY()<<"]->";
    }
}

//Uses recursion to find way out, loads path onto vector
bool findOut(vector<vector<node> >&ar, int x, int y, vector<node> &path)
{
    if(y>= ar[x].size()-1 || x>=ar.size()-1) return false;
    
    //Checks to see if found way out
    if(ar[x][y].getVal()=='o') return true;
    
    //Checks to see if unit is a wall
    if (ar[x][y].getVal()=='#') return false;
    
    //Unit marked as visited
    ar[x][y].setVisit(true);
    ar[x][y].setVal('+');
    
    //Pushes path onto path vector
    path.push_back(ar[x][y]);
    
    //Go down one unit
    if(!ar[x+1][y].visited())
    {
        if (findOut(ar,x+1,y,path) == true) return true;
    }
    
    //Go right one unit
    if(!ar[x][y+1].visited())
    {
        if(findOut(ar,x,y+1,path) == true) return true;
    }
    
    //Go up one unit
    if(!ar[x-1][y].visited())
    {
        if (findOut(ar, x-1,y,path) == true) return true;
    }
    
    //Go left one unit
    if(!ar[x][y-1].visited())
    {
        if (findOut(ar,x,y-1,path) == true) return true;
    }
    
    return false;
}

int main(int argc, const char * argv[]) {

    //Get file name via std. input
    string filName;
    cout<<"Enter file name: ";
    cin>>filName;
    
    //Used to fetch data
    char runner=0;
    string runner2;
    
    //Store size of maze
    int rows=0, column=0;
    
    //Store starting point of maze
    int x=0, y=0;
    
    //All false because nothing set, changes to true when changed
    bool rowSet=false, colSet=false, xSet=false, ySet=false;
    
    //Creates a input stream and opens it
    ifstream inFile;
    inFile.open(filName);
    
    //Checks if input file is open
    if (inFile.is_open())
    {
        //Loops while not at newline
        while (inFile.peek()!= 10)
        {
            //Runner fetches data
            inFile>>runner2;

            if(!rowSet)
            {
                rows=stoi(runner2);
                rowSet=true;
            }
            else if(!colSet)
            {
                column=stoi(runner2);
                colSet=true;
            }
            else if(!xSet)
            {
                x=stoi(runner2);
                xSet=true;
            }
            else if (!ySet)
            {
                y=stoi(runner2);
                ySet=true;
            }
        }
        
        //2D vector to store maze
        vector< vector<node> >mazeAr;
        
        //Vector to store path
        vector<node>path;
        
        //Resizes rows of 2D array to specs.
        mazeAr.resize(rows);

        //Used to keep track of column and row
        int count=0;
        int height=0;
        
        //Used incase vector is resized
        bool resized=false;

        //Used to get to start of new line
        inFile.get(runner);
        
        //Loops while there are char to be read
        while(inFile.get(runner))
        {
            //If new line and within bounds add element
            if(runner != '\n' && count<column)
            {
                node temp(runner,height,count);
                
                mazeAr[height].push_back(temp);
                count++;
            }
            //If newline reached and end of columns, go down to next row
            else if (count == column && runner == '\n')
            {
                height++;
                count=0;
            }
            //Checks for maze specs that are to big, resizes if true
            else if(runner == '\n' && count<column)
            {
                if(!resized)
                {
                    //Resizes all current rows in 2D vector
                    for (int i=0;i<height;i++)
                    {
                        mazeAr[i].resize(count);
                    }
                    
                    column=count;
                    resized=true;
                    height++;
                    count=0;
                }
            }
            //If maze specs to small, output error and return
            else if (count==column && (runner !='\n' && runner !=' '))
            {
                cout<<"Bad maze\n";
                return 0;
            }
        }
        
        //Resizes vector if more rows allocated than needed
        if(height<rows)
        {
            mazeAr.resize(height);
            rows=height;
        }
        
        //Closes File
        inFile.close();
        
        //If way out found, print path and maze
        if(findOut(mazeAr,x, y,path))
        {
            printPath(path);
            cout<<endl;
            printMaze(mazeAr);
        }
        else
        {
            cout<<"No exit – Sartre was right\n";
        }
    }
    
    return 0;
}
