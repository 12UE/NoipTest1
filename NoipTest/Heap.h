#pragma once
class Heap {
private:
	std::vector<int> data;
	void heapify_up(int index) {
		int parent = (index - 1) / 2;
		if (index > 0 && data[index] > data[parent]) {
			std::swap(data[index], data[parent]);
			heapify_up(parent);
		}
	}
	void heapify_down(int index) {
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int largest = index;
		if (left < data.size() && data[left] > data[index]) {
			largest = left;
		}
		if (right < data.size() && data[right] > data[largest]) {
			largest = right;
		}
		if (index != largest) {
			std::swap(data[index], data[largest]);
			heapify_down(largest);
		}
	}
public:
	Heap() {}
	void insert(int value) {
		data.push_back(value);
		heapify_up(data.size() - 1);
	}
	int extract_max() {
		int max_value = data[0];
		data[0] = data[data.size() - 1];
		data.pop_back();
		heapify_down(0);
		return max_value;
	}
	int get_max() {
		return data[0];
	}
	int size() {
		return data.size();
	}
};
void ReversDatas(int datas[], int length) {
	for (int i = 0; i < length / 2; i++) {
		int nTemp = datas[i];
		datas[i] = datas[length - i - 1];
		datas[length - i - 1] = nTemp;
	}
}
