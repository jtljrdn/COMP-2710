/*
Jordan Lee
jtl0071
project4_Lee_jtl0071.cpp

Compile and Run Instructions:
compile `g++ project4_Lee_jtl0071.cpp -o project4_Lee_jtl0071.out`
execute: `./project4_Lee_jtl0071.out`
*/

// #define UNIT_TESTING

#include <iostream>
#include <list> // Doubly-Linked List
#include <cassert>
using namespace std;
#include <limits>



struct UserAnswers
{
    string userAnswer;
    string correctAnswer;
};

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
    list<UserAnswers> ua;
};

class Question // Class for creating `Question` objects
{
private:
    string type;
    string question;
    list<answer> mcqAnswers;
    bool tfAnswer;
    string wrAnswer;
    char correct;
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

    Question()
    {
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

    // Setters

    void setQuestion(string q)
    {
        this->question = q;
    }

    void setType(string t)
    {
        this->type = t;
    }

    void setMcqAnswers(list<answer> answers)
    {
        this->mcqAnswers = answers;
    }

    void setTfAnswer(bool answer)
    {
        this->tfAnswer = answer;
    }

    void setWrAnswer(string answer)
    {
        this->wrAnswer = answer;
    }

    void setCorrect(char c)
    {
        this->correct = c;
    }

    void setValue(double v)
    {
        this->value = v;
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
    cin.ignore(); // To ignore any leftover newline character in the input buffer
    getline(cin, questionName);
    cout << "[At any time, type \033[31mquit() \033[0mto exit]\n\n";

    while (true)
    {
        string tempAnswer;

        cout << "Enter Choice " << key << ": ";
        answer.key = key;
        getline(cin, tempAnswer);
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
        if (cin.fail() || value <= 0)
        {
            cin.clear();                                         // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
            cout << "[Not a point value, please try again!]\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any extra input
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
    cin.ignore(); // To ignore any leftover newline character in the input buffer
    getline(cin, questionName);
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
        if (cin.fail() || value <= 0)
        {
            cin.clear();                                         // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
            cout << "[Not a point value, please try again!]\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any extra input
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
    cin.ignore(); // To ignore any leftover newline character in the input buffer
    getline(cin, questionName);
    cout << "\n";

    while (true)
    {
        string tempAnswer;
        cout << "Type correct answer: ";
        getline(cin, tempAnswer);
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
        if (cin.fail() || value <= 0)
        {
            cin.clear();                                         // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
            cout << "[Not a point value, please try again!]\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any extra input
        break;
    }

    return Question("wr", questionName, correctAnswer, value);
}

void editQuestionName(list<Question> &Questions, int questionNumToEdit);

void editQuestion(list<Question> &Questions)
{
    string type;
    while (true)
    {
        int questionNumToEdit;
        string response;
        cout << "Select a question to edit, or type quit() [1-" << Questions.size() << "]: ";
        cin >> response;
        if (response == "quit()")
        {
            break;
        }
        questionNumToEdit = stoi(response);
        if (questionNumToEdit <= 0 || questionNumToEdit > Questions.size())
        {
            cout << "[That question does not exist!]\n";
            continue;
        }
        else
        {
            auto itr = Questions.begin();
            for (size_t i = 1; i <= Questions.size(); i++, itr++)
            {
                if (i == questionNumToEdit)
                {
                    cout << "===============================\n";
                    cout << "=== QUESTION " << questionNumToEdit << " SAVED VALUES ===\n";
                    cout << "===============================\n";
                    cout << "   1. Type: " << itr->getType() << "\n";
                    cout << "   2. Question: " << itr->getQuestion() << "\n";
                    if (itr->getType() == "mcq")
                    {
                        cout << "   3. Answer choices: " << itr->getType() << "\n";
                        for (auto choice : itr->getMcqAnswers())
                        {

                            cout << "       " << choice.key << ". " << choice.answer << "\n";
                        }
                    }
                    else if (itr->getType() == "tf")
                    {
                        if (itr->getTfAnswer() == true)
                        {
                            cout << "   3. Answer: True\n";
                        }
                        else if (itr->getTfAnswer() == false)
                        {
                            cout << "   3. Answer: False\n";
                        }
                    }
                    else if (itr->getType() == "wr")
                    {
                        cout << "   3. Answer: " << itr->getWrAnswer() << "\n";
                    }

                    cout << "   4. Value: " << itr->getValue() << "\n";

                    cout << "===============================\n";
                    string choice;
                    cout << "Type a number to edit, or type quit(): ";
                    cin >> choice;
                    cin.ignore();

                    if (choice == "1") // Edit Type
                    {
                        cout << "[Not currently supported.]\n";
                        continue;
                    }
                    else if (choice == "2") // Edit Question
                    {
                        editQuestionName(Questions, questionNumToEdit);
                    }
                    else if (choice == "3") // Edit Answer(s)
                    {
                        if (itr->getType() == "mcq")
                        {
                            cout << "[At any time, type \033[31mquit() \033[0mto exit]\n\n";
                            char key = 65; // ascii A
                            list<answer> answers;
                            answer answer;
                            while (true)
                            {
                                string tempAnswer;

                                cout << "Enter Choice " << key << ": ";
                                answer.key = key;
                                getline(cin, tempAnswer);
                                cout << tempAnswer << " | quit()\n";
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
                            itr->setMcqAnswers(answers);
                            cout << "[Successfully changed answers!]\n";
                        }
                        else if (itr->getType() == "tf")
                        {
                            while (true)
                            {
                                string tempAnswer;
                                cout << "Select correct answer [(t)rue/(f)alse]: ";
                                cin >> tempAnswer;
                                if (tempAnswer == "true" || tempAnswer == "t")
                                {
                                    itr->setTfAnswer(true);
                                    break;
                                }
                                else if (tempAnswer == "false" || tempAnswer == "f")
                                {
                                    itr->setTfAnswer(false);
                                    break;
                                }
                                else
                                {
                                    cout << "[Answer not recognized, please try again!]\n";
                                    continue;
                                }
                            }
                            cout << "[Successfully changed answer!]\n";
                        }
                        else if (itr->getType() == "wr")
                        {
                            while (true)
                            {
                                string tempAnswer;
                                cout << "Type correct answer: ";
                                getline(cin, tempAnswer);
                                if (tempAnswer == "")
                                {
                                    cout << "[Answer cannot be empty]\n";
                                    continue;
                                }
                                else
                                {
                                    itr->setWrAnswer(tempAnswer);
                                    break;
                                }
                            }
                            cout << "[Successfully changed answer!]\n";
                        }
                    }
                    else if (choice == "4")
                    {
                        int newValue;
                        while (true)
                        {
                            cout << "Enter point value: ";
                            cin >> newValue;
                            if (cin.fail() || newValue <= 0)
                            {
                                cin.clear();                                         // clear the error state
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore invalid input
                                cout << "[Not a point value, please try again!]\n";
                                continue;
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any extra input
                            break;
                        }
                        itr->setValue(newValue);
                        cout << "[Successfully changed value!]\n";
                    }
                }
            }
            break;
        }
    }
}

void editQuestionName(list<Question> &Questions, int questionNumToEdit)
{
    string newQuestionName;
    cout << "Enter new question: ";
    getline(cin, newQuestionName);
    auto itr = Questions.begin();
    for (size_t i = 1; i <= Questions.size(); i++, itr++)
    {
        if (i == questionNumToEdit)
        {
            itr->setQuestion(newQuestionName);
            cout << "[Successfully changed question!]\n";
            break;
        }
    }
}

void deleteQuestion(list<Question> &Questions)
{
    while (true)
    {
        int questionNumToEdit;
        string deleteResponse;
        cout << "Select a question to delete, or type quit() [1-" << Questions.size() << "]: ";
        cin >> deleteResponse;
        if (deleteResponse == "quit()")
        {
            break;
        }
        questionNumToEdit = stoi(deleteResponse);
        if (questionNumToEdit <= 0 || questionNumToEdit > Questions.size())
        {
            cout << "[That question does not exist!]\n";
            continue;
        }
        else
        {
            auto itr = Questions.begin();
            advance(itr, questionNumToEdit - 1);
            Questions.erase(itr);
            cout << "[Successfully deleted question!]\n";
            break;
        }
    }
}

Result startTest(list<Question> &Questions)
{
    int count = 0;
    double score = 0;
    int correct = 0;
    Result result;
    list<UserAnswers> answers;

    if (Questions.empty())
    {
        cout << "[There must be atleast 1 question to be quizzed on.]\n";
        return result;
    }

    while (true)
    {

        string response;
        cout << "Do you want to?\n";
        cout << "   1. Go to next question.\n";
        cout << "   2. Jump to question.\n";
        cout << "   3. Submit.\n";
        cout << "Select an action: ";
        cin >> response;
        cout << "\n";

        if (response == "1") // Go to next question
        {
            if (count < Questions.size())
            {
                count++;
                auto itr = Questions.begin();
                advance(itr, count - 1);
                cout << "Question " << count << ": " << itr->getQuestion() << endl;
                if (itr->getType() == "mcq")
                {
                    for (auto choice : itr->getMcqAnswers())
                    {
                        cout << "   " << choice.key << ". " << choice.answer << endl;
                    }
                    char userAnswer;
                    cout << "\nSelect correct answer: ";
                    cin >> userAnswer;
                    cout << "\n";
                    UserAnswers ua;
                    ua.userAnswer = userAnswer;
                    ua.correctAnswer = itr->getCorrect();
                    answers.push_back(ua);
                }
                else if (itr->getType() == "tf")
                {
                    string tempAnswer;
                    bool answer;
                    cout << "Your answer [(t)rue/(f)alse]: ";
                    cin >> tempAnswer;
                    cout << "\n";
                    if (tempAnswer == "true" || tempAnswer == "t")
                    {
                        answer = true;
                    }
                    else if (tempAnswer == "false" || tempAnswer == "f")
                    {
                        answer = false;
                    }
                    UserAnswers ua;
                    ua.userAnswer = answer ? "true" : "false";
                    ua.correctAnswer = itr->getTfAnswer() ? "true" : "false";
                    answers.push_back(ua);
                }
                else if (itr->getType() == "wr")
                {
                    string answer;
                    cout << "Your answer: ";
                    cin.ignore();
                    getline(cin, answer);
                    cout << "\n";
                    UserAnswers ua;
                    ua.userAnswer = answer;
                    ua.correctAnswer = itr->getWrAnswer();
                    answers.push_back(ua);
                }
            }
            else
            {
                cout << "[No more questions available.]\n";
            }
        }
        else if (response == "2") // Jump to question
        {
            int jumpTo;
            cout << "Enter question number to jump to [1-" << Questions.size() << "]: ";
            cin >> jumpTo;
            if (jumpTo > 0 && jumpTo <= Questions.size())
            {
                count = jumpTo - 1;
            }
            else
            {
                cout << "[Invalid question number.]\n";
            }
        }
        else if (response == "3") // Submit
        {
            for (auto &ua : answers)
            {
                if (ua.userAnswer == ua.correctAnswer)
                {
                    correct++;
                    auto itr = Questions.begin();
                    advance(itr, &ua - &answers.front());
                    score += itr->getValue();
                }
            }
            break;
        }
        else
        {
            cout << "[Invalid response. Please try again.]\n";
        }
    }

    cout << "Assessment Complete.\n\n";
    result.correct = correct;
    result.score = score;
    result.ua = answers;
    return result;
}


#ifdef UNIT_TESTING

/* TESTING */ 

void test1()
{
    list<Question> questions;
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message.\n";
    Result result = startTest(questions);
    assert(result.ua.empty());
    cout << "Case 1 Passed\n";
}

void test2()
{
    list<Question> questions;
    string userAnswer = "85";
    string correctAnswer = "38";
    Question testQuestion = Question("wr", "How long was the shortest war on record?", correctAnswer, 100);
    questions.push_back(testQuestion);

    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.\n";
    cout << "How long was the shortest war on record?\n";
    cout << "Answer: 85\n";
    assert(userAnswer != testQuestion.getWrAnswer());
    cout << "Your answer is wrong. The correct answer is 38\n";
    cout << "Total points: 0\n\n";
    cout << "Case 2.1 Passed\n\n";

    userAnswer = "38";
    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.\n";
    cout << "How long was the shortest war on record?\n";
    cout << "Answer: 38\n";
    assert(userAnswer == testQuestion.getWrAnswer());
    cout << "Your answer is correct! You receive " << testQuestion.getValue() << " points!\n";
    cout << "Total points: " << testQuestion.getValue() << "\n\n";
    cout << "Case 2.2 Passed\n\n";
}

void test3()
{
    list<Question> questions;
    string correctAnswer = "C++";
    list<answer> mcqAnswers;
    answer A = {'A', "Java"};
    answer B = {'B', "Python"};
    answer C = {'C', "C++"};
    
    mcqAnswers.push_back(A);
    mcqAnswers.push_back(B);
    mcqAnswers.push_back(C);
    Question testQuestion = Question("mcq", "Which programming language is this?", mcqAnswers, 'C', 50);
    questions.push_back(testQuestion);

    cout << "Unit Test Case 3.1: Ask 1 MCQ question in the linked list. The tester enters an incorrect answer.\n";
    cout << "Which programming language is this?\n";
    cout << "Answer: B\n";
    assert('B' != testQuestion.getCorrect());
    cout << "Your answer is wrong. The correct answer is C\n";
    cout << "Total points: 0\n\n";
    cout << "Case 3.1 Passed\n\n";

    cout << "Unit Test Case 3.2: Ask 1 MCQ question in the linked list. The tester enters a correct answer.\n";
    cout << "Which programming language is this?\n";
    cout << "Answer: C\n";
    assert('C' == testQuestion.getCorrect());
    cout << "Your answer is correct! You receive " << testQuestion.getValue() << " points!\n";
    cout << "Total points: " << testQuestion.getValue() << "\n\n";
    cout << "Case 3.2 Passed\n\n";
}

void test4()
{
    list<Question> questions;
    bool correctAnswer = true;
    Question testQuestion = Question("tf", "Is the sky blue?", correctAnswer, 20);
    questions.push_back(testQuestion);

    cout << "Unit Test Case 4.1: Ask 1 TF question in the linked list. The tester enters an incorrect answer.\n";
    cout << "Is the sky blue?\n";
    cout << "Answer: false\n";
    assert(false != testQuestion.getTfAnswer());
    cout << "Your answer is wrong. The correct answer is true\n";
    cout << "Total points: 0\n\n";
    cout << "Case 4.1 Passed\n\n";

    cout << "Unit Test Case 4.2: Ask 1 TF question in the linked list. The tester enters a correct answer.\n";
    cout << "Is the sky blue?\n";
    cout << "Answer: true\n";
    assert(true == testQuestion.getTfAnswer());
    cout << "Your answer is correct! You receive " << testQuestion.getValue() << " points!\n";
    cout << "Total points: " << testQuestion.getValue() << "\n\n";
    cout << "Case 4.2 Passed\n\n";
}

void test5()
{
    list<Question> questions;
    string correctAnswer = "42";
    Question testQuestion = Question("wr", "What is the answer to life, the universe, and everything?", correctAnswer, 100);
    questions.push_back(testQuestion);

    cout << "Unit Test Case 5.1: Ask 1 WR question in the linked list. The tester enters an incorrect answer.\n";
    cout << "What is the answer to life, the universe, and everything?\n";
    cout << "Answer: 24\n";
    assert("24" != testQuestion.getWrAnswer());
    cout << "Your answer is wrong. The correct answer is 42\n";
    cout << "Total points: 0\n\n";
    cout << "Case 5.1 Passed\n\n";

    cout << "Unit Test Case 5.2: Ask 1 WR question in the linked list. The tester enters a correct answer.\n";
    cout << "What is the answer to life, the universe, and everything?\n";
    cout << "Answer: 42\n";
    assert("42" == testQuestion.getWrAnswer());
    cout << "Your answer is correct! You receive " << testQuestion.getValue() << " points!\n";
    cout << "Total points: " << testQuestion.getValue() << "\n\n";
    cout << "Case 5.2 Passed\n\n";
}

int main()
{
    cout << "*** This is the debugging version ***\n\n";

    test1();
    test2();
    test3();
    test4();
    test5();

    cout << "*** End of the Debugging Version ***\n";
}
/*-------------------*/

#else

int main()
{
    int questionCount = 1;
    list<Question> Questions;
    string response;

    cout << "*** Welcome to Jordan's Testing Service ***\n";

    while (true)
    {
        response = "";

        cout << "\nDo you want to?\n";
        cout << "   1. Create new question.\n";
        cout << "   2. Edit question.\n";
        cout << "   3. Delete question.\n";
        cout << "   4. Finish.\n";

        cout << "Select an action: ";
        cin >> response;
        cout << "\n";
        if (response == "1") // New Question
        {
            Question question = newQuestion(questionCount);
            Questions.push_back(question);
            questionCount++;
            continue;
        }
        else if (response == "2") // Edit Question
        {
            if (Questions.empty())
            {
                cout << "[There must be atleast 1 question to edit.]\n";
                continue;
            }
            editQuestion(Questions);
            continue;
        }
        else if (response == "3") // Delete Question
        {
            if (Questions.empty())
            {
                cout << "[There must be atleast 1 question to edit.]\n";
                continue;
            }
            deleteQuestion(Questions);
            continue;
        }
        else if (response == "4")
        {
            break;
        }
        else
        {
            cout << "[Invalid response. Please try again]\n";
        }
    }

    cout << "=== SESSION LOG ===\n";
    cout << "Total Quesions: " << Questions.size() << endl;
    cout << "Total point values: " << addPoints(Questions) << endl;

    while (true)
    {
        response = "";
        cout << "\nBegin Assessment? [y/n]: ";
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
    int count = 1;

    if (Questions.empty())
    {
        cout << "\n*** Thank you for using the testing service. Goodbye! ***\n";
        return 0;
    }

    cout << "=== SESSION LOG ===\n";
    cout << "Correct answers: " << finalResult.correct << "/" << Questions.size() << endl;
    for (auto response : finalResult.ua)
    {
        cout << "   Question " << count << ": " << response.correctAnswer << "\n";
        cout << "   Your answer: " << response.userAnswer << "\n\n";
        count++;
    }
    cout << "Final score: " << finalResult.score << "/" << addPoints(Questions) << endl;
    cout << "\n*** Thank you for using the testing service. Goodbye! ***\n";
}
#endif
