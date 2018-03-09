using UnrealBuildTool;

public class UMGPlus : ModuleRules
{
	public UMGPlus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"UMGPlus/Public",
			    "UMGPlus/Public/Interfaces"
            });

		PrivateIncludePaths.AddRange(
			new string[] {
				"UMGPlus/Private",
			    "UMGPlus/Private/Interfaces",
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