#ifndef CONFIG_H
#define CONFIG_H

// Shared symbolic configuration
#define CONFIG_DEVICE_MODEL "ESP32-WROOM-32D"
#define CONFIG_OCPP_VERSION "1.6J"

// Load environment-specific secrets and settings
#ifdef CI_BUILD
  #include "env.ci.h"  // used for CI builds only
#else
  #include "env.h"     // excluded from repo, defined locally by developer
#endif

#endif  // CONFIG_H
