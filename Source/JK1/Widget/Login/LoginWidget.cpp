// Copyright 2024 All Rights Reserved by J&K


#include "Widget/Login/LoginWidget.h"
#include "RegisterWidget.h"
#include <Kismet/GameplayStatics.h>

void ULoginWidget::OnLoginButtonClicked()
{
    FString InputID = IDEditableText->GetText().ToString();
    FString InputPassword = PasswordEditableText->GetText().ToString();

    // 여기서 실제 서버 통신 및 검증이 이루어져야 합니다
    if (ValidateLoginInfo(InputID, InputPassword))
    {
        // 로그인 성공
        UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
    }
    else
    {
        // 로그인 실패
        ErrorMessageText->SetVisibility(ESlateVisibility::Visible);
        ErrorMessageText->SetText(FText::FromString("Invalid ID or Password"));
    }
}

void ULoginWidget::OnRegisterButtonClicked()
{
    if (RegisterWidgetClass)
    {
        // Register 위젯 생성 및 표시
        URegisterWidget* RegisterWidget = CreateWidget<URegisterWidget>(GetWorld(), RegisterWidgetClass);
        if (RegisterWidget)
        {
            this->SetVisibility(ESlateVisibility::Hidden);
            RegisterWidget->AddToViewport();
            RegisterWidget->SetLoginWidget(this);
        }
    }
}

bool ULoginWidget::ValidateLoginInfo(const FString& ID, const FString& Password)
{
    // TODO 여기서 인증 요청해야 
	return false;
}
