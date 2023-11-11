#include<map>
#include <iostream>
#include <string>
#include <cstdint>

int main()
{
    std::map<std::string,std::int32_t> badges = { {"John", 12304}, {"Eric", 3204}, {"Mathew", 1320} };

    badges["Paul"] = 14503;

    auto iter = badges.find("Marie");
    if (iter == badges.end())
        std::cout << "Marie n'existe pas" << std::endl;
    else
        std::cout << "Le badge de Marie est le " << iter->second << std::endl;

    iter = badges.find("Eric");
    if (iter == badges.end())
        std::cout << "Marie n'existe pas" << std::endl;
    else
        std::cout << "Le badge d'Eric est le " << iter->second << std::endl;

    for (auto const& values : badges )
        std::cout << values.first << " a pour badge " << values.second << std::endl;

    return EXIT_SUCCESS;  
}