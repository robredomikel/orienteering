#include "cli.hh"
#include <iostream>
#include <algorithm>

Cli::Cli(std::shared_ptr<OrienteeringMap> db):
    database_(db),recognized_(nullptr)
{
}

/// From main this function is run in a while loop, which only breaks if the
/// the command introduced means a return False.
bool Cli::exec_prompt()
{
    // Always clear the command at first
    args_.clear();
    recognized_ = nullptr;

    // Query for the command
    std::string line;
    std::cout << PROMPT;
    std::getline(std::cin, line);

    // Get the args from input
    parse_command(line);

    /* Recognize and execute the command.
     * Interesting notion: You have to change shared_ptr to raw pointer
     * in order to execute the class-method through the function pointer.
     */
    switch( check_command_type() )
    {
    case CommandTypes::WRONG_PARAMETERS:
        std::cout << "Error: Wrong amount of parameters" << std::endl;
        return true;
    case CommandTypes::QUIT:
        return false;
    case CommandTypes::NO_PARAMETERS:
        // Compare to a regular function call:
        // database_->print_map();
        ((database_.get())->*(recognized_->func0_))();
        break;
    case CommandTypes::ONE_PARAMETER:
        ((database_.get())->*(recognized_->func1_))(args_.at(1));
        break;
    case CommandTypes::TWO_PARAMETER:
        ((database_.get())->*(recognized_->func2_))(std::stoi(args_.at(1)),
                                                    std::stoi(args_.at(2)));
        break;
    case CommandTypes::EMPTY:
        return true;
    default:
        std::cout << "Error: Unknown command" << std::endl;
    }
    return true;
}

void Cli::parse_command(const std::string &line)
{
    std::string tmp = line;
    size_t pos = 0;

    if( line.empty() )
    {
        return;
    }

    // Separate each word to a different argument
    while( not tmp.empty() )
    {
        // Treat the string between quote marks as a single argument
        // even if there are spaces in it.
        if( tmp.at(0) == '\"' )
        {
            pos = tmp.find('\"', 1);

            // substr(1, pos-1) drops the quote marks
            if( not tmp.substr(1, pos - 1).empty() )
            {
                args_.push_back(tmp.substr(1, pos - 1));
            }
        }
        else
        {
            pos = tmp.find(' ');
            if( not tmp.substr(0, pos).empty() )
            {
                args_.push_back(tmp.substr(0, pos));
            }
        }
        if( pos == std::string::npos )
        {
            break;
        }
        tmp = tmp.substr(pos + 1);
    }
}

int Cli::check_command_type()
{
    if( args_.empty() )
    {
        return EMPTY;
    }

    // Remove the case sensitivity
    std::string base = args_[0];
    std::transform(base.begin(), base.end(),base.begin(), ::toupper);

    // Loop through the commands and find the correct one
    for( auto &i : COMMANDS )
    {
        for( auto &j : i.lines_ )
        {
            // if j matches with the first word of our introduced command.
            if( j == base )
            {
                // The pointer to the recognize command will point to the one in
                // the current loop.
                recognized_ = &i;

                /* Check for the special cases:
                 * 1: Command not recognized
                 * 2: Command is exit-command
                 * 3: Command doesn't have correct amount of parameters.
                 */

                if( recognized_ == nullptr )
                {
                    return UNKNOWN;
                }
                if( recognized_ == &COMMANDS.at(0) )
                {
                    return QUIT;
                }
                if( (args_.size() == 1 and recognized_->func0_ == nullptr) or
                    (args_.size() == 2 and recognized_->func1_ == nullptr) or
                    (args_.size() == 3 and recognized_->func2_ == nullptr) )
                {
                    return WRONG_PARAMETERS;
                }

                // Normally we just return the amount of arguments
                return args_.size();

                /// Depending on the number, back in the header of this module,
                /// it will match with

            }
        }
    }
    // The command wasn't found while looping, so it must be unknown
    return UNKNOWN;
}
