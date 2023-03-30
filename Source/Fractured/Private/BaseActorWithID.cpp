// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActorWithID.h"
#include "IDManager.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseActorWithID::ABaseActorWithID()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	SetRootComponent(ActorMesh);

	IDText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IDText"));
	IDText->SetupAttachment(RootComponent);
	IDText->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABaseActorWithID::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseActorWithID::SetUniqueID(int32 ID)
{
	UniqueID = ID;
	ActivateText();
}

void ABaseActorWithID::ActivateText() const
{
	IDText->SetText(FText::AsNumber(UniqueID));
	IDText->SetVisibility(true);
}
