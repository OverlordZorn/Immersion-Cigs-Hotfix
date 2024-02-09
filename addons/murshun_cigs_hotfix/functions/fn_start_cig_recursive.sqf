params ["_unit","_cigTime","_gogglesCurrent","_hmdCurrent","_cigTypeGear","_cigClass","_cigType","_maxTime"];

diag_log "[Cigs-Hotfix] start-cig-recursive start";
diag_log format ["[Cigs-Hotfix] start-cig-recursive _this: %1", _this];


switch (_cigTypeGear) do {
    case ("GOGGLES"): {
        _gogglesCurrent = goggles _unit;
        _cigClass = configFile >> "CfgGlasses" >> _gogglesCurrent;
    };
    case ("HMD"): {
        _hmdCurrent = hmd _unit;
        _cigClass = configFile >> "CfgWeapons" >> _hmdCurrent;
    };
};

private _gogglesNew = "";

_nextCigState = getText (_cigClass >> "immersion_cigs_nextState");

private _nextCigStateTime = 0;

switch (_cigTypeGear) do {
    case ("GOGGLES"): {
        _nextCigStateTime = getNumber (configFile >> "CfgGlasses" >> _nextCigState >> "immersion_cigs_initStateTime");
    };
    case ("HMD"): {
        _nextCigStateTime = getNumber (configFile >> "CfgWeapons" >> _nextCigState >> "immersion_cigs_initStateTime");
    };
};

if (_cigTime >= _nextCigStateTime) then {
    _gogglesNew = _nextCigState;
};

if (_gogglesNew != "") then {
    switch (_cigTypeGear) do {
        case ("GOGGLES"): {
            removeGoggles _unit;
            _unit addGoggles _gogglesNew;
        };
        case ("HMD"): {
            _unit removeWeapon _hmdCurrent;
            _unit addWeapon _gogglesNew;
        };
    };

    _gogglesCurrent = _gogglesNew;
    _hmdCurrent = _gogglesNew;
};

private _time = (5.5 + random 2);

_cigTime = _cigTime + _time;

[_unit, _cigType] remoteExecCall ["murshun_cigs_fnc_smoke"];
_unit setFatigue (getFatigue _unit + 0.01);

private _timeToSleep = time + _time;

private _shouldExitLoop = false;


[
    {
        // Check the Conditions
        params ["_unit","_cigTime","_gogglesCurrent","_hmdCurrent","_cigTypeGear","_cigClass","_cigType","_maxTime","_timeToSleep"];
        
        private _condition1 = (!(alive _unit && (_gogglesCurrent in murshun_cigs_cigsArray || _hmdCurrent in murshun_cigs_cigsArray) && (_unit getVariable ["murshun_cigs_cigLitUp", false]) && _cigTime <= _maxTime));
        private _condition2 = (_cigTypeGear == "GOGGLES" && _gogglesCurrent != goggles _unit);
        private _condition3 = (_cigTypeGear == "HMD" && _hmdCurrent != hmd _unit);

        if (_condition1) then {diag_log format ["[Cigs-Hotfix] start-cig-recursive condition 1: %1", _condition1 ]; };
        if (_condition2) then {diag_log format ["[Cigs-Hotfix] start-cig-recursive condition 2: %1", _condition2 ]; };
        if (_condition3) then {diag_log format ["[Cigs-Hotfix] start-cig-recursive condition 3: %1", _condition3 ]; };

        _condition1 ||_condition2 || _condition3

    },
    {
        params ["_unit","_cigTime","_gogglesCurrent","_hmdCurrent","_cigTypeGear","_cigClass","_cigType","_maxTime","_timeToSleep"];

        diag_log format ["[Cigs-Hotfix] start-cig-recursive exit condition detected: %1", ""];
        diag_log format ["[Cigs-Hotfix] start-cig-recursive _this: %1", _this];


        [_unit, "immersion_cigs_cig_out", 1] call murshun_cigs_fnc_anim;

        _unit setVariable ["murshun_cigs_cigLitUp", false, true];

        if (_cigTime >= _maxTime) then {
            switch (_cigTypeGear) do {
                case ("GOGGLES"): {
                    removeGoggles _unit;
                };
                case ("HMD"): {
                    _unit removeWeapon (hmd _unit);
                };
            };
        };
    },
    [_unit,_cigTime,_gogglesCurrent,_hmdCurrent,_cigTypeGear,_cigClass,_cigType,_maxTime, _timeToSleep], //parameters to be taken into the cba_waituntil
    _timeToSleep,      // _timeout time in sec. 

    {
        diag_log "[Cigs-Hotfix] start-cig-recursive no exit detected -> restart";
        diag_log format ["[Cigs-Hotfix] start-cig-recursive _this: %1", _this];
        params ["_unit","_cigTime","_gogglesCurrent","_hmdCurrent","_cigTypeGear","_cigClass","_cigType","_maxTime","_timeToSleep"];


        [_unit,_cigTime,_gogglesCurrent,_hmdCurrent,_cigTypeGear,_cigClass,_cigType,_maxTime] call murshun_cigs_fnc_start_cig_recursive;


        // restart the recursive function
    }      // _timeoutCode - will be executed instead of _statement if the condition times out.

] call CBA_fnc_waitUntilAndExecute;
