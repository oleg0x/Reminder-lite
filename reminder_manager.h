#pragma once

#include "reminder.h"
#include "event.h"

#include <QTimer>

//#define DEBUG

using TodayReminders = std::list<Reminder*>;



class ReminderManager : public QObject
{
	Q_OBJECT

public:
	ReminderManager(const QString& file_name = "data.txt");

private slots:
	void CheckReminders();

private:
	const QString file_name_;
	QDate today_;
	TodayReminders today_reminders_;
//	uint32_t events_count_ = 0;
	uint32_t timer_period_ = 5 * 60;	// in seconds
//	uint32_t timer_period_ = 10;		// DEBUG
	QTimer *timer_;

	void ReadTodayReminders();
	void DebugPrintTodayReminders() const;
	void SetTimer();

	friend class TestReminder;
};

