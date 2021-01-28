#include "reminder_manager.h"
#include "event.h"

#ifdef DEBUG

#include <QtTest>



class TestReminder : public QObject
{
	Q_OBJECT

private slots:
	void today_reminders1();
	void today_reminders2();
};



void TestReminder::today_reminders1()
{
	ReminderManager rm("test1.txt");
	rm.today_.setDate(2021, 1, 10);
	rm.ReadTodayReminders();
//	rm.DebugPrintTodayReminders();

	TodayReminders::iterator it = rm.today_reminders_.begin();
	QCOMPARE( (*it)->shp_event_->description_, "First event" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 1, 10), QTime(13, 53)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 1, 10) );
	QCOMPARE( (*it)->shp_event_->time_, QTime(14, 0) );

	it++;
	QCOMPARE( (*it)->shp_event_->description_, "First event" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 1, 10), QTime(14, 0)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 1, 10) );
	QCOMPARE( (*it)->shp_event_->time_, QTime(14, 0) );

	it++;
	QCOMPARE( (*it)->shp_event_->description_, "Second event (no time)" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 1, 10), QTime(0, 0)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 1, 11) );
	QCOMPARE( (*it)->shp_event_->time_.isNull(), true );

	it++;
	QCOMPARE( (*it)->shp_event_->description_, "Third event" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 1, 10), QTime(12, 00)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 1, 13) );
	QCOMPARE( (*it)->shp_event_->time_, QTime(12, 0) );


}



void TestReminder::today_reminders2()
{
	ReminderManager rm("test2.txt");
	rm.today_.setDate(2021, 6, 10);
	rm.ReadTodayReminders();
//	rm.DebugPrintTodayReminders();

	TodayReminders::iterator it = rm.today_reminders_.begin();
	QCOMPARE( (*it)->shp_event_->description_, "Every 4 days event 111" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 6, 10), QTime(12, 0)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 6, 10) );
	QCOMPARE( (*it)->shp_event_->time_, QTime(12, 0) );

	it++;
	QCOMPARE( (*it)->shp_event_->description_, "Every 2 weeks event 222" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 6, 10), QTime(0, 0)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 6, 10) );
	QCOMPARE( (*it)->shp_event_->time_.isNull(), true );

	it++;
	QCOMPARE( (*it)->shp_event_->description_, "Every 3 months event 333" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 6, 10), QTime(16, 0)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 6, 13) );
	QCOMPARE( (*it)->shp_event_->time_, QTime(16, 00) );

	it++;
	QCOMPARE( (*it)->shp_event_->description_, "Every year event 444" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 6, 10), QTime(0, 0)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 6, 12) );
	QCOMPARE( (*it)->shp_event_->time_.isNull(), true );

	it++;
	QCOMPARE( (*it)->shp_event_->description_, "Every week event 555" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 6, 10), QTime(17, 50)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 6, 10) );
	QCOMPARE( (*it)->shp_event_->time_, QTime(18, 00) );

	it++;
	QCOMPARE( (*it)->shp_event_->description_, "Every week event 555" );
	QCOMPARE( (*it)->date_time_, QDateTime(QDate(2021, 6, 10), QTime(18, 0)) );
	QCOMPARE( (*it)->shp_event_->date_, QDate(2021, 6, 10) );
	QCOMPARE( (*it)->shp_event_->time_, QTime(18, 00) );
}



QTEST_MAIN(TestReminder)

#endif

