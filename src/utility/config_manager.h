#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <json/json.h>

namespace Utility {
  class ConfigManager {
    private:
      Json::Value config_handle;
    public:
      ConfigManager();
      
      const bool loadConfig(const std::string& file_path);
      
      const int getInt(const std::string& key);
      const unsigned int getUnsignedInt(const std::string& key);
      const std::string getString(const std::string& key);
      const float getFloat(const std::string& key);
      const double getDouble(const std::string& key);
      const bool getBool(const std::string& key);
  };
}

#endif