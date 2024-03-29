#include <algorithm>
#include <iomanip>
#include <vector>

#include "xoshiro256ss.h"

bool check_xoshiro256ss()
{
  vigna::xoshiro256ss gen;

  const std::vector<vigna::xoshiro256ss::result_type> reference =
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

  // Check first numbers of the sequence for a given state.
  gen.seed({1, 2, 3, 4});

  for (auto r : reference)
  {
    const auto v(gen());

    if (v != r)
    {
      std::cerr << "Error: " << v << " != " << r << '\n';
      return false;
    }
  }

  // Check `discard` method.
  gen.seed({1, 2, 3, 4});

  const unsigned long long SKIPPED(5);
  gen.discard(SKIPPED);

  for (auto r(std::next(reference.begin(), SKIPPED));
       r != reference.end();
       ++r)
  {
    const auto v(gen());

    if (v != *r)
    {
      std::cerr << "Error: " << v << " != " << *r << '\n';
      return false;
    }
  }

  std::cout << std::setw(16) << std::left << "xoshiro256**" << "[OK]\n";
  return true;
}

bool check_xoroshiro128p()
{
  vigna::xoroshiro128p gen;

  const std::vector<vigna::xoroshiro128p::result_type> reference =
  {
    3791206066794290419u,
    15895565023667069775u,
    10353094603425901311u,
    2310587765582178245u,
    6248954372557818163u,
    17214788232953710521u,
    15724695866974583607u,
    6742597202947952447u,
    1275020938797310118u,
    8226711840634510758u
  };

  // Check first numbers of the sequence for a given state.
  gen.seed();

  for (auto r : reference)
  {
    const auto v(gen());

    if (v != r)
    {
      std::cerr << "Error: " << v << " != " << r << '\n';
      return false;
    }
  }

  // Check `discard` method.
  gen.seed();

  const unsigned long long SKIPPED(5);
  gen.discard(SKIPPED);

  for (auto r(std::next(reference.begin(), SKIPPED));
       r != reference.end();
       ++r)
  {
    const auto v(gen());

    if (v != *r)
    {
      std::cerr << "Error: " << v << " != " << *r << '\n';
      return false;
    }
  }

  std::cout << std::setw(16) << std::left << "xoroshiro128+" << "[OK]\n";
  return true;
}

int main()
{
  const std::vector<bool> results =
    {check_xoshiro256ss(), check_xoroshiro128p()};

  return std::all_of(results.begin(), results.end(),
                     [](auto v) { return v == true; })
         ? 0 : 1;
}
