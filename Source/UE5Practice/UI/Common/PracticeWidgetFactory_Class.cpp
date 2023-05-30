// Copyright Epic Games, Inc. All Rights Reserved.

#include "PracticeWidgetFactory_Class.h"

#include "Blueprint/UserWidget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PracticeWidgetFactory_Class)

TSubclassOf<UUserWidget> UPracticeWidgetFactory_Class::FindWidgetClassForData_Implementation(const UObject* Data) const
{
	// Starting with the current class, work backwards to see if there are any construction rules for this class.
	for (UClass* Class = Data->GetClass(); Class; Class = Class->GetSuperClass())
	{
		TSoftClassPtr<UObject> ClassPtr(Class);
		if (const TSubclassOf<UUserWidget> EntryWidgetClassPtr = EntryWidgetForClass.FindRef(ClassPtr))
		{
			return EntryWidgetClassPtr;
		}
	}

	return TSubclassOf<UUserWidget>();
}
