// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SpaceInvader/Public/BulletActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBulletActor() {}
// Cross Module References
	SPACEINVADER_API UClass* Z_Construct_UClass_ABulletActor_NoRegister();
	SPACEINVADER_API UClass* Z_Construct_UClass_ABulletActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_SpaceInvader();
	ENGINE_API UClass* Z_Construct_UClass_UParticleSystem_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USoundBase_NoRegister();
// End Cross Module References
	void ABulletActor::StaticRegisterNativesABulletActor()
	{
	}
	UClass* Z_Construct_UClass_ABulletActor_NoRegister()
	{
		return ABulletActor::StaticClass();
	}
	struct Z_Construct_UClass_ABulletActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Speed_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Speed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TimeBeforeDestroy_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_TimeBeforeDestroy;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LifeTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_LifeTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BulletFireFX_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BulletFireFX;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BulletFireSound_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BulletFireSound;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABulletActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SpaceInvader,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABulletActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BulletActor.h" },
		{ "ModuleRelativePath", "Public/BulletActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABulletActor_Statics::NewProp_Speed_MetaData[] = {
		{ "Category", "Bullet Properties" },
		{ "ModuleRelativePath", "Public/BulletActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABulletActor_Statics::NewProp_Speed = { "Speed", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABulletActor, Speed), METADATA_PARAMS(Z_Construct_UClass_ABulletActor_Statics::NewProp_Speed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABulletActor_Statics::NewProp_Speed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABulletActor_Statics::NewProp_TimeBeforeDestroy_MetaData[] = {
		{ "Category", "Bullet Properties" },
		{ "ModuleRelativePath", "Public/BulletActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABulletActor_Statics::NewProp_TimeBeforeDestroy = { "TimeBeforeDestroy", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABulletActor, TimeBeforeDestroy), METADATA_PARAMS(Z_Construct_UClass_ABulletActor_Statics::NewProp_TimeBeforeDestroy_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABulletActor_Statics::NewProp_TimeBeforeDestroy_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABulletActor_Statics::NewProp_LifeTime_MetaData[] = {
		{ "Category", "Bullet Properties" },
		{ "ModuleRelativePath", "Public/BulletActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABulletActor_Statics::NewProp_LifeTime = { "LifeTime", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABulletActor, LifeTime), METADATA_PARAMS(Z_Construct_UClass_ABulletActor_Statics::NewProp_LifeTime_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABulletActor_Statics::NewProp_LifeTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireFX_MetaData[] = {
		{ "Category", "Bullet Properties" },
		{ "ModuleRelativePath", "Public/BulletActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireFX = { "BulletFireFX", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABulletActor, BulletFireFX), Z_Construct_UClass_UParticleSystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireFX_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireFX_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireSound_MetaData[] = {
		{ "Category", "Bullet Properties" },
		{ "ModuleRelativePath", "Public/BulletActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireSound = { "BulletFireSound", nullptr, (EPropertyFlags)0x0040000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABulletActor, BulletFireSound), Z_Construct_UClass_USoundBase_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireSound_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireSound_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABulletActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABulletActor_Statics::NewProp_Speed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABulletActor_Statics::NewProp_TimeBeforeDestroy,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABulletActor_Statics::NewProp_LifeTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireFX,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABulletActor_Statics::NewProp_BulletFireSound,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABulletActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABulletActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ABulletActor_Statics::ClassParams = {
		&ABulletActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ABulletActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ABulletActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ABulletActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ABulletActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABulletActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ABulletActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ABulletActor, 4290912598);
	template<> SPACEINVADER_API UClass* StaticClass<ABulletActor>()
	{
		return ABulletActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ABulletActor(Z_Construct_UClass_ABulletActor, &ABulletActor::StaticClass, TEXT("/Script/SpaceInvader"), TEXT("ABulletActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABulletActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
