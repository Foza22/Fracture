// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActorWithID.generated.h"

class UTextRenderComponent;
UCLASS()
class FRACTURED_API ABaseActorWithID : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseActorWithID();

	int32 GetUniqueID() const { return UniqueID; }
	void SetUniqueID(int32 ID);
	
	bool WantsToAssignID() const { return bAssignUniqueID; }

	void ActivateText() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Identification)
	bool bAssignUniqueID = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Identification,
		meta = (EditCondition = bAssignUniqueID, EditConditionHides))
	int32 UniqueID = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* ActorMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UTextRenderComponent* IDText;
};
