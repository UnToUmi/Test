#include <iostream>
using namespace std;

// Định nghĩa cấu trúc Node
template <class E>
struct Node
{
    E element;
    Node<E> *next;
    // Hàm tạo mặc định cho Node
    Node(const E &value) : element(value), next(nullptr) {}
};

// Định nghĩa lớp SList (Single Linked List)
template <class E>
class SList
{

protected:
    Node<E> *head; // Con trỏ đến đầu danh sách
    int size;

public:
    // --------------Hàm cơ bản, tiện ích---------------------
    // Hàm tạo mặc định cho danh sách //
    SList() : head(nullptr), size(0) {}

    // Hàm in ra mọi phần tử trong danh sách
    void print() const
    {
        Node<E> *current = head;
        while (current != nullptr)
        {
            cout << current->element << " ";
            current = current->next;
        }
        cout << endl;
    }

    Node<E> *const &getLink(int i) const
    {
        if (i < 0 || i > size)
            throw "Chi so sai\n";
        if (!i)
            return head; // vì head trỏ tới vị trí 0
        Node<E> *v = head;
        for (int j = 0; j < i - 1; j++) // chạy đến khi j = i-1 thì v cũng đến nút i-1
            v = v->next;
        return v->next; // trả về v->next là biến trỏ tới vị trí i
    };

    Node<E> *const &searchLink(const E &e) const
    {
        if (head->element == e)
            return head;
        for (Node<E> *v = head; v; v = v->next)
        {
            if (v->next->element == e)
                return v->next;
        }
        throw "Khong tim thay \n";
    }

    string find(const E &key) const
    {
        Node<E> *current = head;
        while (current != nullptr)
        {
            if (current->element == key)
            {
                return "true";
            }
            current = current->next;
        }
        return "false";
    }

    //--------------Hàm cập nhật-------------------------
    // Hàm thêm một phần tử vào đầu danh sách

    void addFirst(const E &e)
    {
        addToHead(e);
    }
    void addToHead(const E &value) // <=> addFirst
    {
        Node<E> *newNode = new Node<E>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }
    void addLinkedList(int i, const E &e)
    {
        if (i < 0 || i > size)
        {
            throw "Vi tri khong hop le";
        }

        Node<E> *newNode = new Node<E>(e);

        if (i == 0)
        {
            // Thêm vào đầu danh sách
            newNode->next = head;
            head = newNode;
        }
        else
        {
            // Thêm vào vị trí i trong danh sách
            Node<E> *prevNode = getLink(i - 1);
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }
        size++;
    };

    void addLast(const E &value)
    {
        Node<E> *newNode = new Node<E>(value);

        if (head == nullptr)
        {
            // Danh sách rỗng, node mới là node đầu tiên
            head = newNode;
        }
        else
        {
            // Danh sách không rỗng, tìm node cuối cùng và liên kết node mới vào cuối danh sách
            Node<E> *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    // Hàm giải phóng bộ nhớ cho toàn bộ danh sách

    void removeFirst()
    {
        if (head != nullptr)
        {
            Node<E> *temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    }

    void createEmptyList()
    {
        clear(); // Xóa mọi phần tử hiện tại nếu có
        head = nullptr;
        size = 0;
    }

    void removeLast()
    {
        if (head == nullptr)
        {
            // Danh sách rỗng, không có phần tử để xoá
            return;
        }

        if (head->next == nullptr)
        {
            // Danh sách chỉ có một phần tử, xoá phần tử đó
            delete head;
            head = nullptr;
            size = 0;
            return;
        }

        // Sử dụng hai con trỏ để điều hướng, một để duyệt qua danh sách và một để theo dõi node trước node cuối cùng
        Node<E> *current = head;
        Node<E> *previous = nullptr;

        while (current->next != nullptr)
        {
            previous = current;
            current = current->next;
        }

        // previous trỏ đến node trước node cuối cùng
        // current trỏ đến node cuối cùng

        delete current;           // Xoá node cuối cùng
        previous->next = nullptr; // Cập nhật con trỏ next của node trước node cuối cùng để trỏ vào nullptr
        size--;
    }

    Node<E> *search(const E &key) const
    {
        Node<E> *current = head;
        while (current != nullptr)
        {
            if (current->element == key)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    void remove(int i)
    {
        if (i < 0 || i >= size)
        {
            throw "Vi tri khong hop le";
        }

        if (i == 0)
        {
            // Xóa nút đầu tiên
            removeFirst();
        }
        else
        {
            // Xóa nút ở vị trí i trong danh sách
            Node<E> *prevNode = getLink(i - 1);
            Node<E> *current = prevNode->next;

            prevNode->next = current->next;

            delete current;
            size--;
        }
    }

    void removeKey(const E &e)
    {
        // Kiểm tra danh sách rỗng
        if (head == nullptr)
        {
            cout << "Danh sach rong. Khong co phan tu de xoa." << endl;
            return;
        }

        // Kiểm tra xem nút cần xóa có phải là nút đầu tiên hay không
        if (head->element == e)
        {
            removeFirst();
            return;
        }

        // Tìm nút chứa dữ liệu e
        Node<E> *prevNode = nullptr;
        Node<E> *current = head;

        while (current != nullptr && current->element != e)
        {
            prevNode = current;
            current = current->next;
        }

        // Kiểm tra xem có tìm thấy nút chứa dữ liệu e hay không
        if (current == nullptr)
        {
            cout << "Khong tim thay phan tu " << e << " trong danh sach." << endl;
            return;
        }

        // Xóa nút chứa dữ liệu e
        prevNode->next = current->next;
        delete current;
        size--;

        cout << "Da xoa phan tu " << e << " khoi danh sach." << endl;
    }

    void replace(int i, const E &e)
    {
        if (i < 0 || i >= size)
        {
            throw "Vi tri khong hop le";
        }

        Node<E> *current = getLink(i);
        current->element = e;
    }

    void replaceKey(const E &e1, const E &e2)
    {
        Node<E> *current = head;

        while (current != nullptr && current->element != e1)
        {
            current = current->next;
        }

        if (current != nullptr)
        {
            current->element = e2;
            cout << "Da thay the gia tri " << e1 << " bang " << e2 << " trong danh sach." << endl;
        }
        else
        {
            cout << "Khong tim thay phan tu " << e1 << " trong danh sach." << endl;
        }
    }

    // Hàm hủy (destructor) để giải phóng bộ nhớ khi đối tượng bị hủy

    void clear()
    {
        while (head != nullptr)
        {
            Node<E> *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
    virtual ~SList()
    {
        clear();
    }

    //  -----------------------Hàm bổ sung đơn giản------------------

    E getElement(int i) const
    {
        if (i < 0 || i >= size)
        {
            throw "Vi tri khong hop le";
        }

        Node<E> *current = head;
        for (int j = 0; j < i; ++j)
        {
            current = current->next;
        }

        return current->element;
    }

    E getFront() const
    {
        if (head != nullptr)
        {
            return head->element;
        }
        else
        {
            cout << "Danh sach rong. Khong co phan tu dau tien." << endl;
            return E();
        }
    }

    E getBack() const
    {
        if (head != nullptr)
        {
            Node<E> *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            return current->element;
        }
        else
        {
            cout << "Danh sach rong. Khong co phan tu cuoi cung." << endl;
            return E();
        }
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }
    int getSize() const
    {
        return size;
    }

    //-----------------Hàm bổ sung mở rộng--------------
    // Hàm tạo sao chép
    SList(const SList<E> &other)
    {
        // Khởi tạo danh sách mới
        head = nullptr;
        size = 0;

        // Sao chép từ danh sách khác vào danh sách mới
        Node<E> *otherCurrent = other.head;
        Node<E> *lastNode = nullptr;

        while (otherCurrent != nullptr)
        {
            Node<E> *newNode = new Node<E>(otherCurrent->element);

            if (lastNode == nullptr)
            {
                // Nếu đây là nút đầu tiên trong danh sách mới
                head = newNode;
            }
            else
            {
                // Nếu danh sách mới đã có ít nhất một nút, liên kết nút mới vào danh sách mới
                lastNode->next = newNode;
            }

            lastNode = newNode;
            otherCurrent = otherCurrent->next;
        }

        // Cập nhật kích thước của danh sách mới
        size = other.size;
    }
    //--------------------------------------------------
    int countNodesRecursive(Node<E> *currentNode) const
    {
        // Base case: Nếu currentNode là nullptr, tức là đến cuối danh sách
        if (currentNode == nullptr)
            return 0;

        // Đệ quy: Đếm node hiện tại và tiếp tục đến node tiếp theo
        return 1 + countNodesRecursive(currentNode->next);
    }

    // Hàm công khai để gọi hàm đệ quy từ bên ngoài
    int countNodes() const
    {
        return countNodesRecursive(head);
    }
    //--------------------------------------------
    Node<E> *reverseRecursive(Node<E> *currentNode, Node<E> *newHead)
    {
        // Base case: Nếu currentNode là nullptr, tức là đến cuối danh sách
        if (currentNode == nullptr)
            return newHead;

        // Lưu lại next để tránh mất mát liên kết
        Node<E> *nextNode = currentNode->next;

        // Thay đổi liên kết để đưa currentNode vào đầu danh sách mới
        currentNode->next = newHead;

        // Gọi đệ quy cho node tiếp theo, currentNode trở thành newHead
        return reverseRecursive(nextNode, currentNode);
    }

    // Hàm công khai để gọi hàm đệ quy từ bên ngoài
    void reverse()
    {
        head = reverseRecursive(head, nullptr);
    }
};

int main()
{
    // Sử dụng lớp SList và in ra mọi phần tử trong danh sách
    SList<int> myList;

    // Thêm các phần tử vào danh sách
    myList.addToHead(10);
    myList.addToHead(20);
    myList.addToHead(30);

    // In ra danh sách
    // cout << "Danh sach truoc khi xoa: ";

    cout << "Kich thuoc danh sach: " << myList.getSize() << endl;
    cout << "Danh sach co rong? " << myList.isEmpty() << endl;

    myList.addFirst(50);

    cout << "Size: " << myList.getSize() << endl;
    myList.print();

    myList.removeFirst();

    myList.print();

    cout << "Size: " << myList.getSize() << endl;

    cout << "Is It empty: " << myList.isEmpty() << endl;

    cout << "Phan tu dau tien: " << myList.getFront() << endl;

    cout << "Gia tri vi tri thu 2: " << myList.getElement(1) << endl;

    cout << "Tim kiem gia tri: " << myList.find(10) << endl;

    cout << "Search: " << myList.search(60) << endl;

    int n = 40;

    Node<int> *resultNode = myList.search(n);

    if (resultNode != nullptr)
        cout << "Gia tri " << n << " co trong danh sach tai dia chi: " << resultNode << endl;
    else
        cout << "Gia tri " << n << " khong co trong danh sach." << endl;

    myList.addLast(100);
    myList.print();
    cout << "Kich thuoc: " << myList.getSize() << endl;

    cout << "Count node: " << myList.countNodes() << endl;

    myList.reverse();

    myList.print();

    // Xóa danh sách
    // myList.clear();

    // In ra danh sách sau khi xoa
    // cout << "Danh sach sau khi xoa: ";
    // myList.print();

    return 0;
}
