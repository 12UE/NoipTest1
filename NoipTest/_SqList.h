#pragma once
#define MaxSize 100
#define LISTINCREMENT 10

typedef int ElemType;

class SqList {
private:
    ElemType* elem;
    int length;
    int maxSize;
public:
    SqList(int n = MaxSize) {  //构造函数
        elem = new ElemType[n];
        length = 0;
        maxSize = n;
    }

    ~SqList() {  //析构函数
        delete[] elem;
    }

    void SqList_insert(int i, int e) {  // 在第i个位置插入数据元素
        if (i < 1 || i > length + 1 || length == maxSize) {
            throw "Out of Range or Overflow";
        }
        for (int j = length; j >= i; j--) {
            elem[j] = elem[j - 1];
        }
        elem[i - 1] = e;
        length++;
    }

    void SqList_delete(int i, int& e) {  // 删除第i个数据元素
        if (i<1 || i>length) return; //插入位置异常
        int* p = &elem[i - 1], * q = &elem[length - 1];
        e = *p;
        for (; p < q; p++) *p = *(p + 1);
        length--;

    }

    int GetElem(int x) {  // 数据元素定位
        int i = 1;
        while (i <= length && elem[i - 1] != x) {
            i++;
        }
        if (i <= length) {
            return i;
        }
        else {
            return 0;
        }
    }
    int ListLength() {
		return length;
    }

    void mergelist(SqList& la, SqList& lb) {  // 归并顺序表
        int i = 1, j = 1, k = 0;
        while (i <= la.length && j <= lb.length) {
            if (la.elem[i - 1] <= lb.elem[j - 1]) {
                elem[k++] = la.elem[i - 1];
                i++;
            }
            else {
                elem[k++] = lb.elem[j - 1];
                j++;
            }
        }
        while (i <= la.length) {
            elem[k++] = la.elem[i - 1];
            i++;
        }
        while (j <= lb.length) {
            elem[k++] = lb.elem[j - 1];
            j++;
        }
        length = k;
    }

    // 其它基本操作
};
