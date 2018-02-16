#pragma once

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "UMGPStyleCollection.h"
#include "UMGPlusFunctionLibrary.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCanGetStyleCollectionTest, "UMGPlus.Style.CanGetStyleCollection", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FCanGetStyleCollectionTest::RunTest(const FString& Parameters)
{
	// Arrange
	
	// Act
	UUMGPStyleCollection* Collection = UUMGPlusFunctionLibrary::GetStyleCollection();

	// Assert
	TestNotNull("Style Collection", Collection);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCanGetDefaultStyleCollectionTest, "UMGPlus.Style.CanGetDefaultStyleCollection", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FCanGetDefaultStyleCollectionTest::RunTest(const FString& Parameters)
{
	// Arrange

	// Act
	UUMGPStyleCollection* Collection = UUMGPStyleCollection::GetDefault();

	// Assert
	TestNotNull("Default Style Collection", Collection);

	return true;
}

#endif