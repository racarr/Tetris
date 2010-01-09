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
  ret = g_malloc0 (sizeof(TetrisGame));

  return ret;
}

void 
tetris_game_free (TetrisGame *game)
{
  g_free (game);
}

void
tetris_game_drop_all_above (TetrisGame *game, guint row)
{
  /* Is game non null */
  /* Go through all Y's above row:
     if board member is non null (there is a block there):
     move down + update y coord in block
  */

  g_return_if_fail(game);

  guint i, j;
  for (i=row+1; i<TETRIS_BOARD_HEIGHT; i++) 
    {
      for (j = 0; j<TETRIS_BOARD_WIDTH; j++)
	{
	  if (game->board[i][j])
	    {
	      game->board[i][j]->y = game->board[i][j]->y-1;
	      game->board[i-1][j] = game->board[i][j];
	      game->board[i][j] = NULL;
	    }
	}
    }
}

gboolean
tetris_game_move_is_acceptable (TetrisGame *game, TetrisBlock *block, TetrisBlock *new_block)
{
  /* Is game non null */
  /* For every block in new block connections:
         is y < 0 or x < 0 or x >= TETRIS_BOARD_WIDTH? return false
         is the block at x/y != NULL and not connected to our block?
         return false */
  /* Return true */

  g_return_val_if_fail(game, FALSE);

  GList *i;
  for (i = new_block->connections; i; i = i->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      if (c->y < 0 || c->x < 0 || c->x >= TETRIS_BOARD_WIDTH) 
	{
	  return FALSE;
	}
      if (game->board[c->y][c->x] != NULL && !tetris_block_is_connected(game->board[c->y][c->x], block))
	{
	  return FALSE;
	}
     }
  return TRUE;
}

gboolean
tetris_game_move_block (TetrisGame *game, TetrisBlock *block, TetrisDirection direction)
{
  /* Is block non null */
  g_return_val_if_fail(block, FALSE);

  gint dx, dy = 0;
  TetrisBlock *test_block;  

  switch(direction)
    {
    case TETRIS_DIRECTION_LEFT:  dx = -1; dy =  0; break;
    case TETRIS_DIRECTION_RIGHT: dx =  1; dy =  0; break;
    case TETRIS_DIRECTION_DOWN:  dx =  0; dy = -1; break;
    default:  g_assert_not_reached();
    }

  test_block = tetris_block_copy(block);

  GList *i;
  for (i = test_block->connections; i; i = i->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      c->x = c->x + dx; 
      c->y = c->y + dy;
    }

  if(!tetris_game_move_is_acceptable(game, block, test_block)) 
    {
      return FALSE;
    }

  GList *j;
  for (j = block->connections; j; j = j->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      game->board[c-y][c->x] = NULL;
    }

  for (j = block->connections; j; j = j->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      c->x = c->x + dx;
      c->y = c->y + dy;
      game->board[c->y][c->x] = c;
    }
  
  /* Compute dx and dy:- based on direction */
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
