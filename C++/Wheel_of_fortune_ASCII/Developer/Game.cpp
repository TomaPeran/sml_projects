#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <thread>
#include "GameHeader.hpp"
#include "global.hpp"
#include "RegularFunctions.hpp"
#include "FileFunctions.hpp"


using std::string;
using std::cout;


GameElement::GameElement() {}


GameElement::GameElement(string name) : name(name) {}


void GameElement::displayInfo() {}


void GameElement::randomChoice(string& word) {
    int randomNumber = rand() % 5;
    switch (randomNumber) {
    case 0: fileFood(word);
        break;
    case 1:fileCar(word);
        break;
    case 2:fileGame(word);
        break;
    case 3:fileMovie(word);
        break;
    case 4:fileCity(word);
        break;
    default: cout << "Bad Number\n";
        game = false;
        break;
    }


}
/*void GameElement::randomChoice(std::fstream& fin, string& word) {
    int number = 0;

    while (std::getline(fin, word)) {
        number++;
    }

    number = rand() % number;
    fin.clear();
    fin.seekg(0);

    while (number != 0) {
        std::getline(fin, word);
        --number;
    }
}
*/


Player::Player() {
    this->name = "none";
    this->points = 0;
    this->number_of_jokers = 0;
}


Player::Player(string name, int points, int number_of_jokers) :GameElement(name) {
    this->points = points;
    this->number_of_jokers = number_of_jokers;

}


void Player::set_players(std::vector<Player>& players) {
    Player p1("Marko");
    Player p2("Ivan");
    Player p3("Toma");
    Player p4("Luka");

    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
    players.push_back(p4);
}


unsigned int Player::available_jokers() const {
    return number_of_jokers;
}


void Player::display_scoreboard(std::vector<Player>& players) {
    cout << "\tScoreboard: \n\n";
    for (auto& p : players) {
        std::cout << "\t" << p.name << "\t" << p.points << '\n';
    }

}


void Player::give_points(unsigned int value) {
    points += value;
}


void Player::joker_operations(unsigned int state) {
    switch (state) {
    case 1: number_of_jokers++;
        break;
    case 2: number_of_jokers--;
        break;
    case 3: number_of_jokers = number_of_jokers * 2;
        break;
    case 4:
        if (number_of_jokers)
            number_of_jokers = number_of_jokers / 2;
        break;
    deafult: cout << "False state\n";
        break;
    }

}


Player Player::max_winner(std::vector <Player>& all_players) const {
    // std::max_element(all_players.begin(), all_players.end(), [](const Player& a, const Player& b) {return a.points < b.points; });
    Player max = all_players[0];
    for (int i = 0; i < all_players.size(); i++) {
        if (max.points < all_players[i].points)
            max = all_players[i];
    }

    return max;
}


unsigned int WheelSegment::spin_wheel() {
    fileWheel(wheel_value);
    std::cout << "You are playing for: " << wheel_value << "!" << std::endl;


    if (!wheel_value.compare("BANKROT"))
        return 1;
    else if (!wheel_value.compare("JOKER"))
        return 2;
    else
        return 0;


}


unsigned int WheelSegment::value() const {
    return stoi(wheel_value);
}


void Puzzle::set_themes() {
    themes.push_back("food");
    themes.push_back("car");
    themes.push_back("game");
    themes.push_back("movie");
    themes.push_back("city");
}


void Puzzle::makeWord() {
    int indeks = rand() % themes.size();
    game_theme = themes[indeks];
    //string file = game_theme + ".txt";


    //std::cout << game_theme << std::endl;

    randomChoice(word);


    transform(word.begin(), word.end(), word.begin(), ::toupper);
    //std::cout << word << std::endl;
}


void Puzzle::makeAnswer() {
    for (char c : word) {
        if (std::ispunct(c) || c == ' ' || isdigit(c))
            answer += c;
        else
            answer += '-';
    }

    //std::cout << answer << std::endl;
}


bool Puzzle::checkAnswer(Player& player, WheelSegment wheel, string guess, int choose) {
    transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
    bool incorrect = true;
    // ako se desi unos praznog stringa
    // za svaki slucaj
    if (guess.empty()) {
        std::cout << "Inpout not valid, try again\n";
        return true; // zbog while petlje ponavljanja
    }

    // u ovisnosti broja (akcije)
    // oznacava je li slovo ili recenica

    if (choose == 1) {
        // trazi se slovo u stringu
        if (guess.size() > 1) {
            cout << "You have chose letter not sentence, try again\n";
            return true;
        }

        int number = 0;
        for (int i = 0; i < word.size(); i++) {
            if (guess[0] == answer[i] && !(ispunct(word[i]))) {
                cout << "That letter is already used\n";
                return true; // ima pravo ponavljanja
            }
            else if (word[i] == guess[0]) {
                answer[i] = guess[0];
                number++;
                incorrect = false;
            }

        }
        if (incorrect) {
            clearScreen();
            cout << "Incorrect letter\n";
            return false;
        }
        // mnozi se wheel_value sa brojem pronadenih
        player.give_points(wheel.value() * number);


        // gleda je li string answer pun
        if (!answer.compare(word)) {
            cout << "End of the game\n";
            cout << "An answer was: ";
            game = false;
        }

        //cout << answer << std::endl;
        return false; // while petlja se zavrsava
    }
    else {
        // provjerava se string sa stringom
        if (guess.size() > 1) {
            if (!word.compare(guess)) {
                cout << "Correct, searched answer was: " << guess << std::endl;
                player.give_points(wheel.value() * 10);
                game = false;
                return false; // da ugasi while petlja ponavljanja
            }
        }
        else if (guess.size() == 1) {
            cout << "You have choose sentence not letter, try again\n";
            return true;
        }

        cout << "Incorrect\n";
        return false; // nema pravo ponavljanja
    }
}


string Puzzle::choose_vowel() {
    string choose;


    while (true) {
        do {
            cout << "Odaberi samoglasnik: 1.A\t2.E\t3.I\t4.O\t5.U\n";
            std::cin >> choose;
            std::cin.ignore();
        } while (!is_number(choose));

        switch (stoi(choose)) {
        case 1: return "a";
        case 2: return "e";
        case 3: return "i";
        case 4: return "o";
        case 5: return "u";

        default: clearScreen();
            cout << "Input not valid, try again\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            clearScreen();
            break;
        }
    }
}


void Puzzle::displayInfo() const {
    cout << "Tema: " << game_theme << std::endl;
    cout << answer << std::endl;
}