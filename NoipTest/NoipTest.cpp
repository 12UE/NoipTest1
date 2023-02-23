#include"Headers.h"
template<class T>
void ShowData(T datas[], int length) {
	for (int i = 0; i < length; i++) {
		std::cout << datas[i] << " ";
	}
	std::cout << std::endl;
}
using namespace std;


template<class T,std::size_t Row,std::size_t Col>
class Mat {
private:
    T* m_data;
public:
	Mat() {
		m_data = new T[Row * Col];
		std::fill(m_data, m_data + Row * Col, 0);
	}
	~Mat() {
		delete[] m_data;
	}
    
	Mat(const Mat& mat) {//拷贝构造
		m_data = new T[Row * Col];
		std::copy(mat.m_data, mat.m_data + Row * Col, m_data);
	}
   
	Mat(Mat&& mat) { //移动
		m_data = mat.m_data;
		mat.m_data = nullptr;
	}
	
	Mat& operator=(const Mat& mat) {//赋值
		if (this != &mat) {
			std::copy(mat.m_data, mat.m_data + Row * Col, m_data);
		}
		return *this;
	}
	T& operator()(std::size_t row, std::size_t col) {
		if (row < 1 || row > Row || col < 1 || col > Col) {
			throw std::out_of_range("out of range");
		}
		return m_data[(row - 1) * Col + col - 1];
	}
	
    Mat operator+(const Mat& mat) {//重载+
        Mat result;
        for (std::size_t i = 0; i < Row * Col; i++) {
            result.m_data[i] = m_data[i] + mat.m_data[i];
        }
        return result;
    }
	
	Mat operator*(const Mat& mat) {//重载*
		Mat result;
		for (std::size_t i = 0; i < Row; i++) {
			for (std::size_t j = 0; j < Col; j++) {
				for (std::size_t k = 0; k < Col; k++) {
					result.m_data[i * Col + j] += m_data[i * Col + k] * mat.m_data[k * Col + j];
				}
			}
		}
		return result;
	}
    
	Mat operator-(const Mat& mat) {//重载-
		Mat result;
		for (std::size_t i = 0; i < Row * Col; i++) {
			result.m_data[i] = m_data[i] - mat.m_data[i];
		}
		return result;
	}
	
	Mat Transpose() {//矩阵的转置
		Mat result;
		for (std::size_t i = 0; i < Row; i++) {
			for (std::size_t j = 0; j < Col; j++) {
				result.m_data[j * Row + i] = m_data[i * Col + j];
			}
		}
		return result;
	}
	void Show() {
		for (std::size_t i = 0; i < Row; i++) {
			for (std::size_t j = 0; j < Col; j++) {
				std::cout << m_data[i * Col + j] << " ";
			}
			std::cout << std::endl;
		}
	}
};
void print(int a) {
	std::cout << "print " << a << std::endl;
}
namespace nonstd {
	template<typename T>
	class _function {
	private:
		void* _pFn = nullptr;
		template <class... _Args>
		T execute(_Args... args) {
			using functionType = T(__stdcall*)(_Args...);
			if (!_pFn) throw std::exception("function is null");
			return reinterpret_cast<functionType>(_pFn)(args...);
		}
	public:
		_function() = default;
		~_function() = default;
		template<class U>
		_function(U fn) { _pFn = reinterpret_cast<void*>(fn); }
		_function(const _function& fn) { _pFn = fn._pFn; }
		template <class... _Args> T operator()(_Args... args) {
			return execute(args...);
		}
		void* operator & () {
			return reinterpret_cast<void*>(_pFn);
		}
	};
	template<typename T>
	using function = _function<T>;
}
#include<Windows.h>
static nonstd::function<int> myMessageBoxA(MessageBoxA);
int main(){
	//nonstd::function<int> pmsgbox(MessageBoxA);
	//auto pbox = &pmsgbox;
	////输出函数地址
	//std::cout << pbox << std::endl;
	////输出MessageBoxA地址
	//std::cout << &MessageBoxA << std::endl;
	//
	////调用
	//pmsgbox(NULL, "HelloWordl", "TEXT", MB_OK);
	//print(5);
	
	myMessageBoxA(NULL, "HelloWordl", "TEXT", MB_OK);
    return 0;
}