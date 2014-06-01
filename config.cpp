#include "config.h"
#include "ballconfigitem.h"
#include "blockconfigitem.h"
#include "paddleconfigitem.h"
#include "levelconfigitem.h"

/**
 * @brief stripColons - Helper method. Removes any colons from a word. Used for backwards compatibility.
 * @param s
 * @return
 */
std::string stripColons(std::string s)
{
    std::string newStr;
    for(std::string::size_type i = 0; i<s.length(); i++){
        if(s.at(i) != ':'){
            newStr += s.at(i);
        }
    }
    return newStr;
}

/**
 * @brief Config::Config Construct a config and read in from the default location.
 */
Config::Config()
    : width(Defaults::BOX_WIDTH)
    , height(Defaults::BOX_HEIGHT)
{
    readFile();
}

/** Delete the config items on config deletion. */
Config::~Config()
{
	for(std::vector<ConfigItem *>::iterator iter(configItems.begin()); iter!= configItems.end(); ++iter)
		delete *iter;
}

size_t Config::size() const
{
    return configItems.size();
}

ConfigItem * Config::operator[](int i)
{
    return configItems[i];
}

int Config::getWidth() const
{
    return width;
}

int Config::getHeight() const
{
    return height;
}

/**
 * @brief Config::readFile - Reads the config file and makes appropriate ConfigItem objects.
 */
void Config::readFile()
{
    std::string line;
    std::string name;
    double value;

    std::ifstream file(Defaults::CONFIG_PATH.c_str());
    if (file.fail()) {
        std::cout<<"Missing configuration file"<<std::endl;
        exit(0);
    }
    if (file.is_open()) {
        ConfigItem *currentItem = NULL;
		LevelConfigItem *currentLevel = NULL;

        while (std::getline(file, line)) {
            if (line == "[BOX]") {
                // Do nothing for now.
            } else if (line == "[BALL]") {
                currentItem = add(new BallConfigItem());
            } else if (line == "[BLOCK]") {
				if(!currentLevel)
					currentLevel = new LevelConfigItem();
                currentItem = currentLevel->add(new BlockConfigItem());
			} else if (line == "[PADDLE]") {
                currentItem = add(new PaddleConfigItem());
			} else if (line == "[LEVEL]") {
				currentLevel= new LevelConfigItem();
                currentItem = add(currentLevel);
            } else if (line.length() > 0) {
                std::istringstream stream(line);
                stream >> name >> value;

                name = stripColons(name);
                if (name == "height") {
                    height = value;
                } else if (name == "width") {
                    width = value;
                } else {
                    currentItem->addParameter(name, value);
                }
            }

        }
        file.close();
    }
    validate();
}

/**
 * @brief Config::validate Checks if the parsed config parameters are valid.
 */
void Config::validate() const
{
    for (std::vector<ConfigItem *>::const_iterator iter = configItems.begin(); iter != configItems.end(); ++iter) {
        ConfigItem *item = *iter;
        if (!item->validate(width, height)) {
            std::cout << "Item defined in config not entirely within the box. Enum: "
                      << item->getItemType() << std::endl;
            exit(0);
        }
    }
}

/**
 * @brief Config::add - Adds a new ConfigItem to the Config.
 * @param newConfigItem
 * @return
 */
ConfigItem * Config::add(ConfigItem *newConfigItem)
{
    configItems.push_back(newConfigItem);
    return newConfigItem;
}
