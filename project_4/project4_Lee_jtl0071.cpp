/*
Jordan Lee
jtl0071
project4_Lee_jtl0071.cpp

Compile and Run Instructions:
compile `g++ project4_Lee_jtl0071.cpp -o project4_Lee_jtl0071.out`
execute: `./project4_Lee_jtl0071.out`
*/

#include <iostream>
#include <list> // Doubly-Linked List
using namespace std;

/* Structs for storing question data */
struct answer // Struct for storing mcq answers. Ex key: `A`, answer: `C++ is an Object Oriented Programming Language`
{
    char key;
    string answer;
};

// struct mcq // Multiple choice question. `question` string, `answers` list of `answer`, `points` double
// {
//     string question;
//     list<answer> answers;
//     double points;
// };

// struct tf // True/False Question
// {
//     string question;
//     string answer;
//     double points;
// };

// struct wr // Written Response Question
// {
//     string question;
//     string answer;
//     double points;
// };

class Question
{
private:
    string question;
    int value;

public:
    Question(string question, int value)
    {
        this->question = question;
        this->value = value;
    }
    Question()
    {
        this->value = 0;
    }
};
class Mcq : public Question
{
public:
    string question;
    list<answer> answers;
    char correct;
    int value;
    Mcq(string question, list<answer> answers, char correct, int value)
    {
        this->question = question;
        this->answers = answers;
        this->correct = correct;
        this->value = value;
    }
};
class Tf : public Question
{
public:
    string question;
    bool answer;
    int value;
    Tf(string question, bool answer, int value)
    {
        this->question = question;
        this->answer = answer;
        this->value = value;
    }
};
class Wr : public Question
{
public:
    string question;
    string answer;
    int value;
    Wr(string question, string answer, int value)
    {
        this->question = question;
        this->answer = answer;
        this->value = value;
    }
};
list<Question> Questions;
/*-----------------*/

void newQuestion(int num)
{
    string type;
    cout << "=== QUESTION " << num << " ===\n";
    cout << "Type of question [mcq/tf/wr]: ";
    cin >> type;
    cout << "\n";
    if (type == "mcq")
    {
        string questionName;
        char key = 65; // ascii A
        list<answer> answers;
        answer answer;

        cout << "Enter a question: ";
        cin >> questionName;
        cout << "\n[At any time, type \033[31mquit() \033[0mto exit]\n\n";

        while (true)
        {
            string tempAnswer;

            cout << "Enter Choice " << key << ": ";
            answer.key = key;
            cin >> tempAnswer;
            if (tempAnswer == "quit()")
            {
                if (key > 65)
                {
                    break;
                }
                else
                {
                    cout << "[Atleast one answer is required.]\n\n";
                    continue;
                }
            }
            answer.answer = tempAnswer;
            answers.push_back(answer);
            cout << "Added answer to answers list\n";
            key++;
            if (key - 65 >= 26)
            { // If A-Z is occupied, break loop.
                break;
            }
        }

        while (true){
            
        }
    }
}

int main()
{
    int questionCount = 1;

    cout << "*** Welcome to Jordan's Testing Service ***\n\n";

    while (true)
    {
        string response;
        newQuestion(questionCount);
        cout << "Continue? [y/n]: ";
        cin >> response;
        if (response == "n")
        {
            break;
        }
        else if (response == "y")
        {
        }
        else
        {
            
        }
        questionCount++;
    }
}
