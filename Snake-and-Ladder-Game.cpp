#include <bits/stdc++.h>

using namespace std;

// Snake and Ladder board class
class Board {
private:
    map<int, int> snakes;
    map<int, int> ladders;
    int boardSize;

public:
    Board(int size) : boardSize(size) {
        // Initialize snakes
        snakes[16] = 6;
        snakes[47] = 26;
        snakes[49] = 11;
        snakes[56] = 53;
        snakes[62] = 19;
        snakes[64] = 60;
        snakes[87] = 24;
        snakes[93] = 73;
        snakes[95] = 75;
        snakes[98] = 78;

        // Initialize ladders
        ladders[1] = 38;
        ladders[4] = 14;
        ladders[9] = 31;
        ladders[21] = 42;
        ladders[28] = 84;
        ladders[36] = 44;
        ladders[51] = 67;
        ladders[71] = 91;
        ladders[80] = 100;
    }

    int getBoardSize() const {
        return boardSize;
    }

    int checkSnakeOrLadder(int position) const {
        if (snakes.find(position) != snakes.end()) {
            cout << "Oops! Bitten by a snake! Moving from " << position << " to " << snakes.at(position) << endl;
            return snakes.at(position);
        }
        if (ladders.find(position) != ladders.end()) {
            cout << "Yay! Climbed a ladder! Moving from " << position << " to " << ladders.at(position) << endl;
            return ladders.at(position);
        }
        return position;
    }
};

// Player class
class Player {
private:
    string name;
    int position;

public:
    Player(string playerName) : name(playerName), position(0) {}

    string getName() const {
        return name;
    }

    int getPosition() const {
        return position;
    }

    void updatePosition(int newPosition) {
        position = newPosition;
    }
};

// Dice class
class Dice {
public:
    int roll() {
        return (rand() % 6) + 1;
    }
};

// Game class
class Game {
private:
    Board board;
    Dice dice;
    vector<Player> players;

public:
    Game(int boardSize, const vector<string>& playerNames)
        : board(boardSize), dice() {
        for (const auto& name : playerNames) {
            players.emplace_back(name);
        }
        srand(time(0));
    }

    void play() {
        bool gameOver = false;
        while (!gameOver) {
            for (auto& player : players) {
                cout << player.getName() << "'s turn. Press Enter to roll the dice...";
                cin.ignore();

                int roll = dice.roll();
                cout << "Rolled a " << roll << "!" << endl;

                int newPosition = player.getPosition() + roll;

                if (newPosition > board.getBoardSize()) {
                    cout << player.getName() << " rolled too high and stays at position "
                         << player.getPosition() << endl;
                } else {
                    newPosition = board.checkSnakeOrLadder(newPosition);
                    player.updatePosition(newPosition);
                    cout << player.getName() << " moved to position " << newPosition << endl;

                    if (newPosition == board.getBoardSize()) {
                        cout << player.getName() << " wins the game!" << endl;
                        gameOver = true;
                        break;
                    }
                }
            }
        }
    }
};

// Main function
int main() {
    cout << "Welcome to Snake and Ladder Game!" << endl;

    int boardSize = 100;
    vector<string> playerNames;
    int numPlayers;

    cout << "Enter the number of players: ";
    cin >> numPlayers;
    cin.ignore();

    for (int i = 0; i < numPlayers; ++i) {
        string name;
        cout << "Enter the name of player " << i + 1 << ": ";
        getline(cin, name);
        playerNames.push_back(name);
    }

    Game game(boardSize, playerNames);
    game.play();

    return 0;
}
