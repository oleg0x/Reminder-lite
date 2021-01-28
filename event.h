#pragma once

#include <list>
#include <QDate>
#include <QString>
#include <QTextStream>
#include <QTime>



using DateTimes = std::vector<QDateTime>;
using Category = uint8_t;

enum struct Period : uint8_t { day = 1, week = 2, month = 3, year = 4, no = 5 };



class Event
{
public:
	void Clear();
	bool Read(QTextStream& stream, const QDate& today);
	DateTimes GetReminderDateTimes() const;
	void DebugPrint() const;

private:
	QDate date_;
	QTime time_;
	QString description_;
	Category category_;
	bool important_;
	Period period_;
	uint16_t period_count_;
	std::vector<uint16_t> remind_days_;
	std::vector<uint16_t> remind_min_;

	void RenewDateOfPeriodicEvent(const QDate& date);

	friend class Reminder;
	friend class TestReminder;
};
