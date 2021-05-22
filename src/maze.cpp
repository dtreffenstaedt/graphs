#include "maze.h"


#include <boost/program_options.hpp>

auto main(int argc, const char* argv[]) -> int
{
    namespace po = boost::program_options;
    po::variables_map options {};

    po::options_description desc("General options");
    desc.add_options()
            ("help,h", "produce help message")
            ("dimension,d", po::value<std::size_t>()->required(), "Dimension of maze to generate");

    po::store(po::parse_command_line(argc, argv, desc), options);
    if ((options.count("help") != 0) || (options.count("dimension") == 0)) {
        std::cout<<desc;
        return 0;
    }
    po::notify(options);



    std::size_t maze_dimension { options["dimension"].as<std::size_t>() };

    graphs::maze m { maze_dimension};

}
