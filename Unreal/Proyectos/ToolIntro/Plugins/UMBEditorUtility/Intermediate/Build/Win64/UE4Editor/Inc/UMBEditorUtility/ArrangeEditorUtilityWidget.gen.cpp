// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UMBEditorUtility/Public/ArrangeEditorUtilityWidget.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeArrangeEditorUtilityWidget() {}
// Cross Module References
	UMBEDITORUTILITY_API UClass* Z_Construct_UClass_UArrangeEditorUtilityWidget_NoRegister();
	UMBEDITORUTILITY_API UClass* Z_Construct_UClass_UArrangeEditorUtilityWidget();
	BLUTILITY_API UClass* Z_Construct_UClass_UEditorUtilityWidget();
	UPackage* Z_Construct_UPackage__Script_UMBEditorUtility();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UArrangeEditorUtilityWidget::execRadial)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Radius);
		P_GET_OBJECT(AActor,Z_Param_CenterActor);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Radial(Z_Param_Radius,Z_Param_CenterActor);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UArrangeEditorUtilityWidget::execHello)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Hello();
		P_NATIVE_END;
	}
	void UArrangeEditorUtilityWidget::StaticRegisterNativesUArrangeEditorUtilityWidget()
	{
		UClass* Class = UArrangeEditorUtilityWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Hello", &UArrangeEditorUtilityWidget::execHello },
			{ "Radial", &UArrangeEditorUtilityWidget::execRadial },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UArrangeEditorUtilityWidget_Hello_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UArrangeEditorUtilityWidget_Hello_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ArrangeEditorUtilityWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UArrangeEditorUtilityWidget_Hello_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UArrangeEditorUtilityWidget, nullptr, "Hello", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UArrangeEditorUtilityWidget_Hello_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UArrangeEditorUtilityWidget_Hello_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UArrangeEditorUtilityWidget_Hello()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UArrangeEditorUtilityWidget_Hello_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics
	{
		struct ArrangeEditorUtilityWidget_eventRadial_Parms
		{
			float Radius;
			AActor* CenterActor;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Radius;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CenterActor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ArrangeEditorUtilityWidget_eventRadial_Parms, Radius), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::NewProp_CenterActor = { "CenterActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ArrangeEditorUtilityWidget_eventRadial_Parms, CenterActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::NewProp_Radius,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::NewProp_CenterActor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ArrangeEditorUtilityWidget.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UArrangeEditorUtilityWidget, nullptr, "Radial", nullptr, nullptr, sizeof(ArrangeEditorUtilityWidget_eventRadial_Parms), Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UArrangeEditorUtilityWidget_NoRegister()
	{
		return UArrangeEditorUtilityWidget::StaticClass();
	}
	struct Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UEditorUtilityWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_UMBEditorUtility,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UArrangeEditorUtilityWidget_Hello, "Hello" }, // 664708954
		{ &Z_Construct_UFunction_UArrangeEditorUtilityWidget_Radial, "Radial" }, // 101769345
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "ArrangeEditorUtilityWidget.h" },
		{ "ModuleRelativePath", "Public/ArrangeEditorUtilityWidget.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UArrangeEditorUtilityWidget>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics::ClassParams = {
		&UArrangeEditorUtilityWidget::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UArrangeEditorUtilityWidget()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UArrangeEditorUtilityWidget_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UArrangeEditorUtilityWidget, 42758749);
	template<> UMBEDITORUTILITY_API UClass* StaticClass<UArrangeEditorUtilityWidget>()
	{
		return UArrangeEditorUtilityWidget::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UArrangeEditorUtilityWidget(Z_Construct_UClass_UArrangeEditorUtilityWidget, &UArrangeEditorUtilityWidget::StaticClass, TEXT("/Script/UMBEditorUtility"), TEXT("UArrangeEditorUtilityWidget"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UArrangeEditorUtilityWidget);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
