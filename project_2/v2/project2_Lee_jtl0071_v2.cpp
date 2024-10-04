/*
Jordan Lee
jtl0071
project2_Lee_jtl0071_v1.cpp

Compile and Run Instructions:
compile 'g++ project2_Lee_jtl0071_v1.cpp -o project2_Lee_jtl0071_v1.out'
execute: './project2_Lee_jtl0071_v1.out'
*/

/* STRATEGY 2 ANALYSIS
Due to my simulations, strategy 2 is better for Aaron. This is because by Aaron intentionally missing his first shot
at Charlie, there is a 100% chance that now Bob has to shoot at Charlie instead of Aaron. Bob will either hit Charlie
and it will be Aaron's turn again, or he will miss Charlie and Charlie will kill Bob. Either way, it will be Aaron's turn
with one of the other two being dead. If left with just Aaron and Bob, they will go back and forth until one wins.
If left with Aaron and Charlie, Aaron will shoot first and either hit him and win, or miss and get shot by Charlie.

I believe this is better for both Aaron's and Charlie's win % and really only hurts Bob.
*/
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

/**
 * Random Number Generator Utility Function
 *
 * @param chance % chance of shooter hitting shot
 * @return true being hit and false being miss.
 */
bool randomNumberGenerator(int chance) // Derived from example in project2.pdf
{

    int shoot_target_result = rand() % 100;
    if (shoot_target_result < chance)
    {
        return true;
    }
    return false;
}

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
    return (count >= 2 ? true : false);
}

/**
 * Strategy 1: Use call by reference
 *
 * @param B_alive indicates whether Bob alive or dead
 * @param C_alive indicates whether Charlie is alive or dead
 * @returns Change B_alive into false if Bob is killed. Change C_alive into false if Charlie is killed.
 */
void Aaron_shoots1(bool &B_alive, bool &C_alive)
{
    const int AARON_HIT_CHANCE = 33;
    // If both alive, Aaron has 1/3 chance of hitting Aaron
    if (B_alive && C_alive)
    {
        if (randomNumberGenerator(AARON_HIT_CHANCE))
        {

            C_alive = false;
        }

        return;
    }
    if (B_alive && !C_alive)
    {
        if (randomNumberGenerator(AARON_HIT_CHANCE))
        {
            B_alive = false;
        }

        return;
    }
    if (!B_alive && C_alive)
    {
        if (randomNumberGenerator(AARON_HIT_CHANCE))
        {

            C_alive = false;
        }

        return;
    }
}

/**
 * Use call by reference
 *
 * @param A_alive indicates if Aaron is alive or dead
 * @param C_alive indicates whether Charlie is alive or dead
 * @returns Change A_alive into false if Aaron is killed. Change C_alive into false if Charlie is killed.
 */
void Bob_shoots(bool &A_alive, bool &C_alive)
{
    const int BOB_HIT_CHANCE = 50;
    if (A_alive && C_alive)
    {
        if (randomNumberGenerator(BOB_HIT_CHANCE))
        {
            C_alive = false;
        }

        return;
    }
    if (A_alive && !C_alive)
    {
        if (randomNumberGenerator(BOB_HIT_CHANCE))
        {

            A_alive = false;
        }

        return;
    }
    if (!A_alive && C_alive)
    {
        if (randomNumberGenerator(BOB_HIT_CHANCE))
        {

            C_alive = false;
        }
        else

            return;
    }
}

/**
 * Use call by reference
 *
 * @param A_alive indicates if Aaron is alive or dead
 * @param B_alive indicates whether Bob is alive or dead
 * @returns Change A_alive into false if Aaron is killed. Change B_alive into false if Bob is killed.
 */
void Charlie_shoots(bool &A_alive, bool &B_alive)
{
    if (B_alive)
    {
        B_alive = false;
    }
    else if (A_alive)
    {
        A_alive = false;
    }
}

/**
 * Strategy 2: Use call by reference
 *
 * @param B_alive indicates whether Bob alive or dead
 * @param C_alive indicates whether Charlie is alive or dead
 * @returns Change B_alive into false if Bob is killed. Change C_alive into false if Charlie is killed.
 */
void Aaron_shoots2(bool &B_alive, bool &C_alive)
{
    const int AARON_HIT_CHANCE = 33;
    // If both alive, Aaron has 1/3 chance of hitting Aaron
    if (B_alive && C_alive)
    {
        return;
    }
    if (B_alive && !C_alive)
    {
        if (randomNumberGenerator(AARON_HIT_CHANCE))
        {
            B_alive = false;
        }

        return;
    }
    if (!B_alive && C_alive)
    {
        if (randomNumberGenerator(AARON_HIT_CHANCE))
        {

            C_alive = false;
        }

        return;
    }
}

/**
 * Strat 1: Aaron shoots first
 *
 * @param Aaron reference for Aaron bool
 * @param Bob reference for Bob bool
 * @param Charlie reference for Charlie bool
 * @return 1 if Aaron wins, 2 if Bob wins, 3 if Charlie wins.
 */
int Strategy_1(bool &Aaron, bool &Bob, bool &Charlie)
{

    while (at_least_two_alive(Aaron, Bob, Charlie))
    {
        if (Aaron)
        {
            Aaron_shoots1(Bob, Charlie); // Aaron at Charlie shoots but intentionally misses
        }
        if (Bob)
        {
            Bob_shoots(Aaron, Charlie); // Bob shoots at Charlie. 1/2 chance of hitting
        }
        if (Charlie)
        {
            Charlie_shoots(Aaron, Bob); // If Charlie is alive, he shoots at Bob and kills bob
        }
    }
    if (Aaron)
    {
        return 1;
    }
    else if (Bob)
    {
        return 2;
    }
    else if (Charlie)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

/**
 * Strat 2: Aaron misses first shot. Identical to strategy 1 except we skip Aarons first shot.
 *
 * @param Aaron reference for Aaron bool
 * @param Bob reference for Bob bool
 * @param Charlie reference for Charlie bool
 * @return 1 if Aaron wins, 2 if Bob wins, 3 if Charlie wins.
 */
int Strategy_2(bool &Aaron, bool &Bob, bool &Charlie)
{

    while (at_least_two_alive(Aaron, Bob, Charlie))
    {
        if (Aaron)
        {
            Aaron_shoots2(Bob, Charlie); // Aaron at Charlie shoots but intentionally misses
        }
        if (Bob)
        {
            Bob_shoots(Aaron, Charlie); // Bob shoots at Charlie. 1/2 chance of hitting
        }
        if (Charlie)
        {
            Charlie_shoots(Aaron, Bob); // If Charlie is alive, he shoots at Bob and kills bob
        }
    }
    if (Aaron)
    {
        return 1;
    }
    else if (Bob)
    {
        return 2;
    }
    else if (Charlie)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

////////////////
// TEST CASES //
////////////////

void test_at_least_two_alive(void)
{
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    cout << "   Case 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "           Case passed ...\n";
    cout << "   Case 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "           Case passed ...\n";
    cout << "   Case 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "           Case passed ...\n";
    cout << "   Case 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "           Case passed ...\n";
    cout << "   Case 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "           Case passed ...\n";
    cout << "   Case 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "           Case passed ...\n";
    cout << "   Case 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "           Case passed ...\n";
    cout << "   Case 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "           Case passed ...\n";
    cout << "Press any key to continue...";
    cin.ignore().get();
}

void test_Aaron_shoots1(bool &B_alive, bool &C_alive)
{
    B_alive = true;
    C_alive = true;

    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)" << endl;

    cout << "   Case 1: Bob is alive, Charlie is alive" << endl;
    Aaron_shoots1(B_alive, C_alive);
    assert(B_alive || C_alive);
    cout << "           Aaron is shooting Charlie" << endl;

    cout << "   Case 2: Bob is dead, Charlie is alive" << endl;
    B_alive = false;
    C_alive = true;
    Aaron_shoots1(B_alive, C_alive);
    assert(B_alive == false || !C_alive);
    cout << "           Aaron is shooting Charlie" << endl;

    cout << "   Case 3: Bob is alive, Charlie is dead" << endl;
    B_alive = true;
    C_alive = false;
    Aaron_shoots1(B_alive, C_alive);
    assert(!B_alive || C_alive == false);
    cout << "           Aaron is shooting Bob" << endl;

    B_alive = true;
    C_alive = true;

    cout << "Press any key to continue...";
    cin.ignore().get();
}

void test_Bob_shoots(bool &A_alive, bool &C_alive)
{
    A_alive = true;
    C_alive = true;

    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)" << endl;

    cout << "   Case 1: Aaron is alive, Charlie is alive" << endl;
    Bob_shoots(A_alive, C_alive);
    assert(A_alive || C_alive);
    cout << "           Bob is shooting Charlie" << endl;

    cout << "   Case 2: Aaron is dead, Charlie is alive" << endl;
    A_alive = false;
    C_alive = true;
    Bob_shoots(A_alive, C_alive);
    assert(A_alive == false || !C_alive);
    cout << "           Bob is shooting Charlie" << endl;

    cout << "   Case 3: Aaron is alive, Charlie is dead" << endl;
    A_alive = true;
    C_alive = false;
    Bob_shoots(A_alive, C_alive);
    assert(!A_alive || C_alive == false);
    cout << "           Bob is shooting Aaron" << endl;

    A_alive = true;
    C_alive = true;

    cout << "Press any key to continue...";
    cin.ignore().get();
}

void test_Charlie_shoots(bool &A_alive, bool &B_alive)
{
    A_alive = true;
    B_alive = true;

    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)" << endl;

    cout << "   Case 1: Aaron is alive, Bob is alive" << endl;
    Charlie_shoots(A_alive, B_alive);
    assert(B_alive == false);
    cout << "           Charlie is shooting Bob" << endl;

    cout << "   Case 2: Aaron is dead, Bob is alive" << endl;
    A_alive = false;
    B_alive = true;
    Charlie_shoots(A_alive, B_alive);
    assert(B_alive == false);
    cout << "           Charlie is shooting Bob" << endl;

    cout << "   Case 3: Aaron is alive, Bob is dead" << endl;
    A_alive = true;
    B_alive = false;
    Charlie_shoots(A_alive, B_alive);
    assert(A_alive == false);
    cout << "           Charlie is shooting Aaron" << endl;

    A_alive = true;
    B_alive = true;

    cout << "Press any key to continue...";
    cin.ignore().get();
}

void test_Aaron_shoots2(bool &B_alive, bool &C_alive)
{
    B_alive = true;
    C_alive = true;

    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)" << endl;

    cout << "   Case 1: Bob is alive, Charlie is alive" << endl;
    Aaron_shoots2(B_alive, C_alive);
    assert(B_alive && C_alive);
    cout << "           Aaron intentionally missed his first shot" << endl;
    cout << "           Both Bob and Charlie are alive" << endl;

    cout << "   Case 2: Bob is dead, Charlie is alive" << endl;
    B_alive = false;
    C_alive = true;
    Aaron_shoots2(B_alive, C_alive);
    assert(B_alive == false || !C_alive);
    cout << "           Aaron is shooting Charlie" << endl;

    cout << "   Case 3: Bob is alive, Charlie is dead" << endl;
    B_alive = true;
    C_alive = false;
    Aaron_shoots2(B_alive, C_alive);
    assert(!B_alive || C_alive == false);
    cout << "           Aaron is shooting Bob" << endl;

    B_alive = true;
    C_alive = true;

    cout << "Press any key to continue...";
    cin.ignore().get();
}

int main()
{
    // Create boolean variables for each person, true if alive, false if dead.
    bool Aaron = true;   // Hits 1/3 of shots
    bool Bob = true;     // Hits 1/2 of shots
    bool Charlie = true; // Always hits
    int A_count = 0;
    int B_count = 0;
    int C_count = 0;
    double A_win_precent_1;
    double A_win_precent_2;
    double B_win_precent;
    double C_win_precent;
    const int ITERATION_COUNT = 10000;
    srand(static_cast<unsigned int>(time(0))); // Had to use copilot to get rid of this 'implicit conversion loses integer precision' warning

    cout << "*** Welcome to Jordan's Truel of the Fates Simulator ***" << endl;

    test_at_least_two_alive();
    test_Aaron_shoots1(Bob, Charlie);
    test_Bob_shoots(Aaron, Charlie);
    test_Charlie_shoots(Aaron, Bob);
    test_Aaron_shoots2(Bob, Charlie);

    // Strategy 1
    cout << "Ready to test strategy 1 (run " << ITERATION_COUNT << " times):" << endl;
    cout << "Press any key to continue...";
    cin.ignore().get(); // Derived from example in project2.pdf
    cout << "Testing Strategy 1..." << endl;

    for (int i = 0; i < ITERATION_COUNT; i++)
    {
        // Reset everyone to alive
        Aaron = true;
        Bob = true;
        Charlie = true;

        // Find winner
        int S1_winner = Strategy_1(Aaron, Bob, Charlie);

        // Add win to counts
        switch (S1_winner)
        {
        case 1:
            A_count++;
            break;
        case 2:
            B_count++;
            break;
        case 3:
            C_count++;
            break;
        }
    }

    // Calculate Win Percentages
    A_win_precent_1 = (A_count / 10000.0) * 100;
    B_win_precent = (B_count / 10000.0) * 100;
    C_win_precent = (C_count / 10000.0) * 100;

    // Output counts.
    cout << "Aaron won " << A_count << "/10000 truels or " << A_win_precent_1 << "%" << endl;
    cout << "Bob wins: " << B_count << "/10000 truels or " << B_win_precent << "%" << endl;
    cout << "Charlie wins: " << C_count << "/10000 truels or " << C_win_precent << "%" << endl
         << endl;

    // Reset vars
    B_win_precent = 0;
    C_win_precent = 0;
    A_count = 0;
    B_count = 0;
    C_count = 0;

    // Strategy 2
    cout << "Ready to test strategy 2 (run " << ITERATION_COUNT << " times):" << endl;
    cout << "Press any key to continue...";
    cin.ignore().get();

    for (int i = 0; i < ITERATION_COUNT; i++)
    {
        // Reset everyone to alive
        Aaron = true;
        Bob = true;
        Charlie = true;

        // Find winner
        int S2_winner = Strategy_2(Aaron, Bob, Charlie);

        // Add win to counts
        switch (S2_winner)
        {
        case 1:
            A_count++;
            break;
        case 2:
            B_count++;
            break;
        case 3:
            C_count++;
            break;
        }
    }

    // Calculate Win Percentages
    A_win_precent_2 = (A_count / 10000.0) * 100;
    B_win_precent = (B_count / 10000.0) * 100;
    C_win_precent = (C_count / 10000.0) * 100;

    // Output counts
    cout << "Aaron won " << A_count << "/10000 truels or " << A_win_precent_2 << "%" << endl;
    cout << "Bob wins: " << B_count << "/10000 truels or " << B_win_precent << "%" << endl;
    cout << "Charlie wins: " << C_count << "/10000 truels or " << C_win_precent << "%" << endl
         << endl;

    cout << (A_win_precent_1 > A_win_precent_2 ? "Strategy 1 is better than strategy 2." : "Strategy 2 is better than strategy 1.") << endl;
    return 0;
}
