/*
Jordan Lee
jtl0071
project1_Lee_jtl0071.cpp

Compile and Run Instructions:
compile 'g++ project1_Lee_jtl0071.cpp -o project1_Lee_jtl0071.out'
execute: './project1_Lee_jtl0071.out'
*/
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive){}
/* Input: A_alive indicates whether Aaron is alive
* B_alive indicates whether Bob is alive
* C_alive indicates whether Charlie is alive
* Return: true if at least two are alive
* otherwise return false
*/
void Aaron_shoots1(bool& B_alive, bool& C_alive){}
/* Strategy 1: Use call by reference
* Input: B_alive indicates whether Bob alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change B_alive into false if Bob is killed.
* Change C_alive into false if Charlie is killed.
*/
void Bob_shoots(bool& A_alive, bool& C_alive){}
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change C_alive into false if Charlie is killed.
*/
void Charlie_shoots(bool& A_alive, bool& B_alive){}
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
5
* B_alive indicates whether Bob is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change B_alive into false if Bob is killed.
*/
void Aaron_shoots2(bool& B_alive, bool& C_alive){}
/* Strategy 2: Use call by reference
* Input: B_alive indicates whether Bob alive or dead
* C_alive indicates whether Charlie is alive or dead
* Return: Change B_alive into false if Bob is killed.
* Change C_alive into false if Charlie is killed.
*/

int main(){

    return 0;
}
