#include <clutter/clutter.h>
#include <stdlib.h>

#include "tetris.h"

#define BLOCK_DIMENSION 30

ClutterActor *stage;
TetrisGame *game;

TetrisBlock *current_block;

static void
game_coords_to_stage_coords (guint gamex, guint gamey,
			     guint *stagex, guint *stagey)
{
  *stagex = gamex * BLOCK_DIMENSION;
  *stagey = BLOCK_DIMENSION * TETRIS_BOARD_HEIGHT - gamey * BLOCK_DIMENSION;  
}

static void
update_actor_coords (TetrisBlock *block) 
{
  guint stagex, stagey;
  
  GList *i;
  for (i = block->connections; i; i = i->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      game_coords_to_stage_coords (c->x, c->y, &stagex, &stagey);
      clutter_actor_set_position(c->priv, stagex, stagey);
    }
}

static ClutterActor *
make_block_actor (TetrisBlockType type)
{
  /* Make a clutter rectangle */
  /* Set size to BLOCK_DIMENSION*BLOCK_DIMENSION */
  /* Set border color to black + some width */
  /* Set color based on block type */
  
  ClutterColor black = {0x00, 0x00, 0x00, 0xff};
  ClutterColor block_color;

  ClutterActor *rect = clutter_rectangle_new();

  clutter_actor_set_size (rect, BLOCK_DIMENSION, BLOCK_DIMENSION);
  clutter_rectangle_set_border_color (CLUTTER_RECTANGLE(rect), &black);
  clutter_rectangle_set_border_width (CLUTTER_RECTANGLE(rect), 2);

  switch(type)
    {
    case TETRIS_BLOCK_I: clutter_color_from_string(&block_color, "plum"); break;
    case TETRIS_BLOCK_J: clutter_color_from_string(&block_color, "DarkTurquoise"); break;
    case TETRIS_BLOCK_L: clutter_color_from_string(&block_color, "azure"); break;
    case TETRIS_BLOCK_O: clutter_color_from_string(&block_color, "SeaGreen1"); break;
    case TETRIS_BLOCK_S: clutter_color_from_string(&block_color, "LemonChiffon"); break;
    case TETRIS_BLOCK_T: clutter_color_from_string(&block_color, "goldenrod"); break;
    case TETRIS_BLOCK_Z: clutter_color_from_string(&block_color, "tomato"); break;
    default: g_assert_not_reached();
    }

  clutter_rectangle_set_color(CLUTTER_RECTANGLE (rect), &block_color);
  
  return rect;
}

static void add_new_block();

static gboolean
move_block_down (gpointer data)
{
  /* move block in TetrisGame with tetris_game_move_block */
  /* If move was successful, update block coordinates in clutter world
     return TRUE*/
  /* If not return FALSE */

  TetrisBlock *block = (TetrisBlock*) data;
  gboolean moved = tetris_game_move_block(game, block, TETRIS_DIRECTION_DOWN);

  if (moved) 
    {
      update_actor_coords(block);
      return TRUE;
    }
  else
    {
      add_new_block();
      return FALSE;
    }
}

static void
add_new_block ()
{

  /* Create random block at 3,20*/
  /* Put block on game with tetris_game_place_block */
  /* For each b in block->connections: */
  /*     Make block actor.
         Add to stage at right coords.
         clutter_actor_show. 
         set b->priv to actor */

  TetrisBlock *block = tetris_create_random(3, 19);
  guint stagex, stagey;
  GList *i;
  
  tetris_game_place_block(game, block);
  current_block = block;

  for (i = block->connections; i; i = i->next) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      c->priv = make_block_actor(c->type);
      clutter_container_add_actor(CLUTTER_CONTAINER(stage), c->priv);
      game_coords_to_stage_coords(c->x, c->y, &stagex, &stagey);
      clutter_actor_set_position(c->priv, stagex, stagey);
      clutter_actor_show(c->priv);
    }
  
  g_timeout_add (400, move_block_down, block);
}

static gboolean
stage_key_pressed (ClutterActor *actor,
		   ClutterEvent *event,
		   gpointer user_data)
{
  switch (clutter_event_get_key_symbol (event))
    {
    case CLUTTER_Left:
      g_message("Left!");
      break;
    case CLUTTER_Right:
      g_message("Right!");
      break;
    default: break;
    }
  return TRUE;
}
 
int
main (int argc, char **argv)
{
  ClutterColor black = {0x00, 0x00, 0x00, 0xff};

  clutter_init (&argc, &argv);

  stage = clutter_stage_get_default ();
  
  clutter_actor_set_size (stage, 
			  TETRIS_BOARD_WIDTH*BLOCK_DIMENSION,
			  TETRIS_BOARD_HEIGHT*BLOCK_DIMENSION);
  clutter_stage_set_color (CLUTTER_STAGE (stage), &black);
  
  clutter_actor_show (stage);
  
  g_signal_connect (stage, "key-press-event", G_CALLBACK (stage_key_pressed), NULL);
  
  game = tetris_game_new ();
  
  add_new_block ();
  
  clutter_main();
  
  return EXIT_SUCCESS;
}
