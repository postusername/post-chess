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


#ifndef UI_H
#define UI_H

#include "Storage.hpp"
#include "../engine/ai/AI.hpp"


class UI {
public:
    UI();

    void start();

private:
    sf::RenderWindow window;
    sf::Event event{};

    Position position;
    std::vector<Position> positions_history;
    sf::Vector2i buff;

    static constexpr int32_t BOARD_MARGIN = 20;

    enum STATUS {
        WHITE_TO_MOVE,
        BLACK_TO_MOVE,
        WHITE_WON,
        BLACK_WON,
        DRAW
    };

    void update();

    void drawCells();

    void drawPieces();

    void drawSelectedPieceMoves();

    void updateWindowTitle();

    [[nodiscard]] sf::Vector2f getCellSize() const;

    [[nodiscard]] sf::Vector2f getCellPosition(int32_t x, int32_t y) const;

    [[nodiscard]] uint8_t getStatus() const;

    [[nodiscard]] std::string getTextureName(int32_t x, int32_t y) const;
};

#endif
