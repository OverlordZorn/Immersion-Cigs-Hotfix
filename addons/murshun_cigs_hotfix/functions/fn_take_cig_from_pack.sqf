// Doesnt need to be scheduled
// murshun_cigs_fnc_take_cig_from_pack
params ["_player"];

[_player, "murshun_cigs_cigpack"] call murshun_cigs_fnc_removeItemFromMag;

[_player, "murshun_cigs_unwrap"] call murshun_cigs_fnc_playSound;

if (goggles _player == "") then {
    _player addGoggles "murshun_cigs_cig0";
} else {
    if (hmd _player == "") then {
        _player addItem "murshun_cigs_cig0_nv";
        _player assignItem "murshun_cigs_cig0_nv";            
    } else {
        _player addItem "murshun_cigs_cig0";
    };
};
