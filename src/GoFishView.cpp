#include "GoFishView.h"
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

void GoFishView::showHand(Player* p) {
  std::cout << p->getName() << "'s hand" << std::endl;
  std::cout << *p << std::endl;
}

int GoFishView::showMenu() {
  int userChoice;

  do {
    std::cout <<
    "*************************Go Fish Menu*************************"
    << std::endl;
    std::cout << "1: Play Game" << std::endl;
    std::cout << "2: Help" << std::endl;
    std::cout << ">> ";
    std::cin >> userChoice;
    std::cin.clear();
    std::cin.ignore();
    if (!std::cin || !(userChoice == 1 || userChoice == 2)) {
      std::cout << "That was not a valid option. Please try again." <<
      std::endl;
    }
    std::cout <<
    "*************************Go Fish Menu*************************"
    << std::endl;
  } while (!std::cin || !(userChoice == 1 || userChoice == 2));

  return userChoice;
}

int GoFishView::howMany() {
  int num;

  do {
    std::cout << "How many players would you like for your game?" <<
    std::endl << "You can have 2, 3, 4, or 5 players in a game" << std::endl;
    std::cout << ">> ";
    std::cin >> num;
    std::cin.clear();
    std::cin.ignore();
    if (!std::cin || !(num == 2 || num == 3 || num == 4 || num == 5)) {
      std::cout << "That was not a valid option. Please try again." <<
      std::endl;
    }
  } while (!std::cin || !(num == 2 || num == 3 || num == 4 || num == 5));

  return num;
}

std::vector<std::string> GoFishView::playerNames(int howMany) {
  std::vector<std::string> names(howMany);
  int numComputerPlayers = howMany - 1;
  std::cout << "What is your name?" << std::endl;
  std::cout << ">> ";
  getline(std::cin, names[0]);
  for (unsigned int i = 1; i < names.size(); i++) {
    std::string cpuName = std::string("CPU #") + std::to_string(i);
    names[i] = cpuName;
  }

  return names;
}

unsigned int GoFishView::pickPlayerToAsk(unsigned int numPlayers) {
  for (int k = 1; k < numPlayers; k++) {
    std::cout << "CPU #" << k << ", ";
  }

  std::cout << std::endl;

  int choice;

  do {
    std::cout << "Who would you like to ask for a card (pick number of CPU)? "
    << std::endl;
    std::cout << ">> ";
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore();
    if (!std::cin || choice < 1 || choice >= numPlayers) {
      std::cout << "That was not a valid option. Please try again." <<
      std::endl;
    }
  } while (!std::cin || choice < 1 || choice >= numPlayers);

  return choice;
}

Card GoFishView::pickCard(Player* p) {
  showHand(p);
  int pick;
  do {
    std::cout << "Pick a card to ask for (pick by index 0 to numCards - 1)"
    << std::endl;
    std::cout << ">> ";
    std::cin >> pick;
    std::cin.clear();
    std::cin.ignore();
    if (!std::cin || pick < 0 || pick >= p->getSize()) {
      std::cout << "That was not a valid option. Please try again." <<
      std::endl;
    }
  } while (!std::cin || pick < 0 || pick >= p->getSize());

  return p->getCard(pick);
}

void GoFishView::playerGetsCard(const Card& card) {
  Card c = card;
  std::string cardString;
  cardString = c.rankToString(c.getRank()) + ':' + c.suitToString(c.getSuit());
  std::string msg = "You got a " + cardString + "!";
  std::cout << msg << std::endl;
}

void GoFishView::cpuGetsCard(const Card& card, unsigned int idx) {
  Card c = card;
  std::string cardString;
  cardString = c.rankToString(c.getRank()) + ':' + c.suitToString(c.getSuit());
  std::string msg = "CPU #" + std::to_string(idx) +
  " got a " + cardString + "!";
  std::cout << msg << std::endl;
}

void GoFishView::help() {
  std::ifstream fileIn;
  fileIn.open("./docs/help/GoFish.txt");
  std::string line;

  if (fileIn.is_open()) {
    std::getline(fileIn, line);
    std::cout << line << std::endl;
    while (!fileIn.eof()) {
      std::getline(fileIn, line);
      std::cout << line << std::endl;
    }
    fileIn.close();
  }
}

void GoFishView::simpleMessage(const std::string& msg) {
  std::cout << msg << std::endl;
}

void GoFishView::error(const std::string& err) {
  std::cerr << "ERROR: " << err << std::endl;
}
