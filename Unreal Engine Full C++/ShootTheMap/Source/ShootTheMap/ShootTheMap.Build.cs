// ShootTheMap

using UnrealBuildTool;

public class ShootTheMap : ModuleRules
{
	public ShootTheMap(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "PhysicsCore", "GameplayTasks", "NavigationSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { "ShootTheMap/Public/Characters", "ShootTheMap/Public/Characters/Components", "ShootTheMap/Public/Characters/Dev", "ShootTheMap/Public/Weapons", "ShootTheMap/Public/UI", "ShootTheMap/Public/Notifys", "ShootTheMap/Public/PickUps", "ShootTheMap/Public/AI", "ShootTheMap/Public/AI/Tasks", "ShootTheMap/Public/Menu" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
