#include "Widget/Lobby/JK1LobbyWidget.h"
#include "JK1LogChannels.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"

void UJK1LobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Character = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Character")));
	check(Btn_Character != nullptr);

	Btn_GameStart = Cast<UButton>(GetWidgetFromName(TEXT("Btn_GameStart")));
	check(Btn_GameStart != nullptr);

	BtnBox = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("BtnBox")));
	check(BtnBox != nullptr);

	IsOpen = false;
	TransferLevelName = FName(TEXT("L_Lobby"));
}

void UJK1LobbyWidget::CharacterChoice()
{
	UE_LOG(LogSystem, Log, TEXT("Open Character Widget"));
	index = -1;
	if (IsOpen == false)
	{
		Btn_GameStart->SetVisibility(ESlateVisibility::Visible);
		BtnBox->SetVisibility(ESlateVisibility::Visible);
		IsOpen = true;
	}
	else
	{
		Btn_GameStart->SetVisibility(ESlateVisibility::Hidden);
		BtnBox->SetVisibility(ESlateVisibility::Hidden);
		IsOpen = false;
	}
}

void UJK1LobbyWidget::GameStart()
{
	UE_LOG(LogSystem, Log, TEXT("Game Start"));
	// GameStart버튼을 눌렀을 때

	// 선택된 버튼에 따라 작업
	switch (index)
	{
	case 0:
		UE_LOG(LogSystem, Log, TEXT("Warrior"));
		// 매칭 패킷 전달
		MapChange();
		IsOpen = false;
		break;
	case 1:
		UE_LOG(LogSystem, Log, TEXT("Archor"));
		MapChange();
		IsOpen = false;
		break;
	case 2:
		UE_LOG(LogSystem, Log, TEXT("Assassin"));
		MapChange();
		IsOpen = false;
		break;
	default:
		UE_LOG(LogSystem, Log, TEXT("Game Start Error, Not Choice Character"));
		break;
	}
	

	if(IsOpen == false)
		WidgetClose();
}

void UJK1LobbyWidget::MapChange()
{
	// demoraid로 넘어가는 함수
	UGameplayStatics::OpenLevel(this, TransferLevelName);
}
