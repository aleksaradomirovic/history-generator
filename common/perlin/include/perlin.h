/*
 * Copyright (C) 2024 Aleksa Radomirovic
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <stddef.h>

typedef struct {
    float x, y;
} perlin_vec2_t;

int generate_perlin_field(perlin_vec2_t * field, size_t width, size_t height);

float get_perlin_value(float x, float y, perlin_vec2_t * field, size_t width, size_t height);

float get_perlin_value_fractal(float x, float y, float scale, unsigned int depth, perlin_vec2_t * field, size_t width, size_t height);
