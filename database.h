#ifndef DATABASE_H
#define DATABASE_H

#define MAX_TITLE 100
#define MAX_STYLE 50

typedef struct {
    char title[MAX_TITLE];
    int releaseYear;
    char style[MAX_STYLE];
    int trackCount;
    int durationMinutes;
} MusicAlbum;

// Основные операции
void print_album(MusicAlbum album);
void print_all_albums(MusicAlbum albums[], int count);
void add_album(MusicAlbum *album);
void edit_album(MusicAlbum albums[], int count);
void search_album(MusicAlbum albums[], int count);
void sort_albums(MusicAlbum albums[], int count);
int create_test_data(MusicAlbum albums[]);

#endif
