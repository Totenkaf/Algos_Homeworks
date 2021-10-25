/* Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 1000000.
 * Отсортировать массив методом поразрядной сортировки MSD по битам.*/

#include <iostream>

#define TYPE long long

using namespace std;

//----Standart queue
class Queue {
public:
    Queue() {
        data = nullptr;
        len = 0;
        maxLen = 0;
        headId = 0;
    }
    ~Queue() {
        delete[] data;
    }
    TYPE popFront();
    TYPE pushBack(TYPE val);
    TYPE getElem(int i) {return data[(headId + i) % maxLen];}
    void swap(int id1, int id2);

    void sortMSD();

    void print();
private:
    int len, headId, maxLen;
    TYPE* data;

    void addMaxLen();

    void private_sortMSD(int left, int right, int nowRazr);
};

void arrCpy(TYPE* to_arr, const TYPE* from_arr, int len, int from, int offset) {
    for (int i = 0; i < len-from; i++)
        to_arr[i+offset] = from_arr[i+from];
}

TYPE Queue::popFront() {
    if (len == 0)
        return -1;
    int memHeadId = headId;
    headId = (headId + 1) % maxLen;
    len--;
    return data[memHeadId];
}

TYPE Queue::pushBack(TYPE val) {
    if (maxLen == 0) {
        data = new TYPE[1];
        maxLen = 1;
    } else if (maxLen == len)
        addMaxLen();
    data[(len + headId) % maxLen] = val;
    len++;
}

void Queue::addMaxLen() {
    TYPE* tmpBuffer = new TYPE[maxLen * 2];
    arrCpy(tmpBuffer, data, maxLen, headId, 0);
    arrCpy(tmpBuffer, data, headId, 0, maxLen-headId);
    headId = 0;

    delete[] data;
    data = tmpBuffer;
    maxLen *= 2;
}

void Queue::swap(int id1, int id2) {
    TYPE tmp = data[id1];
    data[id1] = data[id2];
    data[id2] = tmp;
}

void Queue::print() {
    for (int i = 0; i < maxLen; i++)
        if (i < headId+len)
            cout << data[i] << ' ';
        /*else
            cout << "~~~" << ' ';
    cout << endl;
    for (int i = 0; i < maxLen; i++)
        if (i == headId)
            cout << "^^^" << ' ';
        else
            cout << ">>>" << ' ';
    cout << ':' << endl;*/
}
//-----Functions

int lenBits(long long n) {
    int rez = 0;
    while (n > 0) {
        n >>= 1;
        rez++;
    }
    /*int rez = 0;
    while (n > 0) {
        n /= 10;
        rez++;
    }*/
    return rez;
}

bool getBit(long long n, int i) {
    return (n >> i) & 1;
    /*for (; i > 0; i--)
        n /= 10;
    return n % 10;*/
}

void Queue::sortMSD() {
    long long tmp, maxLen = 0;
	for (int i = 0; i < len; i++)
        if ((tmp = lenBits(data[i])) > maxLen)
            maxLen = tmp;
    private_sortMSD(0, len, maxLen-1);
}

void Queue::private_sortMSD(int left, int right, int nowRazr) {
    if (left+1 >= right) {
        return;
    }
    int cpyLeft = left;
    int cpyRight = right;
    right--;
    while (left != right) {
        while (left < right && !getBit(data[left], nowRazr)) {
            left++; // ищем первую единицу
            //cout << "Left: " << cpyLeft << ">>> Mid: " << left << " NowEl: " << data[left] << endl;
        }
        while (left < right && getBit(data[right], nowRazr))
            right--; // ищем последний ноль
        swap(left, right);
    }
    if (!getBit(data[cpyRight-1], nowRazr))
        left++;
    //print();
    //cout << "Left: " << cpyLeft << " Mid: " << left << " Right: " << cpyRight << " Now: " << nowRazr << endl;

    if (--nowRazr < 0)
        return;
    private_sortMSD(cpyLeft, left, nowRazr);
    private_sortMSD(left, cpyRight, nowRazr);
}


int main() {
	int n;
	cin >> n;

	Queue Arr;
	long long a;
	for (int i = 0; i < n; i++) {
		cin >> a;
		Arr.pushBack(a);
	}

    Arr.sortMSD();
    Arr.print();

    return 0;
}
