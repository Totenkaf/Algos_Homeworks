// Copyright 2022 Artem Ustsov
#include <iostream>

void fill_sequence(int *seq, size_t seq_size) {
  for (size_t i = 0; i < seq_size; ++i) {
    int value = 0;
    std::cin >> value;
    seq[i] = value;
  }
}

int binary_search(const int *seq, size_t begin, size_t end) {
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

int exponential_search(const int *seq, size_t begin, size_t end) {
  // Граничный индекс, переход через который означает пропуск экстремума
  int border = 1;

  while (border < end) {
    if (seq[border - 1] > seq[begin + border]) {
      return binary_search(seq, border / 2, border);
    } else if (seq[begin + border] > seq[begin + border + 1]) {
      return begin + border;
    } else {
      border = border << 1;
    }
  }
  return binary_search(seq, border / 2, end);
}

int find_index_of_sequence_extremum(const int *seq, size_t begin, size_t end) {
  if (end == 1) // Длина последовательности равна 2
    if (seq[begin] < seq[end]) {
      return end;
    } else {
      return begin;
    }
  return exponential_search(seq, begin, end);
}


int main(int argc, char const *argv[]) {
  size_t size = 0;
  size_t answer = 0;
  std::cin >> size;

  int *sequence = new int[size];
  fill_sequence(sequence, size);

  answer = find_index_of_sequence_extremum(sequence, 0, size-1) + 1;
  std::cout << answer << std::endl;

  delete[] sequence;
  return 0;
}
