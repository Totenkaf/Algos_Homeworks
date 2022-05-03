// Copyright 2022 by Artem Ustsov
// Задача №6_4
/*
 * Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца
 * массива к началу (в одном направлении).
 */

/*
 * Дано множество целых чисел из [0..10^9] размера n.
 * Используя алгоритм поиска k-ой порядковой статистики, требуется найти
 * следующие параметры множества:
 * 1) 10% перцентиль
 * 2) медиана
 * 3) 90% перцентиль
 */

/*
 * Требования: к дополнительной памяти: O(n). Среднее время работы: O(n).
 * Должна быть отдельно выделенная функция partition. Рекурсия запрещена.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 */

/*
* Описание для случая прохода от начала массива к концу:
* 1) Выбирается опорный элемент. Опорный элемент меняется с последним элементом
массива.
* 2) Во время работы Partition в начале массива содержатся элементы, не бОльшие
* опорного. Затем располагаются элементы, строго бОльшие опорного.
* 3) В конце массива лежат нерассмотренные элементы. Последним элементом лежит
опорный.
* 4) Итератор (индекс) i указывает на начало группы элементов, строго бОльших
опорного.
* 5) Итератор j больше i, итератор j указывает на первый нерассмотренный
элемент.
* 6) Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он
больше опорного, то сдвигаем j.
* 7) Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и
сдвигаем j.
* 8) В конце работы алгоритма меняем опорный и элемент, на который указывает
итератор i.
*/

#include <iostream>
#include <iostream>
#include <time.h>

int random_pivot(int left, int right) {
  srand(time(NULL));
  return left == right ? left : std::rand() % (right - left) + left;
}

template <typename Comparator>
int partition(int *sequence, int begin, int end,
              Comparator cmp = Comparator()) {
  int i = end;
  int pivot = random_pivot(begin, end);
  std::swap(sequence[begin], sequence[pivot]);
  pivot = begin;

  for (int j = end; j > begin; --j) {
    if (cmp(sequence[j], sequence[pivot])) {
      std::swap(sequence[j], sequence[i]);
      --i;
    }
  }
  std::swap(sequence[i], sequence[pivot]);
  return i;
}

template <typename Comparator = std::greater_equal<int>>
int find_statistic(int *sequence, int begin, int end, int k,
                  Comparator cmp = Comparator()) {
  int pivot = partition(sequence, begin, end, cmp);

  while (pivot != k) {
    if (pivot > k) {
      end = pivot - 1;
    } else {
      begin = pivot + 1;
    }
    pivot = partition(sequence, begin, end, cmp);
  }
  return sequence[pivot];
}

template <typename T> 
void fill_sequence(T &sequence, size_t seq_size) {
  for (size_t i = 0; i < seq_size; ++i) {
    std::cin >> sequence[i];
  }
  return;
}

template <typename T>
void find_sequence_statistics(T &sequence, size_t seq_size) {
  int percentile_10th = seq_size / 10;
  int percentile_90th = 9 * seq_size / 10;
  int percentile_50th = seq_size / 2;

  std::cout << find_statistic(sequence, 0, seq_size - 1, percentile_10th)
            << std::endl;
  std::cout << find_statistic(sequence, 0, seq_size - 1, percentile_50th)
            << std::endl;
  std::cout << find_statistic(sequence, 0, seq_size - 1, percentile_90th)
            << std::endl;
  return;
}

int main() {
  int seq_size = 0;
  std::cin >> seq_size;

  int* sequence = new int[seq_size];
  fill_sequence(sequence, seq_size);
  find_sequence_statistics(sequence, seq_size);

  delete[] sequence;
  return 0;
}
