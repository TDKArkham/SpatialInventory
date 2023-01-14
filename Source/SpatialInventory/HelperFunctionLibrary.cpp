// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperFunctionLibrary.h"

#include "Item.h"
#include "ItemObject.h"
#include "Kismet/GameplayStatics.h"

AActor* UHelperFunctionLibrary::SpawnActorFromItemObject(UItemObject* ItemObject, AActor* OriginLocationActor)
{
	if (ItemObject && OriginLocationActor)
	{
		FVector SpawnLocation = OriginLocationActor->GetActorLocation() + OriginLocationActor->GetActorForwardVector() * 150;

		FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);

		AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(OriginLocationActor->GetWorld(), ItemObject->ItemClass, SpawnTransform, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		
		return UGameplayStatics::FinishSpawningActor(Actor, SpawnTransform);
	}

	return nullptr;
}
