#ifndef MAP_MANAGER
#define MAP_MANAGER

class Map
{
public:
	int lvlCounter;
	std::vector<std::vector<int>> wall;
	std::vector<std::vector<int>> floor;
	std::vector<std::vector<int>> fiature; // ��� ��� ���, ������ � ��

	Map()
	{
	}

	void Generate(std::string parametrs);
};

#endif // !MAP_MANAGER
