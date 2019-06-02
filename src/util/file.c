/*
 * Paul Rafferty 2019
 */

#include <stdio.h>
#include <stdlib.h> // for itoa
#include <string.h> // memcpy
#include <stdint.h>
#include <errno.h>

#include <util/file.h>
#include <util/log.h>
#include <util/mem.h>
#include <graphics/canvas.h>
#include <graphics/color.h>

/*
 * Create a header for a ppm file, it will follow this format:
 * "P3
 *  WW HH
 *  255"
 * Where WW and HH are strings of the decimal representations of the width and
 * height respectively (not restricted to 2 chars) (P3 is the file format
 * signature and 255 is the max colour component value (R, G and B = 0-255)
 */
static char *_create_ppm_header(const struct canvas c)
{
        // get header length:
        int wc = 1, hc = 1, w = c.w, h = c.h;
        while ((w /= 10) > 0) {
                wc++;
        }

        while ((h /= 10) > 0) {
                hc++;
        }

        #define SIG "P3\n"
        #define END "255\n"

        // "P3\n" + (wc + ' ' + hc copy string safe+ '\n') + "255\n" + '\0'
        int len = 3 + wc + 1 + hc + 1 + 4 + 1;
        char *header = (char *)mem_alloc(len);
        char *ptr = header;

        ptr += sprintf(ptr, SIG);
        ptr += sprintf(ptr, "%d %d\n", c.w, c.h);
        ptr += sprintf(ptr, END);

        return header; 
}

/*
 * Return a string formatted to the ppm pixel data format.
 * ie: 255 0 0 252 152 0 212 124 0 22 76
 * where each number is an r, g or b component
 * restricts each line to 12 components before a newline (ppm has a 70 char
 * legacy limit)
 */
static char *_create_ppm_data(struct canvas c)
{
        int num_pix = c.w * c.h;

        // reserve space assuming each R, G and B will be 3 chars long
        // and for a space between them
        char *data = (char *)mem_alloc(num_pix * 3 * 4);
        char *ptr = data;

        // ppm files like a line break every 70 chars (legacy stuff), I'll
        // put one every 5 pixels (60 chars worst case scenario, 20 best)
        #define LINE_BREAK 5
        for (int i = 0; i < c.w * c.h; i++) {
                char end = (i % LINE_BREAK == (LINE_BREAK-1)) ? '\n' : ' ';
                ptr += sprintf(ptr, "%s%c", color_to_ppm_string(c.pixels[i]), end);
        }

        return data;   
}


/*
 * Export the current canvas to a ppm file with the given name
 * Returns 1 on success, 0 otherwise
 */
const int export_to_ppm(const struct canvas c, const char *filename)
{
        char *header = _create_ppm_header(c);
        char *data = _create_ppm_data(c);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
                log_err("Unable to open file");
                fprintf(stderr, "%s\n", strerror(errno));
                return 0;
        }

        fprintf(file, "%s%s", header, data);
        fclose(file);

        mem_free(header);
        mem_free(data);
        
        return 1;
}

#define BMP_FILE_INFO_SIZE 14
#define BMP_HEADER_SIZE 54

/*
 * BMP files start with a 14 header containing various info about the file
 */
static void *_create_bmp_file_header(const struct canvas c)
{        
        char *buf = mem_alloc(BMP_HEADER_SIZE);
        
        // signature
        memcpy(buf, "BM", 2);

        // the total size of the header for bitmaps varies, but this will
        // always use 54, rest of the file is 4 bytes per pixel (ARGB)
        uint32_t word32 = BMP_HEADER_SIZE + c.w * c.h * 4;
        memcpy(buf+2, &word32, sizeof(word32));
        word32 = 0;       // next 4 bytes must be 0
        memcpy(buf+6, &word32, sizeof(word32));
        word32 = BMP_HEADER_SIZE;      // offset to start of pixel data in file
        memcpy(buf+10, &word32, sizeof(word32));

        word32 = BMP_HEADER_SIZE - BMP_FILE_INFO_SIZE;
        memcpy(buf+BMP_FILE_INFO_SIZE, &word32, sizeof(word32));
        word32 = c.w;
        memcpy(buf+BMP_FILE_INFO_SIZE+4, &word32, sizeof(word32));
        word32 = c.h * -1;      // windows bmp writes stuff upside down...  
        memcpy(buf+BMP_FILE_INFO_SIZE+8, &word32, sizeof(word32));
        uint16_t wee_num = 1;   // biPlanes
        memcpy(buf+BMP_FILE_INFO_SIZE+12, &wee_num, sizeof(wee_num));
        wee_num = 32;   // bit per pixel
        memcpy(buf+BMP_FILE_INFO_SIZE+14, &wee_num, sizeof(wee_num));
        word32 = 0;       // compression (0 = none)
        memcpy(buf+BMP_FILE_INFO_SIZE+16, &word32, sizeof(word32));
        // image size, 0 for uncompressed images
        memcpy(buf+BMP_FILE_INFO_SIZE+20, &word32, sizeof(word32));
        // preferred resolution, optional
        memcpy(buf+BMP_FILE_INFO_SIZE+24, &word32, sizeof(word32));
        // preferred resolution, optional
        memcpy(buf+BMP_FILE_INFO_SIZE+28, &word32, sizeof(word32));
        // number of colours used, 0 for no restrictions
        memcpy(buf+BMP_FILE_INFO_SIZE+32, &word32, sizeof(word32));
        // significant colours (?), usually 0 apparently
        memcpy(buf+BMP_FILE_INFO_SIZE+36, &word32, sizeof(word32));

        return buf;
}

static void *_create_bmp_data(const struct canvas c)
{
        uint32_t *buf = mem_alloc(c.w * c.h * 4);
        for (int i = 0; i < c.w * c.h; i++) {
                uint32_t val = color_to_RGBA(c.pixels[i]);
                *(buf+i) = val;
        }

        return buf;
}

/*
 * Export a canvas to bitmap, returns 1 on succes, 0 on failure
 */
const int export_to_bmp(const struct canvas c, const char *filename)
{
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
                log_err("Unable to open file");
                fprintf(stderr, "%s\n", strerror(errno));
                return 0;
        }

        void *bmp_head = _create_bmp_file_header(c);
        void *bmp_data = _create_bmp_data(c);

        fwrite(bmp_head, BMP_HEADER_SIZE, 1, file);
        fwrite(bmp_data, (c.w * c.h * 4), 1, file);

        fclose(file);

        return 1;
}


