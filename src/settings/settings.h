#ifndef SRC_SETTINGS_SETTINGS_H_
#define SRC_SETTINGS_SETTINGS_H_

#include <libconfig.h++>
#include <string>
#include <stdexcept>

namespace settings {

typedef std::runtime_error SettingsError;

class SettingNotFound : public SettingsError {
 public:
  explicit SettingNotFound(const std::string& error)
    : SettingsError(error.c_str()) {
  }
};

class Settings {
 public:
  static Settings& getSettings() {
    static Settings settings;
    return settings;
  }

  template <class T>
  T GetValue(const std::string& path) {
    T value;
    if (!config_.lookupValue(path, value)) {
      throw SettingNotFound("setting: \'" + path + "\' not found");
    }
    return value;
  }

 private:
  Settings() {
    config_.readFile(kConfigFilePath.c_str());
  }

  libconfig::Config config_;

  static const std::string kConfigFilePath;
};

}  // namespace settings

#endif  // SRC_SETTINGS_SETTINGS_H_
