#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

int load_from_file(MusicAlbum albums[], int max_count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    
    int count = 0;
    while (count < max_count && 
           fread(&albums[count], sizeof(MusicAlbum), 1, file) == 1) {
        count++;
    }
    
    fclose(file);
    return count;
}

int save_to_file(MusicAlbum albums[], int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }
    
    int saved = fwrite(albums, sizeof(MusicAlbum), count, file);
    fclose(file);
    
    return saved;
}
