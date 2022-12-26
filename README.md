
# Orienteering
This project is based on the final structures project required in the course Programming 2: Structures (C++) at Tampere University. Shortly, my work covered the content appearing in modules **orienteeringmap.hh** and **orienteeringmap.c**, and **point.hh** and **point.c** in which I implemented the needed classes and objects.
  
- **Note:** This project is **focused** on the implementation of **classes and objects**, **smart pointers** and **STL containers**.

## Table of contents
- [Description](https://github.com/robredomikel/orienteering#description)
- [How to run](https://github.com/robredomikel/orienteering#how-to-run)
	- [In Qt](https://github.com/robredomikel/orienteering#in-qt)
	- [In terminal](https://github.com/robredomikel/orienteering#in-terminal)
- [Modules](https://github.com/robredomikel/orienteering#main-features)
	- [Orienteering map](https://github.com/robredomikel/orienteering#orienteering-map)
	- [Point](https://github.com/robredomikel/orienteering#point)
- [Further operations](https://github.com/robredomikel/orienteering#further-operations) 
- [Further comments](https://github.com/robredomikel/orienteering#further-comments)
- [References](https://github.com/robredomikel/orienteering#references)

## Description
In this project I implemented the necessary functions for the given module _orienteeringmap_ and created the module _point_ for the class _point_ and design its attributes and methods. The **goal of the project** is to, given the provided _cli_ and _parser_ modules, make a program that prints out a map with orienteering stop-points based on Cartesian coordinates, and that it's printed in the same command terminal.

During this  README file I will mostly **go over some of the most important features** in which the project is based on, rather than the description of each function and their goal, which can be found on the definition of each function in the self-implemented module files.
## How to run
In both explained options, input txt files are available in the project folder, so that the user can type them in the CMD line when executing the project, and all the input commands will be executed simultaneously.
### In Qt
As I used Qt Creator during this course I will continue with this IDE, but any IDE that could run C++ code should be able to run this project (e.g. VS Code...).
Open the _.pro_ file in Qt, build it and you will only need to execute it. Then the terminal will show ```CMD>``` in which you would run the functions that _orienteeringmap_ class contains.

![maps](https://github.com/robredomikel/orienteering/blob/main/screenshots/map.PNG)

![route function](https://github.com/robredomikel/orienteering/blob/main/screenshots/route.PNG)

### In terminal
In the case of this project, running the project from the terminal would end up being the same, but if it's the case that you want fast results, then you can just simply:
1. Run ```qmake``` in the terminal when you are inside the project directory, so that you create a ```Makefile```.
2. Then you would need to run ```make``` to compile the project. Also, note that if you want to change any feature of the project, then you would need to **repeat this step** in order to compile the changes.
3. Finally, type ````run .\project``` on the command line so that the project is executed. _Note that "project" is an orientative name, it could be another one._
## Modules
Explanation of the two classes implemented for this project.
### Orienteering map
This modules creates the map of coordinates for the points and routes, which is the core of the functionality of this project. An orienteeringmap Object should be able to compute methods like _print_map, print_routes, print_points_ and so on and so forth.
The orienteering map will contain the information of the existing points and the routes among them, stored in STL maps as pointers.
```cpp
// Map of Point* objects:
std::map<std::string, std::shared_ptr<Point>>  points_;
// Map of Routes:
std::map< std::string, std::vector<std::shared_ptr<Point> >> routes_;
```
### Point
Point class will define the attributes and methods implemented for Point objects, such as, their coordinates, height or name. Mostly, all methods implemented in this class are __getter__ functions, so that point class works to define and store __all the information__ of each point.
## Further operations
Once all the points and routes are built in the map, the program also computes the **length of the specified route** and **the highest distance rise from a given point**.
![orienteering](https://github.com/robredomikel/orienteering/blob/main/screenshots/rise.PNG)

## Further comments
This project should be seen from a **Modularity** backed perspective. Indeed, all the implemented code has been based on this part of the project.

Rather than efficiency, the implementation of this project is more oriented to the **connection between different objects**, so there may be surely some operations that could be more efficient. 

## References
- [Programming 2: Structures (FITech) | Tampere universities (tuni.fi)](https://www.tuni.fi/en/study-with-us/programming-2-structures-fitech)
- [cppreference.com](https://en.cppreference.com/w/)
