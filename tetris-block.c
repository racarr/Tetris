/*
 * This file is part of a Clutter based Tetris implementation.
 *
 * tetris-block.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * tetris-block.c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with tetris-block.c.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Robert Carr 2009 <racarr@gnome.org>
 * Copyright (C) Amy Wielizcka 2009 <amy.wielizcka@gmail.com>
 */

#include "tetris.h"

/*
 * tetris_block_new:
 * @x: The x-coordinate of the new block.
 * @y: The y-coordinate of the new block.
 * @type: The #TetrisBlockType of the new block.
 * @is_center_of_mass: Is the new block the center of mass of a block formation?
 *
 * Allocates memory and initializes variables for a single block.
 *
 * Return value: The newly created #TetrisBlock
 */
TetrisBlock *
tetris_block_new (guint x, guint y, TetrisBlockType type, gboolean is_center_of_mass)
{
  TetrisBlock *ret;
  
  /* Allocate Block */
  ret = g_malloc0 (sizeof(TetrisBlock));

  /* Initialize Variables*/
  ret->x = x;
  ret->y = y;
  ret->type = type;
  ret->center_of_mass = is_center_of_mass;

  return ret;
}

/*
 * tetris_block_free:
 * @block: The #TetrisBlock to free.
 *
 * Free's all memory assosciated with a single #TetrisBlock.
 */
void
tetris_block_free (TetrisBlock *block)
{
  /* Free blocks connection member */
  g_list_free(block->connections);
  /* Free block */
  g_free(block);
}


/*
 * tetris_block_copy:
 * @block: The #TetrisBlock to copy.
 *
 * Copies a #TetrisBlock and all blocks it is connected to.
 *
 * Return value: The #TetrisBlock in the newly allocated formation
 * corresponding to @block.
 */
TetrisBlock *
tetris_block_copy (TetrisBlock *block)
{
  TetrisBlock *ret;
  
  /* Make sure block is non null */
  if(!block) {
    return NULL;
  }

  TetrisBlock **knex;
  knex = g_malloc0 (sizeof(TetrisBlock *) * (g_list_length(block->connections)+1));

  GList *i;
  guint j = 0;
  for (i = block->connections; i; i = i->next, j++) 
    {
      TetrisBlock *c = (TetrisBlock *)i->data;
      knex[j] = tetris_block_new(c->x, c->y, c->type, c->center_of_mass);
    }

  tetris_interconnect_blocks(knex, j);

  ret = knex[0];

  g_free(knex);
  
  return ret;
}

/*
 * tetris_block_get_center_of_mass:
 * @block: A block in the formation to find the center of mass of.
 * @x: A pointer in which to store the x-coordinate of the center of mass.
 * @y: A pointer in which to store the y-coordinate of the center of mass.
 *
 * Calculates the center-of-mass (point to rotate around) of the block
 * formation containing @block, and stores the result in the @x and @y 
 * pointers.
 */
void
tetris_block_get_center_of_mass (TetrisBlock *block, guint *x, guint *y)
{
  /* Make sure block is non null */
  if(!block) {
    return;
  }

  GList *i;
  guint x_avg, y_avg, j=0;
  TetrisBlock *c;
  
  /* Is block type TETRIS O? if so center of mass is average of other
     blocks coords */
  if(block->type = TETRIS_BLOCK_O) 
    {
      for(i=block->connections; i; i=i->next, j++) 
	{
	  c = (TetrisBlock *)i->data;
	  x_avg = x_avg + c->x;
	  y_avg = y_avg + c->y;
	}
      x_avg = x_avg / j;
      y_avg = y_avg / j;

      *x = x_avg;
      *y = y_avg;
    }
	  
  /* If not, go through block->connections and search for block with
     b->center_of_mass == TRUE */
  else {
    for(i=block->connection; i; i=i->next) 
      {
	c = (TetrisBlock *)i->data;
	if( c->center_of_mass ) 
	  {
	    *x = c->x;
	    *y = c->y;
	  }
      }
  }
  return;
}

/*
 * tetris_block_is_connected:
 * @a: A valid #TetrisBlock
 * @b: A valid #TetrisBlock to search for in the connections of @a
 *
 * Determines whether @b is in the block formation of @a (in all valid
 * blocks this should be a commutative relation).
 *
 * Return value: Returns whether @b is in the block formation of @a.
 */
gboolean 
tetris_block_is_connected (TetrisBlock *a, TetrisBlock *b)
{
  GList *i;
  for (i = a->connections; i; i = i->next)
    {
      TetrisBlock *j = (TetrisBlock *)i->data;
      if (j == b)
	return TRUE;
    }
  return FALSE;
}

