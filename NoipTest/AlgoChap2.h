#pragma once
//排序专题
namespace nonstd {
	void SelectSort(int datas[], int length) {
		for (int i = 0; i < length - 1; i++) {//从0到length-1 依次选出最小的数放在前面
			int nMin = i;
			for (int j = i + 1; j < length; j++) {//遍历i后面的数，找出最小的数
				if (datas[j] < datas[nMin]) {
					nMin = j;//交给临时变量
				}
			}
			if (nMin != i) {//如果最小的数不是i，交换i和最小数的位置
				int nTemp = datas[i];
				datas[i] = datas[nMin];
				datas[nMin] = nTemp;
			}
		}
	}
	void BubbleSort(int datas[], int length) {
		for (int i = 0; i < length - 1; i++) {//从0到length-1 依次选出最小的数放在前面
			for (int j = 0; j < length - i - 1; j++) {//遍历i后面的数，找出最小的数
				if (datas[j] > datas[j + 1]) {//交换datas[j]和datas[j+1]的数据
					int nTemp = datas[j];
					datas[j] = datas[j + 1];
					datas[j + 1] = nTemp;
				}
			}
		}
	}
}