#include <memory>
#include "Deck.h"
#include "gtest/gtest.h"

TEST(TestDeck, constructor) {
  std::unique_ptr<Deck> dptr(new Deck());

  EXPECT_EQ(Card(Card::Ace, Card::Spades), dptr->getCard(0));
  EXPECT_EQ(Card(Card::Jack, Card::Spades), dptr->getCard(10));
  EXPECT_EQ(Card(Card::Seven, Card::Clubs), dptr->getCard(19));
  EXPECT_EQ(Card(Card::King, Card::Hearts), dptr->getCard(38));
  EXPECT_EQ(Card(Card::Three, Card::Diamonds), dptr->getCard(41));
}

TEST(TestDeck, shuffle) {
  std::unique_ptr<Deck> dptr(new Deck());

  std::ofstream fileOut;
  fileOut.open("shuffle_deck_test.txt");

  if (fileOut.is_open()) {
    fileOut << "Deck Before Shuffling\n";
    fileOut << *dptr;
    dptr->shuffle();
    fileOut << "\nDeck After Shuffling\n";
    fileOut << *dptr;
    fileOut.close();
  }
}

TEST(TestDeck, removeCard) {
  std::unique_ptr<Deck> dptr(new Deck());
  std::unique_ptr<Deck> dptr2(new Deck());
  dptr2->removeCard(14);
  EXPECT_NE(dptr, dptr2);
}

TEST(TestDeck, size) {
  std::unique_ptr<Deck> dptr(new Deck());
  std::unique_ptr<Deck> dptr2(new Deck());

  EXPECT_EQ(*dptr, *dptr2);
  EXPECT_EQ(52, dptr->getSize());
  dptr->removeCard(0);
  EXPECT_NE(*dptr, *dptr2);
  EXPECT_EQ(51, dptr->getSize());
}
