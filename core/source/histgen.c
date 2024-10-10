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
#include "tga.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char ** argv) {
    int status;

    unsigned int width = 10, height = 10;

    srandom(time(NULL));

    perlin_vec2_t field[width * height];
    status = generate_perlin_field(field, width, height);
    if(status != 0) return status;

    unsigned int scale = 100;

    float valfield[width * scale * height * scale];
    for(unsigned int y = 0; y < height * scale; y++) {
        #pragma omp parallel for
        for(unsigned int x = 0; x < width * scale; x++) {
            float val = get_perlin_value_fractal(((float) x) / ((float) scale), ((float) y) / ((float) scale), 3.0f / width, 8, field, width, height);
            valfield[(y*height*scale)+x] = val;
        }
    }

    uint8_t tgafield[width * scale * height * scale];
    for(size_t i = 0; i < width * scale * height * scale; i++) {
        tgafield[i] = (uint8_t) ((valfield[i] + 1) * 256 / 2);
    }

    FILE * tga = fopen("perlin.tga", "w");
    if(tga == NULL) return -1;

    status = write_tga_grayscale(tga, tgafield, width * scale, height * scale);
    if(status != 0) {
        fclose(tga);
        return status;
    } else {
        status = fclose(tga);
        if(status != 0) return -1;
    }

    return 0;
}
