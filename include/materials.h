#ifndef SPACESNAKE_MATERIALS_H
#define SPACESNAKE_MATERIALS_H

typedef enum e_material_type {
	MATERIAL_NONE_BEGIN = 0,
	MATERIAL_BRASS,
	MATERIAL_BRONZE,
	MATERIAL_POLISHED_BRONZE,
	MATERIAL_CHROME,
	MATERIAL_COPPER,
	MATERIAL_POLISHED_COPPER,
	MATERIAL_GOLD,
	MATERIAL_POLISHED_GOLD,
	MATERIAL_TIN,
	MATERIAL_SILVER,
	MATERIAL_POLISHED_SILVER,
	MATERIAL_EMERALD,
	MATERIAL_JADE,
	MATERIAL_OBSIDIAN,
	MATERIAL_PERL,
	MATERIAL_RUBY,
	MATERIAL_TURQUOISE,
	MATERIAL_BLACK_PLASTIC,
	MATERIAL_CYAN_PLASTIC,
	MATERIAL_GREEN_PLASTIC,
	MATERIAL_RED_PLASTIC,
	MATERIAL_WHITE_PLASTIC,
	MATERIAL_YELLOW_PLASTIC,
	MATERIAL_BLACK_RUBBER,
	MATERIAL_CYAN_RUBBER,
	MATERIAL_GREEN_RUBBER,
	MATERIAL_RED_RUBBER,
	MATERIAL_WHITE_RUBBER,
	MATERIAL_YELLOW_RUBBER,
	MATERIAL_EMPTY_END
}			 t_material_type;

void applyMaterial(GLenum cullMode, t_material_type materialType);


#endif //SPACESNAKE_MATERIALS_H
