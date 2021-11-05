// Copyright 2021 by Artem Ustsov

// Задача №5_3
/*
 * На числовой прямой окрасили N отрезков.
 * Известны координаты левого и правого концов каждого отрезка (Li и Ri).
 *Найти длину окрашенной части числовой прямой.
 */
#include <functional>
#include <iostream>

enum position { begin_l = 1, end_l = -1 };

struct Point {
  Point() = default;
  Point(int coord, position pos) : coord(coord), pos(pos){};
  int coord;
  position pos;
};

template <typename T> class Array {
public:
  explicit Array(int size);
  ~Array();

  void AddElement(T element);
  int GetSize() const;
  T &operator[](int index) const;

private:
  int size;
  int current_element;
  T *array;
};

template <typename T>
Array<T>::Array(int size) : size(size), current_element(0) {
  array = new T[size];
}

template <typename T> Array<T>::~Array() { delete[] array; }

template <typename T> void Array<T>::AddElement(T element) {
  if (current_element < size) {
    array[current_element++] = element;
  }
}

template <typename T> int Array<T>::GetSize() const { return size; }

template <typename T> T &Array<T>::operator[](int index) const {
  return array[index];
}

template <typename T, typename U>
void Merge(T &array, T &buf, int from, int mid, int to,
           std::function<bool(const U &lhs, const U &rhs)> comparator) {
  int k = from;
  int i = from;
  int j = mid + 1;

  while (i <= mid && j <= to) {
    if (comparator(array[i], array[j])) {
      buf[k++] = array[i++];
    } else {
      buf[k++] = array[j++];
    }
  }

  while (i < array.GetSize() && i <= mid) {
    buf[k++] = array[i++];
  }

  for (i = from; i <= to; i++) {
    array[i] = buf[i];
  }
}

template <typename T, typename U>
void MergeSort(T &A, T &temp, int low, int high,
               std::function<bool(const U &lhs, const U &rhs)> comparator) {
  for (int m = 1; m <= high - low; m *= 2) {
    for (int i = low; i < high; i += 2 * m) {
      int from = i;
      int mid = i + m - 1;
      int to = std::min(i + 2 * m - 1, high);

      Merge<T, U>(A, temp, from, mid, to, comparator);
    }
  }
}

int CalculateSegmentSize(const Array<Point> &array) {
  int layer = 0;
  int result = 0;

  int begin = 0;
  int end = 0;

  for (int i = 0; i < array.GetSize(); ++i) {
    auto layer_prev = layer;
    layer += array[i].pos;

    if (layer_prev == 0 && layer == 1) {
      begin = array[i].coord;
    }

    if (layer_prev > 0 && layer == 0) {
      end = array[i].coord;
      result += end - begin;
    }
  }

  return result;
}

int main() {
  int n = 0;
  int begin = 0;
  int end = 0;

  std::cin >> n;
  Array<Point> array(n * 2);
  Array<Point> buf(n * 2);

  for (int i = 0; i < n; ++i) {
    std::cin >> begin >> end;

    array.AddElement(Point(begin, begin_l));
    buf.AddElement(Point(begin, begin_l));

    array.AddElement(Point(end, end_l));
    buf.AddElement(Point(end, end_l));
  }

  MergeSort<Array<Point>, Point>(
      array, buf, 0, array.GetSize() - 1,
      [](const Point &lhs, const Point &rhs) { return lhs.coord < rhs.coord; });

  std::cout << CalculateSegmentSize(array);

  return 0;
}
