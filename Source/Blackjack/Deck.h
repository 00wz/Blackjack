#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "Deck.generated.h"

/**
 * ADeck represents a standard 52-card playing deck.
 */
UCLASS()
class ADeck : public AActor
{
	GENERATED_BODY()

public:
	/** Default constructor */
	ADeck();

	/** Initializes the deck with 52 unique cards */
	void InitializeDeck();

	/** Shuffles the deck using random swap algorithm */
	void ShuffleDeck();

	/** Draws the top card from the deck */
	ACard* DrawCard();

	/** Remove all cards from the deck */
	void CleanDeck();

protected:
	/** Array of cards currently in the deck */
	UPROPERTY()
	TArray<ACard*> Cards;
};
