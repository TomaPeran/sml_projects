#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <ctime>
#include <thread>
#include "GameHeader.hpp"
#include "global.hpp"
#include "RegularFunctions.hpp"


bool game = true;
using std::cout;
using std::cin;
using std::string;


int main() {

	srand((unsigned int)time(0));
	GameElement gameElement("none");
	cout << "WHEEL OF FORTUNE\n";
	//cout << "Press Enter to continue";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	clearScreen();

	/*
	std::this_thread::sleep_for(std::chrono::seconds(1));
	clearScreen();
	*/
	std::vector<Player>all_players;
	// stavimo da bira rucni ili automatski unos
	/*cout << "Prijava igraca: \n";
	for (int i = 0;i < 4;i++) {
		string name;
		cout << "Enter player's name: \n", cin >> name;
		Player p(name);
		all_players.push_back(p);
	}*/

	//	setanje igraca
	Player player;
	player.set_players(all_players);
	//player.display_scoreboard(all_players);



	for (int i = 0; i < 3; i++) { // broji tri partije
		game = true;

		//	priprema igre
		Puzzle puzzle;
		puzzle.set_themes();
		puzzle.makeWord();
		puzzle.makeAnswer();
		while (game) { // partija


			for (int j = 0; j < 4 && game; j++) { // jedan igrac, idu po redu
				int value;
				string guess, action;
				WheelSegment pWheel;
				bool flag = true, Vowels = false, spin = true;
				puzzle.displayInfo();
				cout << "Player " << all_players[j].name << " is on the turn\n";

				// vrti kolo i provjerava dobit
				while (spin) {

					std::this_thread::sleep_for(std::chrono::seconds(2));
					clearScreen();
					cout << "" << all_players[j].name;
					std::this_thread::sleep_for(std::chrono::seconds(1));
					cout << " SPIN";
					std::this_thread::sleep_for(std::chrono::seconds(1));
					cout << " THAT";
					std::this_thread::sleep_for(std::chrono::seconds(1));
					cout << " WHEEL\n";

					// animacija vrtnje kola, mozda nadodat
					std::this_thread::sleep_for(std::chrono::seconds(2));
					clearScreen();

					//puzzle.displayInfo();
					value = pWheel.spin_wheel();
					std::this_thread::sleep_for(std::chrono::seconds(2));
					// 0 -> value
					// 1 -> bankrot
					// 2 -> joker
					// mozda cak staviti switch ovdje
					// stavit u zasebnu funkciju, cisce
					if (value == 0) {
						// preskace petlju
						spin = false;
					}

					else if (value == 1) { // bankrot
						if (all_players[j].available_jokers() > 0) {

							do {
								cout << "Do You want to use Joker:\t1. Yes\t2.No\n";
								cin >> action;
							} while (!is_number(action));

							if (stoi(action) == 1) {
								all_players[j].joker_operations(2);

								clearScreen();
								// ukloni jokera
								// nanovo vrti
							}
							else {
								if (j == 3) {
									j = -1; // postavlja na poziciju jedan iza zadnjeg
								}
								j++; //dize na novog igraca
								// gotov krug
								// jer ne zeli iskoristiti joker-a

								clearScreen();
								cout << "Your turn is over\n";

								std::this_thread::sleep_for(std::chrono::seconds(1));
								clearScreen();
								puzzle.displayInfo();
								cout << "Player " << all_players[j].name << " is on the turn\n";

								std::this_thread::sleep_for(std::chrono::seconds(2));
								clearScreen();
							}
						}
						else {
							if (j == 3) {
								j = -1; // postavlja na poziciju jedan iza zadnjeg
							}
							j++;

							clearScreen();
							cout << "We are sorry but You haven't enoguh joker's\n";

							std::this_thread::sleep_for(std::chrono::seconds(2));
							clearScreen();
							puzzle.displayInfo();
							cout << "Player " << all_players[j].name << " is on the turn\n";
							// gotov krug jer nema joker-a
						}
					}
					else if (value == 2) { // value == 2
						all_players[j].joker_operations(1);

						clearScreen();
						cout << "Congratulations You have Won a Joker\n";

						std::this_thread::sleep_for(std::chrono::seconds(2));
						clearScreen();

						cout << "You got another chance to spin the wheel\n";
						std::this_thread::sleep_for(std::chrono::seconds(2));
						clearScreen();

						// dodaj jokera
						// nanovo vrti
					}
				}

				////////////////////////////////////////////////////////////////////////////////

				// pita korisnika za unos
				// provjerava unos korisnika
				clearScreen();
				while (flag) {
					do {
						puzzle.displayInfo();
						cout << "Choose Your action: 1. Guess a letter\t2. Guess a sentence";
						if (all_players[j].available_jokers()) {
							cout << "\t3. Use Your Joker";
							Vowels = true;
						}
						cout << std::endl;
						cin >> action;
						std::cin.ignore();
						clearScreen();
					} while (!is_number(action));
					// action mora biti broj, iako je prikazan kao string



					switch (stoi(action)) {
					case 1:
					case 2: cout << "Unos: ";
						getline(cin, guess);
						// provjerava je li unos samoglasnik
						if (isVowel(guess)) {

							clearScreen();
							cout << "Vowel is not allowed!\n";

							std::this_thread::sleep_for(std::chrono::seconds(1));
							clearScreen();
							break;
						}

						clearScreen();

						flag = puzzle.checkAnswer(all_players[j], pWheel, guess, stoi(action));
						std::this_thread::sleep_for(std::chrono::seconds(1));
						clearScreen();
						break;
					case 3:
						if (Vowels) {
							//std::this_thread::sleep_for(std::chrono::seconds(1));
							clearScreen();

							// malo sporija funkcija stoga ce se cini
							// ka da program zastaje, ali cak i nije

							flag = puzzle.checkAnswer(all_players[j], pWheel, puzzle.choose_vowel(), 1);
							std::this_thread::sleep_for(std::chrono::seconds(1));
							clearScreen();
							all_players[j].joker_operations(2);

						}
						else {
							clearScreen();
							cout << "Action not allowed" << std::endl;
							std::this_thread::sleep_for(std::chrono::seconds(1));
							clearScreen();
						}
						break;
					default: clearScreen();
						cout << "Input not valid, try again\n";
						flag = true;
						std::this_thread::sleep_for(std::chrono::seconds(1));
						clearScreen();
						break;
					}

				}

				gameElement.name = all_players[j].name;

				if (game && j == 3)
					j = -1;
			}



		}

		// pogledat printanje kad se pogodi cijela rijec, ili po slovo
		cout << "Winner of this game is: ";
		cout << gameElement.name << std::endl;
		// print scoreboard
		std::this_thread::sleep_for(std::chrono::seconds(1));
		clearScreen();

		player.display_scoreboard(all_players);
		std::this_thread::sleep_for(std::chrono::seconds(3));
		clearScreen();


	}

	std::this_thread::sleep_for(std::chrono::seconds(1));
	clearScreen();
	cout << "Overall Winner is: " << player.max_winner(all_players).name << std::endl;
	// neka animacija

	return 0;

}
