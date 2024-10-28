#ifndef GAMEHEADER_HPP
#define GAMEHEADER_HPP
#include <iostream>
#include <string>
#include<vector>

using std::string;

class GameElement {
public:
	string name;
	GameElement();
	GameElement(string name);
	void randomChoice(string& word);
	virtual void displayInfo();


};
class Player :public GameElement {
protected:
	//string player_name;//nasljeduje  od base class
	int points;
	int number_of_jokers;

public:
	Player();
	Player(string name, int points = 0, int number_of_jokers = 0);
	void set_players(std::vector<Player>& players);
	void display_scoreboard(std::vector<Player>& players);
	unsigned int available_jokers() const;
	void joker_operations(unsigned int state);
	void give_points(unsigned int value);
	Player max_winner(std::vector <Player>& all_players) const;
};


class WheelSegment : public GameElement {
protected:
	string wheel_value;

public:
	unsigned int spin_wheel();
	unsigned int value() const;
	//void print() {};
};


class Puzzle : public GameElement {
protected:
	string word; // trazena rijec
	string answer; // spremaju se crtice
	std::vector <string> themes;
	string game_theme;
	// napravit vector <string> used_words // da nebi bilo ponavljanja rijeci

public:
	void set_themes();
	void makeWord();
	void makeAnswer();
	bool checkAnswer(Player& player, WheelSegment wheel, string guess, int choose);
	string choose_vowel();
	void displayInfo() const;
};


#endif 
