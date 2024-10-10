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

#include <stdint.h>

struct tga_colormap_header {
    uint16_t first;
    uint16_t len;
    uint8_t entsz;
} __attribute__((packed));

struct tga_imgspec_header {
    uint16_t xorg;
    uint16_t yorg;
    uint16_t width;
    uint16_t height;
    uint8_t depth;
    uint8_t imgdesc;
} __attribute__((packed));

struct tga_header {
    uint8_t idlen;
    uint8_t cmap;
    uint8_t type;

    struct tga_colormap_header colormap_header;
    struct tga_imgspec_header imgspec_header;
} __attribute__((packed));
