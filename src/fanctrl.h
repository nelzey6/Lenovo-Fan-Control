/* A fan control application for Lenovo laptops.
 * 
 * References:
 * https://github.com/bitrate16/FanControl/blob/main/FanControl/FanControl.cpp
 * https://github.com/Soberia/Lenovo-IdeaPad-Z500-Fan-Controller?tab=readme-ov-file#-about
 * https://www.allstone.lt/ideafan/
 */
#ifndef LENOVO_FAN_CONTROL_H
#define LENOVO_FAN_CONTROL_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Set this variable to 0 to terminate keep_fan_running()
 */
volatile extern int is_keep_fan_running;

/**
 * Set this variable to 0 to terminate keep_fan_speed_low()
 */
volatile extern int is_keep_fan_speed_low;

/**
 * Timing configuration for keep_fan_running().
 *
 * cycle_ms: How long to keep the dust-removal procedure active before
 *           resetting it back to normal mode.
 * poll_ms:  How often to poll the driver while high speed mode is active.
 *           If firmware stops the dust-removal procedure early, the app
 *           immediately re-issues FAST mode on the next poll.
 */
typedef struct {
    DWORD cycle_ms;
    DWORD poll_ms;
} KeepFanRunningConfig;

/**
 * Possible fan spinning mode.
 *
 * NORMAL: Fan spins at normal speed.
 * FAST: Fan spins at maximum speed.
 */
enum FanMode { NORMAL, FAST };

/**
 * Control the operating mode of the fan.
 *
 * @param mode: Set the fan spinning mode:
 *      NORMAL  Spin at normal speed.
 *      FAST    Spin at maximum speed.
 * @return Operating result:
 *      -1  Failed to access \\.\EnergyDrv device.
 *      1   Succeeded.
 */
int fan_control(enum FanMode mode);

/**
 * Get the current operating mode of the fan.
 *
 * @return The current status of the fan:
 *      -1      Failed to access \\.\EnergyDrv device.
 *      NORMAL  Spin at normal speed.
 *      FAST    Spin at maximum speed.
 */
enum FanMode read_state();

/**
 * Configure timing for keep_fan_running().
 */
void set_keep_fan_running_config(KeepFanRunningConfig config);

/**
 * Try to keep the fan in fast mode. 
 * Block until done. Or set "is_keep_fan_running" variable to 0 to terminate.
 * 
 * For more information, refer to:
 * https://github.com/Soberia/Lenovo-IdeaPad-Z500-Fan-Controller?tab=readme-ov-file#-about
 */
void keep_fan_running();

/**
 * Try to keep the fan spinning at the lowest speed.
 * Block until done. Or set "is_keep_fan_speed_low" variable to 0 to terminate.
 * 
 * Note: Use this function with caution, as it may cause hardware damage from
 * high temperatures.
 */
void keep_fan_speed_low();

#ifdef __cplusplus
}
#endif

#endif
