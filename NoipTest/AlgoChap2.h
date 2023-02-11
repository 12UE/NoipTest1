#pragma once
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
				if (datas[j] > datas[j + 1]) {//交换datas[j]和datas[j+1]的数据 保证前后有序
					int nTemp = datas[j];
					datas[j] = datas[j + 1];
					datas[j + 1] = nTemp;
				}
			}
		}
	}
	//改进版冒泡
	void BubbleSort2(int datas[], int length) {
		bool bSwap = true;
		for (int i = 0; i < length - 1 && bSwap; i++) {//从0到length-1 依次选出最小的数放在前面
			bSwap = false;
			for (int j = 0; j < length - i - 1; j++) {//遍历i后面的数，找出最小的数
				if (datas[j] > datas[j + 1]) {//交换datas[j]和datas[j+1]的数据 保证前后有序
					int nTemp = datas[j];
					datas[j] = datas[j + 1];
					datas[j + 1] = nTemp;
					bSwap = true;
				}
			}
		}
	}
	//冒泡例题 应用
	/*
	*	 车厢重组
	*问题在一个旧式的火车站旁边有一座桥，其桥面可以绕河中心的桥墩水平旋转。一个车站的职工发现桥的长度最多能容纳两节车厢，如果将桥旋转180度，则可以把相邻两节车厢的位置交换，用这种方法可以重新排列车厢的顺序。于是他就负责用这座桥将进站的车厢按车厢号从小到大排列。他退休后，火车站决定将这一工作自动化，其中一项重要的工作是编一个程序，输入初始的车厢顺序，计算最少用多少步就能将车厢排序
	*问题的输入有两行,第一行是车厢的数量n(1<=n<=1000),第二行是n个整数，表示车厢的初始顺序，整数的范围是1到10000。输出只有一行，即最少的交换次数。
	*/
	/*
	void BubbleSortExample(int datas[], int length) {
		int nCount = 0;
		for (int i = 0; i < length - 1; i++) {//从0到length-1 依次选出最小的数放在前面
			for (int j = 0; j < length - i - 1; j++) {//遍历i后面的数，找出最小的数
				if (datas[j] > datas[j + 1]) {//交换datas[j]和datas[j+1]的数据 保证前后有序
					int nTemp = datas[j];
					datas[j] = datas[j + 1];
					datas[j + 1] = nTemp;
					nCount++;
				}
			}
		}
		printf("交换次数为：%d", nCount);
	}*/
	//插入排序
	void InsertSort(int datas[], int length) {
		for (int i = 1; i < length; i++) {//从第二个数开始，依次插入到前面的有序序列中
			int nTemp = datas[i];
			int j = i - 1;
			for (; j >= 0; j--) {//从i-1开始向前遍历，找到合适的位置
				if (datas[j] > nTemp) {
					datas[j + 1] = datas[j];
				}else {
					break;
				}
			}
			datas[j + 1] = nTemp;
		}
	}
	//桶排序
	void BucketSort(int datas[], int length) {
		int nMax = datas[0];
		int nMin = datas[0];
		for (int i = 1; i < length; i++) {//找出最大值和最小值
			if (datas[i] > nMax) {
				nMax = datas[i];
			}
			if (datas[i] < nMin) {
				nMin = datas[i];
			}
		}
		int nBucketCount = nMax - nMin + 1;//桶的个数
		int* pBuckets = new int[nBucketCount];//创建桶
		memset(pBuckets, 0, sizeof(int) * nBucketCount);//初始化桶
		for (int i = 0; i < length; i++) {//将数据放入桶中
			pBuckets[datas[i] - nMin]++;//对未分桶的数据装入
		}
		int nIndex = 0;
		for (int i = 0; i < nBucketCount; i++) {//将桶中的数据取出
			while (pBuckets[i] > 0) {
				datas[nIndex++] = i + nMin;//将数据取出
				pBuckets[i]--;
			}
		}
		delete[] pBuckets;
	}
	
	void HeapSort(int datas[], int length) {
		Heap heap;
		for (int i = 0; i < length; i++) {
			heap.insert(datas[i]);
		}
		for (int i = 0; i < length; i++) {
			datas[i] = heap.extract_max();
		}
		//逆序
		ReversDatas(datas, length);
	}
}