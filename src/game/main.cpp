#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "GoFishController.h"
#include "GoFishView.h"
#include "Player.h"

int main() {
  Deck* deck = new Deck();
  GoFishView* ui = new GoFishView();

  GoFishController* controller = new GoFishController(deck, ui);

  controller->init();

  controller->playGame();

  // this in turn deallocates memory from deck, players, and ui
  // as they were passed to GoFishController's constructor
  delete controller;

  return 0;
}
