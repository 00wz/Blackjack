#include "Card.h"

ACard::ACard()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACard::InitializeCard(ERank InRank, ESuit InSuit)
{
    Rank = InRank;
    Suit = InSuit;
}

int32 ACard::GetValue() const
{
    switch (Rank)
    {
        case ERank::Two:    return 2;
        case ERank::Three:  return 3;
        case ERank::Four:   return 4;
        case ERank::Five:   return 5;
        case ERank::Six:    return 6;
        case ERank::Seven:  return 7;
        case ERank::Eight:  return 8;
        case ERank::Nine:   return 9;
        case ERank::Ten:
        case ERank::Jack:
        case ERank::Queen:
        case ERank::King:   return 10;
        case ERank::Ace:    return 11; // В простом варианте всегда 11
        default:            return 0;
    }
}
