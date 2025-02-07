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


#ifndef SLIDERMASKS_H
#define SLIDERMASKS_H

#include "../positionRepresentation/Bitboard.hpp"


namespace SlidersMasks {
    enum DIRECTION {
        NORTH,
        SOUTH,
        WEST,
        EAST,
        NORTH_WEST,
        NORTH_EAST,
        SOUTH_WEST,
        SOUTH_EAST,
    };

    static consteval Bitboard calcMask(uint8_t p, int8_t direction) {
        Bitboard mask = 0;

        int x = p % 8;
        int y = p / 8;

        for (; ;) {
            switch (direction) {
                case SlidersMasks::DIRECTION::NORTH:
                    y = y + 1;
                    break;
                case SlidersMasks::DIRECTION::SOUTH:
                    y = y - 1;
                    break;
                case SlidersMasks::DIRECTION::WEST:
                    x = x - 1;
                    break;
                case SlidersMasks::DIRECTION::EAST:
                    x = x + 1;
                    break;
                case SlidersMasks::DIRECTION::NORTH_WEST:
                    y = y + 1;
                    x = x - 1;
                    break;
                case SlidersMasks::DIRECTION::NORTH_EAST:
                    y = y + 1;
                    x = x + 1;
                    break;
                case SlidersMasks::DIRECTION::SOUTH_WEST:
                    y = y - 1;
                    x = x - 1;
                    break;
                case SlidersMasks::DIRECTION::SOUTH_EAST:
                    y = y - 1;
                    x = x + 1;
                    break;
                default:
                    break;
            }

            if (x > 7 or x < 0 or y > 7 or y < 0) {
                break;
            }

            mask = BOp::set1(mask, y * 8 + x);
        }

        return mask;
    }

    static consteval std::array<std::array<Bitboard, 8>, 64> calcMasks() {
        std::array<std::array<Bitboard, 8>, 64> masks{};
        for (uint8_t i = 0; i < 64; i++) {
            for (int8_t j = 0; j < 8; j++) {
                masks[i][j] = calcMask(i, j);
            }
        }
        return masks;
    }

    static constexpr std::array<std::array<Bitboard, 8>, 64> MASKS = calcMasks();
}

#endif
