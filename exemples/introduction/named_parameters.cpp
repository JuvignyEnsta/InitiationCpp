#include <iostream>
#include <vector>
#include <cassert>

std::ostream& operator << ( std::ostream& out, std::vector<double> const& u )
{
  out << "[ ";
  for (auto const& val : u ) out << val << " ";
  out << "]";
  return out;
}

struct AxpyParameters {
  double alpha = 1;
  std::size_t dim{0};
  std::vector<double> const& x;
  int incx{1}, offsetX{0};
  std::vector<double>& y;
  int incy{1}, offsetY{0};
};

void axpy( AxpyParameters const& params )
{
  std::size_t dim = params.dim;
  assert(params.x.size() > params.offsetX); assert(params.y.size() > params.offsetY);
  if (dim==0) {
    assert(params.x.size() - params.offsetX == params.y.size() - params.offsetY);
    dim = params.x.size() - params.offsetX;
  }
  assert(params.incx*(dim-1) < params.x.size() - params.offsetX);  assert(params.incy*(dim-1) < params.y.size() - params.offsetY);
  for (std::size_t i=0; i < dim; ++i )
    params.y[i*params.incy + params.offsetY] += params.alpha * params.x[i*params.incx + params.offsetX];
}

int main()
{
  const std::size_t N = 100;
  std::vector<double> u; u.reserve(N);
  std::vector<double> v; v.reserve(N);

  for (std::size_t i = 0; i < N; ++i) {
    u.emplace_back(i+1.);
    v.emplace_back(3*(i+1.));
  }

  axpy( {.alpha=-2., .x=u, .y=v } );
  std::cout << "v = " << v << std::endl;
  return EXIT_SUCCESS;
}
