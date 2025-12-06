#include <iostream>
#include <queue>

using std::cout;

void addToQueue(std::queue<std::string>& queue, const std::string& person){
    queue.push(person);
}

void processQueue(std::queue<std::string>& queue){
    cout << queue.front() << " обработан!\n";
    
}
int main()
{
    std::string name1 = "Иван";
    std::string name2 = "Петя";
    std::string name3 = "Вася";
    std::queue<std::string> myQueue;
    addToQueue(myQueue, name1);
    addToQueue(myQueue, name2);
    addToQueue(myQueue, name3);
    if (myQueue.empty()){
        cout << "лошара, очередь пуста.\n";
    }
    while (!myQueue.empty()){
        processQueue(myQueue);
        myQueue.pop();
    }
    return 0;
}