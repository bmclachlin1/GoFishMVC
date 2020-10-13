#include "GoFishController.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

GoFishController::GoFishController(Deck* deck, GoFishView* ui) {
  this->deck = deck;
  this->ui = ui;
}

GoFishController::~GoFishController() {
  delete deck;
  delete ui;
  for (Player* p : players)
    delete p;
}

void GoFishController::init() {
  int choice;
  do {
    // get users selection
    choice = ui->showMenu();

    // user initiates new game
    if (choice == 1) {
      // get the number of players from user
      int numPlayers = ui->howMany();
      // get the names of the players
      std::vector<std::string> names = ui->playerNames(numPlayers);
      // create new players and assign to vector
      for (std::string s : names) {
        players.push_back(new Player(s));
      }
      // deal the cards
      this->dealCards();
    } else if (choice == 2) {
      // show help menu
      ui->help();
    }
  } while (choice == 2);
}

void GoFishController::displayHand(int which) {
  if (which >= 0 && which < players.size()) {
    ui->showHand(players[which]);
  } else {
    std::string err =
    std::string("Player \"") +
    std::to_string(which) +
    std::string("\" is not a valid option");
    ui->error(err);
  }
}

void GoFishController::dealCards() {
  // shuffle the deck
  deck->shuffle();

  // get amount of players
  size_t plen = players.size();

  // if 2 or 3 players, deal 7 cards to each player
  // if 4 or 5 players, deal 5 cards to each player
  if (plen == 2 || plen == 3) {
    for (unsigned int i = 0; i < plen; i++)
      for (unsigned int j = 0; j < 7; j++) {
        Card c = deck->getCard(deck->getSize() - 1);
        players[i]->addCard(c);
        deck->removeCard(deck->getSize() - 1);
      }
  } else if (plen == 4 || plen == 5) {
      for (unsigned int i = 0; i < plen; i++)
        for (unsigned int j = 0; j < 5; j++) {
          Card c = deck->getCard(deck->getSize() - 1);
          players[i]->addCard(c);
          deck->removeCard(deck->getSize() - 1);
        }
    }
}

void GoFishController::playGame() {
  int whosTurn = 0;

  while (!endGame()) {
    whosTurn = (whosTurn + 1) % players.size();
    if (whosTurn == 0) {
      playTurn();
    } else {
      computerTurn(whosTurn);
    }
  }
}

void GoFishController::playTurn() {
  ui->simpleMessage(std::string(""));
  std::string str1 = players[0]->getName() + "\'s Turn.";
  std::string str2 = "Number of 4-of-a-kinds: " +
  std::to_string(players[0]->getBooks());
  ui->simpleMessage(str1);
  ui->simpleMessage(str2);

  // only ask for card if you have card in your hand
  if (players[0]->getSize() > 0) {
    // ask opponent for card
    unsigned int choice = ui->pickPlayerToAsk(players.size());
    Card picked = ui->pickCard(players[0]);
    bool found = findMatch(picked, choice);

    // continue asking for cards while card of same rank exists in
    // opposing player's hand
    while (found) {
      Card c;
      int foundAt;

      // check if card of same rank exists
      for (unsigned int i = 0; i < players[choice]->getSize(); i++) {
        if (players[choice]->getCard(i).getRank() == picked.getRank()) {
          c = players[choice]->getCard(i);
          foundAt = i;
          break;
        }
      }

      // add card to your hand and remove card from opponents hand
      players[0]->addCard(c);
      players[choice]->removeCard(foundAt);
      ui->playerGetsCard(c);

      // check for four of a kind
      if (players[0]->checkForBook(c)) {
        ui->simpleMessage("You got a four of a kind!");
        // if end game, display winner and quit the program
        if (endGame()) {
          displayWinner();
          return;
        }
      }

      // only ask for card if you have card in your hand
      if (players[0]->getSize() > 0) {
        // ask again
        choice = ui->pickPlayerToAsk(players.size());
        picked = ui->pickCard(players[0]);
        found = findMatch(picked, choice);
      } else {
        found = false;
      }
    }
  }

  // if the card we asked for was not in their hand, we draw from the deck
  ui->simpleMessage("Go Fish!");

  // Make sure the deck is not empty before drawing from deck
  if (deck->getSize() > 0) {
    // add card to your hand and remove it from deck
    Card newCard = deck->getCard(deck->getSize() - 1);
    players[0]->addCard(newCard);
    deck->removeCard(deck->getSize() - 1);

    ui->playerGetsCard(newCard);

    if (players[0]->checkForBook(newCard)) {
      ui->simpleMessage("You got a four of a kind!");
      // if end game, display winner and quit program
      if (endGame()) {
        displayWinner();
        return;
      }
    }
  } else  {
    ui->simpleMessage("The deck is empty!");
  }
}

void GoFishController::computerTurn(unsigned int idx) {
  ui->simpleMessage(std::string(""));
  std::string str1 = "CPU #" + std::to_string(idx) + "\'s Turn.";
  std::string str2 = "Number of 4-of-a-kinds: " +
  std::to_string(players[idx]->getBooks());
  ui->simpleMessage(str1);
  ui->simpleMessage(str2);

  if (players[idx]->getSize() > 0) {
    // generate random seed
    srand(time(NULL));
    // pick player to ask for in players vector
    unsigned int choice;
    do {
      choice = std::rand() % players.size();
    } while (choice == idx);

    // pick card to ask for
    unsigned int size = players[idx]->getSize();
    unsigned int pick = std::rand() % size;
    Card picked = players[idx]->getCard(pick);
    std::string first = "Asking player " + std::to_string(choice) + " for a ";
    std::string second = picked.rankToString(picked.getRank());
    std::string ask = first + second;
    ui->simpleMessage(ask);

    bool found = findMatch(picked, choice);

    // continue asking while card exists
    while (found) {
      Card c;
      int foundAt;

      // check if card of same rank exists
      for (unsigned int i = 0; i < players[choice]->getSize(); i++) {
        if (players[choice]->getCard(i).getRank() == picked.getRank()) {
          c = players[choice]->getCard(i);
          foundAt = i;
          break;
        }
      }

      // add card to your hand and remove card from opponents hand
      players[idx]->addCard(c);
      players[choice]->removeCard(foundAt);
      ui->cpuGetsCard(c, idx);

      // check for four of a kind
      if (players[idx]->checkForBook(c)) {
        std::string msg = "CPU #" + std::to_string(idx) +
        " got a four of a kind!";
        ui->simpleMessage(msg);
        // if end game, display winner and quit the program
        if (endGame()) {
          displayWinner();
          return;
        }
      }

      if (players[idx]->getSize() > 0) {
        // ask again
        do {
          choice = std::rand() % players.size();
        } while (choice == idx);

        // pick card to ask for
        size = players[idx]->getSize();
        pick = std::rand() % size;
        picked = players[idx]->getCard(pick);

        first = "Asking player " + std::to_string(choice) + " for a ";
        second = picked.rankToString(picked.getRank());
        ask = first + second;
        ui->simpleMessage(ask);

        found = findMatch(picked, choice);
      } else {
        found = false;
      }
    }
  }

  // go Fish
  ui->simpleMessage("Go Fish!");

  // Make sure the deck is not empty before drawing from deck
  if (deck->getSize() > 0) {
    // add card to your hand and remove it from deck
    Card newCard = deck->getCard(deck->getSize() - 1);
    players[idx]->addCard(newCard);
    deck->removeCard(deck->getSize() - 1);

    ui->cpuGetsCard(newCard, idx);

    if (players[idx]->checkForBook(newCard)) {
      std::string msg = "CPU #" + std::to_string(idx) +
      " got a four of a kind!";
      ui->simpleMessage(msg);
      // if end game, display winner and quit program
      if (endGame()) {
        displayWinner();
        return;
      }
    }
  } else  {
    ui->simpleMessage("The deck is empty!");
  }
}

bool GoFishController::findMatch(const Card& c, unsigned int idx) {
  for (unsigned int i = 0; i < players[idx]->getSize(); i++) {
    if (players[idx]->getCard(i).getRank() == c.getRank()) {
      return true;
    }
  }

  return false;
}

bool GoFishController::endGame() {
  int sum = 0;
  for (Player* p : players) {
    sum += p->getBooks();
  }

  return sum == 13;
}

void GoFishController::displayWinner() {
  unsigned int max = 0;
  std::string msg;
  for (Player* p : players) {
    if (p->getBooks() > max) {
      max = p->getBooks();
      msg = p->getName() + " Wins!!!";
    }
  }
  ui->simpleMessage(msg);
}

size_t GoFishController::numPlayers() const {
  return players.size();
}
