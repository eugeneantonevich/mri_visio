#include "contour.h"

bool contour_container::filter_all(contour_filter_container filters, contour cont)
{
	bool res = true;
	for each (auto filter in filters)
	{
		res = res && filter(cont);
		if (!res)
			break;
	}

	return res;
}

contour contour_container::next_valid()
{
	while (!is_end() && !filter_all(m_filters, m_current))
	{
		m_current = m_current->h_next;
	}
	return m_current;
}
