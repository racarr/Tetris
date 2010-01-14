#include <clutter/clutter.h>
#include <stdlib.h>

#include "tetris.h"

#define BLOCK_DIMENSION 30

ClutterActor *stage;
TetrisGame *game;

static void
game_coords_to_stage_coords (guint gamex, guint gamey,
			     guint *stagex, guint *stagey)
{
  
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
  clutter_rectangle_set_border_width (CLUTTER_RECTANGLE(rect), 5);

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
  
  game = tetris_game_new ();
  
  clutter_main();
  
  return EXIT_SUCCESS;
}
