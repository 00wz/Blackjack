#include "BlackjackGameMode.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/InputSettings.h"

void ABlackjackGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Spawn deck
    Deck = GetWorld()->SpawnActor<ADeck>();
    StartNewGame();

    // Bind input
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        if (PC->InputComponent == nullptr)
        {
            PC->InputComponent = NewObject<UInputComponent>(PC);
            PC->InputComponent->RegisterComponent();
        }

        PC->InputComponent->BindAction("Hit", IE_Pressed, this, &ABlackjackGameMode::OnPlayerHit);
        PC->InputComponent->BindAction("Stand", IE_Pressed, this, &ABlackjackGameMode::OnPlayerStand);
        PC->bShowMouseCursor = true;
        PC->EnableInput(PC);
    }
}

void ABlackjackGameMode::StartNewGame()
{
    // Removing old cards from hands
    for (ACard* Card : PlayerHand)
    {
        if (IsValid(Card))
        {
            Card->Destroy();
        }
    }
    for (ACard* Card : DealerHand)
    {
        if (IsValid(Card))
        {
            Card->Destroy();
        }
    }
    PlayerHand.Empty();
    DealerHand.Empty();
    
    Deck->InitializeDeck();

    bIsPlayerTurn = true;

    DealerHand.Add(Deck->DrawCard());

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan,
            TEXT("Welcome to Blackjack!\nYour goal is to get as close to 21 as possible without going over.\nPress [H] to Hit (draw a card), or [S] to Stand.\nGood luck!"));
    }
}

void ABlackjackGameMode::ShowPlayerHand()
{
    int32 PlayerValue = GetHandValue(PlayerHand);

    FString HandStr = TEXT("Player hand: ");
    for (ACard* Card : PlayerHand)
    {
        HandStr += FString::Printf(TEXT("[%s of %s] "),
            *UEnum::GetDisplayValueAsText(Card->GetRank()).ToString(),
            *UEnum::GetDisplayValueAsText(Card->GetSuit()).ToString());
    }

    HandStr += FString::Printf(TEXT("= %d"), PlayerValue);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, HandStr);
    }
}

int32 ABlackjackGameMode::GetHandValue(const TArray<ACard*>& Hand) const
{
    int32 Value = 0;

    for (ACard* Card : Hand)
    {
        Value += Card->GetValue();
    }

    return Value;
}

void ABlackjackGameMode::OnPlayerHit()
{
    if (!bIsPlayerTurn)
        return;

    PlayerHand.Add(Deck->DrawCard());
    ShowPlayerHand();

    int32 PlayerValue = GetHandValue(PlayerHand);
    if (PlayerValue >= 21)
    {
        bIsPlayerTurn = false;
        if (PlayerValue == 21)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Blackjack! You win."));
            bIsPlayerTurn = false;
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Bust! You lose."));
            bIsPlayerTurn = false;
        }
        
        ScheduleNextRound();
    }
}

void ABlackjackGameMode::OnPlayerStand()
{
    if (!bIsPlayerTurn)
        return;

    bIsPlayerTurn = false;
    FinishDealerTurn();
}

void ABlackjackGameMode::FinishDealerTurn()
{
    int32 DealerValue = GetHandValue(DealerHand);
    while (DealerValue <= 16)
    {
        DealerHand.Add(Deck->DrawCard());
        DealerValue = GetHandValue(DealerHand);
    }

    int32 PlayerValue = GetHandValue(PlayerHand);

    FString Result;
    if (DealerValue > 21 || PlayerValue > DealerValue)
    {
        Result = TEXT("You win!");
    }
    else if (PlayerValue < DealerValue)
    {
        Result = TEXT("Dealer wins!");
    }
    else
    {
        Result = TEXT("It's a draw!");
    }

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
        FString::Printf(TEXT("Dealer: %d, Player: %d => %s"), DealerValue, PlayerValue, *Result));

    ScheduleNextRound();
}

void ABlackjackGameMode::ScheduleNextRound()
{
    FTimerHandle RestartTimer;
    GetWorld()->GetTimerManager().SetTimer(RestartTimer, this, &ABlackjackGameMode::StartNewGame, 5.0f, false);
}
