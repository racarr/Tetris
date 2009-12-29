#include <clutter/clutter.h>
#include <stdlib.h>

#define STAGE_WIDTH 500
#define STAGE_HEIGHT 500

#define BUTTON_SIZE 50
#define BORDER_SIZE 5

int buttons_pressed = 0;

void
setup_winning_animation (ClutterActor *stage)
{
  ClutterColor white = {0xff, 0xff, 0xff, 0xff};
  ClutterActor *text = clutter_text_new_full("Bitstream Vera Sans 40",
					     "Congratulations",
					     &white);
  
  clutter_actor_set_anchor_point_from_gravity (text, CLUTTER_GRAVITY_CENTER);



  clutter_actor_show (text);
}

void
button_press_callback (ClutterActor *actor,
		       ClutterEvent *event,
		       gpointer user_data)
{
  clutter_actor_animate(actor, CLUTTER_EASE_OUT_QUAD, 250, "opacity", 0, NULL);
  buttons_pressed++;
  
  if (buttons_pressed == 2)
    {
      ClutterActor *stage = clutter_actor_get_parent (actor);
      setup_winning_animation(stage);
    }
}

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
  ClutterActor *but = clutter_rectangle_new ();

  clutter_actor_set_size (but, BUTTON_SIZE, BUTTON_SIZE);

  clutter_rectangle_set_color (CLUTTER_RECTANGLE (but), color);
  clutter_rectangle_set_border_color (CLUTTER_RECTANGLE (but), border_color);
  clutter_rectangle_set_border_width (CLUTTER_RECTANGLE (but), BORDER_SIZE);
  
  return but;
}

void
populate_stage (ClutterActor *stage)
{
  ClutterActor *b1, *b2;
  ClutterColor red = {0xff, 0x00, 0x00, 0xff};
  ClutterColor blue = {0x00, 0x00, 0xff, 0xff};
  ClutterColor white = {0xff, 0xff, 0xff, 0xff};
  
  b1 = make_button (&red, &white);
  b2 = make_button (&blue, &white);

  clutter_container_add_actor (CLUTTER_CONTAINER (stage), b1);
  clutter_container_add_actor (CLUTTER_CONTAINER (stage), b2);
  
  clutter_actor_set_anchor_point_from_gravity (b1, CLUTTER_GRAVITY_CENTER);
  clutter_actor_set_anchor_point_from_gravity (b2, CLUTTER_GRAVITY_CENTER);
  
  clutter_actor_set_position (b1, 50, STAGE_HEIGHT/2);
  clutter_actor_set_position (b2, STAGE_WIDTH-50, STAGE_HEIGHT/2);

  clutter_actor_set_reactive (b1, TRUE);
  clutter_actor_set_reactive (b2, TRUE);

  g_signal_connect (b1, "button-press-event", G_CALLBACK (button_press_callback), NULL);
  g_signal_connect (b2, "button-press-event", G_CALLBACK (button_press_callback), NULL);
}

int
main (int argc, char **argv)
{
  ClutterActor *stage;
  clutter_init (&argc, &argv);
  
  stage = clutter_stage_new ();
  setup_stage (stage);
  populate_stage (stage);

  clutter_actor_show (stage);
  
  clutter_main ();

  return EXIT_SUCCESS;
}
