/*
Jordan Lee
jtl0071
project2_Lee_jtl0071_v1.cpp

Compile and Run Instructions:
compile 'g++ project3_Lee_jtl0071.cpp -o project3_Lee_jtl0071.out'
execute: './project3_Lee_jtl0071.out'
*/
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Data
{
    double value;
    int hour;
    int min;
    int sec;
};

/* PRINTING UTIL FUNCTIONS */
void printVector(vector<Data> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i].value << " " << v[i].hour << "." << v[i].min << "." << v[i].sec << endl;
    }
}

void printValuesInLine(vector<Data> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i].value << " ";
    }
    cout << endl;
}
/*-------------------------*/

int tts(Data entry) // Converts `HH:MM:SS` -> a second integer
{
    int time = 0;
    time += entry.sec;
    time += entry.min * 60;
    time += entry.hour * 3600;
    return time;
}

void chronoSort(vector<Data> &data)
{ // Insertion sort
    for (int i = 1; i < data.size(); ++i)
    {
        Data key = data[i];
        int j = i - 1;

        while (j >= 0 && tts(data[j]) > tts(key))
        {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
}

/* MERGE SORT FOR VALUES */
void mergeValues(vector<Data> &data, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<Data> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back into data[left..right]
    while (i < n1 && j < n2)
    {
        if (L[i].value <= R[j].value)
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        data[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        data[k] = R[j];
        j++;
        k++;
    }
}
/**
 * Merge Sort
 *
 * @param data pointer to the reference of a vector, modifies the vector in place.
 * @param left first index
 * @param right end index
 * @returns void
 */
void mergeSortValues(vector<Data> &data, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSortValues(data, left, mid);
    mergeSortValues(data, mid + 1, right);
    mergeValues(data, left, mid, right);
}
/*------------------------*/

/* STATISTICAL FUNCTIONS*/
double median(vector<Data> v)
{
    int middle;
    if (v.size() % 2 == 1)
    {
        middle = (v.size()) / 2;
        return v[middle].value;
    }
    else
    {
        return (v[v.size() / 2 - 1].value + v[v.size() / 2].value) / 2;
    }
}

double findMode(vector<Data> v)
{
    unordered_map<double, int> freqMap;
    for (size_t i = 0; i < v.size(); i++)
    {
        freqMap[v[i].value]++;
    }

    vector<double> modes;
    int mode_freq = 0;
    for (auto j = freqMap.begin(); j != freqMap.end(); j++)
    {
        if (j->second > mode_freq)
        {
            mode_freq = j->second;
            j = freqMap.begin();
            modes.clear();
        }
        if (j->second == mode_freq)
        {
            modes.push_back(j->first);
        }
    }

    double mode = 0.0;
    for (size_t i = 0; i < modes.size(); i++)
    {
        mode += modes[i];
    }
    mode = mode / modes.size();
    return mode;
}
/*------------------------*/

/**
 * Utility function to see if a file is empty. Taken from example on StackOverflow,
 * source: https://arc.net/l/quote/zhkblxnd
 *
 * @param pFile ifstream file to be check
 * @returns `true` if empty, `false` otherwise
 */
bool is_file_empty(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

/**
 * Reads a file and returns whether or not it was successful.
 *
 * @param name exact name of the file
 * @param data int vector where the data of the file can be stored
 * @returns `true` if the file read without errors, `false` if the file could not be read for some reason
 */
bool readFile(string name, vector<Data> *data)
{
    ifstream openFile(name);
    vector<Data> dataFromThisFile; // Used just for the output, is erased at the end of file processing.

    if (!openFile)
    {
        cout << "File not found. Please try again." << endl
             << endl;
        return false;
    }

    if (is_file_empty(openFile))
    {
        cout << "Not an input file. File is empty. Please try again." << endl
             << endl;
        return false;
    }

    // Loop through file, get each line
    string line;
    int count = 0;
    while (getline(openFile, line))
    {
        istringstream iss(line);
        Data temp;
        string valueStr, hour, min, sec;

        if (getline(iss, valueStr, '\t') && getline(iss, hour, '.') && getline(iss, min, '.') && getline(iss, sec))
        {
            try
            {

                size_t pos;
                temp.value = stod(valueStr, &pos);
                temp.hour = stoi(hour);
                temp.min = stoi(min);
                temp.sec = stoi(sec);
                if (pos != valueStr.length())
                {
                    throw std::invalid_argument("Extra characters found");
                }
            }
            catch (const invalid_argument &e)
            {
                cout << "Error: Invalid value format in line: " << line << endl;
                return false;
            }
            if (temp.hour > 24 || temp.min > 60 || temp.sec > 60)
            {
                cout << "Error: Invalid value format in line: " << line << endl;
                return false;
            }

            count++;
            dataFromThisFile.push_back(temp);
        }
        else
        {
            cout << "Error processing file\n";
            return false;
        }
    }

    cout << "The list of " << count << (count > 1 ? " values" : " value") << " in file \033[31m" << name << "\033[0m is:" << endl;
    printVector(dataFromThisFile);
    cout << endl;

    for (auto entry : dataFromThisFile)
    {
        data->push_back(entry);
    }

    // Clean up
    dataFromThisFile.empty();
    openFile.close();
    return true;
}

void writeFile(vector<Data> data, double mean, double medianValue, double mode, vector<Data> chronoData, double medianTime)
{

    string outputFileName;
    cout << "Enter the output filename to save: ";
    cin >> outputFileName;
    cout << "\n";

    ofstream outputFile(outputFileName);
    outputFile << "***Summarized Statistics***\n\n";

    outputFile << "The orderly sorted list of " << data.size() << " values is: \n";
    for (size_t i = 0; i < data.size(); i++)
    {
        outputFile << data[i].value << " ";
    }
    outputFile << "\n\n";

    outputFile << "The mean is: " << mean << "\n";

    outputFile << "The median is: " << medianValue << "\n";

    outputFile << "The mode is: " << mode << "\n\n";

    outputFile << "The chronologically sorted list of " << chronoData.size() << " values is: \n";
    for (size_t i = 0; i < chronoData.size(); i++)
    {
        outputFile << chronoData[i].value << " ";
    }
    outputFile << "\n\n";

    outputFile << "The mean is: " << mean << "\n";

    outputFile << "The median is: " << medianTime << "\n";

    outputFile << "The mode is: " << mode << "";

    outputFile.close();
    cout << "*** File \033[31m" << outputFileName << "\033[0m has been written to disk ***\n";
}

int main()
{
    int numFiles;
    string fileName;
    vector<Data> data; // Use vector to store doubles for dynamic sizing

    // Greet User, ask for # of files, set that to a variable
    cout << "*** Welcome to Jordan's Data Analyzer ***" << endl;
    cout << "Enter the number of files to read: ";
    cin >> numFiles;
    cout << endl
         << endl;

    // For each file, Ask for file name, read data from file and determine if valid.
    int i = 1;
    while (i <= numFiles)
    {
        cout << "Enter the name for file " << i << ": ";
        cin >> fileName;

        if (fileName == "quit")
        { // If input is "quit", quit process.
            cout << "Input cancelled. Proceeding to calculation..." << endl
                 << endl;
            break;
        }

        if (!readFile(fileName, &data))
        { // If file name is bad, retry
            continue;
        }

        i++;
    }

    if (data.empty())
    {
        cout << "*** Goodbye. ***" << endl;
        return 0;
    }

    // Give statistics on data
    cout << "***Summarized Statistics***\n\n";

    // Sorted list of all elements
    // Sort list and print
    mergeSortValues(data, 0, data.size() - 1);
    vector<Data> orderedSort = data;
    cout << "The orderly sorted list of \033[31m" << data.size() << "\033[0m values is: \n";
    printValuesInLine(data);
    cout << "\n";

    // Mean (average)
    double dataMean = 0.0;
    for (size_t j = 0; j < data.size(); j++)
    {
        dataMean += data[j].value;
    }
    dataMean = dataMean / data.size();

    cout << "The mean is: " << dataMean << "\n";

    // Median (middle)
    double dataMedian = median(data);
    cout << "The median is: " << dataMedian << "\n";

    // Mode (most occuring, find average if multiple)
    double dataMode = findMode(data);
    cout << "The mode is: " << dataMode << "\n\n";

    // Sort values chronologically
    chronoSort(data);
    vector<Data> chronoSorted = data;
    cout << "The chronologically sorted list of \033[31m" << data.size() << "\033[0m values is: \n";
    printValuesInLine(data);

    cout << "\n";

    cout << "The mean is: " << dataMean << "\n";

    double timeMedian = median(data);
    cout << "The median is: " << timeMedian << "\n";

    cout << "The mode is: " << dataMode << "\n\n";

    // Write output file
    writeFile(orderedSort, dataMean, dataMedian, dataMode, chronoSorted, timeMedian);

    cout << "*** Goodbye. ***" << endl;
    return 0;
}