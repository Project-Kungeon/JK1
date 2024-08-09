// Copyright 2024 All Rights Reserved by J&K


#include "JK1Dagger.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AJK1Dagger::AJK1Dagger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create Objects
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	Dagger = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dagger"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	RootComponent = DefaultRootComponent;
	Dagger->SetupAttachment(DefaultRootComponent);

	Box->SetupAttachment(Dagger);
	Box->SetRelativeScale3D(FVector(0.55f, 0.1f, 0.1f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DaggerMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ParagonKallari/FX/Meshes/Materials/Kallari/SM_Kallari_Dagger_Glow.SM_Kallari_Dagger_Glow'"));
	if (DaggerMeshRef.Object)
	{
		Dagger->SetStaticMesh(DaggerMeshRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonKallari/FX/Particles/Kallari/Abilities/DaggerThrow/FX/P_Kallari_DaggerThrow_HitPlayer.P_Kallari_DaggerThrow_HitPlayer'"));
	if (ParticleRef.Object)
	{
		Particle = ParticleRef.Object;
	}

	ProjectileMovement->InitialSpeed = 6500.f;
	ProjectileMovement->MaxSpeed = 6500.f;

	Box->OnComponentBeginOverlap.AddDynamic(this, &AJK1Dagger::OnComponentOverlapBegin);

	// Actor의 LifeTime을 제어하는 변수
	this->InitialLifeSpan = 5.f;

}

// Called when the game starts or when spawned
void AJK1Dagger::BeginPlay()
{
	Super::BeginPlay();
}

void AJK1Dagger::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		UE_LOG(LogTemp, Log, TEXT("other actor name is % s"), *OtherActor->GetActorNameOrLabel());

		ProjectileMovement->StopMovementImmediately();
		ProjectileMovement->ProjectileGravityScale = 0.f;

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, true);
		this->AttachToActor(OtherActor, AttachmentRules);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Box->GetComponentLocation());

		//Hit Action In here
	}
}

// Called every frame
void AJK1Dagger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

