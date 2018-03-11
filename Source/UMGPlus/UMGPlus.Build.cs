using UnrealBuildTool;

public class UMGPlus : ModuleRules
{
	public UMGPlus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"UMGPlus/Public",
			    "UMGPlus/Public/Components",
                "UMGPlus/Public/Interfaces",
			    "UMGPlus/Public/Widgets"
            });

		PrivateIncludePaths.AddRange(
			new string[] {
				"UMGPlus/Private",
			    "UMGPlus/Private/Components",
                "UMGPlus/Private/Interfaces",
			    "UMGPlus/Private/Widgets"
            });

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			    "CoreUObject",
			    "Engine",
			    "InputCore",
                "UMG"
            });

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "UMG"
			});

		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}