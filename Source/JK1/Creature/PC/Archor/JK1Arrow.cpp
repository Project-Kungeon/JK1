// Copyright 2024 All Rights Reserved by J&K


#include "JK1Arrow.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AJK1Arrow::AJK1Arrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Objects
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	RootComponent = DefaultRootComponent;
	Arrow->SetupAttachment(DefaultRootComponent);
	Arrow->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	Arrow->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	Box->SetupAttachment(Arrow);
	Box->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	Box->SetRelativeRotation(FRotator(180.f, -90.f, 180.f));
	Box->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ParagonSparrow/FX/Meshes/Heroes/Sparrow/Abilities/SM_Sparrow_Arrow.SM_Sparrow_Arrow'"));
	if (ArrowMeshRef.Object)
	{
		Arrow->SetStaticMesh(ArrowMeshRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Primary/FX/P_Sparrow_HitHero.P_Sparrow_HitHero'"));
	if (ParticleRef.Object)
	{
		Particle = ParticleRef.Object;
	}

	ProjectileMovement->InitialSpeed = 6500.f;
	ProjectileMovement->MaxSpeed = 6500.f;

	Box->OnComponentBeginOverlap.AddDynamic(this, &AJK1Arrow::OnComponentOverlapBegin);

	this->InitialLifeSpan = 1.f;
}

// Called when the game starts or when spawned
void AJK1Arrow::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJK1Arrow::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Log, TEXT("other actor name is % s"), *OtherActor->GetActorNameOrLabel());
		ProjectileMovement->StopMovementImmediately();
		ProjectileMovement->ProjectileGravityScale = 0.f;

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, true);
		this->AttachToActor(OtherActor, AttachmentRules);
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Box->GetComponentLocation());

		//Hit Action In here
	}
}

// Called every frame
void AJK1Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

