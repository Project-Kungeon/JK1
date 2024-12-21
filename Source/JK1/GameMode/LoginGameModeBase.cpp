// Copyright 2024 All Rights Reserved by J&K


#include "GameMode/LoginGameModeBase.h"

ALoginGameModeBase::ALoginGameModeBase()
{
}

void ALoginGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // �α��� ���� ���� �� ǥ��
    LoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
    if (LoginWidget)
    {
        LoginWidget->AddToViewport();

        // ���콺 Ŀ�� ǥ��
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            PC->SetShowMouseCursor(true);
            PC->SetInputMode(FInputModeUIOnly());
        }
    }
}
