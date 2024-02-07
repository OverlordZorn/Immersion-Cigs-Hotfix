class CfgPatches {

	class murshun_cigs_hotfix
	{
		// Meta information for editor
        name = "Immersive Cigs Hotfix";
		version = "1.0.0";

		author[]= {"Mr Zorn [CVO]"};
        url = "http://chronivoron.net";

        // Minimum compatible version. When the game's version is lower, pop-up warning will appear when launching the game.
        requiredVersion = 2.0;

        // Required addons, used for setting load order.
        // When any of the addons is missing, pop-up warning will appear when launching the game.
        requiredAddons[] = {"murshun_cigs","cba_common"};

		// Optional. If this is 1, if any of requiredAddons[] entry is missing in your game the entire config will be ignored and return no error (but in rpt) so useful to make a compat Mod (Since Arma 3 2.14)
		skipWhenMissingDependencies = 1;
        
        // List of objects (CfgVehicles classes) contained in the addon. Important also for Zeus content (units and groups)
        units[] = {};

        // List of weapons (CfgWeapons classes) contained in the addon.
        weapons[] = {};

	};

};

class CfgFunctions
{
    class murshun_cigs_hotfix
    {
        class functions
        {
            file = "z\zrn_cig_hotfix\addons\murshun_cigs_hotfix\functions";
            tag = "murshun_cigs";
            class preInit
            {
                preInit = 1;
                recompile = 1;
            };
            class postInit
            {
                postInit = 1;
                recompile = 1;
            };
            class smoke {};
            class anim {};
            class removeItemFromMag {};
            class playSound {};
            class useItem {};
            class start_cig_your {};
            class start_cig_their {};
            class start_cig {};
            class stop_cig {};
            class take_cig_from_pack {};
        };
    };
};