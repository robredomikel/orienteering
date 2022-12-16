#include "orienteeringmap.hh"

/* IMPORTANT NOTE:
 * MAIN HEADER OF THE PROGRAM IN MAIN.CPP.
 */

/* Constructor of the object OrienteeringMap, initializes the main attributes.
 *
 * ATTRIBUTES width_x_ : Stores the x coordinate size
              height_y_ : Does the same but with coordinate y.
              points_ : Map structure of all the existing points in the MAP.
              routes_: Map structure with all the existing routes in the MAP.
 */
OrienteeringMap::OrienteeringMap() :
    width_x_(), height_y_(), points_(), routes_()
{

}

/* Destructor of the object OrienteeringMap, clears all the points and routes
 * from the map.
 *
 * RETURN None.
 */
OrienteeringMap::~OrienteeringMap()
{
    points_.clear();
    routes_.clear();
}

/* Gives the values of the map width & height to the Orienteering map attributes.
 *
 * PARAM width: int, size of the width for the map.
 *       height: int, size of the height for the map.
 *
 * RETURN None.
 */
void OrienteeringMap::set_map_size(int width, int height)
{
    width_x_ = width;
    height_y_ = height;
}

/* Adds a new point in the map, with the given name, position (x and y
 * coordinates), height and marker. This data will be introduced in the data
 * structure for points in the form of a Point object.
 *
 * PARAM name: string, name of the point.
 *       x: int, width coordinate for the point.
 *       y: int, height coordinate for the point.
 *       height: int, height sized in metres of the point in the map (altitude).
 *       marker: char, first letter of the point name acting as a marker for
 *       identification purpose.
 *
 * RETURN: None.
 */
void OrienteeringMap::add_point(std::string name, int x, int y, int height,
                                char marker)
{
    std::shared_ptr<Point> new_point = std::make_shared<Point>
            (name, x, y, height, marker);

    points_.insert({name, new_point});
}

/* Connects two existing points such that the point 'to' will be
 * immediately after the point 'from' in the route 'route_name'.
 * The given route can be either a new or an existing one,
 * if it already exists, the connection between points will be updated in the
 * aforementioned way. Returns true, if connection was successful, i.e. if both
 * the points exist, otherwise returns false.
 *
 * PARAM: from: string, the point from the route starts or the last point that
 *        was added in the route.
 *        to: string, the point in which currently the route ends or definitely
 *        ends.
 *        route_name: string, the name of the route.
 */
bool OrienteeringMap::connect_route(std::string from, std::string to,
                                    std::string route_name)
{
    if (points_.find(from) == points_.end() or
            points_.find(to) == points_.end())
    {
        return false;
    }
    else
    {
        if (routes_.find(route_name) == routes_.end())
        {
            routes_.insert({route_name, {}});
            routes_.at(route_name).push_back(points_.at(from));
            routes_.at(route_name).push_back(points_.at(to));
        }
        else
        {
            routes_.at(route_name).push_back(points_.at(to));
        }
        return true;
    }
}

/* Prints the map into the console with the control points in their stored
 * locations based on the coordinates.
 *
 * NO PARAM
 * RETURN: None.
 */
void OrienteeringMap::print_map() const
{
    // First we print the line with the x coords:
    print_fst_line();
    // Second, the rest of the map with control points.
    for (int j = 1; j <= height_y_; ++j) // y size = 10
    {
        std::cout << std::setw(2) << j << "  ";
        for (int i = 1; i <= width_x_; ++i) // x size 15
        {
            bool isDot = true;
            for (const auto &point : points_)
            {
                if (point.second->isInMap(width_x_, i, j)) // Private function.
                {
                    isDot = !isDot;
                    ++i; // One dot less will be printed
                }
            }
            if (isDot or i <= width_x_)
            {
                std::cout << ".";
            }
            if (i < width_x_)
            {
                std::cout << "  ";
            }
            else
            {
                std::cout << std::endl;
            }
        }
    }
}

/* Print all the routes created from the data given in the input file in
 * alphabetical order.
 *
 * NO PARAM.
 * RETURN: None.
 *
 */
void OrienteeringMap::print_routes() const
{
    std::cout << "Routes:" << std::endl;
    for (const auto &route : routes_)
    {
        std::cout << std::setw(2) << "-";
        std::cout<< " " << route.first << std::endl;
    }
}

/* Prints the control points given in the input file with their markers.
 * The printout works in alphabetical order based on the point names.
 *
 * NO PARAM.
 * RETURN: None.
 */
void OrienteeringMap::print_points() const
{
    std::cout << "Points:" << std::endl;
    for (const auto &point : points_)
    {
        std::cout << std::setw(2) << "-";
        std::cout << " " << point.first;
        std::cout << std::setw(2) << ":";
        std::cout << std::setw(2) << char(point.second->getMarker())
                  << std::endl;
    }
}

/* Prints the control points belonging to the given route. The points will be
 * printed in the order they were given in the input file.
 *
 * PARAM: name: string, the name of the route.
 *
 * RETURN: None.
 */
void OrienteeringMap::print_route(const std::string &name) const
{
    bool route_found = false;
    for (const auto &route : routes_)
    {
        if (route.first == name)
        {
            std::cout << route.second.at(0)->getName() << std::endl;
            for (const auto &point : route.second)
            {
                if (point == route.second.at(0))
                {
                    continue;
                }
                std::cout << std::setw(3) << "->";
                std::cout << " " << point->getName() << std::endl;
            }
            route_found = true;
        }
    }
    if (!route_found)
    {
        std::cout << "Error: Route named " << name
                  << " can't be found" << std::endl;
    }
}

/* Prints the length of the given route. The length is calculated as the sum of
 * distances between each subsequent points.
 *
 * PARAM: name: string, name of the given route.
 *
 * RETURN: None.
 */
void OrienteeringMap::route_length(const std::string &name) const
{
    double result = 0;
    bool route_found = false;
    for (const auto &route : routes_)
    {
        if (route.first == name)
        {
            for (uint i = 1; i < route.second.size(); ++i)
            {
                // Private function "distance" performs the mathematical calcu
                // lation for the given route.
                result += distance(route.second.at(i-1)->getX(),
                                   route.second.at(i-1)->getY(),
                                   route.second.at(i)->getX(),
                                   route.second.at(i)->getY());
            }
            route_found = true;
        }
    }
    if (!route_found)
    {
        std::cout << "Error: Route named " << name
                  << " can't be found" << std::endl;
    }
    else
    {
        std::cout << "Route " << name << " length was ";
        std::cout << std::setprecision(2) << result << std::endl;
    }
}

/* Prints the greatest continuous rise, when proceeding from the given control
 * point along to some route. The rise will be counted only if the proceeding
 * points show a higher or equal height to the current rise. Once the height
 * starts to decrease the continuous rise is over and the function ends.
 * Also, if the given point doesn't exist, an error warning is displayed.
 *
 * PARAM: point_name: string, name of the point from where the method starts
 *        to count the rise increase in each function where the point is found.
 *
 * RETURN: None.
 */
void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    if (points_.find(point_name) == points_.end())
    {
        std::cout << "Error: Point named " << point_name
                  << " can't be found" << std::endl;
    }
    else
    {
        // Help map container where the routes where the point was found are
        // added with their respective calculated continuous rise.
        std::map<std::string, int> possible_routes = {};
        for (const auto &route : routes_)
        {
            uint i = 0;
            while (i < route.second.size() &&
                   route.second.at(i)->getName() != point_name)
            {
                ++i;
            }
            // In case we've already reached the end of the route.
            if (i == route.second.size())
            {
                continue;
            }

            int init_height = route.second.at(i)->getHeight();
            int end_height = init_height;
            ++i;

            while (i < route.second.size() &&
                   route.second.at(i)->getHeight() >=
                   route.second.at(i-1)->getHeight())
            {
                end_height = route.second.at(i)->getHeight();
                ++i;
            }
            possible_routes.insert({route.first,
                                    end_height - init_height});
        }        

        // Once the checking of the continuous rise has been done in all routes,
        // next step is to choose which is the greatest rise.
        std::map<std::string, int>::iterator iter;
        iter = possible_routes.begin();
        int greatest_rise = 0;
        // For the sake of a neater code, the check and the printout of the
        // function have been applied in two help functions.
        greatest_rise = check_greatest_rise(greatest_rise, possible_routes,
                                            iter);
        print_greatest_rise(greatest_rise, point_name, possible_routes);

        // Help map structure is cleared for future use.
        possible_routes.clear();
    }
}

/* Prints the first line of the map. This help function has been implemented in
 * order to make this moodle more readable.
 *
 * NO PARAM.
 * RETURN: None.
 */
void OrienteeringMap::print_fst_line() const
{
    std::cout << std::setw(4);
    for (int i = 1; i <= width_x_; ++i)
    {
        std::cout << i << std::setw(3);
        if (i == width_x_)
        {
            std::cout << std::endl;
        }
    }
}

/* Calculates the distance between two points in a given route, given their
 * width and height coordinates.
 *
 * PARAM: x_from: int, width coordinate for the initial point.
 *        y_from: int, height coordinate for the initial point.
 *        x_to: int, width coordinate for the subsequential point.
 *        y_to: int, height coordinate for the subsequential point.
 *
 * RETURN: result: double, final number from the calculation done for the
 *         distance between the two points.
 */
double OrienteeringMap::distance(int x_from, int y_from, int x_to, int y_to)
const
{
    double result = 0;

    result = sqrt(pow(x_to - x_from, 2) + pow(y_to - y_from, 2));

    return result;
}

/* Checks which is the greatest continuous rise in each route in which the
 * given point exists. For that it compares the rise calculated previously in
 * the home function of this help function for each route.
 *
 * PARAM: greatest_rise: int, initial integer variable with 0 value for inner
 *        use in this function.
 *        possible_routes: map, map with the name of the routes in which a
 *        continuous rise has been found as the key and the value of the rises
 *        as the payload.
 *        iter: map iterator, used to operate within the map and do the compa
 *        risons between different rises.
 *
 * RETURN greatest_rise: int, final value for the greatest rise among all the
 *        rises identified.
 */
int OrienteeringMap::check_greatest_rise(int greatest_rise,
                                          const std::map<std::string, int>
                                          &possible_routes,
                                          std::map<std::string, int>::iterator
                                          &iter) const
{
    while (iter != possible_routes.end())
    {
        if (greatest_rise == 0)
        {
            greatest_rise = iter->second;
        }
        if (greatest_rise != 0 && iter->second >= greatest_rise)
        {
            greatest_rise = iter->second;
        }
        ++iter;
    }
    return greatest_rise;
}

/* Once the greatest rise has been found, this function performs the printout
 * of the route(s) in which the greatest rise exists.
 *
 * PARAM: gratest_rise: int, now filled with the greatest value, it's the
 *        greatest rise value among all the identified rises from the given
 *        point.
 *        point_name: string, name of the point from where the continuous rise
 *        has been set to start counting metres.
 *        possible_routes: map, help structure to store temporaly all the routes
 *        in which the given points exists, so that also a continuous rise
 *        MAY exist.
 */
void OrienteeringMap::print_greatest_rise(int greatest_rise,
                                          const std::string &point_name,
                                          const std::map<std::string, int>
                                          &possible_routes) const
{
    if (greatest_rise == 0)
    {
        std::cout << "No route rises after point " << point_name
                  << std::endl;
    }
    else
    {
        std::cout << "Greatest rise after point " << point_name
                  << ", " << greatest_rise << " meters, is on route(s):"
                  << std::endl;
        for (const auto &route : possible_routes)
        {
            if (route.second == greatest_rise)
            {
                std::cout << std::setw(2) << " -" << " " << route.first
                          << std::endl;
            }
        }
    }
}




