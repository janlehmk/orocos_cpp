#ifndef CONFIGURATIONHELPER_H
#define CONFIGURATIONHELPER_H

#include <rtt/TaskContext.hpp>


class ConfigValue
{
public:
    enum Type {
        SIMPLE,
        COMPLEX,
    };
    
    enum Type type;
    std::string name;
    
    virtual bool merge(const ConfigValue *other) = 0;
    
protected:
    ConfigValue(enum Type);
    virtual ~ConfigValue();
};

class SimpleConfigValue : public ConfigValue
{
public:
    virtual bool merge(const ConfigValue* other);
    SimpleConfigValue();
    std::string value;
};

class ComplexConfigValue : public ConfigValue
{
public:
    virtual bool merge(const ConfigValue* other);
    ComplexConfigValue();
    std::map<std::string, ConfigValue *> values;
};

class Configuration
{
public:
    std::string name;
    bool merge(const Configuration &other);
    std::map<std::string, ConfigValue *> values;
};

class ConfigurationHelper
{
    std::map<std::string, Configuration> subConfigs;
public:
    bool loadConfigFile(const std::string &path);
    bool applyConfig(RTT::TaskContext *context, const std::vector<std::string> &names);
};

#endif // CONFIGURATIONHELPER_H