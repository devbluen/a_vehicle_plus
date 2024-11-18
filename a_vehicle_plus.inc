
            // Definers
#define         MAX_VEHICLE_PLATE       (18)

            // Forwards
forward OnVehicleConnect(vehicleid);
forward OnVehicleDisconnect(vehicleid);
forward OnVehicleColorUpdate(vehicleid, color1, color2);
forward OnVehiclePlateUpdate(vehicleid, const newplate[]);

static enum E_VEHICLE_PLUS {
    E_VEHICLE_PLATE[MAX_VEHICLE_PLATE + 1],
    E_VEHICLE_COLOR_1,
    E_VEHICLE_COLOR_2,
    E_VEHICLE_RESPAWN_DELAY,
    bool:E_VEHICLE_SIREN,
    Float:E_VEHICLE_SPAWNPOINT[4],

    // Params
    bool:E_VEHICLE_ENGINE,
    bool:E_VEHICLE_LIGHTS,
    bool:E_VEHICLE_ALARM,
    bool:E_VEHICLE_DOORS,
    bool:E_VEHICLE_BONNET,  // Capô [PT-BR]
    bool:E_VEHICLE_BOOT     // Porta Malas [PT-BR]
};

static e_VehiclePlus[MAX_VEHICLES][E_VEHICLE_PLUS];



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

public OnVehicleStreamIn(vehicleid, forplayerid) {
    SetVehicleFixParams(forplayerid, vehicleid);

    #if defined HOOK_OnVehicleStreamIn
       return HOOK_OnVehicleStreamIn(vehicleid, forplayerid);
    #else 
        return true;
    #endif
}



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock alsCreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, bool:addsiren = false) {
    new vehicleid = CreateVehicle(vehicletype, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
    CreateVehicle_ConfigData(vehicleid, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
    return vehicleid;
}

stock alsAddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2) {
    new vehicleid = AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2);
    CreateVehicle_ConfigData(vehicleid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2);
    return vehicleid;
}

stock alsAddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, bool:addsiren = false) {
    new vehicleid = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay, addsiren);
    CreateVehicle_ConfigData(vehicleid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay, addsiren);
    return vehicleid;
}

stock alsDestroyVehicle(vehicleid) {

    CallLocalFunction("OnVehicleDisconnect", "i", vehicleid);

    static const e_Clear[E_VEHICLE_PLUS];
    e_VehiclePlus[vehicleid] = e_Clear;
    return DestroyVehicle(vehicleid);
}

stock alsChangeVehicleColor(vehicleid, color1, color2) {

    color1 = color1 == -1 ? e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_1] : color1;
    color2 = color2 == -1 ? e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_2] : color2;

    e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_1] = color1;
    e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_2] = color2;

    CallLocalFunction("OnVehicleColorUpdate", "iii", vehicleid, color1, color2);
    return ChangeVehicleColor(vehicleid, color1, color2);
}

stock alsSetVehicleNumberPlate(vehicleid, const numberplate[]) {
    format(e_VehiclePlus[vehicleid][E_VEHICLE_PLATE], MAX_VEHICLE_PLATE, numberplate);

    CallLocalFunction("OnVehiclePlateUpdate", "is", vehicleid, numberplate);
    return SetVehicleNumberPlate(vehicleid, numberplate);
}



/*

                    oooooooooooo oooooooooooo       .o.       ooooooooooooo ooooo     ooo ooooooooo.   oooooooooooo  .oooooo..o 
                    `888'     `8 `888'     `8      .888.      8'   888   `8 `888'     `8' `888   `Y88. `888'     `8 d8P'    `Y8 
                    888          888             .8"888.          888       888       8   888   .d88'  888         Y88bo.      
                    888oooo8     888oooo8       .8' `888.         888       888       8   888ooo88P'   888oooo8     `"Y8888o.  
                    888    "     888    "      .88ooo8888.        888       888       8   888`88b.     888    "         `"Y88b 
                    888          888       o  .8'     `888.       888       `88.    .8'   888  `88b.   888       o oo     .d8P 
                    o888o        o888ooooood8 o88o     o8888o     o888o        `YbodP'    o888o  o888o o888ooooood8 8""88888P'  

*/

stock GetVehiclePlate(vehicleid) {
    new string[MAX_VEHICLE_PLATE + 1];
    strcat(string, e_VehiclePlus[vehicleid][E_VEHICLE_PLATE]);
    return string;
}

stock SetVehicleColor(vehicleid, color1, color2) {
    alsChangeVehicleColor(vehicleid, color1, color2);
}

stock GetVehicleColor(vehicleid, &color1, &color2 = 0) {

    color1 = e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_1];
    color2 = e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_2];
}

stock SetVehicleMotor(vehicleid, bool:status) {SetVehicleEngine(vehicleid, status);}
stock SetVehicleEngine(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_ENGINE] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_ENGINE] = status;
    SetVehicleFixParams(vehicleid);  
}

stock SetVehiclePorta(vehicleid, bool:status) {SetVehicleDoorLock(vehicleid, status);}
stock SetVehicleDoorLock(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_DOORS] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_DOORS] = status;
    SetVehicleFixParams(vehicleid);
}

stock SetVehicleLuz(vehicleid, bool:status) {SetVehicleLights(vehicleid, status);}
stock SetVehicleLights(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_LIGHTS] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_LIGHTS] = status;
    SetVehicleFixParams(vehicleid);    
}

stock SetVehicleAlarme(vehicleid, bool:status) {SetVehicleAlarm(vehicleid, status);}
stock SetVehicleAlarm(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_ALARM] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_ALARM] = status;
    SetVehicleFixParams(vehicleid);       
}

stock SetVehicleCapo(vehicleid, bool:status) {SetVehicleBonnet(vehicleid, status);}
stock SetVehicleBonnet(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_BONNET] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_BONNET] = status;
    SetVehicleFixParams(vehicleid);     
}

stock SetVehiclePortaMalas(vehicleid, bool:status) {SetVehicleBoot(vehicleid, status);}
stock SetVehicleBoot(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_BOOT] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_BOOT] = status;
    SetVehicleFixParams(vehicleid);     
}

stock bool:GetVehicleStatusEngine(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_ENGINE]);
stock bool:GetVehicleStatusMotor(vehicleid) return GetVehicleStatusEngine(vehicleid);

stock bool:GetVehicleStatusDoor(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_DOORS]);
stock bool:GetVehicleStatusPorta(vehicleid) return GetVehicleStatusDoor(vehicleid);

stock bool:GetVehicleStatusLight(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_LIGHTS]);
stock bool:GetVehicleStatusLuz(vehicleid) return GetVehicleStatusLight(vehicleid);

stock bool:GetVehicleStatusAlarm(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_ALARM]);
stock bool:GetVehicleStatusAlarme(vehicleid) return GetVehicleStatusAlarm(vehicleid);

stock bool:GetVehicleStatusBonnet(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_BONNET]);
stock bool:GetVehicleStatusCapo(vehicleid) return GetVehicleStatusBonnet(vehicleid);

stock bool:GetVehicleStatusBoot(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_BONNET]);
stock bool:GetVehicleStatusPortaMalas(vehicleid) return GetVehicleStatusBoot(vehicleid);

static stock SetVehicleFixParams(vehicleid, playerid = INVALID_PLAYER_ID) {

    if(playerid == INVALID_PLAYER_ID) SetVehicleParamsEx(vehicleid, 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_ENGINE], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_LIGHTS], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_ALARM], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_DOORS], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_BONNET], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_BOOT], 
                                                            false);
    else SetVehicleParamsForPlayer(vehicleid, playerid, false, e_VehiclePlus[vehicleid][E_VEHICLE_DOORS]);
}

static stock CreateVehicle_ConfigData(vehicleid, Float:x, Float:y, Float:z, Float:a, color1, color2, respawn_delay = 0, bool:addsiren = false) {

    color1 = color1 == -1 ? random(999) : color1;
    color2 = color2 == -1 ? random(999) : color2;

    e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_1] = color1;
    e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_2] = color2;
    e_VehiclePlus[vehicleid][E_VEHICLE_RESPAWN_DELAY] = respawn_delay;
    e_VehiclePlus[vehicleid][E_VEHICLE_SIREN] = addsiren;
    
    e_VehiclePlus[vehicleid][E_VEHICLE_SPAWNPOINT][0] = x;
    e_VehiclePlus[vehicleid][E_VEHICLE_SPAWNPOINT][1] = y;
    e_VehiclePlus[vehicleid][E_VEHICLE_SPAWNPOINT][2] = z;
    e_VehiclePlus[vehicleid][E_VEHICLE_SPAWNPOINT][3] = a;

    CallLocalFunction("OnVehicleConnect", "i", vehicleid);   
}



/*

                    ooo        ooooo       .o.         .oooooo.   ooooooooo.     .oooooo.    .oooooo..o 
                    `88.       .888'      .888.       d8P'  `Y8b  `888   `Y88.  d8P'  `Y8b  d8P'    `Y8 
                    888b     d'888      .8"888.     888           888   .d88' 888      888 Y88bo.      
                    8 Y88. .P  888     .8' `888.    888           888ooo88P'  888      888  `"Y8888o.  
                    8  `888'   888    .88ooo8888.   888           888`88b.    888      888      `"Y88b 
                    8    Y     888   .8'     `888.  `88b    ooo   888  `88b.  `88b    d88' oo     .d8P 
                    o8o        o888o o88o     o8888o  `Y8bood8P'  o888o  o888o  `Y8bood8P'  8""88888P'  

*/

#if defined _ALS_CreateVehicle
    #undef CreateVehicle
#else
    #define _ALS_CreateVehicle
#endif
 
#define CreateVehicle alsCreateVehicle

#if defined _ALS_AddStaticVehicle
    #undef AddStaticVehicle
#else
    #define _ALS_AddStaticVehicle
#endif
 
#define AddStaticVehicle alsAddStaticVehicle

#if defined _ALS_AddStaticVehicleEx
    #undef AddStaticVehicleEx
#else
    #define _ALS_AddStaticVehicleEx
#endif
 
#define AddStaticVehicleEx alsAddStaticVehicleEx

#if defined _ALS_ChangeVehicleColor
    #undef ChangeVehicleColor
#else
    #define _ALS_ChangeVehicleColor
#endif
 
#define ChangeVehicleColor alsChangeVehicleColor

#if defined _ALS_SetVehicleNumberPlate
    #undef SetVehicleNumberPlate
#else
    #define _ALS_SetVehicleNumberPlate
#endif
 
#define SetVehicleNumberPlate alsSetVehicleNumberPlate

#if defined _ALS_DestroyVehicle
    #undef DestroyVehicle
#else
    #define _ALS_DestroyVehicle
#endif
 
#define DestroyVehicle alsDestroyVehicle

#if defined _ALS_OnVehicleStreamIn
    #undef OnVehicleStreamIn
#else
    #define _ALS_OnVehicleStreamIn
#endif
#define OnVehicleStreamIn HOOK_OnVehicleStreamIn
#if defined HOOK_OnVehicleStreamIn
    forward HOOK_OnVehicleStreamIn(vehicleid, forplayerid); 
#endif 
