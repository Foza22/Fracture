// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/IdentificationComponent.h"
#include "Components/TextRenderComponent.h"


// Sets default values for this component's properties
UIdentificationComponent::UIdentificationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	IDText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IDText"));
	IDText->SetVisibility(false);
}

// Called when the game starts
void UIdentificationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner()) return;

	const auto AimLocation = GetOwner()->GetActorLocation() + FVector{0.f, 30.f, 50.f};
	IDText->SetRelativeLocation(AimLocation);
}

void UIdentificationComponent::SetUniqueID(int32 ID)
{
	UniqueID = ID;
	ActivateText();
}

void UIdentificationComponent::ActivateText() const
{
	IDText->SetText(FText::AsNumber(UniqueID));
	IDText->SetVisibility(true);
}
