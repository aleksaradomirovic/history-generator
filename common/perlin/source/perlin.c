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
#include "perlin.h"

#include <math.h>
#include <stdlib.h>

int generate_perlin_field(perlin_vec2_t * field, size_t width, size_t height) {
    for(size_t y = 0; y < height; y++) {
        for(size_t x = 0; x < width; x++) {
            float angle = (float) random();
            field[(y*height)+x].x = cosf(angle);
            field[(y*height)+x].y = sinf(angle);
        }
    }

    return 0;
}

__attribute__((optimize ("no-fast-math")))
static int clip(int x, int limit) {
    return x - (limit * (x / limit));
}

static float dot_product_gradient(perlin_vec2_t * field, size_t x, size_t y, size_t width, size_t height, float dx, float dy) {
    perlin_vec2_t vec = field[(clip(y, height) * height) + clip(x, width)];
    return (vec.x * dx) + (vec.y * dy);
}

static float interpolate(float i, float j, float w) {
    // return ((j - i) * w) + i;
    // return ((j - i) * (3.0f - (w * 2.0f)) * w * w) + i;
    return ((j - i) * ((w * ((w * 6) - 15)) + 10) * w * w * w) + i;
}

float get_perlin_value(float x, float y, perlin_vec2_t * field, size_t width, size_t height) {
    size_t ix = (size_t) floorf(x),
           iy = (size_t) floorf(y);
    
    float xint[2];
    #pragma omp simd
    for(size_t j = 0; j < 2; j++) {
        float dots[2];
        #pragma omp simd
        for(size_t i = 0; i < 2; i++) {
            dots[i] = dot_product_gradient(field, ix+i, iy+j, width, height, x - ((float)(ix + i)), y - ((float)(iy + j)));
        }
        xint[j] = interpolate(dots[0], dots[1], x - ix);
    }

    float yint = interpolate(xint[0], xint[1], y - iy);
    return yint;
}

float get_perlin_value_fractal(float x, float y, float scale, unsigned int depth, perlin_vec2_t * field, size_t width, size_t height) {
    float frac = 0;
    for(unsigned int i = 0; i < depth; i++) {
        float iscale = scale * powf(2, i);
        frac += get_perlin_value(x*iscale, y*iscale, field, width, height) / powf(2, i+1);
    }
    return frac;
}
