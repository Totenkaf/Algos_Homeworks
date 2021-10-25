// Copyright 2021 Artem Ustsov

/*
* Задача № 2_2
* Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения
массива строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за
O(log m).
* Требования:  Время работы O(log m).
* Внимание! В этой задаче сначала нужно определить диапазон для бинарного поиска
размером порядка m с помощью экспоненциального поиска,
* а потом уже в нем делать бинарный поиск.
*/

#include <iostream>

// Predeclarations
int binarySearch(const int *seq, size_t begin, size_t end);
int exponentialSearch(const int *seq, size_t begin, size_t end);
void fillSeq(int *seq, int seq_size);

void fillSeq(int *seq, int seq_size) {
  for (int i = 0; i < seq_size; ++i) {
    int value = 0;
    std::cin >> value;
    seq[i] = value;
  }
}

int binarySearch(const int *seq, size_t begin, size_t end) {
  while (true) {

    int mid = begin + (end - begin) / 2;

    if (seq[mid] > seq[mid + 1] && seq[mid] > seq[mid - 1]) {
      return mid;
    }
    if (seq[mid] > seq[mid + 1]) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
}

int exponentialSearch(const int *seq, size_t begin, size_t end) {
  // Граничный индекс, переход через который означает пропуск экстремума
  // последовательности
  int border = 1;

  while (border < end) {
    if (seq[border - 1] > seq[begin + border]) {
      return binarySearch(seq, border / 2, border);
    } else if (seq[begin + border] > seq[begin + border + 1]) {
      return begin + border;
    } else {
      border = border << 1;
    }
  }
  return binarySearch(seq, border / 2, end);
}

int find_index_of_sequence_extremum(const int *seq, size_t begin, size_t end) {
  // Длина последовательности равна 2
  if (end == 1)
    if (seq[begin] < seq[end]) {
      return end;
    } else {
      return begin;
    }

  // Строго возрастающая
  if (seq[0] > seq[1])
    return 0;

  // Строго убывающая
  if (seq[end - 1] < seq[end])
    return end;
  return exponentialSearch(seq, begin, end);
}

int main(int argc, char const *argv[]) {
  size_t size = 0;
  size_t answer = 0;
  std::cin >> size;

  // Проверка на входящий размер последовательности
  if (size < 1) {
    return 0;
  }

  int *sequence = new int[size];
  fillSeq(sequence, size);

  answer = find_index_of_sequence_extremum(sequence, 0, size - 1);
  std::cout << answer << std::endl;

  delete[] sequence;
  return 0;
}
