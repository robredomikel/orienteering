/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project3: Suunnistus / Orienteering                                       #
# File: point.hh                                                            #
# Description: Control point generator for Orienteering map.                #
# Notes: * This is a part of an exercise program.                           #
#        * Help class for Orienteering Map.                                 #
#        * Handles all the characteristics of the given point               #
#############################################################################
*/

#ifndef POINT_HH
#define POINT_HH

#include <orienteeringmap.hh>
#include <string>
#include <iostream>


class Point
{
public:
    Point(std::string &name, int x_coor, int y_coor,
          int height, char marker);

    std::string getName() const;
    int getX() const;
    int getY() const;
    char getMarker() const;
    int getHeight() const;
    bool isInMap(int x_size, int x, int y) const;

private:
    // information about each point.
    std::string point_name_;
    int x_coordinate_;
    int y_coordinate_;
    int height_;
    char point_marker_;
};

#endif // POINT_HH
