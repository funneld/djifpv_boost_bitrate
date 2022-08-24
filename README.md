# DJI FPV Bitrate booster

Increases the bitrate up to 30Mbit in 25Mbit mode and 59.9Mbit in 50Mbit mode.


## Reported side effects
- higher latency(delay).
- more missed frames that cause a stuttering effect. This is more noticeable in fast flights.
- seemingly more issues with Vistas than standard Airunits. Possibly due to some extra heat generated when encoding at a higher bitrate(unconfirmed).

## Manual installation

Install:
- `download ipk`
- `opkg install package-name.ipk`

Compile:
- `make ipk`
