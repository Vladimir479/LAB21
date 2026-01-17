#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"


void print_album(MusicAlbum album) {
    printf("Название: %s\n", album.title);
    printf("Год выпуска: %d\n", album.releaseYear);
    printf("Стиль: %s\n", album.style);
    printf("Количество треков: %d\n", album.trackCount);
    printf("Продолжительность: %d минут\n");
    printf("------------------------------\n");
}

void print_all_albums(MusicAlbum albums[], int count) {
    if (count == 0) {
        printf("Нет данных для отображения\n");
        return;
    }
    
    printf("\n=== ВСЕ АЛЬБОМЫ (%d записей) ===\n", count);
    for (int i = 0; i < count; i++) {
        printf("Запись #%d:\n", i + 1);
        print_album(albums[i]);
    }
    
   
    printf("\n=== АЛЬБОМЫ ПО УСЛОВИЮ (треков >= 10, длительность <= 50 мин) ===\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (albums[i].trackCount >= 10 && albums[i].durationMinutes <= 50) {
            print_album(albums[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Нет альбомов, соответствующих условиям.\n");
    }
}

void add_album(MusicAlbum *album) {
    printf("\n=== ДОБАВЛЕНИЕ НОВОГО АЛЬБОМА ===\n");
    
    printf("Название альбома: ");
    fgets(album->title, MAX_TITLE, stdin);
    album->title[strcspn(album->title, "\n")] = 0;
    
    printf("Год выпуска: ");
    scanf("%d", &album->releaseYear);
    
    printf("Стиль музыки: ");
    getchar();
    fgets(album->style, MAX_STYLE, stdin);
    album->style[strcspn(album->style, "\n")] = 0;
    
    printf("Количество треков: ");
    scanf("%d", &album->trackCount);
    
    printf("Продолжительность (минут): ");
    scanf("%d", &album->durationMinutes);
    
    printf("Альбом успешно добавлен!\n");
}

void edit_album(MusicAlbum albums[], int count) {
    if (count == 0) {
        printf("Нет записей для редактирования\n");
        return;
    }
    
    int index;
    printf("Введите номер записи для редактирования (1-%d): ", count);
    scanf("%d", &index);
    
    if (index < 1 || index > count) {
        printf("Неверный номер записи\n");
        return;
    }
    
    index--; // Переводим в 0-based индекс
    
    printf("\nРедактирование альбома: %s\n", albums[index].title);
    printf("Новое название (оставьте пустым для сохранения текущего): ");
    getchar();
    char buffer[MAX_TITLE];
    fgets(buffer, MAX_TITLE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(albums[index].title, buffer);
    }
    
    printf("Новый год выпуска (0 для сохранения текущего): ");
    scanf("%d", &(albums[index].releaseYear));
    
    printf("Альбом успешно отредактирован!\n");
}

void search_album(MusicAlbum albums[], int count) {
    if (count == 0) {
        printf("Нет записей для поиска\n");
        return;
    }
    
    char search_title[MAX_TITLE];
    printf("Введите название альбома для поиска: ");
    getchar();
    fgets(search_title, MAX_TITLE, stdin);
    search_title[strcspn(search_title, "\n")] = 0;
    
    printf("\n=== РЕЗУЛЬТАТЫ ПОИСКА ===\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(albums[i].title, search_title) != NULL) {
            print_album(albums[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Альбомы с названием '%s' не найдены\n", search_title);
    }
}


int compare_year(const void *a, const void *b) {
    MusicAlbum *albumA = (MusicAlbum *)a;
    MusicAlbum *albumB = (MusicAlbum *)b;
    return albumA->releaseYear - albumB->releaseYear;
}

void sort_albums(MusicAlbum albums[], int count) {
    if (count < 2) {
        printf("Недостаточно записей для сортировки\n");
        return;
    }
    
    qsort(albums, count, sizeof(MusicAlbum), compare_year);
}
int create_test_data(MusicAlbum albums[]) {
    // Ваши тестовые данные
    MusicAlbum test_albums[] = {
        {"The Dark Side of the Moon", 1973, "Progressive Rock", 10, 43},
        {"Thriller", 1982, "Pop", 9, 42},
        {"Back in Black", 1980, "Hard Rock", 10, 42},
        {"Nevermind", 1991, "Grunge", 12, 49},
        {"Abbey Road", 1969, "Rock", 17, 47}
    };
    
    for (int i = 0; i < 5; i++) {
        albums[i] = test_albums[i];
    }
    
    return 5;
}
