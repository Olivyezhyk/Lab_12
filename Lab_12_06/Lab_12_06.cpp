#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>

using namespace std;

using WordQueue = queue<string>;

void createQueueFromLine(const string& line, WordQueue& q) {
    istringstream iss(line);
    string word;
    while (iss >> word) {
        q.push(word);
    }
}

void printQueue(const WordQueue& q, const string& label) {
    cout << label << ": ";
    WordQueue temp = q;
    while (!temp.empty()) {
        cout << temp.front() << " | ";
        temp.pop();
    }
    cout << endl;
}

void concatenateQueues(const WordQueue& q1, const WordQueue& q2, WordQueue& result) {
    WordQueue temp = q1;
    while (!temp.empty()) {
        result.push(temp.front());
        temp.pop();
    }
    temp = q2;
    while (!temp.empty()) {
        result.push(temp.front());
        temp.pop();
    }
}

bool compareQueues(const WordQueue& q1, const WordQueue& q2) {
    WordQueue temp1 = q1;
    WordQueue temp2 = q2;

    while (!temp1.empty() && !temp2.empty()) {
        if (temp1.front() != temp2.front())
            return false;
        temp1.pop();
        temp2.pop();
    }
    return temp1.empty() && temp2.empty();
}

int main() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open the file!" << endl;
        return 1;
    }

    string line1, line2;
    getline(file, line1);
    getline(file, line2);

    WordQueue queue1, queue2, queue3;

    createQueueFromLine(line1, queue1);
    createQueueFromLine(line2, queue2);

    printQueue(queue1, "Queue 1");
    printQueue(queue2, "Queue 2");

    concatenateQueues(queue1, queue2, queue3);
    printQueue(queue3, "Concatenated Queue");

    if (compareQueues(queue1, queue2))
        cout << "Queues are equal" << endl;
    else
        cout << "Queues are different" << endl;

    return 0;
}
