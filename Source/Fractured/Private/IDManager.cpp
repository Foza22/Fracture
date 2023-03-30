// Fill out your copyright notice in the Description page of Project Settings.


#include "IDManager.h"
#include "BaseActorWithID.h"
#include "JsonObjectConverter.h"
#include "Components/IdentificationComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIDManager::AIDManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AIDManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), OutActors);
	for (const auto Actor : OutActors)
	{
		const auto IdentificationComponent = Cast<UIdentificationComponent>(Actor->GetComponentByClass(UIdentificationComponent::StaticClass()));
		if (!IdentificationComponent || !IdentificationComponent->WantsToAssignID()) continue;

		TaggedActors.Emplace(Actor);
	}

	LoadFromJson();

	for (const auto Actor : TaggedActors)
	{
		const auto IdentificationComponent = Cast<UIdentificationComponent>(Actor->GetComponentByClass(UIdentificationComponent::StaticClass()));
		
		if (IdentificationComponent->GetUniqueID() == -1)
		{
			IdentificationComponent->SetUniqueID(GenerateID(Actor));
		}
	}

	SaveToJson();
}

int32 AIDManager::GenerateID(AActor* AimActor)
{
	int32 NewID = 0;
	bool bUniqueID = false;

	while (!bUniqueID)
	{
		NewID = FMath::Rand();
		bUniqueID = true;

		for (const auto TaggedActor : TaggedActors)
		{
			const auto IdentificationComponent = Cast<UIdentificationComponent>(TaggedActor->GetComponentByClass(UIdentificationComponent::StaticClass()));
			
			if (IdentificationComponent->GetUniqueID() == NewID)
			{
				UE_LOG(LogTemp, Display, TEXT("NOT UNIQUE"));
				bUniqueID = false;
				break;
			}
		}
	}

	const auto IdentificationComponent = Cast<UIdentificationComponent>(AimActor->GetComponentByClass(UIdentificationComponent::StaticClass()));
	
	IdentificationComponent->SetUniqueID(NewID);
	SaveToJson();
	return NewID;
}

void AIDManager::SaveToJson()
{
	FActorWithIDData ActorData;
	ActorsDetail.Details.Empty();

	UE_LOG(LogTemp, Display, TEXT("%d"), TaggedActors.Num());
	for (const auto TaggedActor : TaggedActors)
	{
		const auto IdentificationComponent = Cast<UIdentificationComponent>(TaggedActor->GetComponentByClass(UIdentificationComponent::StaticClass()));
		
		ActorData.Name = TaggedActor->GetName();
		ActorData.UniqueID = IdentificationComponent->GetUniqueID();

		ActorsDetail.Details.Emplace(ActorData);
	}

	FString JsonString;
	FJsonObjectConverter::UStructToJsonObjectString(ActorsDetail, JsonString);
	FFileHelper::SaveStringToFile(*JsonString, *(FPaths::ProjectContentDir() + TEXT("/Json/ID/ActorsID.json")));
}

void AIDManager::LoadFromJson()
{
	if (TaggedActors.Num() == 0) return;

	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() + TEXT("/Json/ID/ActorsID.json")));

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> FJsonValueArray = JsonObject->GetArrayField(TEXT("details"));

		for (int32 i = 0; i < FJsonValueArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> JsonValue = FJsonValueArray[i];
			TSharedPtr<FJsonObject> JsonValueObject = JsonValue->AsObject();

			FActorWithIDData ActorData;
			ActorData.Name = JsonValueObject->GetStringField(TEXT("name"));
			ActorData.UniqueID = JsonValueObject->GetIntegerField(TEXT("uniqueId"));

			for (const auto Actor : TaggedActors)
			{
				if (Actor->GetName() == ActorData.Name)
				{
					const auto IdentificationComponent = Cast<UIdentificationComponent>(Actor->GetComponentByClass(UIdentificationComponent::StaticClass()));
					
					IdentificationComponent->SetUniqueID(ActorData.UniqueID);
					break;
				}
			}
		}
	}
}
