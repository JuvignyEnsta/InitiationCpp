#include <thread>
#include <iostream>
#include <string>
#include <vector>

void displayIdentite( int id, std::string const& name)
{   std::cout << "Identité de " << id << " : " << name << std::endl;    }

void updateBoundary( int id, std::vector<double>& values )
{  std::fill(values.begin(), values.end(), 1.5*id);  }

int main()
{
std::thread t(displayIdentite, 3, "maitre");
t.join();

 std::vector<double> values(10);
 std::thread t2(updateBoundary, 3, std::ref(values));
 //std::thread t2(updateBoundary, 3, values);
 t2.join();
 for (auto const& coef : values ) std::cout << coef << " ";
 std::cout << std::endl;
 
    return EXIT_SUCCESS;
}
