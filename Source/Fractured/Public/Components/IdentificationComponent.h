// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IdentificationComponent.generated.h"


class UTextRenderComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRACTURED_API UIdentificationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIdentificationComponent();

	int32 GetUniqueID() const { return UniqueID; }
	void SetUniqueID(int32 ID);
	
	bool WantsToAssignID() const { return bAssignUniqueID; }

	void ActivateText() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Identification)
	bool bAssignUniqueID = true;

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Identification,
	// 	meta = (EditCondition = bAssignUniqueID, EditConditionHides))
	int32 UniqueID = -1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UTextRenderComponent* IDText;
		
};
