// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ItemObject.h"


UInventoryComponent::UInventoryComponent()
{
	Columns = 0;
	Rows = 0;
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

bool UInventoryComponent::TryAddItem(UItemObject* ItemObjectToAdd)
{
	if (ItemObjectToAdd)
	{
		for (int32 TopLeftIndex = 0; TopLeftIndex < Items.Num(); TopLeftIndex++)
		{
			if (!CheckIsRoomAvailable(ItemObjectToAdd, TopLeftIndex))
			{
				ItemObjectToAdd->RotateItem();

				if (!CheckIsRoomAvailable(ItemObjectToAdd, TopLeftIndex))
				{
					ItemObjectToAdd->RotateItem();
					continue;
				}
			}

			AddItemAt(ItemObjectToAdd, TopLeftIndex);

			return true;
		}
	}

	return false;
}

bool UInventoryComponent::CheckIsRoomAvailable(UItemObject* ItemObject, int32 TopLeftIndex)
{
	// Convert index into Tile coordinate
	FTile Tile = IndexToTile(TopLeftIndex);

	FIntPoint Dimension = ItemObject->GetDimension();

	for (int32 X = Tile.X; X < Tile.X + Dimension.X; X++)
	{
		for (int32 Y = Tile.Y; Y < Tile.Y + Dimension.Y; Y++)
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

void UInventoryComponent::AddItemAt(UItemObject* ItemObjectToAdd, int32 TopLeftIndex)
{
	// Convert index into Tile coordinate
	FTile Tile = IndexToTile(TopLeftIndex);

	FIntPoint Dimension = ItemObjectToAdd->GetDimension();

	for (int32 X = Tile.X; X < Tile.X + Dimension.X; X++)
	{
		for (int32 Y = Tile.Y; Y < Tile.Y + Dimension.Y; Y++)
		{
			// Convert current Tile coordinate back to Index
			int32 Index = TileToIndex(X, Y);

			Items[Index] = ItemObjectToAdd;
		}
	}

	OnInventoryChanged.Broadcast(ItemObjectToAdd);
}

void UInventoryComponent::RemoveItem(UItemObject* ItemObjectToRemove)
{
	if (ItemObjectToRemove)
	{
		for (int32 Index = 0; Index < Items.Num(); Index++)
		{
			if (ItemObjectToRemove == Items[Index])
			{
				Items[Index] = nullptr;
			}
		}

		OnInventoryChanged.Broadcast(ItemObjectToRemove);
	}
}

TMap<UItemObject*, FTile> UInventoryComponent::GetAllItems() const
{
	TMap<UItemObject*, FTile> AllItems;
	for (int32 Index = 0; Index < Items.Num(); Index++)
	{
		UItemObject* CurrentItemObj = Items[Index];
		if (CurrentItemObj)
		{
			/*if (AllItems.Contains(CurrentItemObj))
			{
				break;
			}
			FTile CurrentTile(Index % Columns, Index / Columns);
			AllItems.Add(CurrentItemObj, CurrentTile);*/
			if (!AllItems.Contains(CurrentItemObj))
			{
				FTile CurrentTile(Index % Columns, Index / Columns);
				AllItems.Add(CurrentItemObj, CurrentTile);
			}
		}
	}
	return AllItems;
}

UInventoryComponent* UInventoryComponent::GetInventoryComponent(AActor* TargetActor)
{
	if (TargetActor)
	{
		return Cast<UInventoryComponent>(TargetActor->GetComponentByClass(StaticClass()));
	}

	return nullptr;
}
