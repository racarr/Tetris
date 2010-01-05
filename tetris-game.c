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
  TetrisGame *ret;
  
  /* Allocate new game */
  /* Zero board array */
  
  return ret;
}

void 
tetris_game_free (void)
{
}

void
tetris_game_drop_all_above (TetrisGame *game, guint row)
{
  /* Is game non null */
  /* Zero everything at Y=row + free blocks */
  /* Go through all Y's above row:
        if board member is non null (there is a block there):
    	   move down + update y coord in block
  */
}

gboolean
tetris_game_move_is_acceptable (TetrisGame *game, TetrisBlock *block, TetrisBlock *new_block)
{
  /* Is game non null */
  /* For every block in new block connections:
         is y < 0 or x < 0 or x >= TILE_WIDTH? return false
         is the block at x/y != NULL and not connected to our block?
         return false */
  /* Return true */
}

gboolean
tetris_game_move_block (TetrisGame *game, TetrisBlock *block, TetrisDirection direction)
{
  /* Is block non null */
  gint dx, dy = 0;
  TetrisBlock *test_block;
  
  
  /* Compute dx and dy based on direction */
  /* Copy block to test block */
  /* Translate all blocks connected to test block by dx/dy */
  /* Is test_block an acceptable move? if not return false, otherwise
     perform translation on actual block + update game board */
  return TRUE;
}

gboolean 
tetris_game_rotate_block (TetrisGame *game, TetrisBlock *block)
{
}
