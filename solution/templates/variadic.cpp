#include <cstdio>
#include <string>
using namespace std::string_literals;

template<typename ...Ts> void printError( std::string const& fmt, Ts... args  )
{
    fprintf(stderr, fmt.c_str(), args...);
}

int main()
{
    printError("%d et %lg\n"s, 2,3.4 );
    return EXIT_SUCCESS;
}