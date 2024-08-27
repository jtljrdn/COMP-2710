/*
Jordan Lee
jtl0071
project1_Lee_jtl0071.cpp

Compile Instructions:
run 'g++ project1_Lee_jtl0071.cpp -o project1_Lee_jtl0071'
*/

#include <iostream>
#include <iomanip> 
using namespace std;

int main(){
    // Create util variables


    // Create input variables
    int loanAmt;
    float interestRate;
    int monthlyPayments;

    // Take User Input, handle errors with input
    cout << "Loan Amount: ";
    cin >> loanAmt;
    if (!cin){
        throw invalid_argument("Input must be a integer"); // Input error handling from Painless Programming on Youtube
    }
    cout << "Interest Rate (% per year): ";
    cin >> interestRate;
    if (!cin){
        throw invalid_argument("Input must be a float");
    }
    cout << "Monthly Payments: ";
    cin >> monthlyPayments; 
    if (!cin){
        throw invalid_argument("Input must be a integer");
    }


    cout << "**********************************************************" << endl;
    cout << "       Amortization Table" << endl;
    cout << "**********************************************************" << endl;
    cout.setf(ios::left, ios::adjustfield);
    cout << setw(7) << "Month" << setw(10) << "Balance" << setw(13) << "Payment" 
    << setw(8) << "Rate" << setw(11) << "Interest" << setw(9) << "Principal" << endl;
    return 0;
}
