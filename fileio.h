#ifndef FILEIO_H
#define FILEIO_H

#include "database.h"

int load_from_file(MusicAlbum albums[], int max_count, const char *filename);
int save_to_file(MusicAlbum albums[], int count, const char *filename);

#endif
