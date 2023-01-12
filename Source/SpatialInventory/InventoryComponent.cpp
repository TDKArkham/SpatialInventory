// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ItemObject.h"


UInventoryComponent::UInventoryComponent()
{
	Columns = 0;
	Rows = 0;

	bIsDirty = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Items.SetNum(Columns * Rows);
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UInventoryComponent::TryAddItem(UItemObject* ItemObject)
{
	if (ItemObject)
	{
		for (int TopLeftIndex = 0; TopLeftIndex < Items.Num(); TopLeftIndex++)
		{
			if (CheckIsRoomAvailable(ItemObject, TopLeftIndex))
			{
				// Convert index into Tile coordinate
				int32 TileX = TopLeftIndex % Columns;
				int32 TileY = TopLeftIndex / Columns;

				FIntPoint Dimension = ItemObject->GetDimension();

				for (int X = TileX; X < TileX + Dimension.X; X++)
				{
					for (int Y = TileY; Y < TileY + Dimension.Y; Y++)
					{
						// Convert current Tile coordinate back to Index
						int32 Index = Y * Columns + X;

						Items[Index] = ItemObject;
					}
				}

				bIsDirty = true;

				return true;
			}
		}
	}

	return false;
}

bool UInventoryComponent::CheckIsRoomAvailable(UItemObject* ItemObject, int32 TopLeftIndex)
{
	// Convert index into Tile coordinate
	int32 TileX = TopLeftIndex % Columns;
	int32 TileY = TopLeftIndex / Columns;

	FIntPoint Dimension = ItemObject->GetDimension();

	for (int X = TileX; X < TileX + Dimension.X; X++)
	{
		for (int Y = TileY; Y < TileY + Dimension.Y; Y++)
		{
			if (X < 0 || X >= Columns || Y < 0 || Y > Rows)
			{
				return false;
			}

			// Convert current Tile coordinate back to Index
			int32 Index = Y * Columns + X;
			if (!Items.IsValidIndex(Index))
			{
				return false;
			}

			UItemObject* ItemObjectAtIndex = Items[Index];
			if (ItemObjectAtIndex != nullptr)
			{
				return false;
			}

		}
	}

	return true;
}

UInventoryComponent* UInventoryComponent::GetInventoryComponent(AActor* TargetActor)
{
	if (TargetActor)
	{
		return Cast<UInventoryComponent>(TargetActor->GetComponentByClass(StaticClass()));
	}

	return nullptr;
}