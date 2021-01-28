#pragma once

#include <memory>
#include <QDateTime>
#include <QWidget>

class Event;



class Reminder : public QWidget
{
Q_OBJECT

public:
	Reminder(const Reminder& reminder);
	Reminder(const QDateTime date_time, const std::shared_ptr<Event> shp_event);
//	~Reminder();
	bool IsTimeToShow(const QDateTime& now, const uint32_t timer_period) const;
	void Show();
	void DebugPrint() const;

private:
	QDateTime date_time_;
	std::shared_ptr<Event> shp_event_;
//	mutable bool continue_remind_ = true;

	friend class TestReminder;
};
