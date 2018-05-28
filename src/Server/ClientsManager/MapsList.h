#ifndef __MAPSLIST_H__
#define __MAPSLIST_H__

#include <dirent.h>
#include <vector>
#include <string>

typedef std::vector<std::string> maps_list_t;

class MapsList{
	public:
		/* Devuelve una lista con todos los mapas */
		static maps_list_t getAllMaps();
};

#endif
