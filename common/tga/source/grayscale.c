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
#include "tga.h"
#include "tgaheader.h"

int write_tga_grayscale(FILE * file, uint8_t * data, uint16_t width, uint16_t height) {
    struct tga_header header = {
        0,
        0,
        3,
        {0},
        {
            0,
            height,
            width,
            height,
            8,
            (1 << 5) | (1 << 4)
        }
    };

    size_t status;
    status = fwrite(&header, sizeof(struct tga_header), 1, file);
    if(status != 1) return -1;
    status = fwrite(data, sizeof(uint8_t), width * height, file);
    if(status != width * height) return -1;
    return 0;
}
