#ifndef __PATH_H__
#define __PATH_H__

#include <string>

#ifndef ROOT_PATH
#define ROOT_PATH std::string(".")
#endif

const std::string RESOURCES(ROOT_PATH + "/resources/");

const std::string IMAGES_PATH(RESOURCES + "images/");

const std::string GIRDER_PATH(IMAGES_PATH + "Girder_client/girder_");

const std::string BULLETS_PATH(IMAGES_PATH + "bullets/");

const std::string WORMS_PATH(IMAGES_PATH + "worms/");

#endif
