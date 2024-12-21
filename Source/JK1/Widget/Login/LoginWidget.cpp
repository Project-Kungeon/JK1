// Copyright 2024 All Rights Reserved by J&K


#include "Widget/Login/LoginWidget.h"
#include "RegisterWidget.h"
#include <Kismet/GameplayStatics.h>

void ULoginWidget::OnLoginButtonClicked()
{
    FString InputID = IDEditableText->GetText().ToString();
    FString InputPassword = PasswordEditableText->GetText().ToString();

    // ���⼭ ���� ���� ��� �� ������ �̷������ �մϴ�
    if (ValidateLoginInfo(InputID, InputPassword))
    {
        // �α��� ����
        UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
    }
    else
    {
        // �α��� ����
        ErrorMessageText->SetVisibility(ESlateVisibility::Visible);
        ErrorMessageText->SetText(FText::FromString("Invalid ID or Password"));
    }
}

void ULoginWidget::OnRegisterButtonClicked()
{
    if (RegisterWidgetClass)
    {
        // Register ���� ���� �� ǥ��
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
    // TODO ���⼭ ���� ��û�ؾ� 
	return false;
}
