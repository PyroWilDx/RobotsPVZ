// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define UE_LOG_SCREEN0(Msg) GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Red, TEXT(Msg))
#define UE_LOG_SCREEN1(Msg, P1) GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Red, FString::Printf(TEXT(Msg), P1))
#define UE_LOG_SCREEN2(Msg, P1, P2) GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Red, FString::Printf(TEXT(Msg), P1, P2))
