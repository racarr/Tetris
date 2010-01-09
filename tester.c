#include "tetris.h"

void
test_block_functions (void)
{
  TetrisBlock *t1, *t2;
  g_message ("Testing tetris-block.c functions");
  
  t1 = tetris_block_new (0, 0, TETRIS_BLOCK_I, FALSE);
  g_assert (t1->x == 0);
  g_assert (t1->y == 0);
  g_assert (t1->type == TETRIS_BLOCK_I);
  g_assert (t1->center_of_mass == FALSE);
  g_assert (t1->connections == NULL);
  
  t2 = tetris_block_copy (t1);
  g_assert (t2->x == t1->x);
  g_assert (t2->y == t1->y);
  g_assert (t2->type == t1->type);
  g_assert (t2->center_of_mass == t1->center_of_mass);
  g_assert (g_list_length (t1->connections) == 
	    g_list_length (t2->connections));
  
}

int 
main (int argc, char **argv)
{
  TetrisGame *game = tetris_game_new ();
  
  test_block_functions ();
}
