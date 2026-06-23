#pragma once

#include "RigVMFunctions/RigVMFunction_ControlFlow.h"
#include "RigVMFunctions/Math/RigVMFunction_MathFloat.h"
#include "RigVMFunctions/Simulation/RigVMFunction_SimBase.h"
#include "Units/RigUnit.h"
#include "AlsRigUnits.generated.h"

/// Clamps a single float value into the [0, 1] range.
USTRUCT(DisplayName = "Clamp 01", Meta = (Category = "ALS"))
struct ALS_API FAlsRigVMFunction_Clamp01Float : public FRigVMFunction_MathFloatBase
{
	GENERATED_BODY()

public:
	/// Value to clamp into the [0, 1] range.
	UPROPERTY(Meta = (Input))
	float Value{0.0f};

	/// The input value clamped to the [0, 1] range.
	UPROPERTY(Meta = (Output))
	float Result{0.0f};

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};

/// Critically damped spring interpolation toward a target vector using an exact (analytical) solver.
USTRUCT(DisplayName = "Damper Exact (Vector)", Meta = (Category = "ALS"))
struct ALS_API FAlsRigVMFunction_DamperExactVector : public FRigVMFunction_SimBase
{
	GENERATED_BODY()

public:
	/// Target vector the damped spring interpolates toward.
	UPROPERTY(Meta = (Input))
	FVector Target{ForceInit};

	/// HalfLife is the time it takes for the distance to the target to be reduced by half.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "s"))
	float HalfLife{1.0f};

	/// Current damped vector value, advanced toward the target on each evaluation.
	UPROPERTY(Transient, Meta = (Output))
	FVector Current{ForceInit};

	UPROPERTY(Transient)
	bool bInitialized{false};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

/// Critically damped spring interpolation toward a target rotation using an exact (analytical) solver.
USTRUCT(DisplayName = "Damper Exact (Quaternion)", Meta = (Category = "ALS"))
struct ALS_API FAlsRigVMFunction_DamperExactQuaternion : public FRigVMFunction_SimBase
{
	GENERATED_BODY()

public:
	/// Target rotation the damped spring interpolates toward.
	UPROPERTY(Meta = (Input))
	FQuat Target{ForceInit};

	/// HalfLife is the time it takes for the distance to the target to be reduced by half.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "s"))
	float HalfLife{1.0f};

	/// Current damped rotation value, advanced toward the target on each evaluation.
	UPROPERTY(Transient, Meta = (Output))
	FQuat Current{ForceInit};

	UPROPERTY(Transient)
	bool bInitialized{false};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

/// Calculates the projection location and direction of the perpendicular to AC through B.
USTRUCT(DisplayName = "Calculate Pole Vector", Meta = (Category = "ALS", NodeColor = "0.05 0.25 0.05"))
struct ALS_API FAlsRigUnit_CalculatePoleVector : public FRigUnit
{
	GENERATED_BODY()

public:
	/// First chain item (A); one end of the A-C base line.
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey ItemA;

	/// Middle chain item (B); the joint the pole vector is computed through.
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey ItemB;

	/// End chain item (C); the other end of the A-C base line.
	UPROPERTY(Meta = (Input, ExpandByDefault))
	FRigElementKey ItemC;

	/// When true, samples the initial (reference) pose instead of the current pose.
	UPROPERTY(Meta = (Input))
	bool bInitial{false};

	/// True if all three items were found and the pole vector was computed.
	UPROPERTY(Transient, Meta = (Output))
	bool bSuccess{false};

	/// World-space location of item B.
	UPROPERTY(Transient, DisplayName = "Item B Location", Meta = (Output))
	FVector ItemBLocation{ForceInit};

	/// Projection of item B onto the A-C base line.
	UPROPERTY(Transient, DisplayName = "Item B Projection Location", Meta = (Output))
	FVector ItemBProjectionLocation{ForceInit};

	/// Normalized direction from the A-C base line toward item B (the pole vector direction).
	UPROPERTY(Transient, Meta = (Output))
	FVector PoleDirection{FVector::ForwardVector};

	UPROPERTY(Transient)
	FCachedRigElement CachedItemA;

	UPROPERTY(Transient)
	FCachedRigElement CachedItemB;

	UPROPERTY(Transient)
	FCachedRigElement CachedItemC;

public:
	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

/// Control-flow node that routes execution depending on whether the rig is running in an actual game world.
USTRUCT(DisplayName = "Is Game World", Meta = (Category = "ALS"))
struct ALS_API FAlsRigVMFunction_IsGameWorld : public FRigVMFunction_ControlFlowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, DisplayName = "Execute", Meta = (Input))
	FRigVMExecuteContext ExecuteContext;

	/// Execution block run when the rig is evaluating inside a game world.
	UPROPERTY(Transient, Meta = (Output))
	FRigVMExecuteContext True;

	/// Execution block run when the rig is not in a game world (e.g. editor preview).
	UPROPERTY(Transient, Meta = (Output))
	FRigVMExecuteContext False;

	/// Execution block run after the selected branch has completed.
	UPROPERTY(meta=(Output))
	FRigVMExecuteContext Completed;

	UPROPERTY(Transient, Meta = (Singleton))
	FName BlockToRun;

public:
	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;

	virtual const TArray<FName>& GetControlFlowBlocks_Impl() const override;
};
