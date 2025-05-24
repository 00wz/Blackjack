#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Deck.h"
#include "Card.h"
#include "BlackjackGameMode.generated.h"

/**
 * ABlackjackGameMode implements interactive blackjack logic for a single player vs dealer.
 */
UCLASS()
class ABlackjackGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	/** Called when the player presses H (Hit) */
	void OnPlayerHit();

	/** Called when the player presses S (Stand) */
	void OnPlayerStand();

protected:
	UPROPERTY()
	ADeck* Deck;

	UPROPERTY()
	TArray<ACard*> PlayerHand;

	UPROPERTY()
	TArray<ACard*> DealerHand;

	bool bIsPlayerTurn;

	/** Shows hand and value in console and screen */
	void ShowPlayerHand();

	/** Calculates total hand value with ace logic */
	int32 GetHandValue(const TArray<ACard*>& Hand) const;

	/** Continues dealer logic and prints result */
	void FinishDealerTurn();

	/** Starts a new round */
	void StartNewGame();

	/** Schedules the next round to start after a short delay */
	void ScheduleNextRound();
};
