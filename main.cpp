/* HEADER */
/* Orienteering Project
 *
 * Desc:
 * This program reads an input file based on points, its characteristics & also
 * the routes composed be these same points. For that, the given template
 * parses the input into appropiate self-made data-structures. In the same way,
 * the template comes with a already made user interface that handles all the
 * actions required for each input that the user introduces into the command
 * line.
 *
 * After that, and based on how the data from the input file has been stored and
 * organised, the module Orienteeringmap covers all the actions that the user
 * may require. For that, apart from the constructed implementations in the
 * mentioned module, each point created from the input file will suppose a Point
 * object, which will itself handle all its characteristics, and thus, will
 * help Orienteeringmap by providing all the characteristics required for each
 * user input command.
 *
 * Further information will be given in function headers.
 *
 * No comments will be added to the already given template code.
 *
 * Name: Mikel Robredo Manero
 * Student number: 150167534
 * UserID: pqmiro
 * E-Mail: mikel.robredomanero@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include <iostream>

int main()
{
    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) ) // func in PARSER.CPP
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ } // func in CLI.CPP
    return EXIT_SUCCESS;
}


