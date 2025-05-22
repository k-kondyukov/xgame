
#include "Resources.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ArmorDef.hpp"
#include "ArtifactDef.hpp"
#include "CostDef.hpp"
#include "DiscDef.hpp"
#include "GunDef.hpp"
#include "SpDef.hpp"

static std::vector<ArmorDef> Resources::armors = {
	ArmorDef(1, "Êîæàíûé êîñòþì", 5),
	ArmorDef(2, "Îáìîòêè ìàðîäåðà", 10)
};

static std::vector<ArtifactDef> Resources::artifacts = {
	ArtifactDef(3, "Ïðîìåòåé", 10, 3),
	ArtifactDef(4, "Ãðîìîâåðæåö", 20, 4)
};

static std::vector<SpDef> Resources::enemies = {
	SpDef(5, 10, 5),
	SpDef(6, 15, 3)
};

static std::vector<GunDef> Resources::weapons = {
	GunDef(7, "Ìå÷", 7, 1),
	GunDef(8, "Ëóê", 4, 5)
};

static std::vector<DiscDef> Resources::descriptions = {
	DiscDef(1, "Ïðîñòî êîæàíûé êîñòþì÷èê êîðè÷íåâîãî öâåòà"),
	DiscDef(2, "Ìàðîäåðñêèå îáìîòêè, õàðàêòåðíûå äëÿ îäåæäû ìàðîäåðîâ"),
	DiscDef(3, "Ìåõàíè÷åñêèé ôàêåë, ñ ãîðÿùèì ïëàìåíåì è òðóáêàìè íà âûõëîï êàê ó òåõíèêè"),
	DiscDef(4, "Ïîñîõ ñ êàòóøêîé Òåñëà"),
	DiscDef(5, "Àãðåññèâíûé âîëê"),
	DiscDef(6, "Ïàóê-ïåðåðîñòîê"),
	DiscDef(7, "Äîñòàòî÷íî áàíàëüíûé ìå÷"),
	DiscDef(8, "Ëóê-ïîðåé")
};

static std::vector<CostDef> Resources::costs = {
	CostDef(1, 5),
	CostDef(2, 7),
	CostDef(7, 5),
	CostDef(8, 3)

sf::Texture Resources::wallsTexture;
sf::Texture Resources::floorTexture;
sf::Texture Resources::shaderTexture;

void Resources::init() {
    if (!wallsTexture.loadFromFile("sprites/walls.png")) {
        std::cerr << "Îøèáêà çàãðóçêè òåêñòóðû walls.png" << std::endl;
        exit(1);
    }

    if (!floorTexture.loadFromFile("sprites/floor.png")) {
        std::cerr << "Îøèáêà çàãðóçêè òåêñòóðû floor.png" << std::endl;
        exit(1);
    }

    if (!shaderTexture.loadFromFile("sprites/shader.png")) {
        std::cerr << "Îøèáêà çàãðóçêè òåêñòóðû shader.png" << std::endl;
        exit(1);
    }
}