/**Дан отсортированный массив различных целых чисел A[0..n-1]
и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i].
Найдите минимальный индекс элемента массива A[k],
ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000.
Время работы поиска для каждого элемента B[i]: O(log(k)).**/

#include <iostream>

using namespace std;

int binaryFind(int* where, int what, int from, int to) {
    int mid;
    to--;
    while (from < to-1) {
        mid = (to + from) / 2;
        //cout << ">>> FROM: " << from << " MID: " << mid << " TO: " << to << endl;
        if (what > where[mid])
            from = mid;
        else if (what < where[mid])
            to = mid;
        else
            return mid;
    }
    int ansId, ans;
    if ((where[to] - what) < (what - where[from]))
        ansId = to;
    else
        ansId = from;
    for (ans = where[ansId]; ansId > 0 && where[ansId-1] == ans; ansId--) {;}
    return ansId;
};

int expFind(int* where, int what, int from, int to) {
    if (what < where[from])
        return from;
    int addIndex = 1;
    int left = from;
    while (from < to && (where[left] > what || (from+addIndex < to && where[from+addIndex] < what))) {
        //cout << ">FROM: " << left << " TO: " << from+addIndex << endl;
        if (where[from] < what && where[from] != where[left])
            left = from;
        from += addIndex;
        addIndex *= 2;
    }
    if (left >= to)
        return to-1;
    //cout << ">AT ALL from: " << left << " TO: " << from+addIndex+1 << endl;
    return binaryFind(where, what, left, min(from+addIndex+1, to));
}

int main(void) {
	int n;
	cin >> n;
	int A[n];
    for (int i = 0; i < n; i++) {
		cin >> A[i];
    }
    int m, findThis, lastFind, lastFindId;
	cin >> m;
	cin >> findThis;
	lastFindId = expFind(A, findThis, 0, n);
	cout << lastFindId << ' ';
    for (int i = 0; i < m-1; i++) {
        lastFind = findThis;
		cin >> findThis;
		if (findThis > lastFind)
            lastFindId = expFind(A, findThis, lastFindId, n);
        else if (findThis < lastFind)
            lastFindId = expFind(A, findThis, 0, lastFindId+1);
        cout << lastFindId << ' ';
    }

	cout << endl;
	return 0;
}
