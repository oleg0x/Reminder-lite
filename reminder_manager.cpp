#include "event.h"
#include "reminder_manager.h"

#include <memory>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QtDebug>



void ReminderManager::ReadTodayReminders()
{
	QFile file(file_name_);
	if ( !file.open(QIODevice::ReadOnly) )
	{
		QMessageBox::critical(0, "Error", "Coould not open file 'data.txt'!", QMessageBox::Ok);
		exit(1);
	}
	QTextStream stream(&file);

	stream.readLine();		// read '[DATA]'
	for ( auto shp_event = std::make_shared<Event>();
		  shp_event->Read(stream, today_);
		  shp_event = std::make_shared<Event>() )
	{
//		++events_count_;
//		qDebug() << events_count_;  event->DebugPrint();
		DateTimes reminder_date_times(shp_event->GetReminderDateTimes());
		for ( const auto& r_date_time : reminder_date_times )
			if ( r_date_time.date() == today_ )
				today_reminders_.emplace_back(new Reminder(r_date_time, shp_event));
	}
//	today_reminders_.sort();
}



/*void ReminderManager::DebugPrintTodayReminders() const
{
	qDebug("  Today_reminders_:");
	for ( auto tr : today_reminders_ )  tr->DebugPrint();
}*/



void ReminderManager::CheckReminders()
{
//	QDateTime now = QDateTime(today_, QTime(17, 55));	// DEBUG
	QDateTime now = QDateTime::currentDateTime();
//	qDebug() << now << ": CheckReminders";

	if ( today_ < now.date() )
	{
		today_ = QDate::currentDate();
		for ( auto p_rem : today_reminders_ )  delete p_rem;
		today_reminders_.clear();
		ReadTodayReminders();
	}

	for ( auto it = today_reminders_.begin(); it != today_reminders_.end(); )
		if ( (*it)->IsTimeToShow(now, timer_period_) )
		{
			(*it)->Show();
			it = today_reminders_.erase(it);
		}
		else  it++;
}



void ReminderManager::SetTimer()
{
	timer_ = new QTimer(this);
	connect(timer_, &QTimer::timeout, this, &ReminderManager::CheckReminders);
	timer_->start(timer_period_ * 1000);
}



ReminderManager::ReminderManager(const QString& file_name)
	: file_name_(file_name), today_(QDate::currentDate())
{
	#ifdef DEBUG
		today_.setDate(2021, 1, 10);	// DEBUG
	#endif

	ReadTodayReminders();
//	DebugPrintTodayReminders();
	CheckReminders();
	SetTimer();
}
