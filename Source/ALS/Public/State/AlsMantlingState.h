#pragma once

#include "AlsMantlingState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsMantlingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	int32 RootMotionSourceId{0};

	// 通過タグ付きアクターは mantle 中だけカプセルの移動衝突から外す。終了時に必ず戻すため保持する。
	UPROPERTY(BlueprintReadOnly, Category = "ALS")
	TObjectPtr<AActor> PassThroughActor;
};
