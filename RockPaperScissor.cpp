#include <conio.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Global variable as it will required at multiple fuctions.
string options[3] = {"Rock", "Paper", "Scissor"};

void game1p();
void game2p();
int isP1Point(string, string);
int p1Won(int, int);
void endMsg(int, int, int);
void endMsg2p(int, int, int, string, string);
void playAgain();
void p1p2();

int main() {
    // Game starts here
    p1p2();
    return 0;
}

// p1p2() will check if the user wants to play 1 player mode or 2p mode, and will call the fuction required respectively
void p1p2() {
    int noOfPlayers;
    cout << "Enter the number of players (1/2): ";
    cin >> noOfPlayers;
    cin.ignore(1, '\n');

    if (noOfPlayers == 1) {
        game1p();
    } else if (noOfPlayers == 2) {
        game2p();
    } else {
        p1p2();
    }
}

// Function for 1p mode
void game1p() {
    int rounds;
    int userPoints = 0, cpuPoints = 0;

    cout << "Enter no. of rounds: ";
    cin >> rounds;

    for (int i = 0; i < rounds; i++) {
        // Generating random number between 0-2
        srand(time(0));
        int ranNum = rand() % 3;
        string cpu = options[ranNum];  // Use the random number to get random of Rock, Paper or Scissor

        int userInp;
        cout << "\nCpu has choosen. Now, ";

        // The loop will execute till the user choose and of the valid options
        bool wrongInp = 1;
        while (wrongInp) {
            cout << "choose one of the below:-\n'1' for Rock\n'2' for Paper\n'3' for Scissor\n:";
            cin >> userInp;

            // If the input is not 0,1,
            if (userInp != 1 && userInp != 2 && userInp != 3) {
                cout << "Please enter valid input!!!\n";
                continue;
            }
            wrongInp = 0;  // If the input is valid, `wrongInp = 0` will help to break the loop
        }

        string user = options[userInp - 1];

        int result = isP1Point(user, cpu);
        if (result == 0) {
            userPoints++;
            cpuPoints++;
            cout << "It's a draw!! CPU and you both chose " << cpu << ".\nYour points = " << userPoints << "\nCPU's points = " << cpuPoints;
        } else if (result == 1) {
            userPoints += 1;
            cout << "Congrats! You won this round. Your choice - " << user << " CPU Choice - " << cpu << "\nYour points = " << userPoints << "\nCPU's points = " << cpuPoints;
        } else {
            cpuPoints++;
            cout << "Oops! You should have chose something else. Your choice - " << user << " CPU Choice - " << cpu << "\nYour points = " << userPoints << "\nCPU's points = " << cpuPoints;
        }
    }
    int whoWon = p1Won(userPoints, cpuPoints);
    endMsg(whoWon, userPoints, cpuPoints);
    playAgain();
}

// Fuction for 2p mode
void game2p() {
    int p1Points = 0, p2Points = 0;
    string p1, p2;
    cout << "Player 1, please enter your name: ";
    getline(cin, p1);

    cout << "Player 2, please enter your name: ";
    getline(cin, p2);

    int rounds;
    cout << "Enter no. of Rounds: ";
    cin >> rounds;

    for (int i = 0; i < rounds; i++) {
        char p1Inp, p2Inp;    // We don't want to show what the player enters wo we will get an char using getch() and later store it in int variable.
        int p1Int, p2Int;     // This is where we will store the input number in int.
        string p1opt, p2opt;  // This will store the final option (what the player have choosen).
        bool wrognInp = 1;
        while (wrognInp) {
            cout << endl
                 << p1 << " type:-\n'1' for Rock\n'2' for Paper\n'3' for Scissor\n:";
            p1Inp = getch();
            p1Int = (p1Inp - '0') - 1;  // {var} - '0' will convert p1Inp from char to int.
            p1opt = options[p1Int];

            // We are checking for 0,1 and 2 as we already have subtracted 1 from it for getting an option from "options"
            if ((p1Int != 0) && (p1Int != 1) && (p1Int != 2)) {
                cout << "Please enter valid input!!!\n";
                continue;
            }
            wrognInp = 0;
        }
        wrognInp = 1;
        while (wrognInp) {
            cout << "\nNow " << p2 << " its your turn, type:-\n'1' for Rock\n'2' for Paper\n'3' for Scissor\n:";
            p2Inp = getch();
            p2Int = (p2Inp - '0') - 1;  // {var} - '0' will convert p2Inp from char to int.
            p2opt = options[p2Int];
            if ((p2Int != 0) && (p2Int != 1) && (p2Int != 2)) {
                cout << "Please enter valid input!!!\n";
                continue;
            }
            wrognInp = 0;
        }

        int whosePoint = isP1Point(p1opt, p2opt);
        if (whosePoint == 1) {
            p1Points++;
            cout << endl
                 << p1 << " chose " << p1opt << " and " << p2 << " chose " << p2opt << ", and it's " << p1 << "'s point.\nPoints:-\n"
                 << p1 << "'s points = " << p1Points << endl
                 << p2 << "'s points = " << p2Points << endl;
        } else if (whosePoint == 0) {
            p1Points++;
            p2Points++;
            cout << endl
                 << "Oh you both chose " << p1opt << ".\nPoints:-\n"
                 << p1 << "'s points = " << p1Points << endl
                 << p2 << "'s points = " << p2Points << endl;
        } else {
            p2Points++;
            cout << endl
                 << p2 << " beats " << p1 << " by choosing " << p2opt << " over " << p1opt << ".\nPoints:-\n"
                 << p1 << "'s points = " << p1Points << endl
                 << p2 << "'s points = " << p2Points << endl;
        }
    }
    int whoWon = p1Won(p1Points, p2Points);
    endMsg2p(whoWon, p1Points, p2Points, p1, p2);
    playAgain();
}

// Function to check if its player1's point, player2/cpu's points or a draw
int isP1Point(string p1, string p2) {
    if (p1 == "Rock" && p2 == "Scissor") {
        return 1;
    } else if (p1 == "Rock" && p2 == "Paper") {
        return -1;
    } else if (p1 == "Paper" && p2 == "Rock") {
        return 1;
    } else if (p1 == "Paper" && p2 == "Scissor") {
        return -1;
    } else if (p1 == "Scissor" && p2 == "Paper") {
        return 1;
    } else if (p1 == "Scissor" && p2 == "Rock") {
        return -1;
    }
    // Will return 0 if its a draw
    return 0;
}

// Function to check if player1 won, player2/cpu won or its a draw
int p1Won(int p1Points, int p2Points) {
    if (p1Points > p2Points) {
        return 1;
    } else if (p1Points < p2Points) {
        return -1;
    }
    return 0;  // if tied
}

// It willl print the final score and the winner
void endMsg(int whoWon, int userPoints, int cpuPoints) {
    if (whoWon == 0) {
        cout << "\n\nGG boii, both ended up with " << userPoints << " points." << endl;
    } else if (whoWon == 1) {
        cout << "\n\nYou deserve this win man!\nFinal Points:-\nYour points = " << userPoints << "\nCPU's points = " << cpuPoints << endl;
    } else {
        cout << "\n\nBetter luck next time.\nYou ended with " << userPoints << " and I ended up with " << cpuPoints << " points." << endl;
    }
}

// Same as "endMsg but for 2p mode"
void endMsg2p(int whoWon, int p1Points, int p2Points, string p1, string p2) {
    if (whoWon == 0) {
        cout << "\n\nGG boii, both ended up with " << p1Points << " points." << endl;
    } else if (whoWon == 1) {
        cout << endl
             << endl
             << p1 << ", you deserve this win man!\nFinal Points:-\n"
             << p1 << "'s points = " << p1Points << endl
             << p2 << "'s points = " << p2Points << endl;
    } else {
        cout << endl
             << endl
             << p1 << ", better luck next time.\nYou ended with " << p1Points << " and " << p2 << " ended up with " << p2Points << " points." << endl;
    }
}

// Function to check if the user wants to play again
void playAgain() {
    string again;
    cout << "\nDo you want to play again? (y/n): ";
    cin >> again;

    transform(again.begin(), again.end(), again.begin(), ::tolower);  // It will transform the user input to lower case

    if (again == "y" || again == "yes") {
        p1p2();
    } else if (again == "n" || again == "no") {
        cout << "\n\nThank you for playing the game. See you again.\n(Press any key to exit)";
        getch();
    } else {
        cout << "!!!Invalid Input!!!";
        playAgain();
    }
}
