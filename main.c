#include <clutter/clutter.h>
#include <stdlib.h>

#define STAGE_WIDTH 500
#define STAGE_HEIGHT 500

#define BUTTON_SIZE 50
#define BORDER_SIZE 10

void
setup_stage (ClutterActor *stage)
{
  ClutterColor black = {0x00, 0x00, 0x00, 0xff};

  clutter_actor_set_size (stage, STAGE_WIDTH, STAGE_HEIGHT);
  clutter_stage_set_color (CLUTTER_STAGE (stage), &black);
}

ClutterActor *
make_button (ClutterColor *color, ClutterColor *border_color)
{
  ClutterActor *but;
  
  
  return but;
}

int
main (int argc, char **argv)
{
  ClutterActor *stage;
  clutter_init (&argc, &argv);
  
  stage = clutter_stage_new ();
  setup_stage (stage);

  clutter_actor_show (stage);
  
  clutter_main ();

  return EXIT_SUCCESS;
}
