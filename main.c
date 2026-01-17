#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "fileio.h"
#include "utils.h"

#define MAX_PROJECTS 100
#define FILENAME "projects.bin"

void print_menu() {
    printf("\n=== МЕНЮ УПРАВЛЕНИЯ МУЗЫКАЛЬНЫМИ АЛЬБОМАМИ ===\n");
    printf("1. Загрузить из файла\n");
    printf("2. Добавить альбом\n");
    printf("3. Показать все альбомы\n");
    printf("4. Изменить запись\n");
    printf("5. Поиск альбома\n");
    printf("6. Сортировка по году выпуска\n");
    printf("7. Сохранить в файл\n");
    printf("8. Выход\n");
    printf("============================================\n");
    printf("Выберите действие: ");
}

int main() {
    MusicAlbum albums[MAX_PROJECTS];
    int count = 0;
    int choice;
    
    
    count = load_from_file(albums, MAX_PROJECTS, FILENAME);
    
   
    if (count == 0) {
        printf("Создание тестовых данных...\n");
        count = create_test_data(albums);
        save_to_file(albums, count, FILENAME);
    }
    
    do {
        print_menu();
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                count = load_from_file(albums, MAX_PROJECTS, FILENAME);
                printf("Загружено %d записей\n", count);
                break;
                
            case 2:
                if (count < MAX_PROJECTS) {
                    add_album(&albums[count]);
                    count++;
                } else {
                    printf("Достигнуто максимальное количество записей!\n");
                }
                break;
                
            case 3:
                print_all_albums(albums, count);
                break;
                
            case 4:
                edit_album(albums, count);
                break;
                
            case 5:
                search_album(albums, count);
                break;
                
            case 6:
                sort_albums(albums, count);
                printf("Альбомы отсортированы по году выпуска\n");
                break;
                
            case 7:
                save_to_file(albums, count, FILENAME);
                printf("Данные сохранены в файл\n");
                break;
                
            case 8:
                printf("Выход из программы\n");
                break;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 8);
    
    return 0;
}
