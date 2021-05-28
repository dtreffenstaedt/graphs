#include "maze.h"

#include <iostream>

#include <boost/program_options.hpp>

auto main(int argc, const char* argv[]) -> int
{
    namespace po = boost::program_options;
    po::variables_map options {};

    po::options_description desc("General options");
    desc.add_options()
            ("help,h", "produce help message")
            ("x_dimension,x", po::value<std::size_t>()->required(), "X Dimension of maze to generate")
            ("y_dimension,y", po::value<std::size_t>()->required(), "Y Dimension of maze to generate")
            ("no-colour,n", "do not print using colour")
            ;

    po::store(po::parse_command_line(argc, argv, desc), options);
    if ((options.count("help") != 0) || (options.count("x_dimension") == 0) || (options.count("y_dimension") == 0)) {
        std::cout<<desc;
        return 0;
    }
    po::notify(options);


    bool colour { options.count("no-colour") == 0 };

    std::size_t x { options["x_dimension"].as<std::size_t>() };
    std::size_t y { options["y_dimension"].as<std::size_t>() };

    graphs::maze m {x, y, colour};

    std::cout<<m;

    std::cout<<(m.graph());

}
