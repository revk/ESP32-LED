// Settings
// Generated from:-
// main/settings.def
// components/ESP32-RevK/settings.def

#include <stdint.h>
#include <stddef.h>
typedef struct revk_settings_s revk_settings_t;
struct revk_settings_s {
 void *ptr;
 const char name[16];
 const char *def;
 const char *flags;
 const char *old;
 const char *unit;
 const char *comment;
 uint16_t size;
 uint8_t group;
 uint8_t bit;
 uint8_t dot:4;
 uint8_t len:4;
 uint8_t type:3;
 uint8_t decimal:5;
 uint8_t digits:5;
 uint8_t array:7;
 uint8_t malloc:1;
 uint8_t revk:1;
 uint8_t live:1;
 uint8_t hide:1;
 uint8_t fix:1;
 uint8_t set:1;
 uint8_t hex:1;
 uint8_t base32:1;
 uint8_t base64:1;
 uint8_t secret:1;
 uint8_t dq:1;
 uint8_t gpio:1;
 uint8_t rtc:1;
};
typedef struct revk_settings_blob_s revk_settings_blob_t;
struct revk_settings_blob_s {
 uint16_t len;
 uint8_t data[];
};
typedef struct revk_gpio_s revk_gpio_t;
struct revk_gpio_s {
 uint16_t num:10;
 uint16_t strong:1;
 uint16_t weak:1;
 uint16_t pulldown:1;
 uint16_t nopull:1;
 uint16_t invert:1;
 uint16_t set:1;
};
enum {
#ifdef  CONFIG_IDF_TARGET_ESP32
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#endif
 REVK_SETTINGS_BITFIELD_sk6812,
 REVK_SETTINGS_BITFIELD_rgbw,
 REVK_SETTINGS_BITFIELD_rgswap,
 REVK_SETTINGS_BITFIELD_bgswap,
 REVK_SETTINGS_BITFIELD_micright,
 REVK_SETTINGS_BITFIELD_haenable,
 REVK_SETTINGS_BITFIELD_poweron,
 REVK_SETTINGS_BITFIELD_clapon,
 REVK_SETTINGS_BITFIELD_stack,
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
 REVK_SETTINGS_BITFIELD_otaauto,
 REVK_SETTINGS_BITFIELD_otabeta,
 REVK_SETTINGS_BITFIELD_prefixapp,
 REVK_SETTINGS_BITFIELD_prefixhost,
#ifdef	CONFIG_REVK_BLINK_DEF
#endif
 REVK_SETTINGS_BITFIELD_dark,
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
#endif
#endif
#ifdef  CONFIG_REVK_MQTT
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
 REVK_SETTINGS_BITFIELD_wifips,
 REVK_SETTINGS_BITFIELD_wifimaxps,
#endif
#ifndef	CONFIG_REVK_MESH
 REVK_SETTINGS_BITFIELD_aplr,
 REVK_SETTINGS_BITFIELD_aphide,
#endif
#ifdef	CONFIG_REVK_MESH
 REVK_SETTINGS_BITFIELD_meshlr,
 REVK_SETTINGS_BITFIELD_meshroot,
#endif
};
typedef struct revk_settings_bits_s revk_settings_bits_t;
struct revk_settings_bits_s {
#ifdef  CONFIG_IDF_TARGET_ESP32
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#endif
 uint8_t sk6812:1;	// SK6812 (instead of WS2812)
 uint8_t rgbw:1;	// RGBW (no effects coded for this yet)
 uint8_t rgswap:1;	// Red/green swap
 uint8_t bgswap:1;	// Blue/green swap
 uint8_t micright:1;	// I2S Mic use right channel
 uint8_t haenable:1;	// Enable Home Assistant
 uint8_t poweron:1;	// Start effect 1 on power on
 uint8_t clapon:1;	// Clap to start effect 1
 uint8_t stack:1;	// Presets have priority, in order, else most recent on top
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
 uint8_t otaauto:1;	// OTA auto upgrade
 uint8_t otabeta:1;	// OTA from beta release
 uint8_t prefixapp:1;	// MQTT use appname/ in front of hostname in topic
 uint8_t prefixhost:1;	// MQTT use (appname/)hostname/topic instead of topic/(appname/)hostname
#ifdef	CONFIG_REVK_BLINK_DEF
#endif
 uint8_t dark:1;	// Default LED off
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
#endif
#endif
#ifdef  CONFIG_REVK_MQTT
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
 uint8_t wifips:1;	// WiFi power save
 uint8_t wifimaxps:1;	// WiFi power save (max)
#endif
#ifndef	CONFIG_REVK_MESH
 uint8_t aplr:1;	// AP LR mode
 uint8_t aphide:1;	// AP hide SSID
#endif
#ifdef	CONFIG_REVK_MESH
 uint8_t meshlr:1;	// Mesh use LR mode
 uint8_t meshroot:1;	// This is preferred mesh root
#endif
};
#ifdef  CONFIG_IDF_TARGET_ESP32
extern revk_gpio_t rgb[2];	// GPIO for LED chain
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
extern revk_gpio_t rgb[2];	// GPIO for LED chain
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
extern uint8_t cps;	// Change per second
#else
extern uint8_t cps;	// Change per second
#endif
extern revk_gpio_t relay;	// Relay for strip power
extern revk_gpio_t adc;	// ADC*13.4
extern revk_gpio_t button;	// Button
extern revk_gpio_t blink[3];	// Status LED
extern uint8_t maxr;	// Max RGB Red
extern uint8_t maxg;	// Max RGB Green
extern uint8_t maxb;	// Max RGB Blue
extern uint8_t maxw;	// Max RGBW White
#define	sk6812	revk_settings_bits.sk6812
#define	rgbw	revk_settings_bits.rgbw
#define	rgswap	revk_settings_bits.rgswap
#define	bgswap	revk_settings_bits.bgswap
extern uint16_t leds[2];	// How many LEDs
extern uint8_t webcontrol;	// Web controls
extern revk_gpio_t lsscl;	// Colour sensor SCL
extern revk_gpio_t lssda;	// Colour sensor SDA
extern uint8_t lsals;	// Colour sensor ID
extern revk_gpio_t micdata;	// I2S Mic Data / SD / DATA
extern revk_gpio_t micclock;	// I2S Mic Clock / BCLK / SCK
extern revk_gpio_t micws;	// I2S Mic WS / LR (not set for PDM mode)
#define	micright	revk_settings_bits.micright
extern uint8_t micdamp;	// I2S Mic Damping from peak (higher is slower)
extern uint8_t micmaxgain;	// Max mic gain
extern uint8_t micrange;	// Range for reactive effects
#define	haenable	revk_settings_bits.haenable
#define	poweron	revk_settings_bits.poweron
#define	clapon	revk_settings_bits.clapon
extern char* name[CONFIG_REVK_WEB_EXTRA_PAGES];	// Name (must be set to appear in HA)
extern char* colour[CONFIG_REVK_WEB_EXTRA_PAGES];	// Colour or palette name or #RGB style
extern uint16_t start[CONFIG_REVK_WEB_EXTRA_PAGES];	// First LED (default 1)
extern int16_t top[CONFIG_REVK_WEB_EXTRA_PAGES];	// Top LED (default to first)
extern uint16_t len[CONFIG_REVK_WEB_EXTRA_PAGES];	// Number of LEDs (default to end)
extern char* effect[CONFIG_REVK_WEB_EXTRA_PAGES];	// Default effect (leave blank for HA to pick)
extern uint8_t bright[CONFIG_REVK_WEB_EXTRA_PAGES];	// Brightness
extern int8_t height[CONFIG_REVK_WEB_EXTRA_PAGES];	// Text height
extern uint32_t delay[CONFIG_REVK_WEB_EXTRA_PAGES];	// Delay time, default 1s
extern uint32_t limit[CONFIG_REVK_WEB_EXTRA_PAGES];	// Time limit, default none
extern uint8_t speed[CONFIG_REVK_WEB_EXTRA_PAGES];	// Cycle time, default 1s
extern uint8_t fadein[CONFIG_REVK_WEB_EXTRA_PAGES];	// Fade in time, default 1s
extern uint8_t fadeout[CONFIG_REVK_WEB_EXTRA_PAGES];	// Fade out time, default 1s
extern char* config[CONFIG_REVK_WEB_EXTRA_PAGES];	// Settings as JSON and effect specific settings
#define	stack	revk_settings_bits.stack
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
extern char* password;	// Settings password (this is not sent securely so use with care on local networks you control)
#endif
extern char* hostname;	// Host name
extern char* appname;	// Application name
extern char* otahost;	// OTA hostname
extern uint8_t otadays;	// OTA auto load (days)
extern uint16_t otastart;	// OTA check after startup (min seconds)
#define	otaauto	revk_settings_bits.otaauto
#define	otabeta	revk_settings_bits.otabeta
extern revk_settings_blob_t* otacert;	// OTA cert of otahost
extern char* ntphost;	// NTP host
extern char* tz;	// Timezone (<a href='https://gist.github.com/alwynallan/24d96091655391107939' target=_blank>info</a>)
extern uint32_t watchdogtime;	// Watchdog (seconds)
extern char* topicgroup[2];	// MQTT Alternative hostname accepted for commands
extern char* topiccommand;	// MQTT Topic for commands
extern char* topicsetting;	// MQTT Topic for settings
extern char* topicstate;	// MQTT Topic for state
extern char* topicevent;	// MQTT Topic for event
extern char* topicinfo;	// MQTT Topic for info
extern char* topicerror;	// MQTT Topic for error
extern char* topicha;	// MQTT Topic for homeassistant
#define	prefixapp	revk_settings_bits.prefixapp
#define	prefixhost	revk_settings_bits.prefixhost
#ifdef	CONFIG_REVK_BLINK_DEF
extern revk_gpio_t blink[3];	// LED array
#endif
#define	dark	revk_settings_bits.dark
#ifdef  CONFIG_IDF_TARGET_ESP32S3
extern revk_gpio_t factorygpio;	// Factory reset GPIO (press 3 times)
#else
extern revk_gpio_t factorygpio;	// Factory reset GPIO (press 3 times)
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
extern uint16_t apport;	// TCP port for config web pages on AP
#endif
extern uint32_t aptime;	// Limit AP to time (seconds)
extern uint32_t apwait;	// Wait off line before starting AP (seconds)
extern revk_gpio_t apgpio;	// Start AP on GPIO
#endif
#ifdef  CONFIG_REVK_MQTT
extern char* mqtthost[CONFIG_REVK_MQTT_CLIENTS];	// MQTT hostname
extern uint16_t mqttport[CONFIG_REVK_MQTT_CLIENTS];	// MQTT port
extern char* mqttuser[CONFIG_REVK_MQTT_CLIENTS];	// MQTT username
extern char* mqttpass[CONFIG_REVK_MQTT_CLIENTS];	// MQTT password
extern revk_settings_blob_t* mqttcert[CONFIG_REVK_MQTT_CLIENTS];	// MQTT CA certificate
#endif
extern revk_settings_blob_t* clientkey;	// Client Key (OTA and MQTT TLS)
extern revk_settings_blob_t* clientcert;	// Client certificate (OTA and MQTT TLS)
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
extern uint16_t wifireset;	// Restart if WiFi off for this long (seconds)
extern char* wifissid;	// WiFI SSID (name)
extern char* wifipass;	// WiFi password
extern char* wifiip;	// WiFi Fixed IP
extern char* wifigw;	// WiFi Fixed gateway
extern char* wifidns[3];	// WiFi fixed DNS
extern uint8_t wifibssid[6];	// WiFI BSSID
extern uint8_t wifichan;	// WiFI channel
extern uint16_t wifiuptime;	// WiFI turns off after this many seconds
#define	wifips	revk_settings_bits.wifips
#define	wifimaxps	revk_settings_bits.wifimaxps
#endif
#ifndef	CONFIG_REVK_MESH
extern char* apssid;	// AP mode SSID (name)
extern char* appass;	// AP mode password
extern uint8_t apmax;	// AP max clients
extern char* apip;	// AP mode block
#define	aplr	revk_settings_bits.aplr
#define	aphide	revk_settings_bits.aphide
#endif
#ifdef	CONFIG_REVK_MESH
extern char* nodename;	// Mesh node name
extern uint16_t meshreset;	// Reset if mesh off for this long (seconds)
extern uint8_t meshid[6];	// Mesh ID (hex)
extern uint8_t meshkey[16];	// Mesh key
extern uint16_t meshwidth;	// Mesh width
extern uint16_t meshdepth;	// Mesh depth
extern uint16_t meshmax;	// Mesh max devices
extern char* meshpass;	// Mesh AP password
#define	meshlr	revk_settings_bits.meshlr
#define	meshroot	revk_settings_bits.meshroot
#endif
extern revk_settings_bits_t revk_settings_bits;
enum {
 REVK_SETTINGS_SIGNED,
 REVK_SETTINGS_UNSIGNED,
 REVK_SETTINGS_BIT,
 REVK_SETTINGS_BLOB,
 REVK_SETTINGS_STRING,
 REVK_SETTINGS_JSON,
 REVK_SETTINGS_OCTET,
};
#define	REVK_SETTINGS_HAS_OLD
#define	REVK_SETTINGS_HAS_UNIT
#define	REVK_SETTINGS_HAS_COMMENT
#define	REVK_SETTINGS_HAS_GPIO
#define	REVK_SETTINGS_HAS_NUMERIC
#define	REVK_SETTINGS_HAS_SIGNED
#define	REVK_SETTINGS_HAS_UNSIGNED
#define	REVK_SETTINGS_HAS_BIT
#define	REVK_SETTINGS_HAS_BLOB
#define	REVK_SETTINGS_HAS_STRING
#define	REVK_SETTINGS_HAS_JSON
#define	REVK_SETTINGS_HAS_OCTET
#define	delay_scale	10
#define	limit_scale	10
#define	speed_scale	10
#define	fadein_scale	10
#define	fadeout_scale	10
typedef uint8_t revk_setting_bits_t[14];
typedef uint8_t revk_setting_group_t[2];
extern const char revk_settings_secret[];
