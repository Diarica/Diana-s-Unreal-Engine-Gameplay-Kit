// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MathLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FLATLINE_API UMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable,Category="Algos")
	static void Hanoi(int n,FString a,FString b,FString c)
	{
		if(n == 0)
		{
			return;
			//如果传入、递归执行的盘子是0个，那么跳出，防止无限递归。
		}

		Hanoi(n-1,a,c,b);
		//第一步，将n-1个盘子从A柱移动到B柱，C柱为工具柱。
		//加一条，因为这里是递归，n-1个盘子指的是n个盘子中移动一个（因为汉诺塔一次只能移动一个）
		//不断的递归，一次一个盘子，从A柱移动到B柱，C柱为工具柱。

		
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,FString::Printf(TEXT("%s-->%s"),*a,*c));


		Hanoi(n-1,b,a,c);
		//将A柱的n-1个盘子移动至c柱
	}

	UFUNCTION(BlueprintPure,Category="Algos")
	int rabbit(int month, int rabbit_number)
	{
		if (month < 2)return rabbit_number;

		
		{
			return rabbit(month - 1, rabbit_number) + rabbit(month - 2,rabbit_number);
		}
	}
};
