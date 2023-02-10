#pragma once
#include<iostream>
#include<string>
//�߾��ȼ����½�
class HighPrecisionCalc {
private:
	void ClearBuffer() {
		memset(szBuffer, 0, sizeof(szBuffer));
	}
public:
	char szBuffer[_MAX_PATH * 2];//������ ���ڴ洢������
	HighPrecisionCalc() {
		memset(szBuffer, 0, sizeof(szBuffer));
	}
	~HighPrecisionCalc() = default;
	template<class T>
	std::string toString(T n) {
		return std::to_string(n);
	}
	void LeftShift(int nPos) {//ɾ��ǰ��0
		while (szBuffer[0] == '0' && nPos > 1) {//��λ����0ʱ�� ���� 0123 ת��Ϊ 123
			for (int i = 0; i < nPos; i++) {
				szBuffer[i] = szBuffer[i + 1];
			}
			nPos--;
		}
	}
	int ToInt(char i) {return  i - '0'; }
	void Add(const std::string number1, const std::string& number2) {
		ClearBuffer();
		int nLen1 = number1.length();
		int nLen2 = number2.length();
		int nMaxLen = nLen1 > nLen2 ? nLen1 : nLen2;//���������г�������
		int nMinLen = nLen1 < nLen2 ? nLen1 : nLen2;//���������г�����С��
		int nCarry = 0;//��λ
		int nTemp = 0;//��ʱ���
		int nPos = 0;//������λ��;
		for (int i = 0; i < nMinLen; i++) {//�����λ��ʼ��
			nTemp = ToInt(number1[nLen1 - i - 1]) + ToInt(number2[nLen2 - i - 1])+ nCarry;
			nCarry = nTemp / 10;//��λ
			nTemp %= 10;//ʮλ��
			szBuffer[nPos++] = nTemp + '0';//nTemp + '0' ת��Ϊ�ַ�
		}
		if (nLen1 > nLen2) {//��һ���ȴ��ڴ��� Ҫ�Ѵ�һʣ�µ�������ȥ
			for (int i = nMinLen; i < nMaxLen; i++) { 
				nTemp = ToInt(number1[nLen1 - i - 1]) + nCarry;
				nCarry = nTemp / 10;
				nTemp %= 10;
				szBuffer[nPos++] = nTemp + '0';
			}
		}else {
			for (int i = nMinLen; i < nMaxLen; i++) {//��һС�ڴ��� Ҫ�Ѵ���ʣ�µ�������ȥ
				nTemp = ToInt(number2[nLen2 - i - 1]) + nCarry;
				nCarry = nTemp / 10;
				nTemp %= 10;
				szBuffer[nPos++] = nTemp + '0';
			}
		}
		if (nCarry > 0) {//��λ����0 ˵�����λ�н�λ
			szBuffer[nPos++] = nCarry + '0';
		}
		//ǰ��ߵ�
		 for (int i = 0; i < nPos / 2; i++) {
			char cTemp = szBuffer[i];
			szBuffer[i] = szBuffer[nPos - i - 1];
			szBuffer[nPos - i - 1] = cTemp;
		}
		szBuffer[nPos] = '\0';//��0
	}
	void Sub(const std::string number1, const std::string& number2) {
		ClearBuffer();
		int nLen1 = number1.length();
		int nLen2 = number2.length();
		int nMaxLen = nLen1 > nLen2 ? nLen1 : nLen2;//���������г�������
		int nMinLen = nLen1 < nLen2 ? nLen1 : nLen2;//���������г�����С��
		int nCarry = 0;//��λ
		int nTemp = 0;//��ʱ���
		int nPos = 0;//������λ��;
		for (int i = 0; i < nMinLen; i++) {//�����λ��ʼ��
			//nLen1 - i - 1 �Ӹ�λ��ʼ
			nTemp = ToInt(number1[nLen1 - i - 1]) - ToInt(number2[nLen2 - i - 1]) - nCarry;
			if (nTemp < 0) {//���С��0 ˵��Ҫ��λ
				nTemp += 10;
				nCarry = 1;
			}
			else {
				nCarry = 0;
			}
			szBuffer[nPos++] = nTemp + '0';//nTemp + '0' ת��Ϊ�ַ�
		}
		if (nLen1 > nLen2) {//��һ���ȴ��ڴ��� Ҫ�Ѵ�һʣ�µ�����ȥȥ
			for (int i = nMinLen; i < nMaxLen; i++) {
				nTemp = ToInt(number1[nLen1 - i - 1]) - nCarry;
				if (nTemp < 0) {
					nTemp += 10;
					nCarry = 1;
				}
				else {
					nCarry = 0;
				}
				szBuffer[nPos++] = nTemp + '0';
			}
		}
		else {
			for (int i = nMinLen; i < nMaxLen; i++) {//��һС�ڴ��� Ҫ�Ѵ���ʣ�µ�����ȥȥ
				nTemp = ToInt(number2[nLen2 - i - 1]) - nCarry;
				if (nTemp < 0) {
					nTemp += 10;
					nCarry = 1;
				}
				else {
					nCarry = 0;
				}
				szBuffer[nPos++] = nTemp + '0';
			}
		}
		if (nCarry > 0) {//��λ����0 ˵�����λ�н�λ
			szBuffer[nPos++] = nCarry + '0';
		}
		for (int i = 0; i < nPos / 2; i++) {//ͷβ����
			char cTemp = szBuffer[i];
			szBuffer[i] = szBuffer[nPos - i - 1];
			szBuffer[nPos - i - 1] = cTemp;
		}
		LeftShift(nPos);
	}
	void Mul(const std::string number1, const std::string& number2) {
		ClearBuffer();
		int nlen1 = number1.length();
		int nlen2 = number2.length();
		int nLen = nlen1 + nlen2;//������� ���Ϊ����������֮��
		int nCarry = 0;//��λ
		int nTemp = 0;//��ʱ���
		int nPos = 0;//������λ��;
		int* pTemp = new int[nLen];//��ʱ�������
		memset(pTemp, 0, sizeof(int) * nLen);//��ʼ��Ϊ0
		for (int i = 0; i < nlen1; i++) {//�����λ��ʼ��
			for (int j = 0; j < nlen2; j++) {
				nTemp = ToInt(number1[nlen1 - i - 1]) * ToInt(number2[nlen2 - j - 1]) + pTemp[i + j] + nCarry;
				pTemp[i + j] = nTemp % 10;
				nCarry = nTemp / 10;
			}
			if (nCarry > 0) {//��λ����0 ˵�����λ�н�λ
				pTemp[i + nlen2] = nCarry;
				nCarry = 0;
			}
		}
		for (int i = 0; i < nLen; i++) {//ͷβ����
			szBuffer[i] = pTemp[nLen - i - 1] + '0';
		}
		LeftShift(nLen);
		delete[] pTemp;
	}
	void Div(const std::string number1, const std::string& number2) {
		ClearBuffer();
		int nLen1 = number1.length();
		int nLen2 = number2.length();
		int nPos = 0;
		int nTemp = 0;
		int nCarry = 0;
		int nLen = nLen1 - nLen2 + 1;
		int* pTemp = new int[nLen];
		memset(pTemp, 0, sizeof(int) * nLen);
		for (int i = 0; i < nLen; i++) {
			nTemp = nCarry * 10 + ToInt(number1[i]);
			pTemp[i] = nTemp / ToInt(number2[0]);
			nCarry = nTemp % ToInt(number2[0]);
		}
		for (int i = 0; i < nLen; i++) {
			szBuffer[i] = pTemp[i] + '0';
		}
		LeftShift(nLen);
		delete[] pTemp;
	}
	//����n�Ľ׳�
	void Factorial(int n) {
		ClearBuffer();
		szBuffer[0] = '1';
		for (int i = 1; i <= n; i++) {
			Mul(szBuffer, std::to_string(i));
		}
	}
	void Print() {
		std::cout << szBuffer << std::endl;
	}
};
template<std::size_t nRadix = 10>//Ĭ��10����
class Number {
public:
	int m_number[_MAX_PATH]; //int������
	int m_length = 0;
	void Clear(){
		memset(m_number, 0, sizeof(m_number));
	}
	bool validcheck(int numbers[], int length) {//�ж�����������Ƿ�����n������һ����
		for (int i = 0; i < length; i++) {
			if (numbers[i] >= nRadix) {
				return false;
			}
		}
		return true;
	}
	Number(int numbers[],int length) {//����n����������Ϊ����
		Clear();
		if (!validcheck(numbers,length)) std::cout << "������n���ƷǷ�" << std::endl;;
		m_length = length;
		memcpy(m_number, numbers, length * sizeof(int));
	}
	~Number() = default;
	Number& operator+(Number& b) {//���ؼӺ����� ��ͬ���Ƶ������
		int nLen1 = m_length;
		int nLen2 = b.m_length;
		int nMaxLen = m_length > b.m_length ? m_length : b.m_length;//���������г�������
		int nMinLen = m_length < b.m_length ? m_length : b.m_length;//���������г�����С��
		int nCarry = 0;//��λ
		int nTemp = 0;//��ʱ���
		int nPos = 0;//������λ��;
		int m_numberbuf[_MAX_PATH];
		memset(&m_numberbuf, 0, sizeof(m_numberbuf));
		for (int i = 0; i < nMinLen; i++) {//�����λ��ʼ��
			nTemp = m_number[nLen1 -i -1] + b.m_number[nLen2 - i - 1] + nCarry;
			nCarry = nTemp / nRadix;//��λ
			nTemp %= nRadix;//ʮλ��
			m_numberbuf[nPos++] = nTemp;
		}
		if (nLen1 > nLen2) {//��һ���ȴ��ڴ��� Ҫ�Ѵ�һʣ�µ�������ȥ
			for (int i = nMinLen; i < nMaxLen; i++) {
				nTemp = m_number[nLen1 - i - 1] + nCarry;
				nCarry = nTemp / nRadix;
				nTemp %= nRadix;
				m_numberbuf[nPos++] = nTemp;
			}
		}else {
			for (int i = nMinLen; i < nMaxLen; i++) {//��һС�ڴ��� Ҫ�Ѵ���ʣ�µ�������ȥ
				nTemp = b.m_number[nLen2 - i - 1] + nCarry;
				nCarry = nTemp / nRadix;
				nTemp %= nRadix;
				b.m_number[nPos++] = nTemp;
			}
		}
		if (nCarry > 0) {//��λ����0 ˵�����λ�н�λ
			m_number[nPos++] = nCarry;
		}
		//ǰ��ߵ�
		for (int i = 0; i < nPos / 2; i++) {
			int cTemp = m_numberbuf[i];
			m_numberbuf[i] = m_numberbuf[nPos - i - 1];
			m_numberbuf[nPos - i - 1] = cTemp;
		}
		m_length = nPos;
		memcpy(m_number, m_numberbuf, nPos * sizeof(int));
		return *this;
	}
	void Print() {
		for (int i = 0; i < m_length; i++) {
			std::cout << m_number[i];
		}
	}
};
/*
* int number1[2] = {1,2};//12 
	int number2[1] = {2};//2 
	Number<10> a(number1, 2);
	Number<10> b(number2,1);
	Number<10> c = a + b;//14
*/
