//Chao thay Duy
#include <iostream>
#include <string>
using namespace std;

// template <class T>
// T layGiaTriLonHon(T *a, T *b)
// {
//     if (*a > *b)
//     {
//         return *a;
//     }
//     else if (*a < *b)
//     {
//         return *b;
//     }
//     else
//     {
//         if (is_same<T, string>::value)
//         {
//             return *a + *b;
//         }
//         else
//         {
//             return *a + *b;
//         }
//     }
// }

// int main()
// {
//     // Sử dụng hàm template với các kiểu dữ liệu khác nhau
//     int int1 = 5, int2 = 10;
//     cout << "Greater value: " << layGiaTriLonHon(&int1, &int2) << endl;

//     double double1 = 3.5, double2 = 7.2;
//     cout << "Greater value: " << layGiaTriLonHon(&double1, &double2) << endl;

//     string str1 = "Hello", str2 = "World";
//     cout << "Greater value: " << layGiaTriLonHon(&str1, &str2) << endl;

//     return 0;
// }
// template <class Type>
// Type lonHon(Type *a, Type *b)
// {
//     if (typeid(*a) == typeid(string))
//         return *a + *b;
//     if (*a > *b)
//         return *a;
//     return *b;
// }

// int main()
// {
//     int a = 3;
//     int b = 6;

//     string c = "Hai";
//     string d = "Doan";

//     string *ptr3 = &c;
//     string *ptr4 = &d;

//     int *ptr1 = &a;
//     int *ptr2 = &b;

//     cout << lonHon(ptr1, ptr2) << endl;
//     cout << lonHon(ptr3, ptr4) << endl;

//     return 0;
// }
template <class E>
class Alist
{
protected:
    int maxSize;
    int size;
    E *list;

public:
    // Ham co ban, tien ich
    Alist(int maxSize = 100) : maxSize(maxSize), size(0)
    {
        list = new E[maxSize];
    }

    void print() const
    {
        cout << "Danh sach list: ";
        for (int i = 0; i < size; ++i)
        {
            cout << list[i] << " ";
        }
        cout << endl;
    }

    E getElement(int i) const
    {
        if (i >= 0 && i < size)
        {
            return list[i];
        }
        else
        {
            cout << "Vi tri can lay khong hop le." << endl;
            return E();
        }
    }

    bool find(const E &e) const
    {
        return search(e) != -1;
    }

    int search(const E &e) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (list[i] == e)
            {
                return i; // Return the index if found
            }
        }
        return -1; // Return -1 if not found
    }

    // Ham cap nhat
    void add(int i, const E &e)
    {
        if (i >= 0 && i <= size)
        {
            if (size < maxSize)
            {
                for (int j = size; j > i; --j)
                {
                    list[j] = list[j - 1];
                }
                list[i] = e;
                ++size;
            }
            else
            {
                cout << "Danh sach da day" << endl;
            }
        }
        else
        {
            cout << "Khong ton tai vi tri can them" << endl;
        }
    }

    void remove(int i)
    {
        if (i >= 0 && i < size)
        {
            for (int j = i; j < size - 1; ++j)
            {
                list[j] = list[j + 1];
            }
            --size;
        }
        else
        {
            cout << "Vi tri khong ton tai." << endl;
        }
    }

    void removeKey(const E &e)
    {
        int index = search(e);
        if (index != -1)
        {
            remove(index);
        }
        else
        {
            cout << "Khong tim trong list" << endl;
        }
    }

    void replace(int i, const E &e)
    {
        if (i >= 0 && i < size)
        {
            list[i] = e;
        }
        else
        {
            cout << "Vi tri khong hop le" << endl;
        }
    }

    void clear()
    {
        size = 0;
    }

    int replaceKey(const E &e1, const E &e2)
    {
        int index = search(e1);
        if (index != -1)
        {
            list[index] = e2;
            return index;
        }
        else
        {
            cout << "Khong tim thay e1" << endl;
            return -1;
        }
    }

    virtual ~Alist()
    {
        delete[] list;
    }

    // Ham bo sung don gian
    int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    bool isFull() const
    {
        return size == maxSize;
    }

    void addElement(const E &element)
    {
        if (size < maxSize)
        {
            list[size] = element;
            ++size;
        }
        else
        {
            cout << "Danh sach da day, khong the them moi." << endl;
        }
    }

    // ham bo sung mo rong
    Alist(const Alist<E> &other)
    {
        maxSize = other.maxSize;
        size = other.size;

        // Cấp phát bộ nhớ mới cho danh sách và sao chép dữ liệu từ danh sách khác
        list = new E[maxSize];
        for (int i = 0; i < size; ++i)
        {
            list[i] = other.list[i];
        }
    }

    Alist<E> &operator=(const Alist<E> &other)
    {
        if (this != &other) // Kiểm tra tránh tự gán vào chính bản thân
        {
            // Giải phóng bộ nhớ hiện tại
            delete[] list;

            // Sao chép dữ liệu từ danh sách khác
            maxSize = other.maxSize;
            size = other.size;
            list = new E[maxSize];
            for (int i = 0; i < size; ++i)
            {
                list[i] = other.list[i];
            }
        }
        return *this; // Trả về tham chiếu tới đối tượng hiện tại để hỗ trợ gán chuỗi
    }
};

int main()
{
    Alist<int> intList(5);

    intList.addElement(10);
    intList.addElement(20);
    intList.addElement(30);
    intList.addElement(40);
    intList.add(2, 15);

    // cout << "Is the list empty? " << (intList.isEmpty() ? "Yes" : "No") << endl;

    // cout << "Is the list full? " << (intList.isFull() ? "Yes" : "No") << endl;

    cout << "Size of the list: " << intList.getSize() << endl;

    cout << "Element at index 1: " << intList.getElement(2) << endl;
    intList.print();

    // int searchResult = intList.search(20);
    // if (searchResult != -1)
    // {
    //     cout << "Element 20 found at index: " << searchResult << endl;
    // }
    // else
    // {
    //     cout << "Element 20 not found in the list." << endl;
    // }

    // cout << "Is element 30 in the list? " << (intList.find(10) ? "Yes" : "No") << endl;

    return 0;
}
