#pragma once

#include "ESuit.generated.h"

/**
 * Enum representing the four suits in a standard French playing card deck.
 */
UENUM(BlueprintType)
enum class ESuit : uint8
{
	Clubs      UMETA(DisplayName = "Clubs"),
	Diamonds   UMETA(DisplayName = "Diamonds"),
	Hearts     UMETA(DisplayName = "Hearts"),
	Spades     UMETA(DisplayName = "Spades")
};
