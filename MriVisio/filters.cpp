
#include "filters.h"

std::function<bool(contour)> contour_filters::empty =
	[](contour c) ->bool {
		return true;
	};

/*
	фильтр для коры мозга. ориентируемся что периметр будет не меньше 200 пикселей
*/

#define min_cortex_lanth 200

std::function<bool(contour)> contour_filters::cortex =
	[](contour c) ->bool {
		return c->total > min_cortex_lanth;
	};



