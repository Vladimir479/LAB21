 База данных музыкальных альбомов

---

🎯 Назначение

Проект демонстрирует практическое применение структур данных, файлового ввода-вывода и алгоритмов поиска/сортировки в языке C. Может использоваться как учебный пример или основа для персональной музыкальной коллекции.

---

📋 Функциональные возможности

Основной функционал:

· ✅ CRUD-операции: Создание, чтение, обновление, удаление записей
· ✅ Поиск: По названию альбома и стилю музыки
· ✅ Сортировка: По году выпуска (возрастание)
· ✅ Фильтрация: По количеству треков и продолжительности
· ✅ Сохранение: Бинарный формат для долговременного хранения
· ✅ Консольный интерфейс: Интерактивное меню с 8 командами

Структура данных альбома:

Поле Тип Описание
title char[100] Название альбома
releaseYear int Год выпуска
style char[50] Музыкальный стиль
trackCount int Количество треков
durationMinutes int Продолжительность в минутах

---

🏗️ Архитектура проекта

Модульная структура:

src/
├── main.c          # Точка входа, управление меню
├── database.h/c    # Модель данных и операции
├── fileio.h/c      # Работа с файлами
├── utils.h/c       # Вспомогательные функции
└── menu.h/c        # Функции меню
Ключевые алгоритмы:

1. Поиск: Линейный поиск по полям title и style
2. Сортировка: Быстрая сортировка через qsort() по полю releaseYear
3. Фильтрация: Условия по trackCount и durationMinutes

---

🚀 Сборка и запуск

Требования:

· Компилятор C (GCC/Clang/MSVC)
· Стандарт C99 или новее

Инструкция по сборки:

Bash

# 1. Создание директории проекта
mkdir music-albums-db
cd music-albums-db

# 2. Создание структуры папок
mkdir src

# 3. Компиляция
gcc -std=c99 -o musicdb src/*.c

# 4. Запуск
./musicdb  # Linux/macOS
musicdb.exe # Windows
Использование:

1. Запустите программу
2. Следуйте инструкциям в консольном меню
3. Для выхода выберите соответствующий пункт меню
4. Не забудьте сохранить данные перед выходом

---

📁 Структура файлов проекта

1. database.h

C

#ifndef DATABASE_H
#define DATABASE_H

#define MAX_ALBUMS 100
#define FILENAME "albums.dat"

typedef struct {
    char title[100];
    int releaseYear;
    char style[50];
    int trackCount;
    int durationMinutes;
} MusicAlbum;

typedef struct {
    MusicAlbum albums[MAX_ALBUMS];
    int count;
} Database;

// Основные операции с базой данных
void initDatabase(Database *db);
int addAlbum(Database *db, const MusicAlbum *album);
int deleteAlbum(Database *db, int index);
int updateAlbum(Database *db, int index, const MusicAlbum *album);
void displayAllAlbums(const Database *db);
void displayAlbum(const MusicAlbum *album);

// Поиск и фильтрация
void searchByTitle(const Database *db, const char *title);
void searchByStyle(const Database *db, const char *style);
void filterByTracksAndDuration(const Database *db, int minTracks, int maxDuration);

// Сортировка
void sortByYear(Database *db);

#endif
2. database.c

`c
#include "database.h"
#include <stdio.h>
#include <string.h>

void initDatabase(Database *db) {
    db->count = 0;
}

int addAlbum(Database *db, const MusicAlbum *album) {
    if (db->count >= MAX_ALBUMS) {
        printf("База данных заполнена!\n");
        return 0;
    }
    
    db->albums[db->count] = *album;
    db->count++;
    return 1;
}

int deleteAlbum(Database *db, int index) {
    if (index < 0 || index >= db->count) {
        printf("Неверный индекс!\n");
        return 0;
    }
    
    for (int i = index; i < db->count - 1; i++) {
        db->albums[i] = db->albums[i + 1];
    }
    db->count--;
    return 1;
}

int updateAlbum(Database *db, int index, const MusicAlbum *album) {
    if (index < 0 || index >= db->count) {
        printf("Неверный индекс!\n");
        return 0;
    }
    
    db->albums[index] = *album;
    return 1;
}
void displayAllAlbums(const Database *db) {
    printf("\n=== Все альбомы (%d) ===\n", db->count);
    printf("==========================\n");
    
    for (int i = 0; i < db->count; i++) {
        printf("\nАльбом #%d:\n", i + 1);
        displayAlbum(&db->albums[i]);
    }
}

void displayAlbum(const MusicAlbum *album) {
    printf("Название: %s\n", album->title);
    printf("Год выпуска: %d\n", album->releaseYear);
    printf("Стиль: %s\n", album->style);
    printf("Количество треков: %d\n", album->trackCount);
    printf("Продолжительность: %d минут\n", album->durationMinutes);
}

void searchByTitle(const Database *db, const char *title) {
    printf("\n=== Результаты поиска по названию: '%s' ===\n", title);
    int found = 0;
    
    for (int i = 0; i < db->count; i++) {
        if (strstr(db->albums[i].title, title) != NULL) {
            printf("\nНайден альбом #%d:\n", i + 1);
            displayAlbum(&db->albums[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Альбомы не найдены.\n");
    }
}

void searchByStyle(const Database *db, const char *style) {
    printf("\n=== Результаты поиска по стилю: '%s' ===\n", style);
    int found = 0;
    
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->albums[i].style, style) == 0) {
            printf("\nНайден альбом #%d:\n", i + 1);
            displayAlbum(&db->albums[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Альбомы не найдены.\n");
    }
}

void filterByTracksAndDuration(const Database *db, int minTracks, int maxDuration) {
    printf("\n=== Фильтр: треков >= %d, длительность <= %d мин ===\n", 
           minTracks, maxDuration);
    int found = 0;
    
    for (int i = 0; i < db->count; i++) {
        if (db->albums[i].trackCount >= minTracks && 
            db->albums[i].durationMinutes <= maxDuration) {
            printf("\nАльбом #%d соответствует условиям:\n", i + 1);
            displayAlbum(&db->albums[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Нет альбомов, соответствующих условиям.\n");
    }
}

// Функция сравнения для сортировки
int compareByYear(const void *a, const void *b) {
    const MusicAlbum *albumA = (const MusicAlbum *)a;
    const MusicAlbum *albumB = (const MusicAlbum *)b;
    return albumA->releaseYear - albumB->releaseYear;
}

void sortByYear(Database *db) {
    qsort(db->albums, db->count, sizeof(MusicAlbum), compareByYear);
    printf("Альбомы отсортированы по году выпуска.\n");
}

3. fileio.h
c
#ifndef FILEIO_H
#define FILEIO_H

#include "database.h"

// Функции для работы с файлами
int saveDatabase(const Database *db, const char *filename);
int loadDatabase(Database *db, const char *filename);
void exportToText(const Database *db, const char *filename);

#endif

4. fileio.c
c
#include "fileio.h"
#include <stdio.h>

int saveDatabase(const Database *db, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Ошибка открытия файла для записи!\n");
        return 0;
    }
    
    // Сохраняем количество альбомов
    fwrite(&db->count, sizeof(int), 1, file);
    
    // Сохраняем все альбомы
    fwrite(db->albums, sizeof(MusicAlbum), db->count, file);
    
    fclose(file);
    printf("База данных сохранена в файл '%s' (%d записей)\n", 
           filename, db->count);
    return 1;
}

int loadDatabase(Database *db, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Файл '%s' не найден. Создана новая база данных.\n", filename);
        return 0;
    }
    
    // Читаем количество альбомов
    fread(&db->count, sizeof(int), 1, file);
    
    // Читаем все альбомы
    fread(db->albums, sizeof(MusicAlbum), db->count, file);
    
    fclose(file);
    printf("База данных загружена из файла '%s' (%d записей)\n", 
           filename, db->count);
    return 1;
}
void exportToText(const Database *db, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка создания текстового файла!\n");
        return;
    }
    
    fprintf(file, "=== База данных музыкальных альбомов ===\n");
    fprintf(file, "Всего альбомов: %d\n\n", db->count);
    
    for (int i = 0; i < db->count; i++) {
        fprintf(file, "Альбом #%d:\n", i + 1);
        fprintf(file, "  Название: %s\n", db->albums[i].title);
        fprintf(file, "  Год выпуска: %d\n", db->albums[i].releaseYear);
        fprintf(file, "  Стиль: %s\n", db->albums[i].style);
        fprintf(file, "  Количество треков: %d\n", db->albums[i].trackCount);
        fprintf(file, "  Продолжительность: %d минут\n\n", db->albums[i].durationMinutes);
    }
    
    fclose(file);
    printf("Данные экспортированы в текстовый файл '%s'\n", filename);
}

5. menu.h
c
#ifndef MENU_H
#define MENU_H

#include "database.h"

// Функции меню
void displayMenu();
void handleMenuChoice(Database *db, int choice);
MusicAlbum inputAlbum();

#endif

6. menu.c
c
#include "menu.h"
#include <stdio.h>
#include <string.h>

void displayMenu() {
    printf("\n=== Меню управления базой данных альбомов ===\n");
    printf("1. Показать все альбомы\n");
    printf("2. Добавить альбом\n");
    printf("3. Удалить альбом\n");
    printf("4. Обновить альбом\n");
    printf("5. Поиск по названию\n");
    printf("6. Поиск по стилю\n");
    printf("7. Фильтр по трекам и длительности\n");
    printf("8. Сортировать по году выпуска\n");
    printf("9. Сохранить в файл\n");
    printf("10. Загрузить из файла\n");
    printf("11. Экспорт в текстовый файл\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

MusicAlbum inputAlbum() {
    MusicAlbum album;
    
    printf("\nВведите данные альбома:\n");
    
    printf("Название: ");
    fgets(album.title, sizeof(album.title), stdin);
    album.title[strcspn(album.title, "\n")] = 0;
    
    printf("Год выпуска: ");
    scanf("%d", &album.releaseYear);
    getchar(); // Очистка буфера
    
    printf("Стиль: ");
    fgets(album.style, sizeof(album.style), stdin);
    album.style[strcspn(album.style, "\n")] = 0;
    
    printf("Количество треков: ");
    scanf("%d", &album.trackCount);
    
    printf("Продолжительность (минут): ");
    scanf("%d", &album.durationMinutes);
    getchar(); // Очистка буфера
    
    return album;
}

void handleMenuChoice(Database *db, int choice) {
    char searchStr[100];
    int index, minTracks, maxDuration;
    MusicAlbum album;
    
    switch(choice) {
        case 1:
            displayAllAlbums(db);
            break;
            
        case 2:
            album = inputAlbum();
            if (addAlbum(db, &album)) {
                printf("Альбом добавлен успешно!\n");
            }
            break;
            
        case 3:
            printf("Введите номер альбома для удаления: ");
            scanf("%d", &index);
            getchar();
            if (deleteAlbum(db, index - 1)) {
                printf("Альбом удален успешно!\n");
            }
            break;
            
        case 4:
            printf("Введите номер альбома для обновления: ");
            scanf("%d", &index);
            getchar();
            album = inputAlbum();
            if (updateAlbum(db, index - 1, &album)) {
                printf("Альбом обновлен успешно!\n");
            }
            break;
            
        case 5:
            printf("Введите название для поиска: ");
            fgets(searchStr, sizeof(searchStr), stdin);
            searchStr[strcspn(searchStr, "\n")] = 0;
            searchByTitle(db, searchStr);
            break;
            
        case 6:
            printf("Введите стиль для поиска: ");
            fgets(searchStr, sizeof(searchStr), stdin);
searchStr[strcspn(searchStr, "\n")] = 0;
            searchByStyle(db, searchStr);
            break;
            
        case 7:
            printf("Минимальное количество треков: ");
            scanf("%d", &minTracks);
            printf("Максимальная продолжительность (минут): ");
            scanf("%d", &maxDuration);
            getchar();
            filterByTracksAndDuration(db, minTracks, maxDuration);
            break;
            
        case 8:
            sortByYear(db);
            break;
            
        case 9:
            saveDatabase(db, FILENAME);
            break;
            
        case 10:
            loadDatabase(db, FILENAME);
            break;
            
        case 11:
            exportToText(db, "albums_export.txt");
            break;
            
        case 0:
            printf("Выход из программы...\n");
            break;
            
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
    }
}

7. main.c
c
#include <stdio.h>
#include "database.h"
#include "fileio.h"
#include "menu.h"

int main() {
    Database db;
    int choice;
    
    // Инициализация базы данных
    initDatabase(&db);
    
    // Загрузка данных из файла при запуске
    loadDatabase(&db, FILENAME);
    
    // Добавление демонстрационных данных, если база пуста
    if (db.count == 0) {
        printf("База данных пуста. Добавлены демонстрационные данные.\n");
        
        MusicAlbum demoAlbums[] = {
            {"The Dark Side of the Moon", 1973, "Progressive Rock", 10, 43},
            {"Thriller", 1982, "Pop", 9, 42},
            {"Back in Black", 1980, "Hard Rock", 10, 42},
            {"Nevermind", 1991, "Grunge", 12, 49},
            {"Abbey Road", 1969, "Rock", 17, 47}
        };
        
        for (int i = 0; i < 5; i++) {
            addAlbum(&db, &demoAlbums[i]);
        }
    }
    
    printf("=== База данных музыкальных альбомов ===\n");
    printf("Загружено альбомов: %d\n", db.count);
    
    // Главный цикл программы
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Очистка буфера
        
        handleMenuChoice(&db, choice);
        
    } while (choice != 0);
    
    // Предложение сохранить данные перед выходом
    printf("Сохранить изменения перед выходом? (y/n): ");
    char saveChoice = getchar();
    if (saveChoice == 'y' || saveChoice == 'Y') {
        saveDatabase(&db, FILENAME);
    }
    
    printf("Программа завершена. До свидания!\n");
    return 0;
}

8. Makefile (опционально)
makefile
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
TARGET = musicdb
SRC = src/main.c src/database.c src/fileio.c src/menu.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
 $(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
 $(CC) $(CFLAGS) -c $< -o $@

clean:
 rm -f $(OBJ) $(TARGET) albums.dat albums_export.txt

run: $(TARGET)
 ./$(TARGET)

.PHONY: all clean run
`

---

🤝 Вклад в проект

Сообщения об ошибках:

· Через Issues с подробным описанием проблемы и шагами для воспроизведения

Предложения по улучшению:

· Обсуждение в комментариях к проекту

Pull Requests:

· Приветствуются с понятным описанием изменений
· Требования к коду: соблюдение стиля, комментарии к сложным участкам

Планируемые улучшения:

· Добавление поиска по диапазонам (годы, продолжительность)
· Поддержка экспорта в CSV/JSON форматы
· Добавление статистики по стилям музыки
· Реализация GUI интерфейса
· Добавление возможности импорта из текстовых файлов

---

Автор: [Ваше имя и группа]
Курс: Программирование на языке C
Год: 2024
Лицензия: MIT

Проект создан в образовательных целях
