
#include "filters.h"

std::function<bool(contour)> contour_filters::empty =
	[](contour c) ->bool {
		return true;
	};

/*
	������ ��� ���� �����. ������������� ��� �������� ����� �� ������ 200 ��������
*/

#define min_cortex_lanth 200

std::function<bool(contour)> contour_filters::cortex =
	[](contour c) ->bool {
		return c->total > min_cortex_lanth;
	};



