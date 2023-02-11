#include"Headers.h"
template<class T>
void ShowData(T datas[], int length) {
	for (int i = 0; i < length; i++) {
		std::cout << datas[i] << " ";
	}
	std::cout << std::endl;
}
int main(){
	srand(time(NULL)); 
	int datas[100];
	for (int i = 0; i < 100; i++) {
		datas[i] = rand() % 100;
	}
	nonstd::HeapSort(datas, 100);
	ShowData(datas, 100);
	return 0;
}