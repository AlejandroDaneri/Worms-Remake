#include "MapsList.h"
#include "Path.h"
#include <string>

maps_list_t MapsList::getAllMaps(){
	maps_list_t maps_list;

	struct dirent* entry;
	DIR* dir = opendir(MAPS_PATH.c_str());
	if (!dir){
		std::move(maps_list);
	}

	while((entry = readdir(dir))){  // NOLINT (La solucion que propone esta deprecated)
		std::string file(entry->d_name);
		if (file.rfind(YAML_EXTENSION) != std::string::npos){
			maps_list.push_back(file);
		}
	}

	closedir(dir);
	return std::move(maps_list);
}
