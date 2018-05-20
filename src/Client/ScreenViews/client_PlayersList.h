#ifndef __PLAYERSLIST_H__
#define __PLAYERSLIST_H__

#include <map>
#include <string>

class PlayersList{
	private:
		std::map<int, std::string> players;

	public:
		PlayersList();

		~PlayersList();

		void addPlayer(int id, const std::string& name);

		const std::string& getPlayer(int id) const;
};

#endif
