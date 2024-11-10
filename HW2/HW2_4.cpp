#include <iostream>
using namespace std;

struct Point 
{
    int x, y;
};

// 动态队列实现
struct Queue 
{
    Point* data;
    int front, rear, capacity;

    void init(int max_size) 
    {
        capacity = max_size;
        data = new Point[capacity];
        front = rear = 0;
    }

    void enqueue(int x, int y) 
    {
        if (rear == capacity)
        {
            capacity *= 2;
            Point* new_data = new Point[capacity];
            for (int i = front; i < rear; i++) 
                new_data[i - front] = data[i];
            rear -= front;
            front = 0;
            delete[] data;
            data = new_data;
        }
        data[rear++] = {x, y};
    }

    Point dequeue() 
    {
        return data[front++];
    }

    bool isEmpty()
    {
        return front == rear;
    }

    void free() 
    {
        delete[] data;
    }
};

// 四个方向：上、下、左、右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int n, m;
int matrix[1000][1000];   
bool visited[1000][1000]; 

bool bfs(int startX, int startY) 
{
    Queue q;
    q.init(1000); 
    q.enqueue(startX, startY);
    visited[startX][startY] = true;

    bool hasInternal = false;
    bool isEdgeOnly = true;

    while (!q.isEmpty()) 
    {
        Point current = q.dequeue();
        int x = current.x;
        int y = current.y;

        // 判断当前点是否在边缘，如果不在边缘，设置 hasInternal = true
        if (x > 0 && x < n - 1 && y > 0 && y < m - 1)
        {
            hasInternal = true;
        }

        for (int i = 0; i < 4; i++) 
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrix[nx][ny] == 1 && !visited[nx][ny]) 
            {
                visited[nx][ny] = true;
                q.enqueue(nx, ny);
            }
        }
    }
    q.free();  

    return hasInternal;
}

int main() 
{
    cin >> n >> m;  

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            cin >> matrix[i][j];
            visited[i][j] = false; 
        }
    }

    int regions = 0; 

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            if (matrix[i][j] == 1 && !visited[i][j]) 
            {
                if (bfs(i, j)) // 如果区域包含内部的 1，则计数
                {
                    regions++; 
                }
            }
        }
    }

    cout << regions << endl;  
    return 0;
}
