#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct game {
	char Name[100];
	char Developer[100];
	char Publisher[100];
	int Year;
	char Platform[100];
	bool Multiplayer;
};

typedef struct game Game;

Game* add_el(Game* ptrarr, int* size);
Game loading();
void print_el(Game game);
int save(FILE* file, char* adress, Game* ptrarr, int size);
Game file_loading(FILE* file);
Game* load(FILE* file, char* adress, int* size);
int compare(const void* a, const void* b);
Game* find(Game* ptrarr, int size, int* size_n, char* str, int choice);

int main() {
	system("chcp 1251");
	int size = 0;
	Game* database = (Game*)malloc(size * sizeof(Game));

	FILE* file = NULL;
	char* adress = (char*)malloc(40 * sizeof(char));
	adress = "data.txt";

	int choice;

	do {
		printf("\n===========================================================\n");
		printf("%30.30s\n", "[Меню]");
		printf("(1) Записать игру >\n");
		printf("(2) Поиск игры по платформе >\n");
		printf("(3) Поиск игры по мультиплееру >\n");
		printf("(4) Вывести базу данных в консоль >\n");
		printf("(5) Отсортировать по году выпуска >\n");
		printf("(6) Запись в файл всех элементов базы данных >\n");
		printf("(7) Загрузить из файла все записи >\n");
		printf("(8) Покинуть базу данных >\n");
		printf("===========================================================\n");
		printf(">");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:;
			Game temp = loading();
			database = add_el(database, &size);
			database[size - 1] = temp;
			break;
		case 2:
			printf("\n===========================================================\n");
			printf("Введите параметр поиска: ");
			char str_h[100];
			scanf(" %s", str_h);
			int size_h = 0;
			Game* data0 = find(database, size, &size_h, &str_h, 0);
			if (data0 == NULL) {
				printf("Записи не найдены");
			}
			else {
				printf("%5c| %20.20s | %20.20s | %20.20s | %6.6s | %20.20s | %11.11s |\n", ' ', "Название", "Разработчик", "Издатель", "Год", "Платформа", "Мультиплеер");
				for (int i = 0; i < size_h; i++) {
					print_el(data0[i]);
				}
				printf("===========================================================\n");
				printf("Чтобы продолжить нажмите Enter");
				getchar();
				getchar();
			}
			break;
		case 3:
			printf("\n===========================================================\n");
			printf("Введите параметр поиска: ");
			char str_g[100];
			scanf(" %s", str_g);
			int size_g = 0;
			Game* data1 = find(database, size, &size_g, &str_g, 1);
			if (data1 == NULL) {
				printf("Записи не найдены");
			}
			else {
				printf("%5c| %20.20s | %20.20s | %20.20s | %6.6s | %20.20s | %11.11s |\n", ' ', "Название", "Разработчик", "Издатель", "Год", "Платформа", "Мультиплеер");
				for (int i = 0; i < size_g; i++) {
					print_el(data1[i]);
				}
				printf("===========================================================\n");
				printf("Чтобы продолжить нажмите Enter");
				getchar();
				getchar();
			}
			break;
		case 4:
			printf("\n===========================================================\n");
			printf("%30.30s\n", "[База данных]");
			printf("%5c| %20.20s | %20.20s | %20.20s | %6.6s | %20.20s | %11.11s |\n", ' ', "Название", "Разработчик", "Издатель", "Год", "Платформа", "Мультиплеер");
			for (int i = 0; i < size; i++) {
				print_el(database[i]);
			}
			printf("===========================================================\n");
			printf("Чтобы продолжить нажмите Enter");
			getchar();
			getchar();
			break;
		case 5:
			printf("\n===========================================================\n");
			qsort(database, size, sizeof(Game), compare);
			printf("Сортировка завершена\n");
			printf("===========================================================\n");
			break;
		case 6:;
			int result_save = save(file, adress, database, size);
			printf("\n===========================================================\n");
			if (result_save == 1) printf("Данные успешно записанны в файл\n");
			if (result_save == 0) printf("Данные успешно не записанны в файл\n");
			printf("===========================================================\n");
			break;
		case 7:
			free(database);
			int size_n = 0;
			printf("\n===========================================================\n");
			database = load(file, adress, &size_n);
			size = size_n;
			printf("===========================================================\n");
			break;
		default:
			break;
		}

	} while (choice < 8);

	return 0;
}

Game* add_el(Game* ptrarr, int* size) {
	int size_n = (*size) + 1;
	Game* temp = (Game*)realloc(ptrarr, size_n * sizeof(Game));
	ptrarr = temp;
	(*size)++;
	return ptrarr;
}

Game loading() {
	Game temp = { "", "", "", 1, 1, 1, "", true };
	printf("\n===========================================================\n");
	printf("%30.30s\n", "[Записать игру]");
	printf("%5cВведите название игры: ", ' ');
	scanf(" %s", temp.Name);
	printf("%5cВведите разработчика: ", ' ');
	scanf(" %s", temp.Developer);
	printf("%5cВведите издателя: ", ' ');
	scanf(" %s", temp.Publisher);
	printf("%5cВведите год выпуска: ", ' ');
	scanf(" %d", &temp.Year);
	printf("%5cВведите платформу: ", ' ');
	scanf(" %s", temp.Platform);
	char h[5];
	char g[5] = "Да";
	printf("%5cВведите есть ли мультиплеер (Да / Нет): ", ' ');
	scanf(" %s", h);
	if (strcmp(h, g)) {
		temp.Multiplayer = false;
	}
	else {
		temp.Multiplayer = true;
	}
	printf("===========================================================\n");
	printf("Новая запись успешно добавлена в базу данных\n");
	printf("Чтобы продолжить нажмите Enter");
	getchar();
	getchar();
	return temp;
}

void print_el(Game game) {
	char* mult = (char*)malloc(3 * sizeof(char));
	if (game.Multiplayer) {
		mult = "Да";
	}
	else {
		mult = "Нет";
	}
	printf("%5c| %20.20s | %20.20s | %20.20s | %6d | %20.20s | %11.11s |\n", ' ', game.Name, game.Developer, game.Publisher, game.Year, game.Platform, mult);
}

int save(FILE* file, char* adress, Game* ptrarr, int size) {
	file = fopen(adress, "w");
	if (file == NULL) return 0;
	for (int i = 0; i < size; i++) {
		if (file)
		{
			if (i != 0) fprintf(file, "\n");
			fprintf(file, "%s\n", ptrarr[i].Name);
			fprintf(file, "%s\n", ptrarr[i].Developer);
			fprintf(file, "%s\n", ptrarr[i].Publisher);
			fprintf(file, "%d\n", ptrarr[i].Year);
			fprintf(file, "%s\n", ptrarr[i].Platform);
			fprintf(file, "%d\0", ptrarr[i].Multiplayer);
		}
	}
	fclose(file);
	return 1;
}


Game file_loading(FILE* file) {

	Game temp;
	fgets(temp.Name, 100, file);
	fgets(temp.Developer, 100, file);
	fgets(temp.Publisher, 100, file);
	fscanf(file, "%d\n", &temp.Year);
	fgets(temp.Platform, 100, file);
	fscanf(file, "%d\n", &temp.Multiplayer);

	strtok(temp.Name, "\n");
	strtok(temp.Developer, "\n");
	strtok(temp.Publisher, "\n");
	strtok(temp.Platform, "\n");

	return temp;
}

Game* load(FILE* file, char* adress, int* size) {
	file = fopen(adress, "r");
	if (file == NULL) printf("Данные успешно не загружены из файла\n");

	int lines = 0;
	int previous = '\n';
	int ch;
	while ((ch = fgetc(file)) != EOF) {
		if (previous == '\n') lines++;
		previous = ch;
	}
	*size = lines / 6;
	fclose(file);

	file = fopen(adress, "r");
	int i = 0;
	Game* database = (Game*)malloc(*size * sizeof(Game));
	while (feof(file) == 0) {
		Game temp = file_loading(file);
		database[i] = temp;
		i++;
	}
	fclose(file);
	printf("Данные успешно загружены из файла\n");
	return database;
}

int compare(const void* a, const void* b)
{
	Game* data1 = a;
	Game* data2 = b;
	if (data1->Year < data2->Year)
		return -1;
	else if (data1->Year == data2->Year)
		return 0;
	else
		return 1;
}

Game* find(Game* ptrarr, int size, int* size_n, char* str, int choice) {
	int count = 0;
	char g[5] = "Да";
	int Bool;
	if (choice == 1) {
		if (strcmp(str, g)) {
			Bool = 0;
		}
		else {
			Bool = 1;
		}
	}
	for (int i = 0; i < size; i++) {
		if (choice == 0) {
			if (!strcmp(str, ptrarr[i].Platform)) count++;
		}
		if (choice == 1) {
			if (Bool == ptrarr[i].Multiplayer) count++;
		}
	}
	if (count == 0) return NULL;
	*size_n = count;
	Game* temp = (Game*)malloc(*size_n * sizeof(Game));
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (choice == 0) {
			if (!strcmp(str, ptrarr[i].Platform)) {
				temp[j] = ptrarr[i];
				j++;
			};
		}
		if (choice == 1) {
			if (Bool == ptrarr[i].Multiplayer) {
				temp[j] = ptrarr[i];
				j++;
			}
		}
	}
	return temp;
}