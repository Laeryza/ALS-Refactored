#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_DistributeRotationSimple.generated.h"

/// Distributes a single rotation evenly across a chain of items (e.g. a spine), applying a fraction to each.
USTRUCT(DisplayName = "Distribute Rotation Simple", Meta = (Category = "ALS", NodeColor = "0.0 0.36 1.0"))
struct ALS_API FAlsRigUnit_DistributeRotationSimple : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	/// Ordered chain of items the rotation is distributed across.
	UPROPERTY(Meta = (Input))
	TArray<FRigElementKey> Items;

	/// Total rotation to distribute evenly across the items.
	UPROPERTY(meta = (Input))
	FQuat Rotation{ForceInit};

	UPROPERTY(Transient)
	TArray<FCachedRigElement> CachedItems;

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
