/*
 *  chess-cpp
 *  Copyright (C) 2025 postusername
 *
 *  chess-cpp is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  chess-cpp is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with chess-cpp.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef REPEATHISTORY_H
#define REPEATHISTORY_H

#include <vector>

#include "ZobristHash.hpp"


class RepetitionHistory {
public:
    RepetitionHistory();

    void addPosition(ZobristHash hash);

    void clear();

    [[nodiscard]] uint8_t getRepetitionNumber(ZobristHash hash) const;

private:
    std::vector<ZobristHash> hashes;
};

#endif
