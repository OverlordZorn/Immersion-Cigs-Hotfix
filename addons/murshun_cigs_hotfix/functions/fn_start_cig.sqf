// Current WIP
// needs to be unscheduled
// TODO remoteexec -> RemoteExecCall

murshun_cigs_fnc_start_cig = {
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


    _code = {
        params ["_unit", "_cigType"];
        [_unit, _cigType] remoteExecCall ["murshun_cigs_fnc_smoke"];
    };
    
    [_code, [_unit, _cigType], (3.5 + random 2)] call CBA_fnc_waitAndExecute;


/// Sleep
    sleep (1 + random 1);                                                                           /// Sleep 1.0 ~ 2.0
    [_unit, _cigType] remoteExecCall ["murshun_cigs_fnc_smoke"];


    private _maxTime = getNumber (_cigClass >> "immersion_cigs_maxTime");

    if (_maxTime == 0) then {
        _maxTime = 330;
    };

//// START OF WHILE LOOP
    while ({true}) do {
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

        waitUntil {
            if (!(alive _unit && (_gogglesCurrent in murshun_cigs_cigsArray || _hmdCurrent in murshun_cigs_cigsArray) && (_unit getVariable ["murshun_cigs_cigLitUp", false]) && _cigTime <= _maxTime)) exitWith {
                _shouldExitLoop = true;

                true
            };

            if (_cigTypeGear == "GOGGLES" && _gogglesCurrent != goggles _unit) exitWith {
                _shouldExitLoop = true;

                true
            };

            if (_cigTypeGear == "HMD" && _hmdCurrent != hmd _unit) exitWith {
                _shouldExitLoop = true;

                true
            };

            time > _timeToSleep
        };

        if (_shouldExitLoop) exitWith {};
    };
////End of While{true}

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
};