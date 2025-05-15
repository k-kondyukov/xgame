#ifndef COST_DEF
#define COST_DEF

struct CostDef {
	int id;
	int price;
	CostDef(const int& id, const int& price) : id(id), price(price) {}
};

#endif // !COST_DEF
