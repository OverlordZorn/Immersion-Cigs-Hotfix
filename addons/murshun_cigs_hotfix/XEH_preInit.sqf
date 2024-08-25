#include "script_component.hpp"

ADDON = false;

PREP_RECOMPILE_START;
//#include "XEH_PREP.hpp"
PREP_RECOMPILE_END;
// ### Non Functions - Checks and Arrays
// Doesnt need to be scheduled

if !(isClass (configFile >> "CfgPatches" >> "ace_common")) then {
    ace_common_fnc_displayTextStructured = {
        params ["_string"];
        hintSilent _string;
    };
};

// Doesnt need to be scheduled
if (isNil "immersion_cigs_giveItemsInSP") then {
    immersion_cigs_giveItemsInSP = true;
};

murshun_cigs_cigsArray = ["EWK_Cigar1", "EWK_Cigar2", "EWK_Cig1", "EWK_Cig2", "EWK_Cig3", "EWK_Cig4", "EWK_Glasses_Cig1", "EWK_Glasses_Cig2", "EWK_Glasses_Cig3", "EWK_Glasses_Cig4", "EWK_Glasses_Shemag_GRE_Cig6", "EWK_Glasses_Shemag_NB_Cig6", "EWK_Glasses_Shemag_tan_Cig6", "EWK_Cig5", "EWK_Glasses_Cig5", "EWK_Cig6", "EWK_Glasses_Cig6", "EWK_Shemag_GRE_Cig6", "EWK_Shemag_NB_Cig6", "EWK_Shemag_tan_Cig6"] + (("getNumber (_x >> 'immersion_cigs_isCig') == 1" configClasses (configFile >> "CfgGlasses")) apply {configName _x}) + (("getNumber (_x >> 'immersion_cigs_isCig') == 1" configClasses (configFile >> "CfgWeapons")) apply {configName _x});

immersion_cigs_canStartSmoking = {
    params ["_unit"];

    (((goggles _unit) in murshun_cigs_cigsArray) || ((hmd _unit) in murshun_cigs_cigsArray)) && !(_unit getVariable ['murshun_cigs_cigLitUp', false])
};

immersion_cigs_canStopSmoking = {
    params ["_unit"];

    (((goggles _unit) in murshun_cigs_cigsArray) || ((hmd _unit) in murshun_cigs_cigsArray)) && (_unit getVariable ['murshun_cigs_cigLitUp', false])
};

immersion_cigs_canTakeCigFromPack = {
    params ["_unit"];
    "murshun_cigs_cigpack" in (magazines _unit)
};

ADDON = true;