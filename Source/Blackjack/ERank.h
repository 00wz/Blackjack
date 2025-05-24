#pragma once

#include "ERank.generated.h"

/**
 * Enum representing the thirteen ranks in a standard French playing card deck.
 */
UENUM(BlueprintType)
enum class ERank : uint8
{
	Two     UMETA(DisplayName = "2"),
	Three   UMETA(DisplayName = "3"),
	Four    UMETA(DisplayName = "4"),
	Five    UMETA(DisplayName = "5"),
	Six     UMETA(DisplayName = "6"),
	Seven   UMETA(DisplayName = "7"),
	Eight   UMETA(DisplayName = "8"),
	Nine    UMETA(DisplayName = "9"),
	Ten     UMETA(DisplayName = "10"),
	Jack    UMETA(DisplayName = "Jack"),
	Queen   UMETA(DisplayName = "Queen"),
	King    UMETA(DisplayName = "King"),
	Ace     UMETA(DisplayName = "Ace")
};
