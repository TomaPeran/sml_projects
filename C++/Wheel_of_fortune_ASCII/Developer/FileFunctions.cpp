#include "FileFunctions.hpp"

std::string randomWord(std::vector<std::string> theme) {
	int number = rand() % theme.size();
	return theme[number];
}

void fileFood(std::string& word) {
	std::vector <std::string> theme = {
		"Pizza", "Bread", "Soup", "Lasagne", "Chia seeds", "Garlic", "Gouda", "Bananas", "Barbecued meat", "Beef", "Beets",
		"Bell peppers", "Bitter almond oil", "Cucumber", "Melon", "Black beans", "Black tea", "Dry beans", "Fermented milk"
	};

	word = randomWord(theme);
}
void fileCar(std::string& word) {
	std::vector <std::string> theme = {
		"Abarth", "Alfa Romeo", "Aston Martin", "Audi", "Bentley", "Bugatti", "Cadillac", "Chevrolet", "Chrysler", "Dacia", "Daewoo",
		"Daihatsu", "Dodge", "Ferrari", "Fiat", "Fisker", "Ford", "Honda", "Hummer", "Hyundai", "Infiniti", "Iveco", "Jaguar", "Jeep",
		"Kia", "KTM", "Lada", "Lamborghini", "Lancia", "Land Rover", "Landwind", "Lexus", "Lotus", "Maserati", "Maybach", "Mazda",
		"McLaren", "Mercedes - Benz", "Mini", "Mitsubishi","Nissan", "Opel", "Peugeot", "Porsche", "Renault", "Rolls - Royce", "Rover",
		"Saab", "Seat", "Skoda", "Smart", "SsangYong", "Subaru", "Suzuki", "Toyota", "Volkswagen", "Volvo"
	};

	word = randomWord(theme);
}
void fileGame(std::string& word) {
	std::vector <std::string> theme = {
		"Assassin's creed", "Warcraft", "Risk", "Minecraft", "Grand Theft Auto 5", "Wii Sports", "PUBG : Battlegrounds", "Mario Kart 8",
		"Super Mario Bros", "Red Dead Redemption", "Overwatch", "The Witcher 3 : Wild Hunt", "Tetris", "Terraria", "Animal Crossing : New Horizons",
		"Pac - Man", "Human : Fall Flat", "Mario Kart Wii", "Wii Sports Resort", "The Legend of Zelda : Breath of the Wild",
		"Super Smash Bros : Ultimate", "New Super Mario Bros", "Call of Duty : Modern Warfare", "Diablo 3", "Pokemon Gold",
		"Duck Hunt", "The Walking Dead", "Grand Theft Auto : San Andreas", "Borderlands 2", "Super Mario Odyssey", "Super Mario World",
		"Call of Duty : Modern Warfare 3", "FIFA 18", "Call of Duty : Black Ops", "Cyberpunk 2077", "Horizon Zero Dawn", "Call of Duty : Black Ops 2"
	};

	word = randomWord(theme);
}
void fileMovie(std::string& word) {
	std::vector <std::string> theme = {
		"Interstellar", "Hoodwinked", "Die Hard", "I Robot", "Alice, Sweet Alice", "Alice Doesn't Live Here Anymore", "Alice in Wonderland",
		"Alice's Restaurant", "Alien", "Alien Abduction", "Alien Contamination", "Baba Yaga : Terror of the Dark Forest", "The Baby",
		"Baby Face", "Back to School", "Back to the Future", "Batman Returns", "Batman : The Movie", "The Conjuring", "Constantine",
		"Contact", "Containment", "Contempt"
	};

	word = randomWord(theme);
}
void fileCity(std::string& word) {
	std::vector <std::string> theme = {
		"Split","Zagreb","Dublin", "Sydney", "Tokyo", "Delhi", "Shanghai", "Sao Paulo", "Mexico City", "Cairo", "Mumbai",
		"Lagos", "New York", "Moscow", "Dhaka", "Mumbai", "Beijing", "Osaka"
	};

	word = randomWord(theme);
}
void fileWheel(std::string& word) {
	std::vector <std::string> theme = {
		"500", "900", "700", "2500", "BANKROT", "900", "650", "500", "800", "950", "650", "600", "550", "JOKER", "600", "500", "700",
		"500", "650", "750", "800", "BANKROT"
	};

	word = randomWord(theme);
}