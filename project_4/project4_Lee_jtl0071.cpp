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

/* Struct for storing mcq answer data */
struct answer // Struct for storing mcq answers. Ex key: `A`, answer: `C++ is an Object Oriented Programming Language`
{
    char key;
    string answer;
};

struct Result
{
    int correct;
    double score;
};

class Question
{
private:
    string type;
    string question;
    list<answer> mcqAnswers;
    bool tfAnswer;
    string wrAnswer;
    char correct;
    string wrCorrect;
    double value;

public:
    // Constructor for MCQ
    Question(string type, string question, list<answer> answers, char correct, double value)
    {
        if (type != "mcq")
        {
            cerr << "Type for MCQ must be mcq\n";
            return;
        }
        mcqAnswers = answers;
        this->type = type;
        this->question = question;
        this->correct = correct;
        this->value = value;
    }

    // Constructor for TF
    Question(string type, string question, bool answer, double value)
    {
        if (type != "tf")
        {
            cerr << "Type for TF must be tf\n";
            return;
        }
        tfAnswer = answer;
        this->type = type;
        this->question = question;
        this->value = value;
    }

    // Constructor for WR
    Question(string type, string question, string answer, double value)
    {
        if (type != "wr")
        {
            cerr << "Type for WR must be wr\n";
            return;
        }
        wrAnswer = answer;
        this->type = type;
        this->question = question;
        this->value = value;
    }

    // Getters
    string getQuestion() const
    {
        return this->question;
    }

    string getType() const
    {
        return this->type;
    }

    double getValue() const
    {
        return this->value;
    }

    list<answer> getMcqAnswers() const
    {
        return mcqAnswers;
    }

    bool getTfAnswer() const
    {
        return tfAnswer;
    }

    string getWrAnswer() const
    {
        return wrAnswer;
    }

    char getCorrect() const
    {
        return correct;
    }

    string getWrCorrect() const
    {
        return wrCorrect;
    }
};

double addPoints(list<Question> q)
{
    double points = 0;
    for (auto i : q)
    {
        points += i.getValue();
    }
    return points;
}

Question createMcq();

Question createTf();

Question createWr();

Question newQuestion(int num)
{
    string type;

    cout << "=== QUESTION " << num << " ===\n";

    while (true)
    {
        cout << "Type of question [mcq/tf/wr]: ";
        cin >> type;
        cout << "\n";

        if (type == "mcq")
        {
            return createMcq();
        }
        else if (type == "tf")
        {
            return createTf();
        }
        else if (type == "wr")
        {
            return createWr();
        }
        else
        {
            cout << "[Invalid Input, please try again]\n";
            continue;
        }
    }
}

Question createMcq()
{
    char correctAnswer;
    string questionName;
    double value;
    char key = 65; // ascii A
    list<answer> answers;
    answer answer;

    cout << "Enter a question: ";
    cin >> questionName;
    cout << "[At any time, type \033[31mquit() \033[0mto exit]\n\n";

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
        key++;
        if (key - 65 >= 26)
        { // If A-Z is fully occupied, break loop.
            break;
        }
    }

    while (true)
    {
        cout << "\nSelect correct answer: ";
        cin >> correctAnswer;
        if (correctAnswer < 65 || correctAnswer >= 65 + answers.size() || !cin)
        {
            cout << "[Answer not recognized, please try again!]\n";
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Enter point value: ";
        cin >> value;
        if (value <= 0 || !cin)
        {
            cout << "[Not a point value, please try again!]\n";
            continue;
        }
        break;
    }

    return Question("mcq", questionName, answers, correctAnswer, value);
}

Question createTf()
{
    string questionName;
    double value;
    bool correctAnswer;

    cout << "Enter a question: ";
    cin >> questionName;
    cout << "\n";

    while (true)
    {
        string tempAnswer;
        cout << "Select correct answer [(t)rue/(f)alse]: ";
        cin >> tempAnswer;
        if (tempAnswer == "true" || tempAnswer == "t")
        {
            correctAnswer = true;
            break;
        }
        else if (tempAnswer == "false" || tempAnswer == "f")
        {
            correctAnswer = false;
            break;
        }
        else
        {
            cout << "[Answer not recognized, please try again!]\n";
            continue;
        }
    }

    while (true)
    {
        cout << "Enter point value: ";
        cin >> value;
        if (value <= 0 || !cin)
        {
            cout << "[Not a point value, please try again!]\n";
            continue;
        }
        break;
    }

    return Question("tf", questionName, correctAnswer, value);
}

Question createWr()
{
    string questionName;
    double value;
    string correctAnswer;

    cout << "Enter a question: ";
    cin >> questionName;
    cout << "\n";

    while (true)
    {
        string tempAnswer;
        cout << "Type correct answer: ";
        cin >> tempAnswer;
        if (tempAnswer == "")
        {
            cout << "[Answer cannot be empty]\n";
            continue;
        }
        else
        {
            correctAnswer = tempAnswer;
            break;
        }
    }

    while (true)
    {
        cout << "Enter point value: ";
        cin >> value;
        if (value <= 0 || !cin)
        {
            cout << "[Not a point value, please try again!]\n";
            continue;
        }
        break;
    }

    return Question("wr", questionName, correctAnswer, value);
}

Result startTest(list<Question> Questions)
{
    int count = 0;
    double score = 0;
    int correct = 0;
    Result result;

    for (auto question : Questions)
    {
        count++;
        cout << "Question " << count << ": " << question.getQuestion() << endl;
        if (question.getType() == "mcq")
        {
            for (auto choice : question.getMcqAnswers())
            {
                cout << "   " << choice.key << ". " << choice.answer << endl;
            }
            while (true)
            {
                char userAnswer;
                cout << "\nSelect correct answer: ";
                cin >> userAnswer;
                if (userAnswer < 65 || userAnswer >= 65 + question.getMcqAnswers().size() || !cin)
                {
                    cout << "[Answer not recognized, please try again!]\n";
                    continue;
                } else if (userAnswer != question.getCorrect())
                {
                    cout << "[Your answer is incorrect. The correct answer is " << question.getCorrect() << ".]\n\n";
                    break;
                } else {
                    cout << "[You answer is correct!]\n\n";
                    score += question.getValue();
                    correct++;
                    break;
                }
            }
        }
    }
    cout << "Assessment Complete.\n\n";
    result.correct = correct;
    result.score = score;
    return result;
}

int main()
{
    int questionCount = 1;
    list<Question> Questions;
    string response;

    cout << "*** Welcome to Jordan's Testing Service ***\n\n";

    while (true)
    {
        response = "";
        Question question = newQuestion(questionCount);
        Questions.push_back(question);

        cout << "Question Saved. Continue? [y/n]: ";
        cin >> response;
        cout << "\n";
        if (response == "n")
        {
            break;
        }
        else if (response == "y")
        {
            questionCount++;
            continue;
        }
    }

    cout << "=== SESSION LOG ===\n";
    cout << "Total Quesions: " << Questions.size() << endl;
    cout << "Total point values: " << addPoints(Questions) << endl;

    while (true)
    {
        response = "";
        cout << "Begin Assessment? [y/n]: ";
        cin >> response;
        cout << "\n";
        if (response == "n")
        {
            cout << "*** Thank you for using the testing service. Goodbye! ***\n";
            return 0;
        }
        else if (response == "y")
        {
            break;
        }
        else if (!cin)
        {
            cout << "Invalid Input. Please try again.\n";
        }
        else
        {
            cout << "Invalid Input. Please try again.\n";
        }
    }

    Result finalResult = startTest(Questions);

    cout << "=== SESSION LOG ===\n";
    cout << "Correct answers: " << finalResult.correct << "/" << Questions.size() << endl;
    cout << "Final score: " << finalResult.score << "/" << addPoints(Questions) << endl;
    cout << "\n*** Thank you for using the testing service. Goodbye! ***";

    // for (auto i : Questions)
    // {
    //     cout << i.getType() << " | " << i.getQuestion() << " | " << i.getValue() << endl;
    //     if (i.getType() == "mcq")
    //     {
    //         for (auto j : i.getMcqAnswers())
    //         {
    //             cout << j.key << ": " << j.answer << endl;
    //         }
    //     }
    //     if (i.getType() == "tf")
    //     {
    //         cout << i.getTfAnswer() << endl;
    //     }
    //     if (i.getType() == "wr")
    //     {
    //         cout << i.getWrAnswer() << endl;
    //     }
    // }
}
