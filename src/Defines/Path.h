#ifndef __PATH_H__
#define __PATH_H__

#include <string>

#ifndef ROOT_PATH
#define ROOT_PATH "."
#endif

const std::string YAML_EXTENSION(".yaml");


//general

const std::string RESOURCES(std::string(ROOT_PATH) + "/resources/");

const std::string IMAGES_PATH(RESOURCES + "Images/");

const std::string SOUNDS_PATH(RESOURCES + "Sounds/");

const std::string GLADE_PATH(RESOURCES + "Glade/");

const std::string ANIMATIONS_PATH(IMAGES_PATH + "Animations/");

const std::string CONFIG_PATH(std::string(ROOT_PATH) + "/config/");

const std::string MAPS_PATH(std::string(CONFIG_PATH) + "Maps/");

const std::string CLIENT_WINDOW_NAME("Worms");

const std::string EDITOR_WINDOW_NAME("Worms - Editor");

const std::string ICON_PATH(IMAGES_PATH + "icon.png");

//client

const std::string GIRDER_PATH(IMAGES_PATH + "Girder_client/girder_");

const std::string BULLETS_PATH(IMAGES_PATH + "Bullets/");

const std::string WORMS_PATH(IMAGES_PATH + "Worms/");

const std::string WEAPONS_PATH(IMAGES_PATH + "Weapons_icons/");

const std::string SCOPE_IMAGE(IMAGES_PATH + "Scope/Scope.gif");

const std::string VICTORY_ANIMATION(ANIMATIONS_PATH + "Victory.gif");

const std::string EXPLOSION_ANIMATION(ANIMATIONS_PATH + "Explosion.png");


//server

const std::string SERVER_CONFIG_FILE(CONFIG_PATH + "server_config.yaml");

#endif
