//1 задание
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

// функция создания дерева 
struct Node* CreateTree(struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        r->data = data;
        r->left = NULL;
        r->right = NULL;
        return r;
    }

    if (data < r->data) {
        r->left = CreateTree(r->left, data);
    }
    else {
        r->right = CreateTree(r->right, data);
    }

    return r;
}

// Реализация алгоритма поиска
struct Node* search(struct Node* r, int key) {
    if (r == NULL || r->data == key) {
        return r;
    }

    if (key < r->data) {
        return search(r->left, key);
    }
    else {
        return search(r->right, key);
    }
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) return;
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) printf("   ");
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

void free_tree(struct Node* r) {
    if (r == NULL) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

int main() {
    setlocale(LC_ALL, "");
    int D;
    root = NULL;

    printf("=== задание 1: Алгоритм поиска в бинарном дереве ===\n");

    int test_data[] = { 50, 30, 70, 20, 40, 60, 80 };
    int n = 7;

    for (int i = 0; i < n; i++) {
        root = CreateTree(root, test_data[i]);
    }

    printf("Построенное дерево:\n");
    print_tree(root, 0);

    // Тестирование поиска
    printf("\n--- поиск ---\n");
    printf("Введите число для поиска: ");
    scanf_s("%d", &D);

    struct Node* found = search(root, D);
    if (found != NULL) {
        printf(" Элемент %d найден в дереве!\n", D);
    }
    else {
        printf(" Элемент %d не найден в дереве.\n", D);
    }

    free_tree(root);
    return 0;
}
//2 задание
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        r->data = data;
        r->left = NULL;
        r->right = NULL;
        return r;
    }

    if (data < r->data) {
        r->left = CreateTree(r->left, data);
    }
    else {
        r->right = CreateTree(r->right, data);
    }

    return r;
}

// 2: Функция подсчёта числа вхождений
int count_occurrences(struct Node* r, int key) {
    if (r == NULL) {
        return 0;
    }

    int count = 0;
    if (r->data == key) {
        count = 1;
    }

    // Ищем во всем дереве 
    count += count_occurrences(r->left, key);
    count += count_occurrences(r->right, key);

    return count;
}

// Вывод дерева 
void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf("   ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

void free_tree(struct Node* r) {
    if (r == NULL) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

// Функция для проверки, состоит ли строка только из цифр и знака минус
int is_valid_number(const char* str) {
    int i = 0;

    while (isspace((unsigned char)str[i])) {
        i++;
    }

    if (str[i] == '-') {
        i++;
    }


    if (str[i] == '\0') {
        return 0;
    }

    while (str[i] != '\0') {
        if (!isdigit((unsigned char)str[i]) && !isspace((unsigned char)str[i])) {
            return 0;
        }
        i++;
    }

    return 1; // Строка содержит только цифры и пробелы
}


int safe_input() {
    char input[100];
    int number;
    int valid_input;

    while (1) {
        printf("Введите число для подсчёта (-1 для выхода): ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Ошибка ввода. Попробуйте снова.\n");
            continue;
        }

        // Убираем символ новой строки
        input[strcspn(input, "\n")] = 0;

        // Проверяем, что строка содержит только допустимые символы
        if (!is_valid_number(input)) {
            printf("Ошибка: введите целое число без букв.\n");
            continue;
        }

        // Проверяем, что введено число
        valid_input = sscanf_s(input, "%d", &number);

        if (valid_input != 1) {
            printf("Ошибка: введите целое число.\n");
            continue;
        }

        if (number != -1 && (number < -100000 || number > 100000)) {
            printf("Ошибка: число должно быть в диапазоне от -100000 до 100000.\n");
            continue;
        }

        break;
    }

    return number;
}

int main() {
    setlocale(LC_ALL, "");
    int D;
    root = NULL;

    printf("=== задание 2: Подсчёт числа вхождений элемента ===\n");

    int test_data[] = { 50, 30, 70, 30, 20, 50, 40, 50 };
    int n = 8;

    for (int i = 0; i < n; i++) {
        root = CreateTree(root, test_data[i]);
    }

    printf("Построенное дерево:\n");
    print_tree(root, 0);

    while (1) {
        printf("\n--- подсчет вхождений ---\n");

        D = safe_input();

        if (D == -1) {
            printf("Выход из программы.\n");
            break;
        }

        int count = count_occurrences(root, D);
        printf("Элемент %d встречается в дереве %d раз(а)\n", D, count);
    }

    free_tree(root);
    return 0;
}
free_tree(root);
return 0;
}
//3 задание
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

//  3: Функция с исключением дубликатов
struct Node* CreateTree(struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        r->data = data;
        r->left = NULL;
        r->right = NULL;
        printf(" Добавлен элемент: %d\n", data);
        return r;
    }

    if (data == r->data) {
        printf(" Элемент %d уже существует. Пропускаем.\n", data);
        return r;
    }

    if (data < r->data) {
        r->left = CreateTree(r->left, data);
    }
    else {
        r->right = CreateTree(r->right, data);
    }

    return r;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) return;
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) printf("   ");
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

void free_tree(struct Node* r) {
    if (r == NULL) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

int main() {
    setlocale(LC_ALL, "");
    int D;
    root = NULL;

    printf("=== задание 3: Исключение добавления одинаковых элементов ===\n");
    printf("Вводите числа по одному, для завершения введите -1\n\n");

    // Интерактивное создание дерева
    while (1) {
        printf("Введите число: ");
        if (scanf_s("%d", &D) != 1) {
            printf("Ошибка ввода! Введите целое число.\n");
            while (getchar() != '\n');
            continue;
        }

        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            break;
        }

        root = CreateTree(root, D);
    }

    printf("\nИтоговое дерево (без дубликатов):\n");
    print_tree(root, 0);

    printf("\n--- проверка ---\n");
    printf("Все дубликаты были автоматически отклонены!\n");

    free_tree(root);
    return 0;
}
//4 задание
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        r->data = data;
        r->left = NULL;
        r->right = NULL;
        return r;
    }

    if (data < r->data) {
        r->left = CreateTree(r->left, data);
    }
    else {
        r->right = CreateTree(r->right, data);
    }

    return r;
}

// Функция поиска для демонстрации
struct Node* search(struct Node* r, int key, int* steps) {
    (*steps)++;
    if (r == NULL || r->data == key) {
        return r;
    }

    if (key < r->data) {
        return search(r->left, key, steps);
    }
    else {
        return search(r->right, key, steps);
    }
}

// Функция для вычисления высоты дерева
int tree_height(struct Node* r) {
    if (r == NULL) return 0;
    int left_height = tree_height(r->left);
    int right_height = tree_height(r->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int count_nodes(struct Node* r) {
    if (r == NULL) return 0;
    return 1 + count_nodes(r->left) + count_nodes(r->right);
}

// Функция вывода дерева
void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf("   ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

void free_tree(struct Node* r) {
    if (r == NULL) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

int main() {
    setlocale(LC_ALL, "");
    int D;
    root = NULL;

    printf("=== задание 4: Оценка сложности процедуры поиска ===\n\n");

    // Ручной ввод дерева
    printf("Вводите числа для построения дерева (для завершения введите -1):\n");

    while (1) {
        printf("Введите число: ");
        scanf_s("%d", &D);

        if (D == -1) {
            printf("Построение дерева завершено.\n\n");
            break;
        }

        root = CreateTree(root, D);
    }

    // Вывод построенного дерева
    printf("Построенное дерево:\n");
    print_tree(root, 0);
    printf("\n");

    int height = tree_height(root);
    int node_count = count_nodes(root);

    printf("АНАЛИЗ СЛОЖНОСТИ ПОИСКА\n");
    printf("==========================\n");
    printf("Количество элементов (n): %d\n", node_count);
    printf("Высота дерева (h): %d\n", height);
    printf("Теоретический log₂(n) ≈ %.2f\n", log2(node_count));
    printf("\n");


    if (height <= log2(node_count) + 2) {
        printf("• Ваше дерево близко к сбалансированному \n");
    }
    else {
        printf("• Ваше дерево ближе к вырожденному \n");
    }

    free_tree(root);

    printf("\nНажмите Enter для выхода...");
    getchar(); getchar();
    return 0;
}
