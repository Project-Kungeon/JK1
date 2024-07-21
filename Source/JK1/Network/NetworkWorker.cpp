// Copyright 2024 All Rights Reserved by J&K


#include "NetworkWorker.h"
using work_guard_type = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;

NetworkWorker::NetworkWorker(TSharedPtr<asio::io_context> io_context, TSharedPtr<PacketSession> Session)
	: SessionRef(Session)
{
	Thread = FRunnableThread::Create(this, TEXT("NetworkWorker"));
}

NetworkWorker::NetworkWorker(TSharedPtr<PacketSession> Session)
	: SessionRef(Session)
{
	Thread = FRunnableThread::Create(this, TEXT("NetworkWorker"));
}

NetworkWorker::~NetworkWorker()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("~NetworkWorker()")));
}

bool NetworkWorker::Init()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Network Thread Init")));

	return true;
}

uint32 NetworkWorker::Run()
{
	try
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Network Thread Running")));
		if (TSharedPtr<PacketSession> Session = SessionRef.Pin())
		{
			//Session->GetIoContext().Pin()->run();
			work_guard_type work_guard(Session->GetIOContext().get_executor());
			Session->GetIOContext().run();
		}

		//io_contextRef->run();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Network Thread Done")));
	}
	catch (const std::exception& e)
	{
		FString formattedString = FString::Printf(TEXT("%s"), *FString(UTF8_TO_TCHAR(e.what())));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *formattedString);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, formattedString);
	}
	return 0;
}

void NetworkWorker::Exit()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Network Thread Exited")));
}

void NetworkWorker::Stop()
{
}

void NetworkWorker::Destroy()
{
	Running = false;
	Thread->Kill();
	//if ( TSharedPtr<PacketSession> Session = SessionRef.Pin() )
	//{
	//	Session->GetIoContext().Pin()->stop();
	//}
}