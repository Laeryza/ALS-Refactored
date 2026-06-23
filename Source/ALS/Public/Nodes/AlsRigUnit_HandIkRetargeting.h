#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_HandIkRetargeting.generated.h"

/// Retargets hand IK so a two-handed prop stays aligned to both hands, blending left/right hand dominance.
USTRUCT(DisplayName = "Hand Ik Retargeting", Meta = (Category = "ALS", NodeColor = "0.0 0.36 1.0"))
struct ALS_API FAlsRigUnit_HandIkRetargeting : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	/// Left hand bone item (current pose).
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey LeftHandItem;

	/// Left hand IK target item.
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey LeftHandIkItem;

	/// Right hand bone item (current pose).
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey RightHandItem;

	/// Right hand IK target item.
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey RightHandIkItem;

	/// Items shifted by the retargeting offset (e.g. the held prop and both hands).
	UPROPERTY(Meta = (Input, ExpandByDefault))
	TArray<FRigElementKey> ItemsToMove;

	/// Which hand to favor. 0.5 means equal weight for both hands, 0 means left hand, andf 1 means right hand.
	UPROPERTY(Meta = (Input))
	float RetargetingWeight{0.5f};

	/// Overall blend weight of the retargeting (0 = disabled, 1 = full).
	UPROPERTY(Meta = (Input))
	float Weight{1.0f};

	/// When true, the retargeting offset is propagated to child items.
	UPROPERTY(Meta = (Input, Constant))
	bool bPropagateToChildren{false};

	UPROPERTY(Transient)
	FCachedRigElement CachedLeftHandItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedLeftHandIkItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedRightHandItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedRightHandIkItem;

	UPROPERTY(Transient)
	TArray<FCachedRigElement> CachedItemsToMove;

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
