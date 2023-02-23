#pragma once
namespace nonstd {
	void SelectSort(int datas[], int length) {
		for (int i = 0; i < length - 1; i++) {//��0��length-1 ����ѡ����С��������ǰ��
			int nMin = i;
			for (int j = i + 1; j < length; j++) {//����i����������ҳ���С����
				if (datas[j] < datas[nMin]) {
					nMin = j;//������ʱ����
				}
			}
			if (nMin != i) {//�����С��������i������i����С����λ��
				int nTemp = datas[i];
				datas[i] = datas[nMin];
				datas[nMin] = nTemp;
			}
		}
	}
	void BubbleSort(int datas[], int length) {
		for (int i = 0; i < length - 1; i++) {//��0��length-1 ����ѡ����С��������ǰ��
			for (int j = 0; j < length - i - 1; j++) {//����i����������ҳ���С����
				if (datas[j] > datas[j + 1]) {//����datas[j]��datas[j+1]������ ��֤ǰ������
					int nTemp = datas[j];
					datas[j] = datas[j + 1];
					datas[j + 1] = nTemp;
				}
			}
		}
	}
	//�Ľ���ð��
	void BubbleSort2(int datas[], int length) {
		bool bSwap = true;
		for (int i = 0; i < length - 1 && bSwap; i++) {//��0��length-1 ����ѡ����С��������ǰ��
			bSwap = false;
			for (int j = 0; j < length - i - 1; j++) {//����i����������ҳ���С����
				if (datas[j] > datas[j + 1]) {//����datas[j]��datas[j+1]������ ��֤ǰ������
					int nTemp = datas[j];
					datas[j] = datas[j + 1];
					datas[j + 1] = nTemp;
					bSwap = true;
				}
			}
		}
	}
	//ð������ Ӧ��
	/*
	*	 ��������
	*������һ����ʽ�Ļ�վ�Ա���һ���ţ�����������ƺ����ĵ��Ŷ�ˮƽ��ת��һ����վ��ְ�������ŵĳ���������������ڳ��ᣬ���������ת180�ȣ�����԰��������ڳ����λ�ý����������ַ��������������г����˳���������͸����������Ž���վ�ĳ��ᰴ����Ŵ�С�������С������ݺ󣬻�վ��������һ�����Զ���������һ����Ҫ�Ĺ����Ǳ�һ�����������ʼ�ĳ���˳�򣬼��������ö��ٲ����ܽ���������
	*���������������,��һ���ǳ��������n(1<=n<=1000),�ڶ�����n����������ʾ����ĳ�ʼ˳�������ķ�Χ��1��10000�����ֻ��һ�У������ٵĽ���������
	*/
	/*
	void BubbleSortExample(int datas[], int length) {
		int nCount = 0;
		for (int i = 0; i < length - 1; i++) {//��0��length-1 ����ѡ����С��������ǰ��
			for (int j = 0; j < length - i - 1; j++) {//����i����������ҳ���С����
				if (datas[j] > datas[j + 1]) {//����datas[j]��datas[j+1]������ ��֤ǰ������
					int nTemp = datas[j];
					datas[j] = datas[j + 1];
					datas[j + 1] = nTemp;
					nCount++;
				}
			}
		}
		printf("��������Ϊ��%d", nCount);
	}*/
	//��������
	void InsertSort(int datas[], int length) {
		for (int i = 1; i < length; i++) {//�ӵڶ�������ʼ�����β��뵽ǰ�������������
			int nTemp = datas[i];
			int j = i - 1;
			for (; j >= 0; j--) {//��i-1��ʼ��ǰ�������ҵ����ʵ�λ��
				if (datas[j] > nTemp) {
					datas[j + 1] = datas[j];
				}else {
					break;
				}
			}
			datas[j + 1] = nTemp;
		}
	}
	//Ͱ����
	void BucketSort(int datas[], int length) {
		int nMax = datas[0];
		int nMin = datas[0];
		for (int i = 1; i < length; i++) {//�ҳ����ֵ����Сֵ
			if (datas[i] > nMax) {
				nMax = datas[i];
			}
			if (datas[i] < nMin) {
				nMin = datas[i];
			}
		}
		int nBucketCount = nMax - nMin + 1;//Ͱ�ĸ���
		int* pBuckets = new int[nBucketCount];//����Ͱ
		memset(pBuckets, 0, sizeof(int) * nBucketCount);//��ʼ��Ͱ
		for (int i = 0; i < length; i++) {//�����ݷ���Ͱ��
			pBuckets[datas[i] - nMin]++;//��δ��Ͱ������װ��
		}
		int nIndex = 0;
		for (int i = 0; i < nBucketCount; i++) {//��Ͱ�е�����ȡ��
			while (pBuckets[i] > 0) {
				datas[nIndex++] = i + nMin;//������ȡ��
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
		//����
		ReversDatas(datas, length);
	}
#include<iostream>
	using namespace std;

	void QuickSortIMPL(int a[], const int left, const int right)
	{
		if (left < right)
		{
			//ѡ����
			int i = left;
			int j = right + 1;
			int pivot = a[left];  //pivotΪ���ᣬ��������߿�ʼ

			//���л���
			do {
				do i++; while (a[i] < pivot);  //�ҵ���������
				do j--; while (a[j] > pivot);  //�ҵ�������С��
				if (i < j){
					std::swap(a[i], a[j]);  //С�ķ���ߣ���ķ��ұ�
				}
			} while (i < j);
			std::swap(a[left], a[j]);
			QuickSortIMPL(a, left, j - 1);
			QuickSortIMPL(a, j + 1, right);
		}
	}
	//ʵ�ֿ�������
	void QuickSort(int datas[], int length) {
		return QuickSortIMPL(datas, 0, length-1);
	}
	//�鲢����
	void Merge(int datas[], int pTemp[], int left, int nMid, int right) {
		int i = left;
		int j = nMid + 1;
		int k = left;
		while (i <= nMid && j <= right) {
			if (datas[i] < datas[j]) {
				pTemp[k++] = datas[i++];
			}
			else {
				pTemp[k++] = datas[j++];
			}
		}
		while (i <= nMid) {
			pTemp[k++] = datas[i++];
		}
		while (j <= right) {
			pTemp[k++] = datas[j++];
		}
		for (int i = left; i <= right; i++) {
			datas[i] = pTemp[i];
		}
	}
	void MergeSortImpl(int datas[], int pTemp[], int left, int right) {
		if (left < right) {
			int nMid = (left + right) / 2;
			MergeSortImpl(datas, pTemp, left, nMid);
			MergeSortImpl(datas, pTemp, nMid + 1, right);
			Merge(datas, pTemp, left, nMid, right);
		}
	}
	//ʵ�ֹ鲢����
	void MergeSort(int datas[], int length) {
		int* pTemp = new int[length];
		MergeSortImpl(datas, pTemp, 0, length - 1);
		delete[] pTemp;
	}
	
}