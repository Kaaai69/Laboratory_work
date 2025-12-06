#include <iostream>
#include <queue>

using std::cout;

void addToQueue(std::queue<std::string>& queue, const std::string& event){
    queue.push(event);
}

void processQueue(std::queue<std::string>& queue){
    cout << queue.front() << " обрабатывается (довольно странно, не понимаю, что именно он обрабатывает)!\n";
    queue.pop();
    
}
int main()
{
    std::string name1 = "Теннис";
    std::string name2 = "Пятничный вечер";
    std::string name3 = "Просто Вася";
    std::queue<std::string> myQueue;
    addToQueue(myQueue, name1);
    addToQueue(myQueue, name2);
    addToQueue(myQueue, name3);
    if (myQueue.empty()){
        cout << "К сожалению, очередь пуста.\n";
    }
    while (!myQueue.empty()){
        processQueue(myQueue);
    }
    return 0;
}