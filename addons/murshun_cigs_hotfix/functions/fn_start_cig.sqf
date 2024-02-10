params ["_unit"];

if (!(local _unit)) exitWith {};

private _cigTime = 0;

private _gogglesCurrent = goggles _unit;
private _hmdCurrent = hmd _unit;

private _cigTypeGear = "";

if (_gogglesCurrent in murshun_cigs_cigsArray) then {
    _cigTypeGear = "GOGGLES";
};

if (_hmdCurrent in murshun_cigs_cigsArray) then {
    _cigTypeGear = "HMD";
};

if (_cigTypeGear == "") exitWith {};

private _cigClass = configFile;

switch (_cigTypeGear) do {
    case ("GOGGLES"): {
        _cigClass = configFile >> "CfgGlasses" >> _gogglesCurrent;
    };
    case ("HMD"): {
        _cigClass = configFile >> "CfgWeapons" >> _hmdCurrent;
    };
};

_cigTime = getNumber (_cigClass >> "immersion_cigs_initStateTime");

if (_unit getVariable ["murshun_cigs_cigLitUp", false]) exitWith {};
_unit setVariable ["murshun_cigs_cigLitUp", true, true];

[_unit, "immersion_cigs_cig_in", 3] call murshun_cigs_fnc_anim;

private _cigType = getText (_cigClass >> "immersion_cigs_type");


private _sleep1 = (3.5 + random 2);
private _sleep2 = _sleep1 + (1 + random 1);

private _code = {   
    params ["_unit", "_cigType"];
    [_unit, _cigType] remoteExecCall ["murshun_cigs_fnc_smoke"];
};
[_code, [_unit, _cigType], _sleep1] call CBA_fnc_waitAndExecute;
[_code, [_unit, _cigType], _sleep2] call CBA_fnc_waitAndExecute;

_code = {
    params ["_unit","_cigTime","_gogglesCurrent","_hmdCurrent","_cigTypeGear","_cigClass","_cigType"];

    private _maxTime = getNumber (_cigClass >> "immersion_cigs_maxTime");
    if (_maxTime == 0) then {
        _maxTime = 330;
    };

    [_unit,_cigTime,_gogglesCurrent,_hmdCurrent,_cigTypeGear,_cigClass,_cigType,_maxTime] call murshun_cigs_fnc_start_cig_recursive;

};

[_code, [_unit,_cigTime,_gogglesCurrent,_hmdCurrent,_cigTypeGear,_cigClass,_cigType], _sleep2] call CBA_fnc_waitAndExecute;