# 🚓 VEHICLE PLUS
If you have any problems or bugs, call me on discord or open an issue in this repository.

## 📝 New Functions [ENG/PT-BR]
```pawn
SetVehicleColor(vehicleid, color1, color2)
SetVehicleEngine(vehicleid, bool:status) OR SetVehicleMotor(vehicleid, bool:status)
SetVehicleDoorLock(vehicleid, bool:status) OR SetVehiclePorta(vehicleid, bool:status)
SetVehicleLights(vehicleid, bool:status) OR SetVehicleLuz(vehicleid, bool:status)
SetVehicleAlarm(vehicleid, bool:status) OR SetVehicleAlarme(vehicleid, bool:status)
SetVehicleBonnet(vehicleid, bool:status) OR SetVehicleCapo(vehicleid, bool:status)
SetVehicleBoot(vehicleid, bool:status) OR SetVehiclePortaMalas(vehicleid, bool:status)
//
GetVehicleColor(vehicleid, &color1, &color2 = (opitional))
GetVehicleStatusMotor(vehicleid) OR GetVehicleStatusEngine(vehicleid)
GetVehicleStatusDoor(vehicleid) OR GetVehicleStatusPorta(vehicleid)
GetVehicleStatusLight(vehicleid) OR GetVehicleStatusLuz(vehicleid)
GetVehicleStatusAlarm(vehicleid) OR GetVehicleStatusAlarme(vehicleid)
GetVehicleStatusBonnet(vehicleid) OR GetVehicleStatusCapo(vehicleid)
GetVehicleStatusBoot(vehicleid) OR GetVehicleStatusPortaMalas(vehicleid)
```

## 🫧 New Callbacks
```pawn
public OnVehicleConnect(vehicleid);
public OnVehicleDisconnect(vehicleid);
public OnVehicleColorUpdate(vehicleid, color1, color2);
public OnVehiclePlateUpdate(vehicleid, const newplate[]);
//
public OnVehicleBonnetUpdate(vehicleid, bool:status);  // Capô
public OnVehicleBootUpdate(vehicleid, bool:status);  // Porta Malas
public OnVehicleEngineUpdate(vehicleid, bool:status);
public OnVehicleDoorsUpdate(vehicleid, bool:status);
public OnVehicleLightsUpdate(vehicleid, bool:status);
public OnVehicleAlarmUpdate(vehicleid, bool:status);
```
