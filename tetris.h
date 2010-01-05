#ifndef _TETRIS_H
#define _TETRIS_H

#include <glib.h>
#include <stdlib.h>

#define TETRIS_BOARD_WIDTH 10
#define TETRIS_BOARD_HEIGHT 20

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

TetrisBlock *tetris_copy_block(TetrisBlock *block);

void tetris_block_get_center_of_mass(TetrisBlock *block, guint *x, guint *y);
void tetris_connect_blocks(TetrisBlock **blocks, guint num_blocks);
gboolean tetris_block_is_connected(TetrisBlock *a, TetrisBlock *b);

TetrisBlock *tetris_create_I(guint x, guint y);
TetrisBlock *tetris_create_J(guint x, guint y);
TetrisBlock *tetris_create_L(guint x, guint y);
TetrisBlock *tetris_create_O(guint x, guint y);
TetrisBlock *tetris_create_S(guint x, guint y);
TetrisBlock *tetris_create_T(guint x, guint y);
TetrisBlock *tetris_create_Z(guint x, guint y);

TetrisBlock *tetris_create_random(gint x, gint y);

gboolean tetris_move_is_acceptable(TetrisGame *game, TetrisBlock *block, TetrisBlock *new_block);
void tetris_move_block(TetrisGame *game, TetrisBlock *block, TetrisDirection direction);
void tetris_rotate_block(TetrisGame *game, TetrisBlock *block);

TetrisGame *tetris_game_new();
void tetris_game_drop_all_above(TetrisGame *game, guint row);

#endif