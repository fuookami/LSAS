#include "Date.h"

#include <sstream>
#include <iomanip>
#include <exception>
#include <cmath>

namespace Fuookami
{
	Date::Date(const Year & year, const Month & month, const Day & day)
		: m_year(year.data()), m_mon(month.data() - 1), m_day(day.data() - 1),
		m_dayInYear(calDayInYear(m_year, m_mon, m_day)), m_dayInWeek(calDayInWeek(m_year, m_mon, m_day))
	{
		if (!isValid())
		{
			std::ostringstream sout;
			sout << "Invalid Date \"" << *this << "\"";
			throw std::runtime_error(sout.str().c_str());
		}
	}

	Date::Date(const Date & ano)
		: m_year(ano.m_year), m_mon(ano.m_mon), m_day(ano.m_day),
		m_dayInYear(ano.m_dayInYear), m_dayInWeek(ano.m_dayInWeek)
	{
	}

	Date::Date(const Date && ano)
		: m_year(ano.m_year), m_mon(ano.m_mon), m_day(ano.m_day),
		m_dayInYear(ano.m_dayInYear), m_dayInWeek(ano.m_dayInWeek)
	{
	}

	Date::~Date()
	{
	}

	Date & Date::operator=(const Date & ano)
	{
		m_year = ano.m_year;
		m_mon = ano.m_mon;
		m_day = ano.m_day;
		m_dayInYear = ano.m_dayInYear;
		m_dayInWeek = ano.m_dayInWeek;
		return *this;
	}

	Date & Date::operator=(const Date && ano)
	{
		m_year = ano.m_year;
		m_mon = ano.m_mon;
		m_day = ano.m_day;
		m_dayInYear = ano.m_dayInYear;
		m_dayInWeek = ano.m_dayInWeek;
		return *this;
	}

	Date Date::today()
	{
		return Date();
	}

	Date Date::tomorrow()
	{
		Date ret(today());
		--ret;
		return std::move(ret);
	}

	Date Date::yesterday()
	{
		Date ret(today());
		++ret;
		return std::move(ret);
	}

	Date Date::fromBytes(const unsigned int bytes)
	{
		short year(0);
		unsigned char mon(0), day(0);
		day = bytes & 0x000000ff;
		mon = (bytes & 0x0000ff00) >> 8;
		year = (bytes & 0xffff0000) >> 16;

		return Date(Year(year), Month(mon), Day(day));
	}

	inline unsigned int Date::toBytes(void) const
	{
		unsigned int ret(0);
		ret |= m_year;
		ret <<= 16;
		ret |= m_mon;
		ret <<= 8;
		ret |= m_day;

		return ret;
	}

	inline const short Date::year() const
	{
		return m_year;
	}

	inline const unsigned char Date::month() const
	{
		return m_mon + 1;
	}

	inline const unsigned char Date::day() const
	{
		return m_day + 1;
	}

	inline const unsigned short Date::dayInYear() const
	{
		return m_dayInYear + 1;
	}

	inline const unsigned char Date::dayInWeek() const
	{
		return m_dayInWeek;
	}

	Date Date::daysAfter(const unsigned int days) const
	{
		return Date();
	}

	Date Date::monthsAfter(const unsigned int months) const
	{
		return Date();
	}

	Date Date::yearsAfter(const unsigned int years) const
	{
		return Date();
	}

	Date Date::daysBefore(const unsigned int days) const
	{
		return Date();
	}

	Date Date::monthsBefore(const unsigned int months) const
	{
		return Date();
	}

	Date Date::yearsBefore(const unsigned int years) const
	{
		return Date();
	}

	Date Date::operator+(const unsigned int days) const
	{
		return this->daysAfter(days);
	}

	Date & Date::operator+=(const unsigned int days)
	{
		*this = this->daysAfter(days);
		return *this;
	}

	Date Date::operator-(const unsigned int days) const
	{
		return this->daysBefore(days);
	}

	Date & Date::operator-=(const unsigned int days)
	{
		*this = this->daysBefore(days);
		return *this;
	}

	Date & Date::operator++(void)
	{
		*this = this->daysAfter(1);
		return *this;
	}

	Date & Date::operator++(const int i)
	{
		*this = this->daysAfter(1);
		return *this;
	}

	Date & Date::operator--(void)
	{
		*this = this->daysBefore(1);
		return *this;
	}

	Date & Date::operator--(const int i)
	{
		*this = this->daysBefore(1);
		return *this;
	}

	inline unsigned char Date::daysOfMonth(const short year, const unsigned char mon)
	{
		return mon != 2 ? DaysOfMonths[mon - 1]
			: isLeapYear(year) ? DaysOfFebInLeapYear : DaysOfMonths[mon - 1];
	}

	inline bool Date::isLeapYear(const short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}

	unsigned short Date::calDayInYear(const short year, const unsigned char mon, const unsigned char day)
	{
		unsigned short days(0);
		for (unsigned char i(0); i != mon; ++i)
		{
			days += daysOfMonth(year, mon + 1);
		}
		return days + day;
	}

	unsigned char Date::calDayInWeek(const short year, const unsigned char mon, const unsigned char day)
	{
		return 0;
	}

	const bool Date::isValid() const
	{
		return false;
	}

	Date distinctionBetween(const Date & lhs, const Date & rhs)
	{
		return Date();
	}

	const unsigned int daysBetween(const Date & lhs, const Date & rhs)
	{
		if (lhs == rhs)
		{
			return 0;
		}

		const Date *minSide(&lhs), *bigSide(&rhs);
		if (lhs > rhs)
		{
			std::swap(minSide, bigSide);
		}

		unsigned int days(0);
		for (unsigned short i(minSide->year()), j(bigSide->year()); i != j; ++i)
		{
			days += Date::isLeapYear(i) ? Date::DaysOfLeapYear 
				: Date::DaysOfCommonYear;
		}

		days += rhs.dayInYear() - lhs.dayInYear();
		return days;
	}

	const unsigned int monthsBetween(const Date & lhs, const Date & rhs)
	{
		if (lhs == rhs)
		{
			return 0;
		}

		const Date *minSide(&lhs), *bigSide(&rhs);
		if (lhs > rhs)
		{
			std::swap(minSide, bigSide);
		}

		return (bigSide->year() - minSide->year()) * Date::MonthsOfYear + rhs.month() - lhs.month();
	}

	const unsigned int yearsBetween(const Date & lhs, const Date & rhs)
	{
		return abs(static_cast<int>(lhs.year()) - static_cast<int>(rhs.year()));
	}
};

std::istream &operator >> (std::istream &is, Fuookami::Date &date)
{
	using Fuookami::Date;

	short year(0);
	unsigned char mon(0), day(0);
	is >> year >> mon >> day;
	date = Date(Date::Year(year), Date::Month(mon), Date::Day(day));

	return is;
}

std::ostream &operator << (std::ostream &os, const Fuookami::Date &date)
{
	os << std::setfill(0)
		<< date.year() << std::setw(2) << date.month() << std::setw(2) << date.day()
		<< std::setfill(' ');

	return os;
}

bool operator==(const Fuookami::Date &lhs, const Fuookami::Date &rhs)
{
	return lhs.year() == rhs.year() && lhs.month() == rhs.month() && lhs.day() == rhs.day();
}

bool operator!=(const Fuookami::Date &lhs, const Fuookami::Date &rhs)
{
	return lhs.year() != rhs.year() || lhs.month() != rhs.month() || lhs.day() != rhs.day();
}

bool operator<(const Fuookami::Date &lhs, const Fuookami::Date &rhs)
{
	return lhs.toBytes() < rhs.toBytes();
}

bool operator>(const Fuookami::Date &lhs, const Fuookami::Date &rhs)
{
	return lhs.toBytes() > rhs.toBytes();
}

bool operator<=(const Fuookami::Date &lhs, const Fuookami::Date &rhs)
{
	return lhs.toBytes() <= rhs.toBytes();
}

bool operator>=(const Fuookami::Date &lhs, const Fuookami::Date &rhs)
{
	return lhs.toBytes() >= rhs.toBytes();
}
