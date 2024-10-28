# Wheel of fortune (ASCII)

The Wheel of Fortune ASCII project brings a classic game to the command line, allowing players of all ages to experience the excitement of spinning the wheel and solving puzzles in a nostalgic, text-based format. This engaging game combines strategy, luck, and wordplay, making it a perfect pastime for friends and family gatherings or solo play.


## Instalation

### Prerequisitories

* git tools (git bash)


### Installation Instructions

Installation is possible via a .zip file; further instructions are provided for installation using the git command.

##### Using Git

1. Open Bash and connect to the project's HTTPS repository with the command:

   ```bash
   git clone https://gitlab.com/group_19351201/Wheel_of_fortune_ASCII.git


2. Navigate to the folder:

   ```bash
    Wheel_of_fortune_ASCII/Wheel_of_fortuneSetup/Debug


3. Double-click on `setup.exe` to start the installation process automatically. Make sure to accept all options.


## Rules

One game consists of three rounds, played by four players. The current player spins the wheel and plays for the obtained value (value features). The player can enter a letter or a whole word.

### Game Mechanics

- If the letter exists in the phrase, it will appear in the corresponding places, and the player is awarded a value multiplied by the number of matched places. The turn goes to the next player.
- If the player has a joker, they can choose a vowel, which costs one joker.
- If the player guesses the phrase correctly, their value is multiplied by 10, and the turn goes to the next player.

- If the letter does not exist or the phrase is incorrect, the player loses their turn.
- Players try to guess the phrase, and the winner is the one with the most points at the end of three rounds.

### Value Features

Below is a brief explanation of the possible values on the wheel and their actions:

- **BANKRUPT** -> The player loses their turn. If the player has a joker and wants to use it, they spin the wheel again and lose one joker.
- **Number** -> The player plays for the value of the number.
- **JOKER** -> The player’s number of jokers increases, and they spin again.



## Authors
#### Marko25043
#### TomaPeran


## Improvements
There is a lot of elementary stuff in the begining of this document, but all of those components are what it takes to make a student management system. Down here are just some ideas that will make this application become better and more appealing.

#### Visual Improvements
- [ ] Ascii art and sound effects
- [ ] Center Render Animation (recomended library `fmtlib`)

#### Developer Improvements
- [ ] Add an option for more/fewer players