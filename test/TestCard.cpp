#include <memory>
#include <string>
#include "Card.h"
#include "gtest/gtest.h"

TEST(TestCard, constructor) {
  std::unique_ptr<Card> cptr(new Card(Card::Ace, Card::Clubs));

  EXPECT_EQ(Card::Ace, cptr->getRank());
  EXPECT_EQ(Card::Clubs, cptr->getSuit());
}

TEST(TestCard, setMethods) {
  std::unique_ptr<Card> cptr(new Card(Card::Eight, Card::Spades));

  EXPECT_EQ(Card::Eight, cptr->getRank());
  EXPECT_EQ(Card::Spades, cptr->getSuit());

  cptr->setRank(Card::Two);
  cptr->setSuit(Card::Hearts);

  EXPECT_EQ(Card::Two, cptr->getRank());
  EXPECT_EQ(Card::Hearts, cptr->getSuit());
}

TEST(TestCard, stringMethods) {
  std::unique_ptr<Card> cptr(new Card(Card::Two, Card::Diamonds));

  std::string rank = cptr->rankToString(cptr->getRank());
  std::string suit = cptr->suitToString(cptr->getSuit());

  EXPECT_NE(std::string("Two"), rank);
  EXPECT_EQ(std::string("2"), rank);
  EXPECT_EQ(std::string("Diamonds"), suit);
}
