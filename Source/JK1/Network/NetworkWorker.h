// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "JK1.h"
#include "CoreMinimal.h"

/**
 * 
 */
class JK1_API NetworkWorker : public FRunnable
{
public:
	NetworkWorker(TSharedPtr<asio::io_context> io_context, TSharedPtr<PacketSession> Session);
	NetworkWorker(TSharedPtr<PacketSession> Session);

	~NetworkWorker();

	// 가상함수 (Override)
	virtual bool Init() override;	// 스레드 시작
	virtual uint32 Run() override;	// 스레드 실행
	virtual void Exit() override;	// 스레드 실행 끝
	virtual void Stop() override;	// 스레드 정지

	void Destroy();

private:

protected:
	// 스레드 관련 멤버
	FRunnableThread* Thread = nullptr;
	bool Running = true;

	// 소켓 & 세션 멤버 
	TWeakPtr<class PacketSession> SessionRef;

};
