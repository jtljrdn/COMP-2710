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


/**
 * Checks if atleast two people are still alive
 * 
 * @param A_alive indicates whether Aaron is alive
 * @param B_alive indicates whether Bob is alive
 * @param C_alive indicates whether Charlie is alive
 * @returns true if atleast 2 people are alive, false otherwise
 */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive)
{
    int count = 0;
    if (A_alive)
    {
        count++;
    }
    if (B_alive)
    {
        count++;
    }
    if (C_alive)
    {
        count++;
    }
    return (true ? count >= 2 : false);
}
/**
 * Strategy 1: Use call by reference
 * 
 * @param B_alive indicates whether Bob alive or dead
 * @param C_alive indicates whether Charlie is alive or dead
 * @returns Change B_alive into false if Bob is killed. Change C_alive into false if Charlie is killed.
 */
void Aaron_shoots1(bool &B_alive, bool &C_alive) {}
/* Strategy 1: Use call by reference
 * Input: B_alive indicates whether Bob alive or dead
 * C_alive indicates whether Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed.
 * Change C_alive into false if Charlie is killed.
 */
void Bob_shoots(bool &A_alive, bool &C_alive) {}
/* Call by reference
 * Input: A_alive indicates if Aaron is alive or dead
 * C_alive indicates whether Charlie is alive or dead
 * Return: Change A_alive into false if Aaron is killed.
 * Change C_alive into false if Charlie is killed.
 */
void Charlie_shoots(bool &A_alive, bool &B_alive) {}
/* Call by reference
* Input: A_alive indicates if Aaron is alive or dead
5
* B_alive indicates whether Bob is alive or dead
* Return: Change A_alive into false if Aaron is killed.
* Change B_alive into false if Bob is killed.
*/
void Aaron_shoots2(bool &B_alive, bool &C_alive) {}
/* Strategy 2: Use call by reference
 * Input: B_alive indicates whether Bob alive or dead
 * C_alive indicates whether Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed.
 * Change C_alive into false if Charlie is killed.
 */

void main()
{
    bool Aaron = true;
    bool Bob = true;
    bool Charlie = true;
}
