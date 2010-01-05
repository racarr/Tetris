/*
 * This file is part of a Clutter based Tetris implementation.
 *
 * tetris.h is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * tetris.h is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with tetris.h.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Robert Carr 2009 <racarr@gnome.org>
 * Copyright (C) Amy Wielizcka 2009 <amy.wielizcka@gmail.com>
 */


#ifndef _TETRIS_H
#define _TETRIS_H

#include <glib.h>
#include <stdlib.h>

#define TETRIS_BOARD_WIDTH 10
#define TETRIS_BOARD_HEIGHT 20

#define TETRIS_BLOCK_START_X 3
#define TETRIS_BLOCK_START_Y 20

typedef enum
{
  TETRIS_DIRECTION_DOWN,
  TETRIS_DIRECTION_LEFT,
  TETRIS_DIRECTION_RIGHT
} TetrisDirection;

typedef enum
{
  TETRIS_BLOCK_I,
  TETRIS_BLOCK_J,
  TETRIS_BLOCK_L,
  TETRIS_BLOCK_S,
  TETRIS_BLOCK_Z,
  TETRIS_BLOCK_T,
  TETRIS_BLOCK_O
} TetrisBlockType;

typedef struct _TetrisBlock
{
  GList *connections;
  guint x,y;
  TetrisBlockType type;
  
  gboolean center_of_mass;
} TetrisBlock;

typedef struct _TetrisGame
{
  TetrisBlock *board[TETRIS_BOARD_HEIGHT][TETRIS_BOARD_WIDTH];
} TetrisGame;

TetrisBlock *tetris_block_new(guint x, guint y, TetrisBlockType type,
			      gboolean is_center_of_mass);
void tetris_block_free(TetrisBlock *block);

TetrisBlock *tetris_block_copy(TetrisBlock *block);

void tetris_block_get_center_of_mass(TetrisBlock *block, guint *x, guint *y);
gboolean tetris_block_is_connected(TetrisBlock *a, TetrisBlock *b);

void tetris_interconnect_blocks(TetrisBlock **blocks, guint num_blocks);

TetrisBlock *tetris_create_I(guint x, guint y);
TetrisBlock *tetris_create_J(guint x, guint y);
TetrisBlock *tetris_create_L(guint x, guint y);
TetrisBlock *tetris_create_O(guint x, guint y);
TetrisBlock *tetris_create_S(guint x, guint y);
TetrisBlock *tetris_create_T(guint x, guint y);
TetrisBlock *tetris_create_Z(guint x, guint y);

TetrisBlock *tetris_create_random(guint x, guint y);

gboolean tetris_game_move_is_acceptable(TetrisGame *game, TetrisBlock *block, TetrisBlock *new_block);
gboolean tetris_game_move_block(TetrisGame *game, TetrisBlock *block, TetrisDirection direction);
gboolean tetris_game_rotate_block(TetrisGame *game, TetrisBlock *block);

TetrisGame *tetris_game_new();
void tetris_game_free(TetrisGame *game);

void tetris_game_drop_all_above(TetrisGame *game, guint row);

#endif
