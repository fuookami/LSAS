#pragma once

#include "ArgumentData.h"

namespace Fuookami
{
	class Date
	{
		friend std::istream &operator >> (std::istream &is, Date &date);
		friend std::ostream &operator << (std::ostream &os, const Date &time);

		friend bool operator==(const Date &left, const Date &right);
		friend bool operator!=(const Date &left, const Date &right);
		friend bool operator<(const Date &left, const Date &right);
		friend bool operator>(const Date &left, const Date &right);
		friend bool operator<=(const Date &left, const Date &right);
		friend bool operator>=(const Date &left, const Date &right);

		friend Date distinctionBetween(const Date &left, const Date &right);

	public:
		class Year : public ArgumentData<unsigned short>
		{
		public:
			explicit Year(const unsigned short year) : ArgumentData<unsigned short>(year) {}
		};

		class Month : public ArgumentData<unsigned char>
		{
		public:
			explicit Month(const unsigned char mon) : ArgumentData<unsigned char>(mon) {}
		};

		class Day : public ArgumentData<unsigned char>
		{
		public:
			explicit Day(const unsigned char day) : ArgumentData<unsigned char>(day) {}
		};

		Date() : Date(today()) {};
		Date(const Year &year)
			: m_year(year.data()), m_mon(0), m_day(0) {};
		Date(const Year &year, const Month &month)
			: m_year(year.data()), m_mon(month.data()), m_day(0) {};
		Date(const Year &year, const Month &month, const Day &day)
			: m_year(year.data()), m_mon(month.data()), m_day(day.data()) {};
		Date(const Date &ano)
			: m_year(ano.m_year), m_mon(ano.m_mon), m_day(ano.m_day) {};
		Date(const Date &&ano)
			: m_year(ano.m_year), m_mon(ano.m_mon), m_day(ano.m_day) {};
		~Date() {};

		Date &operator=(const Date &ano);
		Date &operator=(const Date &&ano);

		static Date today();
		static Date tomorrow();
		static Date yesterday();

	public:
		const unsigned short year() const;
		const unsigned char month() const;
		const unsigned char day() const;

		Date daysAfter(const unsigned int days) const;
		Date monthsAfter(const unsigned int months) const;
		Date yearsAfter(const unsigned int years) const;

		Date daysBefore(const unsigned int days) const;
		Date monthsBefore(const unsigned int months) const;
		Date yearsBefore(const unsigned int years) const;

		Date operator+(const unsigned char days);
		Date &operator+=(const unsigned char days);

		Date operator-(const unsigned char days);
		Date &operator-=(const unsigned char days);

	private:
		const bool isValid() const;
		static unsigned char daysNumOfMon(const unsigned short year, const unsigned char mon);
		static bool isLeapYear(const unsigned short year);

	private:
		unsigned short m_year;
		unsigned char m_mon;
		unsigned char m_day;
	};
};
