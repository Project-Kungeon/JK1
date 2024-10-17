// Copyright 2024 All Rights Reserved by J&K


#include "Widget/Lobby/JK1MatchingWidget.h"
#include "Widget/Lobby/JK1WaitMatchingWidget.h"
#include "Widget/Lobby/JK1AcceptMatchingWidget.h"
#include "Components/Button.h"

void UJK1MatchingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnMatchingUpdate.BindUObject(this, &UJK1MatchingWidget::UpdateAcceptWidget);
}

void UJK1MatchingWidget::StartMatching()
{
	//  매칭 시작 버튼을 눌렀을 때
	WBP_WaitMatching->SetVisibility(ESlateVisibility::Visible);

	// 매칭 시작 패킷 전달
	
}

void UJK1MatchingWidget::TryMatching()
{
	// 매칭  시 델리게이트를 통해 불려지는 함수
	WBP_WaitMatching->MatchingComplete();								// loading ui off
	WBP_AcceptMatching->SetVisibility(ESlateVisibility::Visible);		// accept ui on
}

void UJK1MatchingWidget::UpdateAcceptWidget(bool IsAccpet)
{
	// 다른 인원의 수락 여부 패킷을 받아 ui를 갱신해야 할때
	// delegate를 통해 불려짐
	WBP_AcceptMatching->ResultMatching(IsAccpet);
}

void UJK1MatchingWidget::MatchingFail()
{
	WBP_AcceptMatching->SetVisibility(ESlateVisibility::Hidden);
	WBP_AcceptMatching->InitWidget();
}
