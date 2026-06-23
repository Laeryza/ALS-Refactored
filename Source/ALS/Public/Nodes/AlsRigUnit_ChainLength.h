#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_ChainLength.generated.h"

/// Computes the total length of a bone chain by summing the distances between successive items.
USTRUCT(DisplayName = "Chain Length", Meta = (Category = "ALS", NodeColor = "0.05 0.25 0.05"))
struct ALS_API FAlsRigUnit_ChainLength : public FRigUnit
{
	GENERATED_BODY()

public:
	/// Top item of the chain (ancestor).
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey AncestorItem;

	/// Bottom item of the chain (descendant).
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey DescendantItem;

	/// When true, measures the initial (reference) pose instead of the current pose.
	UPROPERTY(Meta = (Input))
	bool bInitial{false};

	/// Total length of the chain from ancestor to descendant.
	UPROPERTY(Transient, Meta = (Output))
	float Length{0.0f};

	UPROPERTY(Transient)
	FCachedRigElement CachedAncestorItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedDescendantItem;

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
