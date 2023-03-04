# SpatialInventory
An simple Escape from Tarkov like inventory system learned from [Spatial Inventory Tutorial](https://youtube.com/playlist?list=PLFic00P0BufTLu4CB_S_4c0LCEV0fv9Ye)

Tip1: C++ Classes derived from UObject should have "Blueprintable" specifier in UCLASS() macro to make the Class can be derived by Blueprint and can be used by "Construct Object From Class" node in Blueprint.

Tip2: How to spawn an actor in static function (Such as BlueprintFunctionLibrary function) ?
If we use `GetWorld()->SpawnActor<AActor>(Params...)`, it will throw us an error to warn us not to use non-static object in static funtion, the right way to do is to use `BeginDeferredActorSpawnFromClass` function and `FinishSpawningActor` function in `UGameplayStatics` like this (like what I did in `HelperFunctionLibrary`):
```cpp
.h
static AActor* SpawnActorFromItemObject(UItemObject* ItemObject, AActor* OriginLocationActor);

.cpp
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
```
