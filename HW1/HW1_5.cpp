#include <iostream>
#include <string>
using namespace std;

struct Student 
{
    string id;
    string name;
};

struct Node 
{
    Student student; 
    Node* next;      
};

struct LinkedList 
{
    Node* head=nullptr; // 头节点
    int size=0;   //链表大小
};

int insert(LinkedList& list, int pos, const string& id, const string& name) 
{
    if (pos < 1 || pos > list.size + 1) 
        return -1;

    Node* newNode = new Node; // 创建新节点
    newNode->student.id = id;
    newNode->student.name = name;
    newNode->next = nullptr;

    if (pos == 1) //插入顶部
    { 
        newNode->next = list.head;
        list.head = newNode;
    } 
    else 
    { 
        Node* current = list.head;
        for (int i = 1; i < pos - 1; ++i) 
            current = current->next; // 找到插入位置的前一个节点
        newNode->next = current->next;
        current->next = newNode;
    }
    list.size++;
    return 0;
}

int remove(LinkedList& list, int pos) 
{
    if (pos < 1 || pos > list.size) 
        return -1;

    Node* toDelete;
    if (pos == 1) // 删除头节点
    { 
        toDelete = list.head;
        list.head = list.head->next;
    } 
    else 
    { 
        Node* current = list.head;
        for (int i = 1; i < pos - 1; ++i) 
            current = current->next; 
        toDelete = current->next;
        current->next = toDelete->next;
    }
    delete toDelete;
    list.size--;
    return 0;
}

int check_name(const LinkedList& list, const string& name) 
{
    Node* current = list.head;
    int pos = 1;
    while (current != nullptr) 
    {
        if (current->student.name == name) 
        {
            cout << pos << " " << current->student.id << " " << current->student.name << endl;
            return pos;
        }
        current = current->next;
        pos++;
    }
    return -1;
}

int check_no(const LinkedList& list, const string& id) 
{
    Node* current = list.head;
    int pos = 1;
    while (current != nullptr) 
    {
        if (current->student.id == id) 
        {
            cout << pos << " " << current->student.id << " " << current->student.name << endl;
            return pos;
        }
        current = current->next;
        pos++;
    }
    return -1;
}

void destroy(LinkedList& list) 
{
    Node* current = list.head;
    while (current != nullptr) 
    {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    list.head = nullptr;
    list.size = 0;
}

// 主程序
int main() 
{
    int n;
    cin >> n;
    LinkedList list;

    for (int i = 0; i < n; ++i) 
    {
        string id, name;
        cin >> id >> name;
        insert(list, i + 1, id, name);
    }

    string command;
    while (cin >> command) 
    {
        if (command == "insert") 
        {
            int pos;
            string id, name;
            cin >> pos >> id >> name;
            cout << insert(list, pos, id, name) << endl;
        } 
        else if (command == "remove") 
        {
            int pos;
            cin >> pos;
            cout << remove(list, pos) << endl;
        } 
        else if (command == "check") 
        {
            string s;
            cin >> s;
            if (s == "name") 
            {
                string name;
                cin >> name;
                if (check_name(list, name) == -1) 
                    cout << -1 << endl;
            }
            else if (s == "no") 
            {
                string id;
                cin >> id;
                if (check_no(list, id) == -1) 
                    cout << -1 << endl;
            }
        } 
        else if (command == "end") 
        {
            cout<<list.size<<endl;
            break;
        }
    }

    destroy(list); 
    return 0;
}