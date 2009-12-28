#include <clutter/clutter.h>
#include <stdlib.h>

void
add_rectangle_one (ClutterActor *stage)
{
  ClutterColor red = {0xff, 0x00, 0x00, 0xff};
  //Don't need to use typesafe cast, since we know it will be a rectangle
  ClutterActor *rect = clutter_rectangle_new ();
  
  clutter_container_add_actor (CLUTTER_CONTAINER (stage), rect);
  
  clutter_actor_set_size (rect, 100, 100);
  clutter_actor_set_position (rect, 0, 0);
  
  clutter_rectangle_set_color (CLUTTER_RECTANGLE (rect), &red);
}

int
main (int argc, char **argv)
{
  ClutterActor *stage;
  clutter_init (&argc, &argv);
  
  stage = clutter_stage_new ();

  add_rectangle_one (stage);

  clutter_actor_show (stage);
  
  clutter_main ();

  return EXIT_SUCCESS;
}
