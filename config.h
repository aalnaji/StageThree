#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <vector>

#include "defaults.h"
#include "configitem.h"

class Config
{
public:
    Config();
	/** Delete the config items on config deletion. */
	~Config();

    size_t size() const;

    ConfigItem * operator[](int i);

    int getWidth() const;
    int getHeight() const;

private:
    void readFile();
    void validate() const;
    ConfigItem *add(ConfigItem *newConfigItem);

    int width;
    int height;

    std::vector<ConfigItem *> configItems;
};

#endif // CONFIG_H
