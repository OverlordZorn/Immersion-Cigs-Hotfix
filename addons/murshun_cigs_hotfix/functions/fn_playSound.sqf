// no scheduler needed
//murshun_cigs_fnc_playSound
params ["_unit", "_class"];
[_unit, _class] remoteExec ["say3D"];
diag_log "[Cigs-Hotfix] soundPlayed";