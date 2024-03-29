#include <iomanip>
#include <map>

#include "xoshiro256ss.h"

void test_xoshiro256ss()
{
  vigna::xoshiro256ss gen;

  std::random_device dev;
  gen.seed(dev());

  std::uniform_int_distribution<> dist(0, 10);

  std::map<unsigned, unsigned> hist;

  for (unsigned n(0); n < 1000000; ++n)
    ++hist[dist(gen)];

  std::cout << "XOSHIRO256**\n";
  for (auto p : hist)
    std::cout << std::setw(3) << p.first << ' '
              << std::string(p.second / 10000, '*') << '\n';
}

void test_xoroshiro128p()
{
  vigna::xoroshiro128p gen;

  std::random_device dev;
  gen.seed(dev());

  std::uniform_int_distribution<> dist(0, 10);

  std::map<unsigned, unsigned> hist;

  for (unsigned n(0); n < 1000000; ++n)
    ++hist[dist(gen)];

  std::cout << "XOROSHIRO128+\n";
  for (auto p : hist)
    std::cout << std::setw(3) << p.first << ' '
              << std::string(p.second / 10000, '*') << '\n';
}

int main()
{
  test_xoshiro256ss();
  test_xoroshiro128p();
}
