#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define BLOCK_SIZE 512

// Correctly define the JPEG signature (allowing for different APPn markers)
static const uint8_t JPEG_SIGNATURE[] = {0xFF, 0xD8, 0xFF};

bool check_jpeg_signature(uint8_t *block) {
    return block[0] == JPEG_SIGNATURE[0] &&
           block[1] == JPEG_SIGNATURE[1] &&
           block[2] == JPEG_SIGNATURE[2] &&
           (block[3] & 0xF0) == 0xE0; // Check if it's an APPn marker
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "rb");
    if (raw_file == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    int image_number = 0;

    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE) {
        if (check_jpeg_signature(buffer)) {
            char filename[8];
            sprintf(filename, "%03d.jpg", image_number++);

            FILE *img = fopen(filename, "wb");
            if (img == NULL) {
                printf("Could not create image file.\n");
                fclose(raw_file);
                return 1;
            }

            fwrite(buffer, 1, BLOCK_SIZE, img);

            // Read subsequent blocks until next JPEG signature or EOF
            while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE) {
                if (check_jpeg_signature(buffer)) {
                    // Start of a new JPEG, stop writing the current one
                    fseek(raw_file, -BLOCK_SIZE, SEEK_CUR); // Go back one block
                    break;
                }
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
            fclose(img);
        }
    }

    fclose(raw_file);
    return 0;
}

