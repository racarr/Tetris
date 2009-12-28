#include <clutter/clutter.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
  ClutterActor *stage;
  clutter_init (&argc, &argv);
  
  stage = clutter_stage_new ();
  clutter_actor_show (stage);
  
  clutter_main ();

  return EXIT_SUCCESS;
}
