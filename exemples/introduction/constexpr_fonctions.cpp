#include <iostream>
#include <cmath>
#include <numbers>

constexpr double cteExp(int n)
{
  if consteval 
  {
    if (n==0) return 1;
    else
    {
      if (n%2==0) 
      {
	      double v = cteExp(n/2);
	      return v*v;
      } 
      else 
      {
	      return std::numbers::e * cteExp(n-1);
      }
    }
  }
  else { 
    std::cout << "Appel fct math" << std::endl;
    return std::exp(n); 
  }
}

consteval double evalExp(int n)
{
  if (n==0) return 1;
  else {
    if (n%2==0) {
	    double v = cteExp(n/2);
	    return v*v;
    } 
    else 
    {
	    return std::numbers::e * cteExp(n-1);
    }
  }
}

int main()
{
  constexpr double cx = cteExp(7);
  double ix = 7;
  double x = cteExp(ix);
  double vx = std::exp(7);
  constexpr double cx2 = evalExp(7);
  double x2 = evalExp(7);// Valeur évaluée à la compilation mais x2 non constexpr...
# if defined(DO_ERROR)
  double x3 = evalExp(ix);
# endif
  std::cout << "cx = " << cx << ", x = " << x 
            << ", cx2 = " << cx2 << " et vx = " << vx << std::endl;
  return EXIT_SUCCESS;
}
