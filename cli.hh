/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project3: Suunnistus / Orienteering                                       #
# File: cli.hh                                                              #
# Description: Commandline interface for the program.                       #
# Notes: * This is a part of an exercise program.                           #
#        * Student's don't touch this file.                                 #
#        * Understanding how the module works isn't necessary to complete   #
#          this exercise.                                                   #
#        * This is also an example how you can use function pointers to     #
#          a class' functions.                                              #
#        * This could be upgraded to have commandhistory with a relative    #
#          ease.                                                            #
#############################################################################
*/

#ifndef CLI_HH
#define CLI_HH

#include "orienteeringmap.hh"
#include <string>
#include <vector>
#include <memory>

/* In order to define a function pointer to a class you have to add
 * class as the visibility range before the pointer declaring * and
 * after that comes the type-name for the pointer.
 * In this case we have named the types according to the amount of
 * parameters the function receives.
 */

using noparam = void (OrienteeringMap::*)() const;
using oneparam = void (OrienteeringMap::*)(const std::string&) const;
using twoparam = void (OrienteeringMap::*)(int, int) const;

// CommandInfo contains the list of strings that select it and
// function pointers to the function that is going to be called through it.
struct CommandInfo
{
    std::vector<std::string> lines_;
    noparam func0_;
    oneparam func1_;
    twoparam func2_;
};


class Cli
{
public:
    // The database that is going to be used is given as a parameter.
    Cli(std::shared_ptr<OrienteeringMap> db);

    /* Description: Runs the interface.
     * Return values:
     *  True    - Normal command
     *  False   - Exit command
     */
    bool exec_prompt();

private:
    std::shared_ptr<OrienteeringMap> database_;

    // Stores the arguments from current command.
    std::vector<std::string> args_;

    // Pointer to the recognized command
    const CommandInfo* recognized_;

    // Prompt printed for every query
    const std::string PROMPT = "CMD> ";

    // To make code more readable. Could also be different constants but this
    // groups them better.
    enum CommandTypes {QUIT = -1, NO_PARAMETERS = 1, ONE_PARAMETER = 2,
                       TWO_PARAMETER = 3, FIVE_PARAMETER = 6,EMPTY = 0,
                       UNKNOWN = -3, WRONG_PARAMETERS = -2};

    // Constant table that contains the different commands that the CLI can
    // recognize.
    std::vector<CommandInfo> const COMMANDS = {
        {{"EXIT","QUIT","Q","LOPETA"},nullptr,nullptr,nullptr},
        {{"MAP","KARTTA"},&OrienteeringMap::print_map,nullptr,nullptr},
        {{"ROUTES","REITIT"},&OrienteeringMap::print_routes,nullptr,nullptr},
        {{"ROUTE","REITTI"}, nullptr,&OrienteeringMap::print_route,nullptr},
        {{"LENGTH","PITUUS"}, nullptr,&OrienteeringMap::route_length,nullptr},
        {{"RISE","NOUSU"}, nullptr,&OrienteeringMap::greatest_rise,nullptr},
        {{"POINTS","PISTEET"},&OrienteeringMap::print_points,nullptr,nullptr},
        {{},nullptr,nullptr,nullptr}
    };

    // Parses the given input to different arguments.
    void parse_command(const std::string& line);

    /* Description: Sets the recognized_ to point at the correct CommandInfo.
     * Return values:
     *  Amount of arguments - Command can be executed
     *  -1                  - Exit command
     *  -2                  - Invalid amount of parameters
     *  -3                  - Command not recognized.
     */
    int check_command_type();
};

#endif // CLI_HH
