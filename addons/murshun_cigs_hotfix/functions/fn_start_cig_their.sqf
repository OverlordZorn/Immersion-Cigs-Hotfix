// murshun_cigs_fnc_start_cig_their
params ["_unit", "_player"];

if !([_unit, _player] call murshun_cigs_fnc_useItem) exitWith {};
_player playActionNow "PutDown";
[_unit] remoteExecCall ["murshun_cigs_fnc_start_cig", _unit];