#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_FootOffsetTrace.generated.h"

/// Traces against the world below a foot to find the ground, returning the vertical offset and surface normal.
USTRUCT(DisplayName = "Foot Offset Trace", Meta = (Category = "ALS", NodeColor = "0.2 0.4 1.0"))
struct ALS_API FAlsRigUnit_FootOffsetTrace : public FRigUnit
{
	GENERATED_BODY()

public:
	/// World-space foot location the trace is centered on.
	UPROPERTY(Transient, Meta = (Input))
	FVector FootTargetLocation{ForceInit};

	/// Collision channel used for the ground trace.
	UPROPERTY(Meta = (Input))
	TEnumAsByte<ECollisionChannel> TraceChannel{ECC_Visibility};

	/// How far above the foot the trace starts.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "cm"))
	float TraceDistanceUpward{50.0f};

	/// How far below the foot the trace reaches.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "cm"))
	float TraceDistanceDownward{80.0f};

	/// Maximum floor slope angle still treated as walkable ground.
	UPROPERTY(Meta = (Input, ClampMin = 0, ClampMax = 90, ForceUnits = "deg"))
	float WalkableFloorAngle{45.0f};

	/// Height of the foot above the sole, offsetting the hit location.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "cm"))
	float FootHeight{13.5f};

	/// When false, the trace is skipped and a zero offset is returned.
	UPROPERTY(Meta = (Input))
	bool bEnabled{true};

	/// When true, draws debug visualization for the trace.
	UPROPERTY(meta = (Input, DetailsOnly))
	bool bDrawDebug{false};

	/// Resulting vertical (Z) offset from the foot target to the ground.
	UPROPERTY(Transient, Meta = (Output))
	float OffsetLocationZ{0.0f};

	/// Surface normal at the ground hit.
	UPROPERTY(Transient, Meta = (Output))
	FVector OffsetNormal{ForceInit};

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
