/*
 * This file is part of a Clutter based Tetris implementation.
 *
 * tetris-util.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * tetris-util.c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with tetris-util.c.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Robert Carr 2009 <racarr@gnome.org>
 * Copyright (C) Amy Wielizcka 2009 <amy.wielizcka@gmail.com>
 */

#include "tetris.h"

/*
 * tetris_interconnect_blocks:
 * @blocks: An array of blocks to interconnect.
 * @num_blocks: The number of blocks in the @blocks array.
 *
 * Takes an array of blocks (@blocks) and puts each #TetrisBlock in
 * each other blocks list of connections, including itself.
 */
void
tetris_interconnect_blocks (TetrisBlock **blocks, guint num_blocks)
{
  guint i, j;

  for (i=0; i<num_blocks; i++) 
    {
      for (j=0; j<num_blocks; j++) 
	{
	  blocks[i]->connections = g_list_append(blocks[i]->connections, blocks[j]);
	}
    }
}

TetrisBlock *
tetris_create_I (guint x, guint y)
{
  TetrisBlock *blocks[] = 
    {
      tetris_block_new (x, y, TETRIS_BLOCK_I, FALSE),
      tetris_block_new (x+1, y, TETRIS_BLOCK_I, TRUE),
      tetris_block_new (x+2, y, TETRIS_BLOCK_I, FALSE),
      tetris_block_new (x+3, y, TETRIS_BLOCK_I, FALSE)
    };
  tetris_interconnect_blocks (blocks, 4);
  
  return blocks[0];
}

TetrisBlock *
tetris_create_J (guint x, guint y)
{
}

TetrisBlock *
tetris_create_L (guint x, guint y)
{
}

TetrisBlock *
tetris_create_O (guint x, guint y)
{
}

TetrisBlock *
tetris_create_S (guint x, guint y)
{
}

TetrisBlock *
tetris_create_T (guint x, guint y)
{
}

TetrisBlock *
tetris_create_Z (guint x, guint y)
{
}

TetrisBlock *
tetris_create_random (guint x, guint y)
{
  gint32 r = g_random_int_range(1,8);
  switch (r)
    {
    case 1: return tetris_create_I(x,y);
    case 2: return tetris_create_J(x,y);
    case 3: return tetris_create_L(x,y); 
    case 4: return tetris_create_O(x,y); 
    case 5: return tetris_create_S(x,y);
    case 6: return tetris_create_T(x,y); 
    case 7: return tetris_create_Z(x,y); 
    default: g_assert_not_reached();
    }
}
