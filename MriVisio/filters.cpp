
#include "filters.h"

std::function<bool(contour)> contour_filters::empty =
	[](contour c) ->bool {
		return true;
	};

/*
	������ ��� ���� �����. ������������� ��� �������� ����� �� ������ 200 ��������
*/

#define min_cortex_lanth 150

std::function<bool(contour)> contour_filters::cortex =
	[](contour c) ->bool {	
	return true;
		return c->total > min_cortex_lanth;
	};

std::function<bool(contour)> contour_filters::remove_noize =
	[](contour c) ->bool {
		return c->total > 3;
	};