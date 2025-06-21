#include <iostream>
#include <vector>
#include <type_traits>
#include <string>

//Класс узла
template <typename T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

//башка
template <typename T>
class ListHead {
public:
    Node<T>* first;
    size_t size;

    ListHead() : first(nullptr), size(0) {}
};

//конец списка
template <typename T>
class ListTail {
public:
    Node<T>* last;

    ListTail() : last(nullptr) {}
};

//класс для двусвязного списка
template <typename T>
class DoublyLinkedList {
private:
    ListHead<T>* head;
    ListTail<T>* tail;

    T getDefaultValue() {
        if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
            return 0;
        } else if constexpr (std::is_same_v<T, bool>) {
            return true;
        } else if constexpr (std::is_same_v<T, std::string>){
            return "";
        }
        else {
            return T();
        }
    }

public:
    DoublyLinkedList() {
        head = new ListHead<T>();
        tail = new ListTail<T>();
    }

    //копирка
    DoublyLinkedList(const DoublyLinkedList& other) : DoublyLinkedList() {
        Node<T>* current = other.head->first;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }

    //конструктор из вектора
    template <typename Container>
    DoublyLinkedList(const Container& container) : DoublyLinkedList() {
        for (const auto& item : container) {
            push(item);
        }
    }

    //НЕ ТЕРЯЙСЯываывыбваьюывпьб
    ~DoublyLinkedList() {
        clear();
        delete head;
        delete tail;
    }

    void clear() {
        Node<T>* current = head->first;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head->first = nullptr;
        tail->last = nullptr;
        head->size = 0;
    }

    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head->first == nullptr) {
            head->first = newNode;
            tail->last = newNode;
        } else {
            newNode->prev = tail->last;
            tail->last->next = newNode;
            tail->last = newNode;
        }
        head->size++;
    }

    T pop() {
        if (head->first == nullptr) {
            return getDefaultValue();
        }

        Node<T>* lastNode = tail->last;
        T value = lastNode->data;

        if (lastNode->prev != nullptr) {
            lastNode->prev->next = nullptr;
            tail->last = lastNode->prev;
        } else {
            head->first = nullptr;
            tail->last = nullptr;
        }
        delete lastNode;
        head->size--;
        return value;
    }

   
    T& operator[](size_t index) {
        if (index >= head->size) {
            throw std::out_of_range("Index out of range");
        }
                                    //индексы в связных списках для интеллектуалов
        Node<T>* current = head->first;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    size_t size() const {
        return head->size;
    }

    bool empty() const {
        return head->size == 0;
    }

    //примерно отсюда можно считать начало отдела "всё для людей"
    void printList() {

        if(!empty())
        {
            //std::cout << "Head -> ";
            Node<T>* nodePtr = head->first;

            while (nodePtr->next != nullptr)
            {
                std::cout << nodePtr->data;
                nodePtr = nodePtr->next;
                if(nodePtr->next != nullptr)
                    std::cout << " -> ";
            }
            //std::cout <<  nodePtr->data << " -> Tail" << std::endl; 
            std::cout << " -> " << nodePtr->data << std::endl;           
        }
        else
            std::cout << "List is empty" << std::endl;
    }
};


int main() {
    //вот теперь точно всё для людей, запускаем и наслаждаемся 
    DoublyLinkedList<int> intList;
    DoublyLinkedList<double> doubleList;
    DoublyLinkedList<char> charList;
    DoublyLinkedList<std::string> strList;

std::cout << "                                          П Р И В Е Т     К У Р А Г А  :)" << std::endl << std::endl;
    std::cout << "Проверка инициализации контейнера и его вывода\n----------------------------------------------" << std::endl;
    strList.push("Freddy");
    strList.push("Fazber");
    strList.push("Pizza");

    for(int i = 1; i <= 10; i++)
        intList.push(i);

    doubleList.push(0);
    doubleList.push(100.5);
    doubleList.push(-1.5);

    std::cout << " Int list size: " << intList.size() << std::endl;
    intList.printList();
    std::cout << " Double list size: " << doubleList.size() << std::endl;
    doubleList.printList();
    std::cout << " Char list size: " << charList.size() << std::endl;
    charList.printList();
    std::cout << " String list size: " << strList.size() << std::endl;
    strList.printList();


    std::cout << "\nТестирование конструктора копирования" << std::endl;
    std::cout << "-------------------------------------"<< std::endl;
    DoublyLinkedList<int> copiedIntList(intList);
    std::cout << "Copied list size: " << copiedIntList.size() << std::endl;
    copiedIntList.printList();


    std::cout << "\nТестирование конструктора из vector" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::vector<double> vec = {-100, 5, 0};
    std::cout << "Vector: {-100, 5, 0}" << std::endl;
    DoublyLinkedList<int> NewList(vec);
    std::cout << "New List size: " << doubleList.size() << std::endl;
    NewList.printList();


    std::cout << "\nТестирование взятия значения по индексу" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "NewList[0] = " << NewList[0] << std::endl;
    std::cout << "NewList[1] = " << NewList[1] << std::endl;
    NewList.push(NewList[0]+NewList[1]);
    std::cout << "NewList[3] = NewList[0] + NewList[1] = " << NewList[0] << " + " << NewList[1] << " = " << NewList[3] << std::endl;


    std::cout << "\nТестирование функции pop" <<std::endl;
    std::cout << "------------------------" << std::endl;
    NewList.printList();
    std::cout << "NewList_last = " << NewList.pop() << std::endl;
    NewList.printList();


    std::cout << "\nТестирование очистки списка" <<std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "NewList: ";
    NewList.printList();
    std::cout << "NewList after clear: ";
    NewList.clear();
    NewList.printList();

    std::cout << "                                       П О К А     К У Р А Г А  :(" << std::endl << std::endl;

    return 0;
}