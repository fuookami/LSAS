#pragma once

#include "ArgumentData.h"
#include <array>

namespace Fuookami
{
	class Date
	{
	public:
		class Year : public ArgumentData<short>
		{
		public:
			explicit Year(const short year) : ArgumentData<short>(year) {}
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

	public:
		static const unsigned short DaysOfLeapYear = 366;
		static const unsigned short DaysOfCommonYear = 365;
		static const unsigned short UTCEraYear = 1900;
		static const Date UTCEra;
		static const unsigned char MonthsOfYear = 12;
		static const std::array<unsigned char, MonthsOfYear> DaysOfMonths;
		static const unsigned char DaysOfFebInLeapYear = 29;
		static const std::array<std::string, MonthsOfYear> ENOfMonths;
		static const std::array<std::string, MonthsOfYear> ShortENOfMonths;
		static const std::array<std::string, MonthsOfYear> CNOfMonths;
		static const unsigned char DaysOfWeek = 7;
		static const std::array<std::string, DaysOfWeek> ENOfDayOfWeek;
		static const std::array<std::string, DaysOfWeek> ShortENOfDayOfWeek;
		static const std::array<std::string, DaysOfWeek> CNOfDayOfWeek;

	public:
		Date(const Year &year = Year(UTCEraYear), const Month &month = Month(0), const Day &day = Day(0));
		Date(const Date &ano);
		Date(const Date &&ano);
		~Date();

		Date &operator=(const Date &ano);
		Date &operator=(const Date &&ano);

		static Date today();
		static Date tomorrow();
		static Date yesterday();

		static Date fromBytes(const unsigned int bytes);
		inline unsigned int toBytes(void) const;

	public:
		inline const short year() const;
		inline const unsigned char month() const;
		inline const unsigned char day() const;
		inline const unsigned short dayInYear() const;
		inline const unsigned char dayInWeek() const;

		Date daysAfter(const unsigned int days) const;
		Date monthsAfter(const unsigned int months) const;
		Date yearsAfter(const unsigned int years) const;

		Date daysBefore(const unsigned int days) const;
		Date monthsBefore(const unsigned int months) const;
		Date yearsBefore(const unsigned int years) const;

		Date operator+(const unsigned int days) const;
		Date &operator+=(const unsigned int days);

		Date operator-(const unsigned int days) const;
		Date &operator-=(const unsigned int days);

		Date &operator++(void);
		Date &operator++(const int i);
		Date &operator--(void);
		Date &operator--(const int i);

	public:
		inline static unsigned char daysOfMonth(const short year, const unsigned char mon);
		inline static bool isLeapYear(const short year);
		static unsigned short calDayInYear(const short year, unsigned char mon, unsigned char day);
		static unsigned char calDayInWeek(const short year, unsigned char mon, unsigned char day);

	private:
		const bool isValid() const;

	private:
		short m_year;
		unsigned char m_mon;
		unsigned char m_day;
		unsigned short m_dayInYear;
		unsigned char m_dayInWeek;
	};

	const Date Date::UTCEra = Date(Year(Date::UTCEraYear));

	const std::array<unsigned char, Date::MonthsOfYear> Date::DaysOfMonths = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	const std::array<std::string, Date::MonthsOfYear> Date::ENOfMonths = {
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};

	const std::array<std::string, Date::MonthsOfYear> Date::ShortENOfMonths = {
		"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"
	};

	const std::array<std::string, Date::MonthsOfYear> Date::CNOfMonths = {
		"一月", "二月", "三月", "四月", "五月", "六月", "七月", "八月", "九月", "十月", "十一月", "十二月"
	};

	const std::array<std::string, Date::DaysOfWeek> Date::ENOfDayOfWeek = {
		"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
	};

	const std::array<std::string, Date::DaysOfWeek> Date::ShortENOfDayOfWeek = {
		"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"
	};

	const std::array<std::string, Date::DaysOfWeek> Date::CNOfDayOfWeek = {
		"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"
	};

	Date distinctionBetween(const Date &lhs, const Date &rhs);
	const unsigned int daysBetween(const Date &lhs, const Date &rhs);
	const unsigned int monthsBetween(const Date &lhs, const Date &rhs);
	const unsigned int yearsBetween(const Date &lhs, const Date &rhs);
};

std::istream &operator >> (std::istream &is, Fuookami::Date &date);
std::ostream &operator << (std::ostream &os, const Fuookami::Date &date);

bool operator==(const Fuookami::Date &lhs, const Fuookami::Date &rhs);
bool operator!=(const Fuookami::Date &lhs, const Fuookami::Date &rhs);
bool operator<(const Fuookami::Date &lhs, const Fuookami::Date &rhs);
bool operator>(const Fuookami::Date &lhs, const Fuookami::Date &rhs);
bool operator<=(const Fuookami::Date &lhs, const Fuookami::Date &rhs);
bool operator>=(const Fuookami::Date &lhs, const Fuookami::Date &rhs);
