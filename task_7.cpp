// Copyright 2021 by Artem Ustsov
// Задача №7_3. Binary MSD для long long.
// Дан массив неотрицательных целых 64-разрядных чисел.
// Количество чисел не
// больше 106. Отсортировать массив методом MSD по битам (бинарный QuickSort).

#include <iostream>

#define BITSWORD 63
typedef unsigned long long int ull_i;

// Проверка наличия единицы в раряде под номером индекс
inline bool digit(ull_i num, int index) { return num & ((ull_i)1 << index); }

// Перегрузка std::swap для long long int
void swap(ull_i *a, ull_i *b) {
  ull_i temp = *a;
  *a = *b;
  *b = temp;
  return;
}

//Бинарная сортировка по старшему биту
void quicksortB(ull_i *a, int first, int last, int bitsword) {
  int i = first;
  int j = last;
  if (last <= first || bitsword < 0) {
    return;
  }
  while (j != i) {
    while (!digit(a[i], bitsword) && (i < j)) {
      ++i;
    }
    while (digit(a[j], bitsword) && (j > i)) {
      --j;
    }
    swap(&(a[i]), &(a[j]));
  }

  if (!digit(a[last], bitsword)) {
    ++j;
  }

  quicksortB(a, first, j - 1, bitsword - 1);
  quicksortB(a, j, last, bitsword - 1);
}

void fillNumVector(const int size, ull_i *num_vector) {
  for (auto i = 0; i < size; ++i) {
    std::cin >> num_vector[i];
  }
  return;
}

void prinNumVector(const int size, ull_i *num_vector) {
  for (int i = 0; i < size; ++i) {
    std::cout << num_vector[i] << " ";
  }
  std::cout << std::endl;
  return;
}

int main() {
  int size = 0;
  std::cin >> size;
  ull_i *num_vector = new ull_i[size];

  fillNumVector(size, num_vector);
  quicksortB(num_vector, 0, size - 1, BITSWORD);
  prinNumVector(size, num_vector);
  delete[] num_vector;
}
