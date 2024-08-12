class CfgPatches
{

	class murshun_cigs_hotfix
	{
		// Meta information for editor
        name = "Immersive Cigs Hotfix";
		version = "1.0.0";

		author = "Mr Zorn [CVO]";
		authors[]= {"Mr Zorn [CVO]"};
        url = "https://github.com/OverlordZorn/Immersion-Cigs-Hotfix";

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
    class murshun_cigs
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
                preInit = 1;
                recompile = 1;
            };
            class smoke {};
            class anim {};
            class removeItemFromMag {};
            class useItem {};

            class start_cig_your {};
            class start_cig_their {};

            class start_cig {};
            class start_cig_recursive {};

            class stop_cig {};
            class take_cig_from_pack {};
        };
    };
};


class CfgVehicles
{
    class Man;
    class CAManBase: Man
    {
        class ACE_SelfActions
        {
            class ACE_Equipment {
                class murshun_cigs_start_cig
                {
                    displayName = "$STR_murshun_cigs_start_cig";
                    condition = "[_player] call immersion_cigs_canStartSmoking";
                    statement = "[_player] call murshun_cigs_fnc_start_cig_your";
                    showDisabled = 0;
                    exceptions[] = {"isNotInside", "isNotSitting"};
                    icon = "murshun_cigs\UI\light_cig.paa";
                };
                class murshun_cigs_stop_cig
                {
                    displayName = "$STR_murshun_cigs_stop_cig";
                    condition = "[_player] call immersion_cigs_canStopSmoking";
                    statement = "[_player] call murshun_cigs_fnc_stop_cig";
                    showDisabled = 0;
                    exceptions[] = {"isNotInside", "isNotSitting"};
                    icon = "murshun_cigs\UI\light_cig.paa";
                };
                class murshun_cigs_take_cig_from_pack
                {
                    displayName = "$STR_murshun_cigs_take_cig_from_pack";
                    condition = "[_player] call immersion_cigs_canTakeCigFromPack";
                    statement = "[_player] call murshun_cigs_fnc_take_cig_from_pack";
                    showDisabled = 0;
                    exceptions[] = {"isNotInside", "isNotSitting"};
                    icon = "murshun_cigs\UI\take_cig.paa";
                };
            };
        };
    };

    /*
    class WeaponHolder_Single_limited_item_F;

    class murshun_cigs_matchesItem: WeaponHolder_Single_limited_item_F {
        scope = 2;
        scopeCurator = 2;
        displayName = "$STR_murshun_cigs_matches";
        author = "$STR_murshun_cigs_author";
        vehicleClass = "Magazines";

        class TransportMagazines {
            class murshun_cigs_matches {
                magazine = "murshun_cigs_matches";
                count = 1;
            };
        };
    };

    class murshun_cigs_lighterItem: WeaponHolder_Single_limited_item_F {
        scope = 2;
        scopeCurator = 2;
        displayName = "$STR_murshun_cigs_lighter";
        author = "$STR_murshun_cigs_author";
        vehicleClass = "Magazines";

        class TransportMagazines {
            class murshun_cigs_lighter {
                magazine = "murshun_cigs_lighter";
                count = 1;
            };
        };
    };

    class murshun_cigs_cigpackItem: WeaponHolder_Single_limited_item_F {
        scope = 2;
        scopeCurator = 2;
        displayName = "$STR_murshun_cigs_cigpack";
        author = "$STR_murshun_cigs_author";
        vehicleClass = "Magazines";

        class TransportMagazines {
            class murshun_cigs_cigpack {
                magazine = "murshun_cigs_cigpack";
                count = 1;
            };
        };
    };

    */
};

class CfgMagazines {
    class CA_Magazine;
    class murshun_cigs_matches: CA_Magazine {
        ACE_asItem = 1;
    };

    class murshun_cigs_lighter: CA_Magazine {
        ACE_asItem = 1;
    };

    class murshun_cigs_cigpack: CA_Magazine {
        ACE_asItem = 1;
    };
};

/*
class CfgGlasses {
    class None;

    class murshun_cigs_cig0: None {
        scope = 2;
        author = "$STR_murshun_cigs_author";
        mass = 0.02;
        displayName = "$STR_murshun_cigs_cigarette0";
        model = "\murshun_cigs\cig0.p3d";
        picture = "\murshun_cigs\UI\gear_cig0_x_ca";
        identityTypes[] = {};

        immersion_cigs_type = "cigarette";
        immersion_cigs_maxTime = 330;
        immersion_cigs_initStateTime = 0;
        immersion_cigs_nextState = "murshun_cigs_cig1";
        immersion_cigs_isCig = true;
    };

    class murshun_cigs_cig1: murshun_cigs_cig0 {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigarette (Stage 1)";
        model = "\murshun_cigs\cig1.p3d";
        picture = "\murshun_cigs\UI\gear_cig1_x_ca";

        immersion_cigs_initStateTime = 6;
        immersion_cigs_nextState = "murshun_cigs_cig2";
        immersion_cigs_isCig = true;
    };

    class murshun_cigs_cig2: murshun_cigs_cig0 {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigarette (Stage 2)";
        model = "\murshun_cigs\cig2.p3d";
        picture = "\murshun_cigs\UI\gear_cig2_x_ca";

        immersion_cigs_initStateTime = 66;
        immersion_cigs_nextState = "murshun_cigs_cig3";
        immersion_cigs_isCig = true;
    };

    class murshun_cigs_cig3: murshun_cigs_cig0 {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigarette (Stage 3)";
        model = "\murshun_cigs\cig3.p3d";
        picture = "\murshun_cigs\UI\gear_cig3_x_ca";

        immersion_cigs_initStateTime = 126;
        immersion_cigs_nextState = "murshun_cigs_cig4";
        immersion_cigs_isCig = true;
    };

    class murshun_cigs_cig4: murshun_cigs_cig0 {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigarette (Stage 4)";
        model = "\murshun_cigs\cig4.p3d";
        picture = "\murshun_cigs\UI\gear_cig4_x_ca";

        immersion_cigs_initStateTime = 306;
        immersion_cigs_nextState = "";
        immersion_cigs_isCig = true;
    };

    class immersion_cigs_cigar0: None {
        scope = 2;
        author = "$STR_murshun_cigs_author";
        mass = 0.1;
        displayName = "Cigar";
        model = "\murshun_cigs\cigars\cigar0.p3d";
        picture = "\murshun_cigs\UI\gear_cigar0_x_ca";
        identityTypes[] = {};

        immersion_cigs_type = "cigar";
        immersion_cigs_maxTime = 660;
        immersion_cigs_initStateTime = 0;
        immersion_cigs_nextState = "immersion_cigs_cigar1";
        immersion_cigs_isCig = true;
    };

    class immersion_cigs_cigar1: immersion_cigs_cigar0 {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigar (Stage 1)";
        model = "\murshun_cigs\cigars\cigar1.p3d";
        picture = "\murshun_cigs\UI\gear_cigar1_x_ca";

        immersion_cigs_initStateTime = 12;
        immersion_cigs_nextState = "immersion_cigs_cigar2";
        immersion_cigs_isCig = true;
    };

    class immersion_cigs_cigar2: immersion_cigs_cigar0 {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigar (Stage 2)";
        model = "\murshun_cigs\cigars\cigar2.p3d";
        picture = "\murshun_cigs\UI\gear_cigar2_x_ca";

        immersion_cigs_initStateTime = 132;
        immersion_cigs_nextState = "immersion_cigs_cigar3";
        immersion_cigs_isCig = true;
    };

    class immersion_cigs_cigar3: immersion_cigs_cigar0 {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigar (Stage 3)";
        model = "\murshun_cigs\cigars\cigar3.p3d";
        picture = "\murshun_cigs\UI\gear_cigar3_x_ca";

        immersion_cigs_initStateTime = 252;
        immersion_cigs_nextState = "immersion_cigs_cigar4";
        immersion_cigs_isCig = true;
    };

    class immersion_cigs_cigar4: immersion_cigs_cigar0 {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigar (Stage 4)";
        model = "\murshun_cigs\cigars\cigar4.p3d";
        picture = "\murshun_cigs\UI\gear_cigar4_x_ca";

        immersion_cigs_initStateTime = 612;
        immersion_cigs_nextState = "";
        immersion_cigs_isCig = true;
    };
};
*/

/*
class CfgSounds
{
    sounds[] = {};

    class murshun_cigs_unwrap
    {
        sound[] = {"\murshun_cigs\murshun_cigs_unwrap.ogg", 2, 1, 15};
        titles[] = {};
    };
    class murshun_cigs_matches_01
    {
        sound[] = {"\murshun_cigs\murshun_cigs_matches_01.ogg", 2, 1, 15};
        titles[] = {};
    };
    class murshun_cigs_lighter_01
    {
        sound[] = {"\murshun_cigs\murshun_cigs_lighter_01.ogg", 2, 1, 15};
        titles[] = {};
    };
};
*/


/*
class CfgWeapons {
	class NVGoggles;

    class murshun_cigs_cig0_nv: NVGoggles {
        scope = 2;
        author = "$STR_murshun_cigs_author";
        mass = 0.02;
        displayName = "$STR_murshun_cigs_cigarette0_nv";
        descriptionShort = "";
        model = "\murshun_cigs\cig0.p3d";
        picture = "\murshun_cigs\UI\gear_cig0_x_ca";
        visionMode[] = {"Normal"};
		thermalMode[] = {0};
		modelOptics[] = {};
		opticsPPEffects[] = {};

        immersion_cigs_type = "cigarette";
        immersion_cigs_maxTime = 330;
        immersion_cigs_initStateTime = 0;
        immersion_cigs_nextState = "murshun_cigs_cig1_nv";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cig0.p3d";
	    	modelOff = "\murshun_cigs\cig0.p3d";
            mass = 0.02;
        };
    };



    class murshun_cigs_cig1_nv: murshun_cigs_cig0_nv {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigarette (Stage 1)";
        model = "\murshun_cigs\cig1.p3d";
        picture = "\murshun_cigs\UI\gear_cig1_x_ca";

        immersion_cigs_initStateTime = 6;
        immersion_cigs_nextState = "murshun_cigs_cig2_nv";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cig1.p3d";
	    	modelOff = "\murshun_cigs\cig1.p3d";
        };
    };

    class murshun_cigs_cig2_nv: murshun_cigs_cig0_nv {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigarette (Stage 2)";
        model = "\murshun_cigs\cig2.p3d";
        picture = "\murshun_cigs\UI\gear_cig2_x_ca";

        immersion_cigs_initStateTime = 66;
        immersion_cigs_nextState = "murshun_cigs_cig3_nv";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cig2.p3d";
	    	modelOff = "\murshun_cigs\cig2.p3d";
        };
    };

    class murshun_cigs_cig3_nv: murshun_cigs_cig0_nv {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigarette (Stage 3)";
        model = "\murshun_cigs\cig3.p3d";
        picture = "\murshun_cigs\UI\gear_cig3_x_ca";

        immersion_cigs_initStateTime = 126;
        immersion_cigs_nextState = "murshun_cigs_cig4_nv";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cig3.p3d";
	    	modelOff = "\murshun_cigs\cig3.p3d";
        };
    };

    class murshun_cigs_cig4_nv: murshun_cigs_cig0_nv {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigarette (Stage 4)";
        model = "\murshun_cigs\cig4.p3d";
        picture = "\murshun_cigs\UI\gear_cig4_x_ca";

        immersion_cigs_initStateTime = 306;
        immersion_cigs_nextState = "";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cig4.p3d";
	    	modelOff = "\murshun_cigs\cig4.p3d";
        };
    };

    class immersion_cigs_cigar0_nv: NVGoggles {
        scope = 2;
        author = "$STR_murshun_cigs_author";
        mass = 0.1;
        displayName = "Cigar (NVG Slot)";
        model = "\murshun_cigs\cigars\cigar0.p3d";
        picture = "\murshun_cigs\UI\gear_cigar0_x_ca";
        visionMode[] = {"Normal"};
		thermalMode[] = {0};
		modelOptics[] = {};
		opticsPPEffects[] = {};

        immersion_cigs_type = "cigar";
        immersion_cigs_maxTime = 660;
        immersion_cigs_initStateTime = 0;
        immersion_cigs_nextState = "immersion_cigs_cigar1_nv";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cigars\cigar0.p3d";
	    	modelOff = "\murshun_cigs\cigars\cigar0.p3d";
        };
    };

    class immersion_cigs_cigar1_nv: immersion_cigs_cigar0_nv {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigar (Stage 1)";
        model = "\murshun_cigs\cigars\cigar1.p3d";
        picture = "\murshun_cigs\UI\gear_cigar1_x_ca";

        immersion_cigs_initStateTime = 12;
        immersion_cigs_nextState = "immersion_cigs_cigar2_nv";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cigars\cigar1.p3d";
	    	modelOff = "\murshun_cigs\cigars\cigar1.p3d";
        };
    };

    class immersion_cigs_cigar2_nv: immersion_cigs_cigar0_nv {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigar (Stage 2)";
        model = "\murshun_cigs\cigars\cigar2.p3d";
        picture = "\murshun_cigs\UI\gear_cigar2_x_ca";

        immersion_cigs_initStateTime = 132;
        immersion_cigs_nextState = "immersion_cigs_cigar3_nv";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cigars\cigar2.p3d";
	    	modelOff = "\murshun_cigs\cigars\cigar2.p3d";
        };
    };

    class immersion_cigs_cigar3_nv: immersion_cigs_cigar0_nv {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigar (Stage 3)";
        model = "\murshun_cigs\cigars\cigar3.p3d";
        picture = "\murshun_cigs\UI\gear_cigar3_x_ca";

        immersion_cigs_initStateTime = 252;
        immersion_cigs_nextState = "immersion_cigs_cigar4_nv";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cigars\cigar3.p3d";
	    	modelOff = "\murshun_cigs\cigars\cigar3.p3d";
        };
    };

    class immersion_cigs_cigar4_nv: immersion_cigs_cigar0_nv {
        scope = 1;
        author = "$STR_murshun_cigs_author";
        displayName = "Cigar (Stage 4)";
        model = "\murshun_cigs\cigars\cigar4.p3d";
        picture = "\murshun_cigs\UI\gear_cigar4_x_ca";

        immersion_cigs_initStateTime = 612;
        immersion_cigs_nextState = "";
        immersion_cigs_isCig = true;

        class ItemInfo
        {
            type = 616;
            hmdType = 0;
    		uniformModel = "\murshun_cigs\cigars\cigar4.p3d";
	    	modelOff = "\murshun_cigs\cigars\cigar4.p3d";
        };
    };
};
*/