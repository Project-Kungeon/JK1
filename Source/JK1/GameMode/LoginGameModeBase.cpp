// Copyright 2024 All Rights Reserved by J&K


#include "GameMode/LoginGameModeBase.h"

ALoginGameModeBase::ALoginGameModeBase()
{
}

void ALoginGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // 로그인 위젯 생성 및 표시
    LoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
    if (LoginWidget)
    {
        LoginWidget->AddToViewport();

        // 마우스 커서 표시
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            PC->SetShowMouseCursor(true);
            PC->SetInputMode(FInputModeUIOnly());
        }
    }
}
