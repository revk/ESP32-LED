// CPP code for Matter

extern "C"
{
#include "revk.h"
#include "control.h"
}

#ifdef  CONFIG_REVK_MATTER

#include <esp_err.h>
#include <esp_log.h>
#include <nvs_flash.h>

#include <esp_matter.h>
#include <esp_matter_console.h>
#include <esp_matter_ota.h>

#include <app_priv.h>
//#include <app_reset.h>
#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
#include <platform/ESP32/OpenthreadLauncher.h>
#endif

#include <app/server/CommissioningWindowManager.h>
#include <app/server/Server.h>

const char TAG[] = "Matter";

constexpr auto k_timeout_seconds = 300;

uint16_t light_endpoint_id = 0;

using namespace esp_matter;
using namespace
   esp_matter::attribute;
using namespace
   esp_matter::endpoint;
using namespace
   chip::app::Clusters;

#if CONFIG_ENABLE_ENCRYPTED_OTA
extern const char
   decryption_key_start[]
asm ("_binary_esp_image_encryption_key_pem_start");
extern const char
   decryption_key_end[]
asm ("_binary_esp_image_encryption_key_pem_end");

static const char *
   s_decryption_key = decryption_key_start;
static const uint16_t
   s_decryption_key_len = decryption_key_end - decryption_key_start;
#endif // CONFIG_ENABLE_ENCRYPTED_OTA

static void
app_event_cb (const ChipDeviceEvent * event, intptr_t arg)
{
   switch (event->Type)
   {
   case chip::DeviceLayer::DeviceEventType::kInterfaceIpAddressChanged:
      ESP_LOGE (TAG, "Interface IP Address changed");
      break;

   case chip::DeviceLayer::DeviceEventType::kCommissioningComplete:
      ESP_LOGE (TAG, "Commissioning complete");
      break;

   case chip::DeviceLayer::DeviceEventType::kFailSafeTimerExpired:
      ESP_LOGE (TAG, "Commissioning failed, fail safe timer expired");
      break;

   case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStarted:
      ESP_LOGE (TAG, "Commissioning session started");
      break;

   case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStopped:
      ESP_LOGE (TAG, "Commissioning session stopped");
      break;

   case chip::DeviceLayer::DeviceEventType::kCommissioningWindowOpened:
      ESP_LOGE (TAG, "Commissioning window opened");
      break;

   case chip::DeviceLayer::DeviceEventType::kCommissioningWindowClosed:
      ESP_LOGE (TAG, "Commissioning window closed");
      break;

   case chip::DeviceLayer::DeviceEventType::kFabricRemoved:
      {
         ESP_LOGE (TAG, "Fabric removed successfully");
         if (chip::Server::GetInstance ().GetFabricTable ().FabricCount () == 0)
         {
            chip::CommissioningWindowManager & commissionMgr = chip::Server::GetInstance ().GetCommissioningWindowManager ();
            constexpr auto
               kTimeoutSeconds = chip::System::Clock::Seconds16 (k_timeout_seconds);
            if (!commissionMgr.IsCommissioningWindowOpen ())
            {
               /* After removing last fabric, this example does not remove the Wi-Fi credentials
                * and still has IP connectivity so, only advertising on DNS-SD.
                */
               CHIP_ERROR
                  err = commissionMgr.OpenBasicCommissioningWindow (kTimeoutSeconds,
                                                                    chip::CommissioningWindowAdvertisement::kDnssdOnly);
               if (err != CHIP_NO_ERROR)
               {
                  ESP_LOGE (TAG, "Failed to open commissioning window, err:%" CHIP_ERROR_FORMAT, err.Format ());
               }
            }
         }
         break;
      }

   case chip::DeviceLayer::DeviceEventType::kFabricWillBeRemoved:
      ESP_LOGE (TAG, "Fabric will be removed");
      break;

   case chip::DeviceLayer::DeviceEventType::kFabricUpdated:
      ESP_LOGE (TAG, "Fabric is updated");
      break;

   case chip::DeviceLayer::DeviceEventType::kFabricCommitted:
      ESP_LOGE (TAG, "Fabric is committed");
      break;
   default:
      ESP_LOGE (TAG, "CB %d", event->Type);
      break;
   }
}

static esp_err_t
app_identification_cb (identification::callback_type_t type, uint16_t endpoint_id, uint8_t effect_id,
                       uint8_t effect_variant, void *priv_data)
{
   ESP_LOGE (TAG, "ID CB");
   return ESP_OK;
}

static esp_err_t
app_attribute_update_cb (attribute::callback_type_t type, uint16_t endpoint_id, uint32_t cluster_id,
                         uint32_t attribute_id, esp_matter_attr_val_t * val, void *priv_data)
{
   // See esp-matter/components/esp_matter/esp_matter_attribute_utils.h
   ESP_LOGE (TAG, "ATT CB endpoint=%u cluster=%lu attribute=%lu type %d, val->type=%d%s", endpoint_id, cluster_id, attribute_id,
             type, val->type & 0x7F, val->type & ESP_MATTER_VAL_NULLABLE_BASE ? " (nullable)" : "");
   esp_err_t
      err = ESP_OK;
   switch (type)
   {
   case PRE_UPDATE:
      if (endpoint_id == light_endpoint_id && !attribute_id && val->type == 1)
      {
         if (val->val.b)
            led_add ("pulse", NULL);
         else
            led_stop ();
      }
      break;
   case POST_UPDATE:
   case READ:
   case WRITE:
      break;
   }
   return err;
}

extern
   "C" void
matter_main (void)
{
   esp_err_t
      err = ESP_OK;

   /* Initialize the ESP NVS layer */
   nvs_flash_init ();

   /* Create a Matter node and add the mandatory Root Node device type on endpoint 0 */
   node::config_t node_config;
   node_t *
      node = node::create (&node_config, app_attribute_update_cb, app_identification_cb);

   // See esp-matter/components/esp_matter/esp_matter_endpoint.h

   extended_color_light::config_t light_config;
   light_config.on_off.on_off = DEFAULT_POWER;
   light_config.on_off.lighting.start_up_on_off = nullptr;
   light_config.level_control.current_level = DEFAULT_BRIGHTNESS;
   light_config.level_control.lighting.start_up_current_level = DEFAULT_BRIGHTNESS;
   light_config.color_control.color_mode = EMBER_ZCL_COLOR_MODE_COLOR_TEMPERATURE;
   light_config.color_control.enhanced_color_mode = EMBER_ZCL_ENHANCED_COLOR_MODE_COLOR_TEMPERATURE;
   light_config.color_control.color_temperature.startup_color_temperature_mireds = nullptr;
   endpoint_t *
      endpoint = extended_color_light::create (node, &light_config, ENDPOINT_FLAG_NONE, NULL);

   /* These node and endpoint handles can be used to create/add other endpoints and clusters. */
   if (!node || !endpoint)
   {
      ESP_LOGE (TAG, "Matter node creation failed");
   }

   light_endpoint_id = endpoint::get_id (endpoint);
   ESP_LOGE (TAG, "Light created with endpoint_id %d", light_endpoint_id);

#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
   /* Set OpenThread platform config */
   esp_openthread_platform_config_t config = {
      .radio_config = ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG (),
      .host_config = ESP_OPENTHREAD_DEFAULT_HOST_CONFIG (),
      .port_config = ESP_OPENTHREAD_DEFAULT_PORT_CONFIG (),
   };
   set_openthread_platform_config (&config);
#endif

   /* Matter start */
   err = esp_matter::start (app_event_cb);
   if (err != ESP_OK)
   {
      ESP_LOGE (TAG, "Matter start failed: %d", err);
   }

   /* Starting driver with default values */
   //app_driver_light_set_defaults(light_endpoint_id);

#if CONFIG_ENABLE_ENCRYPTED_OTA
   err = esp_matter_ota_requestor_encrypted_init (s_decryption_key, s_decryption_key_len);
   if (err != ESP_OK)
   {
      ESP_LOGE (TAG, "Failed to initialized the encrypted OTA, err: %d", err);
   }
#endif // CONFIG_ENABLE_ENCRYPTED_OTA

#if CONFIG_ENABLE_CHIP_SHELL
   esp_matter::console::diagnostics_register_commands ();
   esp_matter::console::wifi_register_commands ();
   esp_matter::console::init ();
#endif
}
#endif
