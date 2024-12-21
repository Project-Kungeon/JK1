// Copyright 2024 All Rights Reserved by J&K


#include "Widget/Login/RegisterWidget.h"
#include "LoginWidget.h"

void URegisterWidget::OnRegisterButtonClicked()
{
    FString InputID = IDEditableText->GetText().ToString();
    FString InputPassword = PasswordEditableText->GetText().ToString();
    FString ConfirmPassword = ConfirmPasswordEditableText->GetText().ToString();

    if (InputPassword != ConfirmPassword)
    {
        ErrorMessageText->SetVisibility(ESlateVisibility::Visible);
        ErrorMessageText->SetText(FText::FromString("Passwords do not match"));
        return;
    }

    // 여기에 실제 회원가입 로직 구현
    if (RegisterNewUser(InputID, InputPassword))
    {
        if (LoginWidget)
        {
            // 로그인 위젯 다시 보이게 하기
            LoginWidget->SetVisibility(ESlateVisibility::Visible);
        }
        // 성공시 로그인 화면으로 돌아가기
        this->RemoveFromParent();  // 현재 위젯 제거
    }
    else
    {
        ErrorMessageText->SetVisibility(ESlateVisibility::Visible);
        ErrorMessageText->SetText(FText::FromString("Registration failed"));
    }
}

void URegisterWidget::OnBackButtonClicked()
{
    if (LoginWidget)
    {
        // 로그인 위젯 다시 보이게 하기
        LoginWidget->SetVisibility(ESlateVisibility::Visible);
    }
    this->RemoveFromParent();  // 현재 위젯 제거
}

bool URegisterWidget::RegisterNewUser(FString InputID, FString InputPassword)
{
    return false;
}
