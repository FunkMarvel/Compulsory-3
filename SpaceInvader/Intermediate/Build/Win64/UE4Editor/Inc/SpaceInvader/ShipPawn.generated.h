// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SPACEINVADER_ShipPawn_generated_h
#error "ShipPawn.generated.h already included, missing '#pragma once' in ShipPawn.h"
#endif
#define SPACEINVADER_ShipPawn_generated_h

#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_SPARSE_DATA
#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execResetLoaction);


#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execResetLoaction);


#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAShipPawn(); \
	friend struct Z_Construct_UClass_AShipPawn_Statics; \
public: \
	DECLARE_CLASS(AShipPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SpaceInvader"), NO_API) \
	DECLARE_SERIALIZER(AShipPawn)


#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAShipPawn(); \
	friend struct Z_Construct_UClass_AShipPawn_Statics; \
public: \
	DECLARE_CLASS(AShipPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SpaceInvader"), NO_API) \
	DECLARE_SERIALIZER(AShipPawn)


#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AShipPawn(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AShipPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShipPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShipPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AShipPawn(AShipPawn&&); \
	NO_API AShipPawn(const AShipPawn&); \
public:


#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AShipPawn(AShipPawn&&); \
	NO_API AShipPawn(const AShipPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShipPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShipPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AShipPawn)


#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_PRIVATE_PROPERTY_OFFSET
#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_12_PROLOG
#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_PRIVATE_PROPERTY_OFFSET \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_SPARSE_DATA \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_RPC_WRAPPERS \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_INCLASS \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_PRIVATE_PROPERTY_OFFSET \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_SPARSE_DATA \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_INCLASS_NO_PURE_DECLS \
	SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SPACEINVADER_API UClass* StaticClass<class AShipPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SpaceInvader_Source_SpaceInvader_Public_ShipPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
