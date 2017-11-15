/*
 File: node.h
 Project: Recursive Maze Walk
 Created by MacBook Air on 11/15/17.
 Copyright © 2017 Aleksandr Golovin. All rights reserved.
*/

#ifndef node_h
#define node_h

using namespace std;

class node
{
private:
    
    //Private variables
    char value;
    int x,y;
    bool checked;
    
public:
    
    //Overloaded ostream operator to print value stored in node
    friend ostream & operator << (ostream & out, const node & toPrint)
    {
        out<<toPrint.value;
        return out;
    }
    
    //Default constructor
    node(): value(0), x(0), y(0), checked(false){}
    
    //Constructor, takes: value, x coord, y coord
    node(char nwVal, int nwX, int nwY): value(nwVal), x(nwX), y(nwY){}
    
    //Sets vistit status
    void setVisit(bool check){checked=check;};
    
    //Returns visit status
    bool visited() const {return checked;}
    
    //Sets value stoted in node
    void setVal (char nwVal){value=nwVal;}
    
    //Returns value in node
    char getVal()const {return value;}
    
    //Returns X Coord.
    int getX()const {return x;}
    
    //Returns Y Coord.
    int getY()const {return y;}
};

#endif /* node_h */
