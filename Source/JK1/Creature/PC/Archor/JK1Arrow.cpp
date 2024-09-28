// Copyright 2024 All Rights Reserved by J&K


#include "JK1Arrow.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "JK1//Creature/PC/JK1PlayerCharacter.h"
#include "JK1/Physics/JK1Collision.h"

// Sets default values
/*-------------------------
* 현재 화살이 폰 캡슐의 밑부분에 닿으면 폰이 날라가는 버그가 있음.
-------------------------*/

AJK1Arrow::AJK1Arrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Objects
	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	CollisionComponent = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("CollisionComponent"));

	//Set Arrow Location
	RootComponent = DefaultRootComponent;
	Arrow->SetupAttachment(DefaultRootComponent);
	Arrow->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	Arrow->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	//Set Arrow HitBox
	Box->SetupAttachment(Arrow);
	Box->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	Box->SetRelativeRotation(FRotator(180.f, -90.f, 180.f));
	Box->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	


	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ParagonSparrow/FX/Meshes/Heroes/Sparrow/Abilities/SM_Sparrow_Arrow.SM_Sparrow_Arrow'"));
	if (ArrowMeshRef.Object)
	{
		Arrow->SetStaticMesh(ArrowMeshRef.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Primary/FX/P_Sparrow_Primary_Ballistic_HitPlayer.P_Sparrow_Primary_Ballistic_HitPlayer'"));
	if (ParticleRef.Object)
	{
		Particle = ParticleRef.Object;
	}

	ProjectileMovement->InitialSpeed = 6500.f;
	ProjectileMovement->MaxSpeed = 6500.f;

	Box->OnComponentBeginOverlap.AddDynamic(this, &AJK1Arrow::OnComponentOverlapBegin);

	this->InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AJK1Arrow::BeginPlay()
{
	Super::BeginPlay();
}

void AJK1Arrow::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* MyCharacter = Cast<ACharacter>(OtherActor);
	if (MyCharacter && MyCharacter->GetClass()->IsChildOf(AJK1PlayerCharacter::StaticClass()))
	{
		UE_LOG(LogArrow, Log, TEXT("Overlapped with Jk1Character"));
	}

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

void AJK1Arrow::PlaySkillQParticleEffect()
{
}

// Called every frame
void AJK1Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

