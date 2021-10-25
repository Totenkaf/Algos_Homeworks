#include <iostream>

using namespace std;

//------Standart Heap + Heap methods

template <typename Type, typename Comparator = std::less<Type>>
class Heap {
public:
    Heap() {
        data = nullptr;
        len = 0;
        maxLen = 0;
        headId = 0;
    }
    ~Heap() {
        delete[] data;
    }
    void popFront(int delLen = 1);
    void pushBack(Type val);
    Type getElem(int i) {return data[(headId + i) % maxLen];}
    void delElem(int i);
    bool isEmpty() {return len < 1;}
    int getLen() {return len;}
    void swap(int id1, int id2);

    void print();

    void shiftUp(int i);
    void shiftDown(int i);
private:
    int len, headId, maxLen;
    Type* data;

    Comparator cmp;

    void addMaxLen();
};

template <typename Type>
void arrCpy(Type* to_arr, const Type* from_arr, int len, int from, int offset) {
    for (int i = 0; i < len-from; i++)
        to_arr[i+offset] = from_arr[i+from];
}


template <typename T, typename Comparator>
void Heap<T, Comparator>::popFront(int delLen) {
    if (len - delLen < 0 || delLen < 1)
        return;
    int memHeadId = headId;
    headId = (headId + delLen) % maxLen;
    len -= delLen;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::pushBack(T val) {
    if (maxLen == 0) {
        data = new T[1];
        maxLen = 1;
    } else if (maxLen == len)
        addMaxLen();
    data[(len + headId) % maxLen] = val;
    len++;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::delElem(int i) {
    for (int c = headId+i; c < len-1; c++)
        data[c % maxLen] = data[(c+1) % maxLen];
    len--;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::addMaxLen() {
    T* tmpBuffer = new T[maxLen * 2];
    arrCpy(tmpBuffer, data, maxLen, headId, 0);
    arrCpy(tmpBuffer, data, maxLen, headId, maxLen-headId);
    headId = 0;

    delete[] data;
    data = tmpBuffer;
    maxLen *= 2;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::swap(int id1, int id2) {
    id2 = (headId + id2) % maxLen;
    id1 = (headId + id1) % maxLen;
    T tmp = data[id1];
    data[id1] = data[id2];
    data[id2] = tmp;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::print() {
    for (int i = 0; i < maxLen; i++)
        if (i < headId+len)
            cout << data[i] << ' ';
        else
            cout << "~~" << ' ';
    cout << endl;
    for (int i = 0; i < maxLen; i++)
        if (i == headId)
            cout << "^^" << ' ';
        else
            cout << ">>" << ' ';
    cout << ':' << endl;
}

//------Heap sort
template <typename T, typename Comparator>
void Heap<T, Comparator>::shiftDown(int i) {
	int lasti, child1, child2;
	while (i < len) {
		lasti = i;
		child1 = 2 * i + 1;
		child2 = child1 + 1;
		if (child1 < len && cmp(data[child1], data[i]))
			i = child1;
		if (child2 < len && cmp(data[child2], data[i]))
			i = child2;
        if (i == lasti)
            return;
        swap(lasti, i);
	}
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::shiftUp(int i) {
    int lasti;
    while (i > 0) {
        lasti = i;
        i = (i - 1) / 2;
        if (!cmp(data[lasti], data[i])) // !< - is >=
            return;
        swap(lasti, i);
    }
}

//------Main

int main(void) {
	int c, n, in, out, maxLen = 0;
	Heap<int> heap;
	cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> in >> out;

        while(!heap.isEmpty() && heap.getElem(0) < in) {
            heap.swap(0, heap.getLen()-1);
            heap.delElem(heap.getLen()-1);
            heap.shiftDown (0);
        }

        heap.pushBack(out);
        heap.shiftUp(heap.getLen()-1);

        //heap.print();
        //cout << "----" << endl;

        if (heap.getLen() > maxLen)
            maxLen = heap.getLen();
    }

	cout << maxLen << endl;
	return 0;
}
