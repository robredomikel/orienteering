#include "point.hh"



Point::Point(std::string &name, int x_coor, int y_coor,
             int height, char marker):
    point_name_(name), x_coordinate_(x_coor), y_coordinate_(y_coor),
    height_(height), point_marker_(marker)
{

}

/* FIVE GETTER METHODS for each of the attributes of the object Point.
 * None of them have parameters, and all of them return the attributes for
 * the one the function has been explicitly created.
 */
std::string Point::getName() const
{
    return point_name_;
}

int Point::getX() const
{
    return x_coordinate_;
}

int Point::getY() const
{
    return y_coordinate_;
}

char Point::getMarker() const
{
    return point_marker_;
}

int Point::getHeight() const
{
    return height_;
}

/* Boolean function that checks if the given width and height coordinates are
 * within the map, if so returns TRUE and does the printout with the marker
 * of the point that does have the specific coordinates. Else, returns FALSE
 * and nothing is printed.
 *
 * PARAM: x_size: int, width size of the map.
 *        x: int, width coordinate for the current location in the map.
 *        Y: int, height coordinate for the current location in the map.
 *
 * RETURN: Bool (Already explained.)
 */
bool Point::isInMap(int x_size, int x, int y) const
{
    if (x == x_coordinate_ && y == y_coordinate_)
    {
        if( x == x_size)
        {
            std::cout << char(point_marker_);
        }
        else
        {
            std::cout << char(point_marker_)
                      << "  ";
        }
        return true;
    }
    return false;
}




