#include <vector>
#include "ArmorDef.hpp"
#include "ArtifactDef.hpp"
#include "CostDef.hpp"
#include "DiscDef.hpp"
#include "GunDef.hpp"
#include "SpDef.hpp"

static std::vector<ArmorDef> Resources::armors = {
	ArmorDef(1, "������� ������", 5),
	ArmorDef(2, "������� ��������", 10)
};

static std::vector<ArtifactDef> Resources::artifacts = {
	ArtifactDef(3, "��������", 10, 3),
	ArtifactDef(4, "�����������", 20, 4)
};

static std::vector<SpDef> Resources::enemies = {
	SpDef(5, 10, 5),
	SpDef(6, 15, 3)
};

static std::vector<GunDef> Resources::weapons = {
	GunDef(7, "���", 7, 1),
	GunDef(8, "���", 4, 5)
};

static std::vector<DiscDef> Resources::descriptions = {
	DiscDef(1, "������ ������� ��������� ����������� �����"),
	DiscDef(2, "����������� �������, ����������� ��� ������ ���������"),
	DiscDef(3, "������������ �����, � ������� �������� � �������� �� ������ ��� � �������"),
	DiscDef(4, "����� � �������� �����"),
	DiscDef(5, "����������� ����"),
	DiscDef(6, "����-����������"),
	DiscDef(7, "���������� ��������� ���"),
	DiscDef(8, "���-�����")
};

static std::vector<CostDef> Resources::costs = {
	CostDef(1, 5),
	CostDef(2, 7),
	CostDef(7, 5),
	CostDef(8, 3)
}