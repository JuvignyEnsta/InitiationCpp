#include <cstdlib>
#include <regex>
#include <iostream>

int main()
{
    std::string str = "zzxayyzzzzXaYyXz";
    std::regex re1(".*(a|xayy)"); // ECMA
    std::regex re2(".*(a|xayy)", std::regex::extended); // POSIX
    std::regex re3(".*(a|xayy)", std::regex::extended | std::regex::icase); // POSIX
 
    std::cout << "Searching for .*(a|xayy) in zzxayyzz:\n";
    std::smatch m;
    std::regex_search(str, m, re1);
    for ( auto const& match : m )
        std::cout << " ECMA matches : " << match << '\n';
    std::regex_search(str, m, re2);
    for ( auto const& match : m )
        std::cout << " Posix matches : " << match << '\n';

    std::regex_search(str, m, re3);
    for ( auto const& match : m )
        std::cout << " Posix matches without cases : " << match << '\n';

    

    return EXIT_SUCCESS;
}