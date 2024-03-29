#include <iomanip>
#include <map>

#include "xoshiro256ss.h"

int main()
{
  const vigna::xoshiro256ss::result_type reference[] =
  {
    11520u,
    0u,
    1509978240u,
    1215971899390074240u,
    1216172134540287360u,
    607988272756665600u,
    16172922978634559625u,
    8476171486693032832u,
    10595114339597558777u,
    2904607092377533576u
  };

  vigna::xoshiro256ss gen;
  gen.seed({1, 2, 3, 4});

  for (auto r : reference)
  {
    const auto v(gen());

    if (v != r)
    {
      std::cerr << "Error: " << v << " != " << r << '\n';
      return 1;
    }
  }

  std::cout << "OK\n";
}
