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


#ifndef PSEUDOMOVES_H
#define PSEUDOMOVES_H

#include "KingMasks.hpp"
#include "KnightMasks.hpp"
#include "SlidersMasks.hpp"
#include "../positionRepresentation/Position.hpp"


class PsLegalMoveMaskGen {
public:
    static Bitboard generatePawnsDefaultMask(const Pieces &pieces, uint8_t side);
    static Bitboard generatePawnsLongMask(const Pieces &pieces, uint8_t side);
    static Bitboard generatePawnsLeftCapturesMask(const Pieces &pieces, uint8_t side, bool includeAllAttacks=false);
    static Bitboard generatePawnsRightCapturesMask(const Pieces &pieces, uint8_t side, bool includeAllAttacks=false);

    static Bitboard generateKnightMask(const Pieces &pieces, uint8_t p, uint8_t side, bool onlyCaptures=false);
    static Bitboard generateBishopMask(const Pieces &pieces, uint8_t p, uint8_t side, bool onlyCaptures=false);
    static Bitboard generateRookMask(const Pieces &pieces, uint8_t p, uint8_t side, bool onlyCaptures=false);
    static Bitboard generateQueenMask(const Pieces &pieces, uint8_t p, uint8_t side, bool onlyCaptures=false);
    static Bitboard generateKingMask(const Pieces &pieces, uint8_t p, uint8_t side, bool onlyCaptures=false);

    static bool inDanger(const Pieces &pieces, uint8_t p, uint8_t side);
private:
    static Bitboard calcRay(const Pieces &pieces, uint8_t p, uint8_t side, bool onlyCaptures, uint8_t direction, bool bsr);
};

#endif
