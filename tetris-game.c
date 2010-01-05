/*
 * This file is part of a Clutter based Tetris implementation.
 *
 * tetris-game.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * tetris-game.c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with tetris-game.c.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Robert Carr 2009 <racarr@gnome.org>
 * Copyright (C) Amy Wielizcka 2009 <amy.wielizcka@gmail.com>
 */

#include "tetris.h"

TetrisGame *
tetris_game_new (void)
{
  
}

void
tetris_game_drop_all_above (TetrisGame *game, guint row)
{
}

gboolean
tetris_game_move_is_acceptable (TetrisGame *game, TetrisBlock *block, TetrisBlock *new_block)
{
}

gboolean
tetris_game_move_block (TetrisGame *game, TetrisBlock *block, TetrisDirection direction)
{
}

gboolean 
tetris_game_rotate_block (TetrisGame *game, TetrisBlock *block)
{
}
