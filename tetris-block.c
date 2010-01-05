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

TetrisBlock *
tetris_block_new (guint x, guint y, TetrisBlockType type, gboolean is_center_of_mass)
{
}

void
tetris_block_free (TetrisBlock *block)
{
}

TetrisBlock *
tetris_block_copy (TetrisBlock *block)
{
}

void
tetris_block_get_center_of_mass (TetrisBlock *block, guint *x, guint *y)
{
}

gboolean 
tetris_block_is_connected (TetrisBlock *a, TetrisBlock *b)
{
}

