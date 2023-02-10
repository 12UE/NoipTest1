#pragma once
//����ר��
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
				if (datas[j] > datas[j + 1]) {//����datas[j]��datas[j+1]������
					int nTemp = datas[j];
					datas[j] = datas[j + 1];
					datas[j + 1] = nTemp;
				}
			}
		}
	}
}