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
  guint i, j;

  g_return_if_fail(game);

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
  GList *i;
  g_return_val_if_fail(game, FALSE);

  for (i = new_block->connections; i; i = i->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      if (c->y <= 0 || c->x < 0 || c->x >= TETRIS_BOARD_WIDTH) 
	{
	  return FALSE;
	}
      //only test if block is actually at a valid y
      if (c->y < TETRIS_BOARD_HEIGHT && game->board[c->y][c->x] != NULL && !tetris_block_is_connected(game->board[c->y][c->x], block))
	{
	  return FALSE;
	}
     }
  return TRUE;
}

gboolean
tetris_game_move_block (TetrisGame *game, TetrisBlock *block, TetrisDirection direction)
{
  TetrisBlock *test_block;  
  GList *i;
  gint dx, dy = 0;

  g_return_val_if_fail(block, FALSE);

  switch(direction)
    {
    case TETRIS_DIRECTION_LEFT:  dx = -1; dy =  0; break;
    case TETRIS_DIRECTION_RIGHT: dx =  1; dy =  0; break;
    case TETRIS_DIRECTION_DOWN:  dx =  0; dy = -1; break;
    default:  g_assert_not_reached();
    }

  test_block = tetris_block_copy(block);

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

  for (i = block->connections; i; i = i->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      game->board[c->y][c->x] = NULL;
    }

  for (i = block->connections; i; i = i->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      c->x = c->x + dx;
      c->y = c->y + dy;
      game->board[c->y][c->x] = c;
    }
  
  return TRUE;
}

/* 
   when i try to rotate the blue and red pieces at the top, i get a series of 
   assertion 'clutter_is_actor(self)' failed 
   errors. it doesn't seem to happen with the other pieces.
   otherwise, rotate now seems to work. 
   the seg fault on rotate was because we were testing tetris_block_is_connected
   (called in tetris_game_move_is_acceptable)
   against a board piece that didn't exist (was off the top of the board)
*/

gboolean 
tetris_game_rotate_block (TetrisGame *game, TetrisBlock *block)
{
  TetrisBlock *test_block = tetris_block_copy(block);
  GList *i;
  guint new_x, new_y, cx, cy, j, dy = 0;

  g_return_val_if_fail(block, FALSE);
  
  tetris_block_get_center_of_mass (block, &cx, &cy);

  for (i = test_block->connections; i; i = i->next) 
    {
      TetrisBlock *b = (TetrisBlock *)i->data;
      new_x = cx - (cy - ((gfloat) b->y));
      new_y = cy + (cx - ((gfloat) b->x));
      b->x = new_x;
      b->y = new_y;
    }

  if(!tetris_game_move_is_acceptable(game, block, test_block)) 
    {
      return FALSE;
    }

  /* 
     test_block has already been rotated,
     for each block in test_block
       if the block extends past the height of the board
       if this is the topmost block that extends past the height of the board
       set dy equal to how far off it goes
  */
  for (i = test_block->connections; i; i = i->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      if (c->y >= TETRIS_BOARD_HEIGHT) 
	{
	  if (c->y - TETRIS_BOARD_HEIGHT + 1 > dy)
	    dy = c->y - TETRIS_BOARD_HEIGHT + 1;
	}
    }

  /* 
     block has not yet been rotated, before rotating
     call move_block to move the block down far enough such that
     when it rotates, it doesn't go off the board
   */
  for (j = 0; j<dy; j++) 
    {
      tetris_game_move_block(game, block, TETRIS_DIRECTION_DOWN);
    }
  
  for (i = block->connections; i; i = i->next) 
    {
      TetrisBlock *b = (TetrisBlock *)i->data;
      game->board[b->y][b->x] = NULL;
    }

  for (i = block->connections; i; i = i->next) 
    {
      TetrisBlock *b = (TetrisBlock *)i->data;
      new_x = cx - (cy - ((gfloat) b->y));
      new_y = cy + (cx - ((gfloat) b->x));
      b->x = new_x;
      b->y = new_y;
      game->board[b->y][b->x] = b;
    }

  return TRUE;
}

void
tetris_game_place_block (TetrisGame *game, TetrisBlock *block)
{
  GList *i;
  
  for (i = block->connections; i; i = i->next)
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      
      game->board[c->y][c->x] = c;
    }
}
