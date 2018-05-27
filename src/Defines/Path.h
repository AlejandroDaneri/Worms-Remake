#ifndef __PATH_H__
#define __PATH_H__

#include <string>

#ifndef ROOT_PATH
#define ROOT_PATH "."
#endif


//general

const std::string RESOURCES(std::string(ROOT_PATH) + "/resources/");

const std::string IMAGES_PATH(RESOURCES + "images/");

const std::string SOUNDS_PATH(RESOURCES + "Sounds/");

const std::string ANIMATIONS_PATH(IMAGES_PATH + "animations/");

const std::string CONFIG_PATH(std::string(ROOT_PATH) + "/config/");

const std::string MAPS_PATH(std::string(CONFIG_PATH) + "/Maps/");

//client

const std::string GIRDER_PATH(IMAGES_PATH + "Girder_client/girder_");

const std::string BULLETS_PATH(IMAGES_PATH + "bullets/");

const std::string WORMS_PATH(IMAGES_PATH + "worms/");

const std::string WEAPONS_PATH(IMAGES_PATH + "Weapons_icons/");

const std::string SCOPE_IMAGE(IMAGES_PATH + "scope/scope.png");

//server

const std::string SERVER_CONFIG_FILE(CONFIG_PATH + "server_config.yaml");

#endif
