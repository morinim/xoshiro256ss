/**
 *  \file
 *
 *  \copyright Copyright (C) 2018 Manlio Morini.
 *
 *  \license
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this file,
 *  You can obtain one at http://mozilla.org/MPL/2.0/
 */

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
