// Settings
// Generated from:-
// main/settings.def
// components/ESP32-RevK/settings.def

#include <stdint.h>
#include "sdkconfig.h"
#include "settings.h"
revk_settings_bits_t revk_settings_bits={0};
#define	str(s)	#s
#define	quote(s)	str(s)
revk_settings_t const revk_settings[]={
#ifdef  CONFIG_IDF_TARGET_ESP32
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="rgb",.comment="GPIO for LED chain",.len=3,.def="22",.ptr=&rgb,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.array=2},
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="rgb",.comment="GPIO for LED chain",.len=3,.def="4",.ptr=&rgb,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.array=2},
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
 {.type=REVK_SETTINGS_UNSIGNED,.name="cps",.comment="Change per second",.len=3,.def="25",.ptr=&cps,.size=sizeof(uint8_t),.unit="/s"		},
#else
 {.type=REVK_SETTINGS_UNSIGNED,.name="cps",.comment="Change per second",.len=3,.def="10",.ptr=&cps,.size=sizeof(uint8_t),.unit="/s"		},
#endif
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="relay",.comment="Relay for strip power",.len=5,.ptr=&relay,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="adc",.comment="ADC*13.4",.len=3,.ptr=&adc,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="button",.comment="Button",.len=6,.ptr=&button,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="blink",.comment="Status LED",.len=5,.ptr=&blink,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.array=3},
 {.type=REVK_SETTINGS_UNSIGNED,.name="maxr",.comment="Max RGB Red",.group=1,.len=4,.dot=3,.def="255",.ptr=&maxr,.size=sizeof(uint8_t),.unit="/255"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="maxg",.comment="Max RGB Green",.group=1,.len=4,.dot=3,.def="255",.ptr=&maxg,.size=sizeof(uint8_t),.unit="/255"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="maxb",.comment="Max RGB Blue",.group=1,.len=4,.dot=3,.def="255",.ptr=&maxb,.size=sizeof(uint8_t),.unit="/255"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="maxw",.comment="Max RGBW White",.group=1,.len=4,.dot=3,.def="255",.ptr=&maxw,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_BIT,.name="sk6812",.comment="SK6812 (instead of WS2812)",.len=6,.bit=REVK_SETTINGS_BITFIELD_sk6812,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="rgbw",.comment="RGBW (no effects coded for this yet)",.len=4,.bit=REVK_SETTINGS_BITFIELD_rgbw,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="rgswap",.comment="Red/green swap",.len=6,.bit=REVK_SETTINGS_BITFIELD_rgswap,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="bgswap",.comment="Blue/green swap",.len=6,.bit=REVK_SETTINGS_BITFIELD_bgswap,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="leds",.comment="How many LEDs",.len=4,.ptr=&leds,.size=sizeof(uint16_t),.hide=1,.array=2},
 {.type=REVK_SETTINGS_UNSIGNED,.name="webcontrol",.comment="Web controls",.len=10,.def="2",.ptr=&webcontrol,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="lsscl",.comment="Colour sensor SCL",.group=2,.len=5,.dot=2,.ptr=&lsscl,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="lssda",.comment="Colour sensor SDA",.group=2,.len=5,.dot=2,.ptr=&lssda,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.name="lsals",.comment="Colour sensor ID",.group=2,.len=5,.dot=2,.def="10",.ptr=&lsals,.size=sizeof(uint8_t),.hex=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="micdata",.comment="I2S Mic Data / SD / DATA",.group=3,.len=7,.dot=3,.ptr=&micdata,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.old="audiodata"	},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="micclock",.comment="I2S Mic Clock / BCLK / SCK",.group=3,.len=8,.dot=3,.ptr=&micclock,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.old="audioclock"	},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="micws",.comment="I2S Mic WS / LR (not set for PDM mode)",.group=3,.len=5,.dot=3,.ptr=&micws,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.old="audiows"		},
 {.type=REVK_SETTINGS_BIT,.name="micright",.comment="I2S Mic use right channel",.group=3,.len=8,.dot=3,.bit=REVK_SETTINGS_BITFIELD_micright,.old="audioright"	},
 {.type=REVK_SETTINGS_UNSIGNED,.name="micdamp",.comment="I2S Mic Damping from peak (higher is slower)",.group=3,.len=7,.dot=3,.def="3",.ptr=&micdamp,.size=sizeof(uint8_t),.old="audiodamp",.live=1	},
 {.type=REVK_SETTINGS_UNSIGNED,.name="micmaxgain",.comment="Max mic gain",.group=3,.len=10,.dot=3,.def="30",.ptr=&micmaxgain,.size=sizeof(uint8_t),.live=1,.unit="dB"	},
 {.type=REVK_SETTINGS_UNSIGNED,.name="micrange",.comment="Range for reactive effects",.group=3,.len=8,.dot=3,.def="10",.ptr=&micrange,.size=sizeof(uint8_t),.live=1,.unit="dB"	},
 {.type=REVK_SETTINGS_BIT,.name="haenable",.comment="Enable Home Assistant",.group=4,.len=8,.dot=2,.def="1",.bit=REVK_SETTINGS_BITFIELD_haenable,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="poweron",.comment="Start virtual strip 1 on power on",.len=7,.def="1",.bit=REVK_SETTINGS_BITFIELD_poweron,.hide=1,.live=1},
 {.type=REVK_SETTINGS_STRING,.name="name",.comment="Name (must be set to appear in HA)",.len=4,.ptr=&name,.malloc=1,.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="colour",.comment="Colour or palette name or #RGB style",.len=6,.ptr=&colour,.malloc=1,.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="start",.comment="First LED (default 1)",.len=5,.ptr=&start,.size=sizeof(uint16_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1},
 {.type=REVK_SETTINGS_SIGNED,.name="top",.comment="Top LED (default to first)",.len=3,.ptr=&top,.size=sizeof(int16_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="len",.comment="Number of LEDs (default to end)",.len=3,.ptr=&len,.size=sizeof(uint16_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="effect",.comment="Default effect (leave blank for HA to pick)",.len=6,.ptr=&effect,.malloc=1,.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="bright",.comment="Brightness",.len=6,.ptr=&bright,.size=sizeof(uint8_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1,.unit="/255"	},
 {.type=REVK_SETTINGS_SIGNED,.name="height",.comment="Text height",.len=6,.ptr=&height,.size=sizeof(int8_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="delay",.comment="Delay time, default 1s",.len=5,.ptr=&delay,.size=sizeof(uint32_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1,.decimal=1,.unit="s"	},
 {.type=REVK_SETTINGS_UNSIGNED,.name="limit",.comment="Time limit, default none",.len=5,.ptr=&limit,.size=sizeof(uint32_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1,.decimal=1,.unit="s"	},
 {.type=REVK_SETTINGS_UNSIGNED,.name="speed",.comment="Cycle time, default 1s",.len=5,.ptr=&speed,.size=sizeof(uint8_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1,.decimal=1,.unit="s"	},
 {.type=REVK_SETTINGS_UNSIGNED,.name="fadein",.comment="Fade in time, default 1s",.len=6,.ptr=&fadein,.size=sizeof(uint8_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1,.decimal=1,.unit="s"	},
 {.type=REVK_SETTINGS_UNSIGNED,.name="fadeout",.comment="Fade out time, default 1s",.len=7,.ptr=&fadeout,.size=sizeof(uint8_t),.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1,.decimal=1,.unit="s"	},
 {.type=REVK_SETTINGS_JSON,.name="config",.comment="Settings as JSON and effect specific settings",.len=6,.ptr=&config,.malloc=1,.array=CONFIG_REVK_WEB_EXTRA_PAGES,.live=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="stack",.comment="Presets have priority, in order, else most recent on top",.len=5,.def="1",.bit=REVK_SETTINGS_BITFIELD_stack,.live=1,.hide=1},
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
 {.type=REVK_SETTINGS_STRING,.name="password",.comment="Settings password (this is not sent securely so use with care on local networks you control)",.len=8,.ptr=&password,.malloc=1,.revk=1,.hide=1,.secret=1},
#endif
 {.type=REVK_SETTINGS_STRING,.name="hostname",.comment="Host name",.len=8,.ptr=&hostname,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="appname",.comment="Application name",.len=7,.dq=1,.def=quote(CONFIG_REVK_APPNAME),.ptr=&appname,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="otahost",.comment="OTA hostname",.group=5,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTAHOST),.ptr=&otahost,.malloc=1,.revk=1,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="otadays",.comment="OTA auto load (days)",.group=5,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTADAYS),.ptr=&otadays,.size=sizeof(uint8_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="otastart",.comment="OTA check after startup (min seconds)",.group=5,.len=8,.dot=3,.def="600",.ptr=&otastart,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="otaauto",.comment="OTA auto upgrade",.group=5,.len=7,.dot=3,.def="1",.bit=REVK_SETTINGS_BITFIELD_otaauto,.revk=1,.hide=1,.live=1},
 {.type=REVK_SETTINGS_BIT,.name="otabeta",.comment="OTA from beta release",.group=5,.len=7,.dot=3,.bit=REVK_SETTINGS_BITFIELD_otabeta,.revk=1,.hide=1,.live=1},
 {.type=REVK_SETTINGS_BLOB,.name="otacert",.comment="OTA cert of otahost",.group=5,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTACERT),.ptr=&otacert,.malloc=1,.revk=1,.base64=1},
 {.type=REVK_SETTINGS_STRING,.name="ntphost",.comment="NTP host",.len=7,.dq=1,.def=quote(CONFIG_REVK_NTPHOST),.ptr=&ntphost,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="tz",.comment="Timezone (<a href='https://gist.github.com/alwynallan/24d96091655391107939' target=_blank>info</a>)",.len=2,.dq=1,.def=quote(CONFIG_REVK_TZ),.ptr=&tz,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="watchdogtime",.comment="Watchdog (seconds)",.len=12,.dq=1,.def=quote(CONFIG_REVK_WATCHDOG),.ptr=&watchdogtime,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="topicgroup",.comment="MQTT Alternative hostname accepted for commands",.group=6,.len=10,.dot=5,.ptr=&topicgroup,.malloc=1,.revk=1,.array=2},
 {.type=REVK_SETTINGS_STRING,.name="topiccommand",.comment="MQTT Topic for commands",.group=6,.len=12,.dot=5,.def="command",.ptr=&topiccommand,.malloc=1,.revk=1,.old="prefixcommand"			},
 {.type=REVK_SETTINGS_STRING,.name="topicsetting",.comment="MQTT Topic for settings",.group=6,.len=12,.dot=5,.def="setting",.ptr=&topicsetting,.malloc=1,.revk=1,.old="prefixsetting"			},
 {.type=REVK_SETTINGS_STRING,.name="topicstate",.comment="MQTT Topic for state",.group=6,.len=10,.dot=5,.def="state",.ptr=&topicstate,.malloc=1,.revk=1,.old="prefixstate"			},
 {.type=REVK_SETTINGS_STRING,.name="topicevent",.comment="MQTT Topic for event",.group=6,.len=10,.dot=5,.def="event",.ptr=&topicevent,.malloc=1,.revk=1,.old="prefixevent"			},
 {.type=REVK_SETTINGS_STRING,.name="topicinfo",.comment="MQTT Topic for info",.group=6,.len=9,.dot=5,.def="info",.ptr=&topicinfo,.malloc=1,.revk=1,.old="prefixinfo"			},
 {.type=REVK_SETTINGS_STRING,.name="topicerror",.comment="MQTT Topic for error",.group=6,.len=10,.dot=5,.def="error",.ptr=&topicerror,.malloc=1,.revk=1,.old="prefixerror"			},
 {.type=REVK_SETTINGS_STRING,.name="topicha",.comment="MQTT Topic for homeassistant",.group=6,.len=7,.dot=5,.def="homeassistant",.ptr=&topicha,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="prefixapp",.comment="MQTT use appname/ in front of hostname in topic",.group=7,.len=9,.dot=6,.dq=1,.def=quote(CONFIG_REVK_PREFIXAPP),.bit=REVK_SETTINGS_BITFIELD_prefixapp,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="prefixhost",.comment="MQTT use (appname/)hostname/topic instead of topic/(appname/)hostname",.group=7,.len=10,.dot=6,.dq=1,.def=quote(CONFIG_REVK_PREFIXHOST),.bit=REVK_SETTINGS_BITFIELD_prefixhost,.revk=1},
#ifdef	CONFIG_REVK_BLINK_DEF
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="blink",.comment="LED array",.len=5,.dq=1,.def=quote(CONFIG_REVK_BLINK),.ptr=&blink,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1,.array=3},
#endif
 {.type=REVK_SETTINGS_BIT,.name="dark",.comment="Default LED off",.len=4,.bit=REVK_SETTINGS_BITFIELD_dark,.revk=1,.live=1},
#ifdef  CONFIG_IDF_TARGET_ESP32S3
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="factorygpio",.comment="Factory reset GPIO (press 3 times)",.len=11,.def="-21",.ptr=&factorygpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#else
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="factorygpio",.comment="Factory reset GPIO (press 3 times)",.len=11,.ptr=&factorygpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
 {.type=REVK_SETTINGS_UNSIGNED,.name="apport",.comment="TCP port for config web pages on AP",.group=8,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APPORT),.ptr=&apport,.size=sizeof(uint16_t),.revk=1},
#endif
 {.type=REVK_SETTINGS_UNSIGNED,.name="aptime",.comment="Limit AP to time (seconds)",.group=8,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APTIME),.ptr=&aptime,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="apwait",.comment="Wait off line before starting AP (seconds)",.group=8,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APWAIT),.ptr=&apwait,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="apgpio",.comment="Start AP on GPIO",.group=8,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APGPIO),.ptr=&apgpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#endif
#ifdef  CONFIG_REVK_MQTT
 {.type=REVK_SETTINGS_STRING,.name="mqtthost",.comment="MQTT hostname",.group=9,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTHOST),.ptr=&mqtthost,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="mqttport",.comment="MQTT port",.group=9,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTPORT),.ptr=&mqttport,.size=sizeof(uint16_t),.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="mqttuser",.comment="MQTT username",.group=9,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTUSER),.ptr=&mqttuser,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="mqttpass",.comment="MQTT password",.group=9,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTPASS),.ptr=&mqttpass,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.secret=1,.hide=1},
 {.type=REVK_SETTINGS_BLOB,.name="mqttcert",.comment="MQTT CA certificate",.group=9,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTCERT),.ptr=&mqttcert,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.base64=1},
#endif
 {.type=REVK_SETTINGS_BLOB,.name="clientkey",.comment="Client Key (OTA and MQTT TLS)",.group=10,.len=9,.dot=6,.ptr=&clientkey,.malloc=1,.revk=1,.base64=1},
 {.type=REVK_SETTINGS_BLOB,.name="clientcert",.comment="Client certificate (OTA and MQTT TLS)",.group=10,.len=10,.dot=6,.ptr=&clientcert,.malloc=1,.revk=1,.base64=1},
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifireset",.comment="Restart if WiFi off for this long (seconds)",.group=11,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIRESET),.ptr=&wifireset,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="wifissid",.comment="WiFI SSID (name)",.group=11,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFISSID),.ptr=&wifissid,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="wifipass",.comment="WiFi password",.group=11,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIPASS),.ptr=&wifipass,.malloc=1,.revk=1,.hide=1,.secret=1},
 {.type=REVK_SETTINGS_STRING,.name="wifiip",.comment="WiFi Fixed IP",.group=11,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIIP),.ptr=&wifiip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifigw",.comment="WiFi Fixed gateway",.group=11,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIGW),.ptr=&wifigw,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifidns",.comment="WiFi fixed DNS",.group=11,.len=7,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIDNS),.ptr=&wifidns,.malloc=1,.revk=1,.array=3},
 {.type=REVK_SETTINGS_OCTET,.name="wifibssid",.comment="WiFI BSSID",.group=11,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIBSSID),.ptr=&wifibssid,.size=sizeof(uint8_t[6]),.revk=1,.hex=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifichan",.comment="WiFI channel",.group=11,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFICHAN),.ptr=&wifichan,.size=sizeof(uint8_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifiuptime",.comment="WiFI turns off after this many seconds",.group=11,.len=10,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIUPTIME),.ptr=&wifiuptime,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifips",.comment="WiFi power save",.group=11,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIPS),.bit=REVK_SETTINGS_BITFIELD_wifips,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifimaxps",.comment="WiFi power save (max)",.group=11,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIMAXPS),.bit=REVK_SETTINGS_BITFIELD_wifimaxps,.revk=1},
#endif
#ifndef	CONFIG_REVK_MESH
 {.type=REVK_SETTINGS_STRING,.name="apssid",.comment="AP mode SSID (name)",.group=8,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APSSID),.ptr=&apssid,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="appass",.comment="AP mode password",.group=8,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APPASS),.ptr=&appass,.malloc=1,.revk=1,.secret=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="apmax",.comment="AP max clients",.group=8,.len=5,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APMAX),.ptr=&apmax,.size=sizeof(uint8_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="apip",.comment="AP mode block",.group=8,.len=4,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APIP),.ptr=&apip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="aplr",.comment="AP LR mode",.group=8,.len=4,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APLR),.bit=REVK_SETTINGS_BITFIELD_aplr,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="aphide",.comment="AP hide SSID",.group=8,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APHIDE),.bit=REVK_SETTINGS_BITFIELD_aphide,.revk=1},
#endif
#ifdef	CONFIG_REVK_MESH
 {.type=REVK_SETTINGS_STRING,.name="nodename",.comment="Mesh node name",.len=8,.ptr=&nodename,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshreset",.comment="Reset if mesh off for this long (seconds)",.group=12,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHRESET),.ptr=&meshreset,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_OCTET,.name="meshid",.comment="Mesh ID (hex)",.group=12,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHID),.ptr=&meshid,.size=sizeof(uint8_t[6]),.revk=1,.hex=1,.hide=1},
 {.type=REVK_SETTINGS_OCTET,.name="meshkey",.comment="Mesh key",.group=12,.len=7,.dot=4,.ptr=&meshkey,.size=sizeof(uint8_t[16]),.revk=1,.secret=1,.hex=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshwidth",.comment="Mesh width",.group=12,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHWIDTH),.ptr=&meshwidth,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshdepth",.comment="Mesh depth",.group=12,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHDEPTH),.ptr=&meshdepth,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshmax",.comment="Mesh max devices",.group=12,.len=7,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHMAX),.ptr=&meshmax,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="meshpass",.comment="Mesh AP password",.group=12,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHPASS),.ptr=&meshpass,.malloc=1,.revk=1,.secret=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="meshlr",.comment="Mesh use LR mode",.group=12,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHLR),.bit=REVK_SETTINGS_BITFIELD_meshlr,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="meshroot",.comment="This is preferred mesh root",.group=12,.len=8,.dot=4,.bit=REVK_SETTINGS_BITFIELD_meshroot,.revk=1,.hide=1},
#endif
{0}};
#undef quote
#undef str
#ifdef  CONFIG_IDF_TARGET_ESP32
revk_gpio_t rgb[2]={0};
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
revk_gpio_t rgb[2]={0};
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
uint8_t cps=0;
#else
uint8_t cps=0;
#endif
revk_gpio_t relay={0};
revk_gpio_t adc={0};
revk_gpio_t button={0};
revk_gpio_t blink[3]={0};
uint8_t maxr=0;
uint8_t maxg=0;
uint8_t maxb=0;
uint8_t maxw=0;
uint16_t leds[2]={0};
uint8_t webcontrol=0;
revk_gpio_t lsscl={0};
revk_gpio_t lssda={0};
uint8_t lsals=0;
revk_gpio_t micdata={0};
revk_gpio_t micclock={0};
revk_gpio_t micws={0};
uint8_t micdamp=0;
uint8_t micmaxgain=0;
uint8_t micrange=0;
char* name[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
char* colour[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
uint16_t start[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
int16_t top[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
uint16_t len[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
char* effect[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
uint8_t bright[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
int8_t height[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
uint32_t delay[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
uint32_t limit[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
uint8_t speed[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
uint8_t fadein[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
uint8_t fadeout[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
char* config[CONFIG_REVK_WEB_EXTRA_PAGES]={0};
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
char* password=NULL;
#endif
char* hostname=NULL;
char* appname=NULL;
char* otahost=NULL;
uint8_t otadays=0;
uint16_t otastart=0;
revk_settings_blob_t* otacert=NULL;
char* ntphost=NULL;
char* tz=NULL;
uint32_t watchdogtime=0;
char* topicgroup[2]={0};
char* topiccommand=NULL;
char* topicsetting=NULL;
char* topicstate=NULL;
char* topicevent=NULL;
char* topicinfo=NULL;
char* topicerror=NULL;
char* topicha=NULL;
#ifdef	CONFIG_REVK_BLINK_DEF
revk_gpio_t blink[3]={0};
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
revk_gpio_t factorygpio={0};
#else
revk_gpio_t factorygpio={0};
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
uint16_t apport=0;
#endif
uint32_t aptime=0;
uint32_t apwait=0;
revk_gpio_t apgpio={0};
#endif
#ifdef  CONFIG_REVK_MQTT
char* mqtthost[CONFIG_REVK_MQTT_CLIENTS]={0};
uint16_t mqttport[CONFIG_REVK_MQTT_CLIENTS]={0};
char* mqttuser[CONFIG_REVK_MQTT_CLIENTS]={0};
char* mqttpass[CONFIG_REVK_MQTT_CLIENTS]={0};
revk_settings_blob_t* mqttcert[CONFIG_REVK_MQTT_CLIENTS]={0};
#endif
revk_settings_blob_t* clientkey=NULL;
revk_settings_blob_t* clientcert=NULL;
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
uint16_t wifireset=0;
char* wifissid=NULL;
char* wifipass=NULL;
char* wifiip=NULL;
char* wifigw=NULL;
char* wifidns[3]={0};
uint8_t wifibssid[6]={0};
uint8_t wifichan=0;
uint16_t wifiuptime=0;
#endif
#ifndef	CONFIG_REVK_MESH
char* apssid=NULL;
char* appass=NULL;
uint8_t apmax=0;
char* apip=NULL;
#endif
#ifdef	CONFIG_REVK_MESH
char* nodename=NULL;
uint16_t meshreset=0;
uint8_t meshid[6]={0};
uint8_t meshkey[16]={0};
uint16_t meshwidth=0;
uint16_t meshdepth=0;
uint16_t meshmax=0;
char* meshpass=NULL;
#endif
const char revk_settings_secret[]="✶✶✶✶✶✶✶✶";
