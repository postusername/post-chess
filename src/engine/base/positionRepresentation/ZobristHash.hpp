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


#ifndef HASH_H
#define HASH_H

#include "Pieces.hpp"
#include "ZobristHashConstants.hpp"


class ZobristHash {
public:
    ZobristHash();

    ZobristHash(const Pieces &pieces, bool blackToMove, bool wlCastling, bool wsCastling, bool blCastling,
                bool bsCastling);

    friend bool operator ==(ZobristHash left, ZobristHash right);

    void invertPiece(uint8_t square, uint8_t type, uint8_t side);

    void invertMove();

    void invertWLCastling();

    void invertWSCastling();

    void invertBLCastling();

    void invertBSCastling();

    [[nodiscard]] uint64_t getValue() const;

private:
    uint64_t value{};
};

#endif
