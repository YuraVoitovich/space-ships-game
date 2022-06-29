// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FRange {
private:
	int MinRangeValue = 0;
	int MaxRangeValue = 0;
	bool bIsZeroChance = true;

	void SetChance()
	{
		if (MinRangeValue >= MaxRangeValue)
			bIsZeroChance = true;
		else
			bIsZeroChance = false;
	}

public:
	void Clear()
	{
		MinRangeValue = 0;
		MaxRangeValue = 0;
	}

	bool IsZeroChance() {
		return bIsZeroChance;
	}

	int GetMinRangeValue() { return MinRangeValue; };
	int GetMaxRangeValue() { return MaxRangeValue; };

	bool IsInRange(int val)
	{
		if ((val >= this->MinRangeValue) && (val <= this->MaxRangeValue)) { return true; }
		return false;
	}

	void SetRelativeMaxRangeValue(int Val)
	{
		if (Val < 0)
		{
			this->SetMinRangeValue(this->MinRangeValue + Val);
			this->SetMaxRangeValue(this->MinRangeValue);
		}
		else
			this->SetMaxRangeValue(this->MinRangeValue + Val);
	}

	void SetMinRangeValue(int Val)
	{
		if (Val < 0)
		{
			MinRangeValue = 0;
		}
		else
		{
			if (Val > 100)
				MinRangeValue = 100;
			else
				MinRangeValue = Val;
		}
		this->SetChance();
	}

	void SetMaxRangeValue(int Val)
	{
		if (Val < 0)
		{
			MaxRangeValue = 0;
		}
		else
		{
			if (Val > 100)
				MaxRangeValue = 100;
			else
				MaxRangeValue = Val;
		}
		this->SetChance();
	}

	void SetRange(int MinVal, int MaxVal)
	{
		this->SetMinRangeValue(MinVal);
		this->SetMaxRangeValue(MaxVal);
	}

	FRange& operator = (FRange c2) {
		if (&c2 == NULL) return *this;
		this->SetMaxRangeValue(c2.GetMaxRangeValue());
		this->SetMinRangeValue(c2.GetMinRangeValue());
		return *this;
	}
};

struct FRangeCalculation {
private:
	TArray<FRange> SpawnEnemyRangeArray;
	TArray<int> SpawnChancesArray;
public:
	FRange& operator [] (unsigned i) { return SpawnEnemyRangeArray[i]; }

	void FillSpawnEnemyRangeArray()
	{
		FRange tmp;
		tmp.SetMinRangeValue(0);
		if (SpawnChancesArray.Num() == 0) return;
		tmp.SetRelativeMaxRangeValue(SpawnChancesArray[0]);
		SpawnEnemyRangeArray.Add(tmp);

		// Fill array of enemies spawn chances
		for (int i = 1; i < SpawnChancesArray.Num(); i++) {
			tmp.SetMinRangeValue(SpawnEnemyRangeArray[i - 1].GetMaxRangeValue() + 1);
			tmp.SetRelativeMaxRangeValue(SpawnChancesArray[i] - 1);
			SpawnEnemyRangeArray.Add(tmp);
		}
	}

	void SetSpawnChancesArrayItem(int index, int Val)
	{
		if ((Val < 0) || (Val > 100)) return;
		if (!SpawnChancesArray.IsValidIndex(index)) return;
		SpawnChancesArray[index] = Val;
	}

	void AddSpawnChancesArrayItem(int Val)
	{
		if ((Val < 0) || (Val > 100)) return;
		SpawnChancesArray.Add(Val);
	}

	int GetRandomIndex()
	{
		FRandomStream Random;
		Random.GenerateNewSeed();
		int RandomChance = Random.RandRange(0, 100);

		// Find element with this spawn chance
		for (int i = 0; i < SpawnEnemyRangeArray.Num(); i++) {
			if (SpawnEnemyRangeArray[i].IsInRange(RandomChance)) {
				return i;
			}
		}
		return -1;
	}
};

class SHOOTER_API RangeCalculation
{
public:
	RangeCalculation();
	~RangeCalculation();
};
