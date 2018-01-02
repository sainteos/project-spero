#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <json/json.h>
#include <vector>

//= SCRIPTABLE
namespace Utility {
  /**
   * @brief      Class for configuration manager to load json configurations
   */
  class ConfigManager {
    private:
      Json::Value config_handle;
    public:
      /**
       * @brief      Constructs the configManager
       */
      ConfigManager();

      /**
       * @brief      Loads a configuration.
       *
       * @param[in]  file_path  The file path
       *
       * @return     True if successful
       */
      bool loadConfig(const std::string& file_path);
      //= BEGIN SCRIPTABLE

      /**
       * @brief      Gets an int from config.
       *
       * @param[in]  key   The key
       *
       * @return     The int.
       */
      int getInt(const std::string& key);
      /**
       * @brief      Gets an unsigned int from config
       *
       * @param[in]  key   The key
       *
       * @return     The unsigned int.
       */
      unsigned int getUnsignedInt(const std::string& key);
      /**
       * @brief      Gets a string from config
       *
       * @param[in]  key   The key
       *
       * @return     The string.
       */
      std::string getString(const std::string& key);
      /**
       * @brief      Gets a float from config
       *
       * @param[in]  key   The key
       *
       * @return     The float.
       */
      float getFloat(const std::string& key);
      /**
       * @brief      Gets a double from config
       *
       * @param[in]  key   The key
       *
       * @return     The double.
       */
      double getDouble(const std::string& key);
      /**
       * @brief      Gets a bool from config
       *
       * @param[in]  key   The key
       *
       * @return     The bool.
       */
      bool getBool(const std::string& key);
      /**
       * @brief      Gets a string vector from config
       *
       * @param[in]  key   The key
       *
       * @return     The string vector.
       */
      std::vector<std::string> getStringVector(const std::string& key);
      /**
       * @brief      Gets an unsigned int vector from config
       *
       * @param[in]  key   The key
       *
       * @return     The unsigned int vector.
       */
      std::vector<unsigned int> getUnsignedIntVector(const std::string& key);
      //= END SCRIPTABLE
  };
}

#endif
