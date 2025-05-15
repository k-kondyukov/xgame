#include <vector>
#include "ArmorDef.hpp"
#include "ArtifactDef.hpp"
#include "CostDef.hpp"
#include "DiscDef.hpp"
#include "GunDef.hpp"
#include "SpDef.hpp"

static std::vector<ArmorDef> Resources::armors = {
	ArmorDef(1, "Кожаный костюм", 5),
	ArmorDef(2, "Обмотки мародера", 10)
};

static std::vector<ArtifactDef> Resources::artifacts = {
	ArtifactDef(3, "Прометей", 10, 3),
	ArtifactDef(4, "Громовержец", 20, 4)
};

static std::vector<SpDef> Resources::enemies = {
	SpDef(5, 10, 5),
	SpDef(6, 15, 3)
};

static std::vector<GunDef> Resources::weapons = {
	GunDef(7, "Меч", 7, 1),
	GunDef(8, "Лук", 4, 5)
};

static std::vector<DiscDef> Resources::descriptions = {
	DiscDef(1, "Просто кожаный костюмчик коричневого цвета"),
	DiscDef(2, "Мародерские обмотки, характерные для одежды мародеров"),
	DiscDef(3, "Механический факел, с горящим пламенем и трубками на выхлоп как у техники"),
	DiscDef(4, "Посох с катушкой Тесла"),
	DiscDef(5, "Агрессивный волк"),
	DiscDef(6, "Паук-переросток"),
	DiscDef(7, "Достаточно банальный меч"),
	DiscDef(8, "Лук-порей")
};

static std::vector<CostDef> Resources::costs = {
	CostDef(1, 5),
	CostDef(2, 7),
	CostDef(7, 5),
	CostDef(8, 3)
}