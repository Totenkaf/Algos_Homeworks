/*� ������������ ������ �������������� ����� �������. �������� ���������� ������� � ����� ����������� (��� ����� �����).
������� ���������� ���������� �������� ������� 2 �������. ������� ����� ������������� ������ � ������������� ������� �������.
���������� ����� ������ ������� �� ������� ������� �� ������� ����� �� ��������. � ������ ������ ������� ����� ������������ ������ ���� �������.
���������, ��� ������� ������������ ���������. ���� ������� ������������ � ������ ����� ��� �������, �� ���������, ��� ���������� ����� � ����������.
��������� ���������� ����������� ����� ������� �������.*/

#include <iostream>
#include <vector>
using namespace std;

struct Man {
	int In;
	int Out;
};

bool operator <(Man first, Man second) {
	if (first.Out < second.Out) {
		return true;
	}
	else if (first.Out == second.Out) {
		if (first.In <= second.In) {
			return true;
		}
	}
	return false;
}

void ShiftDown(vector<Man>& Arr, int i, int border){
	int i1, Child1, Child2;
	while (i < border){
		i1 = i;
		Child1 = (2 * i) + 1;
		Child2 = Child1 + 1;
		if (Child1 < border && Arr[i1] < Arr[Child1]) {
			i1 = Child1;
		}
		if (Child2 < border && Arr[i1] < Arr
      Child2]) {
			i1 = Child2;
		}
		if (i1 == i) return;
		Man temp = Arr[i];
		Arr[i] = Arr[i1];
		Arr[i1] = temp;
		i = i1;
	}
}

void HeapSort(vector<Man>& arr) {
	int i = (arr.size() / 2) - 1; //���������� ������������ ������
	while (i >= 0) {
		ShiftDown(arr, i, arr.size());
		--i;
	}
	int last = arr.size() - 1;
	while (last > 0)//����������
	{
		Man tmp = arr[0];
		arr[0] = arr[last];
		arr[last] = tmp;
		ShiftDown(arr, 0, last);
		--last;
	}
}

int main()
{
	int N; //���������� �����������
	cin >> N;

	vector<Man> Mans; //��������� �������� � ������ �����������
	int a, b;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;

		Man tmp = {a, b};
		Mans.push_back(tmp);
	}
	HeapSort(Mans);

	//�������������� ���������, ������� ����������
	int rez = 0;
	int FirstBorder = -1;
	int SecondBorder = -1;

	for (int i = 0; i < N; i++)
	{
		Man tmp = Mans[i];

		if (tmp.In > SecondBorder)
		{
			rez = rez + 2;
			FirstBorder = tmp.Out - 1;
			SecondBorder = tmp.Out;
		}
		else if (tmp.In == SecondBorder)
		{
			rez++;
			FirstBorder = SecondBorder;
			SecondBorder = tmp.Out;
		}
		else if (tmp.In > FirstBorder && tmp.Out > SecondBorder)
		{
			rez++;
			FirstBorder = SecondBorder;
			SecondBorder = tmp.Out;
		}
		else if (tmp.In > FirstBorder && tmp.In < SecondBorder) {
			rez++;
			FirstBorder = tmp.Out;
		}
	}
	cout << rez;
	return 0;
}
