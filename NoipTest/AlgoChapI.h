#pragma once

//高精度计算章节
class HighPrecisionCalc {
private:
	void ClearBuffer() {
		memset(szBuffer, 0, sizeof(szBuffer));
	}
public:
	char szBuffer[_MAX_PATH * 2];//缓冲区 用于存储计算结果
	HighPrecisionCalc() {
		memset(szBuffer, 0, sizeof(szBuffer));
	}
	~HighPrecisionCalc() = default;
	template<class T>
	std::string toString(T n) {
		return std::to_string(n);
	}
	void LeftShift(int nPos) {//删除前导0
		while (szBuffer[0] == '0' && nPos > 1) {//首位含有0时候 左移 0123 转换为 123
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
		int nMaxLen = nLen1 > nLen2 ? nLen1 : nLen2;//两个串当中长度最大的
		int nMinLen = nLen1 < nLen2 ? nLen1 : nLen2;//两个串当中长度最小的
		int nCarry = 0;//进位
		int nTemp = 0;//临时结果
		int nPos = 0;//缓冲区位置;
		for (int i = 0; i < nMinLen; i++) {//从最低位开始加
			nTemp = ToInt(number1[nLen1 - i - 1]) + ToInt(number2[nLen2 - i - 1])+ nCarry;
			nCarry = nTemp / 10;//进位
			nTemp %= 10;//十位数
			szBuffer[nPos++] = nTemp + '0';//nTemp + '0' 转换为字符
		}
		if (nLen1 > nLen2) {//串一长度大于串二 要把串一剩下的数加上去
			for (int i = nMinLen; i < nMaxLen; i++) { 
				nTemp = ToInt(number1[nLen1 - i - 1]) + nCarry;
				nCarry = nTemp / 10;
				nTemp %= 10;
				szBuffer[nPos++] = nTemp + '0';
			}
		}else {
			for (int i = nMinLen; i < nMaxLen; i++) {//串一小于串二 要把串二剩下的数加上去
				nTemp = ToInt(number2[nLen2 - i - 1]) + nCarry;
				nCarry = nTemp / 10;
				nTemp %= 10;
				szBuffer[nPos++] = nTemp + '0';
			}
		}
		if (nCarry > 0) {//进位大于0 说明最高位有进位
			szBuffer[nPos++] = nCarry + '0';
		}
		//前后颠倒
		 for (int i = 0; i < nPos / 2; i++) {
			char cTemp = szBuffer[i];
			szBuffer[i] = szBuffer[nPos - i - 1];
			szBuffer[nPos - i - 1] = cTemp;
		}
		szBuffer[nPos] = '\0';//补0
	}
	void Sub(const std::string number1, const std::string& number2) {
		ClearBuffer();
		int nLen1 = number1.length();
		int nLen2 = number2.length();
		int nMaxLen = nLen1 > nLen2 ? nLen1 : nLen2;//两个串当中长度最大的
		int nMinLen = nLen1 < nLen2 ? nLen1 : nLen2;//两个串当中长度最小的
		int nCarry = 0;//进位
		int nTemp = 0;//临时结果
		int nPos = 0;//缓冲区位置;
		for (int i = 0; i < nMinLen; i++) {//从最低位开始减
			//nLen1 - i - 1 从个位开始
			nTemp = ToInt(number1[nLen1 - i - 1]) - ToInt(number2[nLen2 - i - 1]) - nCarry;
			if (nTemp < 0) {//如果小于0 说明要借位
				nTemp += 10;
				nCarry = 1;
			}
			else {
				nCarry = 0;
			}
			szBuffer[nPos++] = nTemp + '0';//nTemp + '0' 转换为字符
		}
		if (nLen1 > nLen2) {//串一长度大于串二 要把串一剩下的数减去去
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
			for (int i = nMinLen; i < nMaxLen; i++) {//串一小于串二 要把串二剩下的数减去去
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
		if (nCarry > 0) {//进位大于0 说明最高位有进位
			szBuffer[nPos++] = nCarry + '0';
		}
		for (int i = 0; i < nPos / 2; i++) {//头尾交换
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
		int nLen = nlen1 + nlen2;//结果长度 最大为两个数长度之和
		int nCarry = 0;//进位
		int nTemp = 0;//临时结果
		int nPos = 0;//缓冲区位置;
		int* pTemp = new int[nLen];//临时结果数组
		memset(pTemp, 0, sizeof(int) * nLen);//初始化为0
		for (int i = 0; i < nlen1; i++) {//从最低位开始乘
			for (int j = 0; j < nlen2; j++) {
				nTemp = ToInt(number1[nlen1 - i - 1]) * ToInt(number2[nlen2 - j - 1]) + pTemp[i + j] + nCarry;
				pTemp[i + j] = nTemp % 10;
				nCarry = nTemp / 10;
			}
			if (nCarry > 0) {//进位大于0 说明最高位有进位
				pTemp[i + nlen2] = nCarry;
				nCarry = 0;
			}
		}
		for (int i = 0; i < nLen; i++) {//头尾交换
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
	//计算n的阶乘
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
template<std::size_t nRadix = 10>//默认10进制
class Number {
public:
	int m_number[_MAX_PATH]; //int缓冲区
	int m_length = 0;
	void Clear(){
		memset(m_number, 0, sizeof(m_number));
	}
	bool validcheck(int numbers[], int length) {//判断输入的数字是否满足n进制这一条件
		for (int i = 0; i < length; i++) {
			if (numbers[i] >= nRadix) {
				return false;
			}
		}
		return true;
	}
	Number(int numbers[],int length) {//接收n进制数据作为数组
		Clear();
		if (!validcheck(numbers,length)) std::cout << "给定的n进制非法" << std::endl;;
		m_length = length;
		memcpy(m_number, numbers, length * sizeof(int));
	}
	~Number() = default;
	Number& operator+(Number& b) {//重载加号运算 相同进制的数相加
		int nLen1 = m_length;
		int nLen2 = b.m_length;
		int nMaxLen = m_length > b.m_length ? m_length : b.m_length;//两个串当中长度最大的
		int nMinLen = m_length < b.m_length ? m_length : b.m_length;//两个串当中长度最小的
		int nCarry = 0;//进位
		int nTemp = 0;//临时结果
		int nPos = 0;//缓冲区位置;
		int m_numberbuf[_MAX_PATH];
		memset(&m_numberbuf, 0, sizeof(m_numberbuf));
		for (int i = 0; i < nMinLen; i++) {//从最低位开始加
			nTemp = m_number[nLen1 -i -1] + b.m_number[nLen2 - i - 1] + nCarry;
			nCarry = nTemp / nRadix;//进位
			nTemp %= nRadix;//十位数
			m_numberbuf[nPos++] = nTemp;
		}
		if (nLen1 > nLen2) {//串一长度大于串二 要把串一剩下的数加上去
			for (int i = nMinLen; i < nMaxLen; i++) {
				nTemp = m_number[nLen1 - i - 1] + nCarry;
				nCarry = nTemp / nRadix;
				nTemp %= nRadix;
				m_numberbuf[nPos++] = nTemp;
			}
		}else {
			for (int i = nMinLen; i < nMaxLen; i++) {//串一小于串二 要把串二剩下的数加上去
				nTemp = b.m_number[nLen2 - i - 1] + nCarry;
				nCarry = nTemp / nRadix;
				nTemp %= nRadix;
				b.m_number[nPos++] = nTemp;
			}
		}
		if (nCarry > 0) {//进位大于0 说明最高位有进位
			m_number[nPos++] = nCarry;
		}
		//前后颠倒
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
