#include<iostream>
#include<string>
#include<cstring>
using namespace std;

struct Card 
{
    string type;   
    string number; 
    Card* next;    
};

class CardStack 
{
private:
    Card* top;
    int getNumberValue(const string& number) const 
    {
        if (number == "A") return 1;
        if (number == "2") return 2;
        if (number == "3") return 3;
        if (number == "4") return 4;
        if (number == "5") return 5;
        if (number == "6") return 6;
        if (number == "7") return 7;
        if (number == "8") return 8;
        if (number == "9") return 9;
        if (number == "10") return 10;
        if (number == "J") return 11;
        if (number == "Q") return 12;
        if (number == "K") return 13;
        return -1;  // 默认值
    }

public:
    CardStack() : top(nullptr) {}

    ~CardStack() 
    {
        while (top != nullptr) 
        {
            Pop();
        }
    }

    void Append(const string& type, const string& number) 
    {
        Card* new_card = new Card{type, number, nullptr};  // 新建一张牌，next 指向 nullptr 表示它是最后一张

        if (top == nullptr) 
        // 牌堆为空，直接将新牌作为顶部牌
            top = new_card;
        else 
        {
            Card* current = top;
            while (current->next != nullptr)   // 遍历到链表的最后一张牌
                current = current->next; 
            current->next = new_card;  // 将新牌加入到牌堆底部
        }
    }

    void Pop() 
    {
        if (top == nullptr) 
        {
            cout << "NULL" << endl;
            return;
        }
        Card* temp = top;
        cout<<temp->type<<" "<<temp->number<<endl;
        top = top->next;  
        delete temp;
    }

    void Revert() 
    {
        Card* prev = nullptr;//定义当前节点的前一个节点
        Card* current = top;
        Card* next = nullptr;
        while (current != nullptr) 
        {
            next = current->next; 
            current->next = prev; 
            prev = current;       
            current = next;       
        }
        top = prev;  
    }
    
	void Extract(const string& type_) 
	{
        if (top == nullptr) 
        {
            return;
        }

        Card* current = top;
        Card* prev = nullptr;
        Card* extractedHead = nullptr; // 提取出的牌的头指针
        Card* extractedTail = nullptr; // 提取出的牌的尾指针

        // 遍历整个链表，提取指定花色的牌
        while (current != nullptr) 
        {
            if (current->type == type_) 
            {
                // 提取当前牌
                Card* extractedCard = current;
                if (prev != nullptr) 
                {
                    prev->next = current->next;
                } 
                else 
                {
                    // 当前牌是顶部牌
                    top = current->next;
                }
                current = current->next;
                extractedCard->next = nullptr;

                if (extractedHead == nullptr) 
                {
                    extractedHead = extractedCard;
                    extractedTail = extractedCard;
                }
                else 
                {
                    extractedTail->next = extractedCard;
                    extractedTail = extractedCard;
                }
            } 
            else 
            {
                prev = current;
                current = current->next;
            }
        }

        if (extractedHead == nullptr) 
        {
            return;
        }

        Card* sorted = nullptr;
        current = extractedHead;
        while (current != nullptr) 
        {
            Card* nextCard = current->next;
            if (sorted == nullptr || getNumberValue(current->number) < getNumberValue(sorted->number)) 
            {
                current->next = sorted;
                sorted = current;
            } 
            else 
            {
                Card* temp = sorted;
                while (temp->next != nullptr && getNumberValue(temp->next->number) <= getNumberValue(current->number)) 
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = nextCard;
        }

        extractedTail = sorted;
        if (extractedTail != nullptr) 
        {
            while (extractedTail->next != nullptr) 
            {
                extractedTail = extractedTail->next;
            }
            extractedTail->next = top;
            top = sorted;
        }

    }

    Card* Top() const 
    {
        return top;
    }
};

int main()
{
	int n;
	cin>>n;
	CardStack stack;
	while(n--)
	{
		string op;
		cin>>op;
        const char*ch=op.c_str();
		if(strcmp(ch,"Append")==0)
		{
			string s,s1;
			cin>>s>>s1;
			stack.Append(s,s1);
		}
		else if(strcmp(ch,"Pop")==0)
		{
			stack.Pop();
		}
		else if(strcmp(ch,"Extract")==0)
		{
			string s;
			cin>>s;
			stack.Extract(s);
		}
		else if(strcmp(ch,"Revert")==0)
		{
			stack.Revert();
		}
		else
			;
	}
	return 0;
}