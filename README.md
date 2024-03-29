A simple [`UniformRandomBitGenerator`](https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator) wrapper for the xoshiro256** and xoroshiro128+ PRNGs (see https://prng.di.unimi.it/).

## Features

- Compatible with the C++11 `<random>` library.
  The engine can be plugged into any random number distribution (https://en.cppreference.com/w/cpp/named_req/RandomNumberDistribution) in order to obtain a random number.

- Directly derived from the public-domain C implementations: [1](https://prng.di.unimi.it/xoshiro256starstar.c), [2](https://prng.di.unimi.it/xoroshiro128plus.c).

- Take advantage of C++20 features.

## Usage

```c++
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

  for(unsigned n(0); n < 1000000; ++n)
    ++hist[dist(gen)];

  std::cout << "XOSHIRO256**\n";
  for(auto p : hist)
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

  for(unsigned n(0); n < 1000000; ++n)
    ++hist[dist(gen)];

  std::cout << "XOROSHIRO128+\n";
  for(auto p : hist)
    std::cout << std::setw(3) << p.first << ' '
              << std::string(p.second / 10000, '*') << '\n';
}

int main()
{
  test_xoshiro256ss();
  test_xoroshiro128p();
}
```

and the output is something like:

```
XOSHIRO256**
  0 *********
  1 *********
  2 *********
  3 *********
  4 *********
  5 *********
  6 *********
  7 *********
  8 *********
  9 *********
 10 *********
XOROSHIRO128+
  0 *********
  1 *********
  2 *********
  3 *********
  4 *********
  5 *********
  6 *********
  7 *********
  8 *********
  9 *********
 10 *********
```

([source code](https://github.com/morinim/xoshiro256ss/blob/master/example.cc))

## Remarks

- The implementation is only partially a C++11 [`RandomNumberEngine`](https://en.cppreference.com/w/cpp/named_req/RandomNumberEngine) missing a constructor that creates an engine whose initial state is determined by a single call to [`SeedSequence::generate`](https://en.cppreference.com/w/cpp/named_req/SeedSequence).
- There are many xoshiro / xoroshiro generators. Since we wanted to keep code clean and maintenable, only xoshiro256** and xoroshiro128+ are implemented.

    They're all-purpose (not cryptographically secure) generators with excellent speed, a large state space and cover almost all general use cases.

    By default use xoshiro256**. If you're tight on space use xoroshiro128+.