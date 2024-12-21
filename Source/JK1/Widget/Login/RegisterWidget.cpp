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

    // ���⿡ ���� ȸ������ ���� ����
    if (RegisterNewUser(InputID, InputPassword))
    {
        if (LoginWidget)
        {
            // �α��� ���� �ٽ� ���̰� �ϱ�
            LoginWidget->SetVisibility(ESlateVisibility::Visible);
        }
        // ������ �α��� ȭ������ ���ư���
        this->RemoveFromParent();  // ���� ���� ����
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
        // �α��� ���� �ٽ� ���̰� �ϱ�
        LoginWidget->SetVisibility(ESlateVisibility::Visible);
    }
    this->RemoveFromParent();  // ���� ���� ����
}

bool URegisterWidget::RegisterNewUser(FString InputID, FString InputPassword)
{
    return false;
}
