// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemObject.h"

void UItemObject::RotateItem()
{
	bIsRotated = !bIsRotated;
}

FIntPoint UItemObject::GetDimension() const
{
	if (bIsRotated)
	{
		return FIntPoint(Dimension.Y, Dimension.X);
	}
	return Dimension;
}

UMaterialInstance* UItemObject::GetIcon() const
{
	if (bIsRotated)
	{
		return IconRotated;
	}

	return Icon;
}
