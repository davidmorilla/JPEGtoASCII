#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <string.h>

char seq[92]="`.-\':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

int ends_with_jpg(const char *str) {
    int len = strlen(str);
    return len > 4 && strcmp(str + len - 4, ".jpg") == 0;
}

void read_jpeg_file(char *filename) {
    // Variables to store the decompressed image
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // Open the JPEG file
    FILE *infile = fopen(filename, "rb");
    if (!infile) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    // Set up the error handler
    cinfo.err = jpeg_std_error(&jerr);

    // Initialize the JPEG decompression object
    jpeg_create_decompress(&cinfo);

    // Specify the data source (the file)
    jpeg_stdio_src(&cinfo, infile);

    // Read the JPEG header
    jpeg_read_header(&cinfo, TRUE);

    // Start the decompression process
    jpeg_start_decompress(&cinfo);

    // Get the image width, height, and number of channels (3 for RGB)
    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int num_channels = cinfo.output_components;

    // Allocate memory to hold one row of the image
    unsigned char *row_pointer = (unsigned char *)malloc(width * num_channels);

    // Read each row of the image
    while (cinfo.output_scanline < cinfo.output_height) {
        // Read a single row
        jpeg_read_scanlines(&cinfo, &row_pointer, 1);

        // Process the row (for example, print the red value of each pixel)
        for (int i = 0; i < width * num_channels; i += num_channels) {
            unsigned char R = row_pointer[i];
            unsigned char G = row_pointer[i + 1];
            unsigned char B = row_pointer[i + 2];
            
            int brightness = ((0.299 * R + 0.587 * G + 0.114 * B)*91)/255;
            if(brightness != 0) {
                brightness--;
            }
            fprintf(stdout, "%c", seq[brightness]);
        }
        fprintf(stdout, "\n");
    }

    // Clean up
    free(row_pointer);
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
}

int main(int argc, char** argv){
    if(argc!=2){
        perror("Incorrect number of input arguments: ./ascii_art input.jpg");
    }
    char *filename = argv[1];
    if(ends_with_jpg(filename)){
        read_jpeg_file(filename);
    } else {
        perror("The file must have a .jpg extension: ./ascii_art input.jpg");
    }
    return 0;

}
