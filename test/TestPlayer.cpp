#include <memory>
#include "Player.h"
#include "gtest/gtest.h"

TEST(TestPlayer, constructor) {
  std::unique_ptr<Player> player(new Player("Batman"));

  EXPECT_EQ("Batman", player->getName());
  EXPECT_NE("Joker", player->getName());
}

TEST(TestPlayer, addCard) {
  std::unique_ptr<Player> player(new Player("Spiderman"));

  EXPECT_EQ("Spiderman", player->getName());

  player->addCard(Card(Card::Queen, Card::Diamonds));
  EXPECT_EQ(Card(Card::Queen, Card::Diamonds), player->getCard(0));
}

TEST(TestPlayer, removeCard) {
  std::unique_ptr<Player> player(new Player("Spiderman"));

  player->addCard(Card(Card::Queen, Card::Spades));
  EXPECT_EQ(1, player->getSize());
  player->removeCard(0);
  EXPECT_EQ(0, player->getSize());
}

TEST(TestPlayer, sortHand) {
  std::unique_ptr<Player> player(new Player("Spiderman"));
  player->sortHand();
}

TEST(TestPlayer, checkForBook) {
  std::unique_ptr<Player> player(new Player("Spiderman"));

  EXPECT_EQ(0, player->getBooks());
  EXPECT_FALSE(player->checkForBook(Card(Card::Jack, Card::Spades)));

  player->addCard(Card(Card::Jack, Card::Spades));
  player->addCard(Card(Card::Jack, Card::Clubs));
  player->addCard(Card(Card::Jack, Card::Hearts));
  player->addCard(Card(Card::Jack, Card::Diamonds));

  EXPECT_TRUE(player->checkForBook(Card(Card::Jack, Card::Spades)));
  EXPECT_EQ(1, player->getBooks());
}
