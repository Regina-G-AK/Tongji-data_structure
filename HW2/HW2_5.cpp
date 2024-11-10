#include <iostream>
using namespace std;

struct Queue {
    int* data;
    int* max_data; // 辅助队列用于存储最大值
    int front, rear, max_front, max_rear, capacity, size;

    void init(int n) {
        capacity = n;
        data = new int[capacity];
        max_data = new int[capacity];
        front = rear = max_front = max_rear = size = 0;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }

    void enqueue(int v) {
        if (isFull()) {
            cout << "Queue is Full" << endl;
            return;
        }

        // 主队列入队
        data[rear] = v;
        rear = (rear + 1) % capacity;
        size++;

        // 辅助队列维护最大值
        while (max_rear != max_front && max_data[(max_rear - 1 + capacity) % capacity] < v) {
            max_rear = (max_rear - 1 + capacity) % capacity; // 移除比新值小的元素
        }
        max_data[max_rear] = v;
        max_rear = (max_rear + 1) % capacity;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }

        int value = data[front];
        front = (front + 1) % capacity;
        size--;

        // 如果出队的值正好是当前最大值，也需要从辅助队列出队
        if (value == max_data[max_front]) {
            max_front = (max_front + 1) % capacity;
        }
        cout << value << endl;
    }

    void getMax() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return;
        }

        cout << max_data[max_front] << endl;
    }

    void printQueue() {
        int count = 0;
        for (int i = front; count < size; i = (i + 1) % capacity) {
            cout << data[i] << " ";
            count++;
        }
        cout << endl;
    }

    void free() {
        delete[] data;
        delete[] max_data;
    }
};

int main() {
    int n;
    cin >> n; // 输入队列容量
    Queue q;
    q.init(n);

    string command;
    while (cin >> command) {
        if (command == "enqueue") {
            int v;
            cin >> v;
            q.enqueue(v);
        } else if (command == "dequeue") {
            q.dequeue();
        } else if (command == "max") {
            q.getMax();
        } else if (command == "quit") {
            q.printQueue();
            break;
        }
    }

    q.free();
    return 0;
}
