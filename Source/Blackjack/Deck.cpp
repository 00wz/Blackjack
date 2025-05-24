#include "Deck.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

ADeck::ADeck()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADeck::InitializeDeck()
{
    CleanDeck();
    
    for (int32 SuitIndex = 0; SuitIndex < 4; ++SuitIndex)
    {
        for (int32 RankIndex = 0; RankIndex < 13; ++RankIndex)
        {
            ACard* NewCard = GetWorld()->SpawnActor<ACard>();
            NewCard->InitializeCard(static_cast<ERank>(RankIndex), static_cast<ESuit>(SuitIndex));
            Cards.Add(NewCard);
        }
    }

    ShuffleDeck();
}

void ADeck::ShuffleDeck()
{
    for (int32 i = 0; i < Cards.Num(); i++)
    {
        int32 SwapIdx = UKismetMathLibrary::RandomIntegerInRange(0, Cards.Num() - 1);
        Cards.Swap(i, SwapIdx);
    }
}

ACard* ADeck::DrawCard()
{
    if (Cards.Num() == 0)
        return nullptr;

    ACard* TopCard = Cards.Pop();
    return TopCard;
}

void ADeck::CleanDeck()
{
    for(ACard* Card : Cards)
    {
        if(IsValid(Card))
        {
            GetWorld()->DestroyActor(Card);
        }
    }
    
    Cards.Empty();
}
