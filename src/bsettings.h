#ifndef _Badge_BSettings_h
#define _Badge_BSettings_h

/*
	bsettings.h -- part of the VegasBadge2018 project.
	Hard-coded system settings, configurable through #defines
*/



/* Defaults should be fine, but you may set each to
	something appropriate for your situation.
*/

// serial_baud_rate -- connect to device at this baud rate
#define serial_baud_rate			57600


// have a "heartbeat" function to hook-up. It will be called 
// periodically while someone is connected...
// Set heartbeat_function_period_ms (millis) to specify
// how often it will be called
#define heartbeat_function_period_ms  50


// serial_maxidle_ms -- how long before we consider the user
// gone, for lack of activity (milliseconds)
#define serial_maxidle_ms			30000

// serial_readtimeout_ms -- timeout when we're expecting input
// for a specific request/read (milliseconds)
#define serial_readtimeout_ms		20000

#define serial_ui_greeting_str	"+++ VegasBadge2018 +++\r\nEnter '?' for options."
// serial_input_terminator -- what we consider an <ENTER> (i.e. newline)
#define serial_input_terminator		'\n'

// if you included requests for "strings",
// request_inputstring_maxlen will set the max length allowable
// (bigger need more RAM)
#define request_inputstring_maxlen	50

#endif
