A simple [`UniformRandomBitGenerator`](http://en.cppreference.com/w/cpp/concept/UniformRandomBitGenerator) wrapper for the [xoroshiro128+](http://xoroshiro.di.unimi.it/) PRNG.

## Features

- Compatible with the C++11 `<random>` library.
  The engine can be plugged into any random number distribution ([`http://en.cppreference.com/w/cpp/concept/RandomNumberDistribution`](http://en.cppreference.com/w/cpp/concept/RandomNumberDistribution)) in order to obtain a random number.

- Directly derived from the [public-domain C implementations](http://xoroshiro.di.unimi.it/xoroshiro128plus.c).

## Usage

```c++
#include <iomanip>
#include <map>

#include "xoroshiro128p.h"

int main()
{
  vigna::xoroshiro128p gen;

  std::random_device dev;
  gen.seed(dev());

  std::uniform_int_distribution<> dist(0, 10);

  std::map<unsigned, unsigned> hist;

  for(unsigned n(0); n < 1000000; ++n)
    ++hist[dist(gen)];

  for(auto p : hist)
    std::cout << std::setw(3) << p.first << ' '
              << std::string(p.second / 10000, '*') << '\n';
}
```

and the output is something like:

```
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

([source code](https://github.com/morinim/xoroshiro128p/blob/master/example.cc))

## Remarks

- The implementation is only partially a C++11 [`RandomNumberEngine`](http://en.cppreference.com/w/cpp/concept/RandomNumberEngine) missing:
  - a constructor that creates an engine whose initial state is determined by a single call to [`SeedSequence::generate`](http://en.cppreference.com/w/cpp/concept/SeedSequence);
  - a way to advance the engine state as if by `n` consecutive calls.
