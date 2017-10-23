#pragma once
#include "definitions.h"

class contour_container;
typedef CvSeq*									contour;
typedef std::function<bool(contour)>			contour_filter;
typedef std::vector<contour_filter>				contour_filter_container;


class contour_container
{
public:

	static bool filter_all(contour_filter_container filters, contour cont);

	contour_container(contour seq, const contour_filter_container& filters)
	{
		m_filters = filters;
		m_contour = seq;

		reset();
	}

	contour_container(const contour_container& copy)
	{
		this->m_contour = copy.m_contour;
		this->m_current = copy.m_current;
		this->m_filters = copy.m_filters;
	}

	void reset()
	{
		m_current = m_contour;
	}

	contour get()
	{
		contour res = next_valid();
		if (!is_end())
			m_current = res->h_next;
		return res;
	}

	bool is_end()
	{
		return m_current == NULL;
	}

private:

	contour next_valid();

	contour_filter_container	m_filters;
	contour						m_current;
	contour						m_contour;
};



