#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_ApplyFootOffsetRotation.generated.h"

/// Applies a surface-aligned foot-IK rotation offset with swing/twist limits and smoothed interpolation.
USTRUCT(DisplayName = "Apply Foot Offset Rotation", Meta = (Category = "ALS", NodeColor = "0.0 0.36 1.0"))
struct ALS_API FAlsRigUnit_ApplyFootOffsetRotation : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	/// Calf (lower leg) bone item; parent of the foot.
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey CalfItem;

	/// Foot bone item whose rotation is offset.
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey FootItem;

	/// Desired foot rotation before the offset is applied.
	UPROPERTY(Transient, Meta = (Input))
	FQuat FootTargetRotation{ForceInit};

	/// Surface normal the foot aligns its sole to.
	UPROPERTY(Transient, Meta = (Input))
	FVector FootOffsetNormal{FVector::UpVector};

	/// Allowed min/max swing angle around the first swing axis.
	UPROPERTY(DisplayName = "Swing 1 Limit Angle", Meta = (Input, ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	FFloatInterval Swing1LimitAngle{-20.0f, 40.0f};

	/// Allowed min/max swing angle around the second swing axis.
	UPROPERTY(DisplayName = "Swing 2 Limit Angle", Meta = (Input, ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	FFloatInterval Swing2LimitAngle{-15.0f, 5.0f};

	/// Allowed min/max twist angle around the foot's forward axis.
	UPROPERTY(Meta = (Input, ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	FFloatInterval TwistLimitAngle{0.0f, 0.0f};

	/// The lower the value, the faster the interpolation. A zero value means instant interpolation.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "s"))
	float OffsetInterpolationHalfLife{0.1f};

	UPROPERTY(Transient)
	bool bInitialized{false};

	UPROPERTY(Transient)
	FCachedRigElement CachedCalfItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedFootItem;

	UPROPERTY(Transient)
	FVector OffsetNormal{FVector::UpVector};

	/// Resulting foot rotation after the surface-aligned offset is applied.
	UPROPERTY(Transient, Meta = (Output))
	FQuat FootRotation{ForceInit};

	UPROPERTY(Transient)
	FQuat FootInitialRotationCalfSpace{ForceInit};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};
