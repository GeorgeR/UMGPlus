using UnrealBuildTool;

public class UMGPlusEditor : ModuleRules
{
	public UMGPlusEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"UMGPlusEditor/Public"
			});

		PrivateIncludePaths.AddRange(
			new string[] {
				"UMGPlusEditor/Private",
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "UMGPlus",
				"UnrealEd"
			});
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			});
	}
}