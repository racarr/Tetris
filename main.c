#include <clutter/clutter.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
  clutter_init (&argc, &argv);
  
  clutter_main ();

  return EXIT_SUCCESS;
}
