/*
 * Paul Rafferty 2019
 */

#ifndef __file_h__
#define __file_h__

#include <graphics/canvas.h>
#include <graphics/color.h>

/*
 * Export the current canvas to a ppm file with the given name
 * Returns 1 on success, 0 otherwise
 */
const int export_to_ppm(const struct canvas c, const char *filename);

/*
 * Export a canvas to bitmap
 */
const int export_to_bmp(const struct canvas c, const char *filename);

/*
 * create a canvas from a bitmap file
 */
struct canvas canvas_from_bmp(const char *filename);

#endif // __file_h__
