/*
Jordan Lee
jtl0071
project1_Lee_jtl0071.cpp

Compile and Run Instructions:
compile 'g++ project1_Lee_jtl0071.cpp -o project1_Lee_jtl0071.out'
execute: './project1_Lee_jtl0071.out'
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // Create util variables
    float principal;
    int monthsCount = 0;
    float interestAmt;
    float totalInterest = 0;

    // Create input variables
    float loanAmt;
    float interestRate;
    float monthlyPayment;

    // Take User Input, handle errors with input
    cout << "Loan Amount: ";
    cin >> loanAmt;
    if (!cin)
    {
        throw invalid_argument("Input must be a float"); // Input error handling from Painless Programming on Youtube
    }
    cout << "Interest Rate (% per year): ";
    cin >> interestRate;
    if (!cin)
    {
        throw invalid_argument("Input must be a float");
    }
    cout << "Monthly Payments: ";
    cin >> monthlyPayment;
    cout << endl;
    if (!cin)
    {
        throw invalid_argument("Input must be a integer");
    }
    // Calculate initial interest amount
    interestAmt = loanAmt * ((interestRate / 12) / 100);
    // Make sure monthly payment is greater than interest
    if (monthlyPayment < interestAmt)
    {
        cout << "ERROR: Interest is more than your payment. Please enter a monthly payment higher than " << interestAmt << ": ";
        cin >> monthlyPayment;
        if (!cin)
        {
            throw invalid_argument("Input must be a float");
        }
    }

    // Output Header
    cout << "**********************************************************" << endl;
    cout << "       Amortization Table" << endl;
    cout << "**********************************************************" << endl;
    cout.setf(ios::left, ios::adjustfield);
    cout << setw(7) << "Month" << setw(10) << "Balance" << setw(13) << "Payment"
         << setw(8) << "Rate" << setw(11) << "Interest" << setw(9) << "Principal" << endl;

    // First Line Output, do separate from loop due to N/As
    cout << setprecision(2) << fixed; // Sets float precision to 2 decimal places, because money
    cout << setw(7) << "0" << "$"
         << setw(9) << loanAmt
         << setw(13) << "N/A"
         << setw(8) << "N/A"
         << setw(11) << "N/A"
         << setw(9) << "N/A"
         << endl;

    // Loop until loan is completely paid off
    while (loanAmt > 0)
    {
        
        monthsCount++;

        // Calculate Interest, Principal, Payment
        interestAmt = loanAmt * ((interestRate / 12) / 100);
        if (monthlyPayment > loanAmt)
        {
            monthlyPayment = loanAmt + interestAmt;
        }
        principal = monthlyPayment - interestAmt;
        loanAmt -= principal;


        cout << setw(7) << monthsCount << "$"
             << setw(9) << loanAmt << "$"
             << setw(12) << monthlyPayment
             << setw(8) << interestRate / 12 << "$"
             << setw(10) << interestAmt << "$"
             << setw(8) << principal
             << endl;

        totalInterest += interestAmt;
    }

    cout << "**********************************************************" << endl
         << endl;
    cout << "It takes " << to_string(monthsCount) << " months to pay off the loan" << endl;
    cout << "Total interest paid is: $" << totalInterest << endl;

    return 0;
}
