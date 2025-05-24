#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERank.h"
#include "ESuit.h"
#include "Card.generated.h"

/**
 * ACard represents a single playing card with a rank and suit.
 */
UCLASS()
class ACard : public AActor
{
	GENERATED_BODY()

public:
	/** Default constructor */
	ACard();

	/** Returns the rank of the card */
	ERank GetRank() const{ return Rank; }

	/** Returns the suit of the card */
	ESuit GetSuit() const { return Suit; }

	/**
	 * Returns the value of the card for blackjack.
	 * Ace counts as 11 in basic version.
	 */
	int32 GetValue() const;

	/** Initializes card with rank and suit */
	void InitializeCard(ERank InRank, ESuit InSuit);

protected:
	/** Card rank (Two through Ace) */
	UPROPERTY()
	ERank Rank;

	/** Card suit (Clubs, Diamonds, Hearts, Spades) */
	UPROPERTY()
	ESuit Suit;
};
