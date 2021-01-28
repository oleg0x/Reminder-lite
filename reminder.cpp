#include "event.h"
#include "reminder.h"

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtDebug>



QVector<QString> category_names = { "Other", "Birthday", "Holiday", "Work" };



Reminder::Reminder(const Reminder& reminder)
	: date_time_(reminder.date_time_), shp_event_(reminder.shp_event_)
{}



Reminder::Reminder(const QDateTime date_time, const std::shared_ptr<Event> shp_event)
	: date_time_(date_time), shp_event_(shp_event)
{}



/*Reminder::~Reminder()
{
	qDebug("~Reminder()");		// DEBUG
}*/



bool Reminder::IsTimeToShow(const QDateTime& now, const uint32_t timer_period) const
{
	return shp_event_->time_.isNull() ||
		   now.secsTo(date_time_) < timer_period ;
}



void Reminder::Show()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setMinimumSize(420, 220);

	QLabel* category = new QLabel;
	QFont font1 = category->font();
	font1.setPointSize(10);
	category->setFont(font1);
	extern QVector<QString> category_names;
	if ( 0 <= shp_event_->category_ && shp_event_->category_ < category_names.size() )
		category->setText(category_names[shp_event_->category_] + ":");

	QLabel* remind_message = new QLabel;
	QFont msg_font(font1);
	msg_font.setPointSize(12);
	remind_message->setWordWrap(true);
	remind_message->setFont(msg_font);
	remind_message->setText(shp_event_->description_);

	QLabel* date_time = new QLabel;
	font1.setItalic(false);
	date_time->setFont(font1);
	QString str("Date: " + shp_event_->date_.toString("ddd dd.MM.yyyy"));
	if ( !shp_event_->time_.isNull() )
		str += ",    Time: " + shp_event_->time_.toString("hh:mm");
	date_time->setText(str);

	QLabel* remains = new QLabel;
	if ( int d = QDate::currentDate().daysTo(shp_event_->date_); d >= 1 )
		remains->setText(QString::number(d) + " day(s) remain(s)");
	else if ( shp_event_->time_.isNull() )
		remains->setText("Today");
	else
	{
		int m = QDateTime::currentDateTime().secsTo(
			QDateTime(shp_event_->date_, shp_event_->time_)) / 60;
		remains->setText(QString::number(m) + " minute(s) remain(s)");
	}

	QPixmap pict("excl.png");
	QLabel* important = new QLabel;
	important->resize(pict.size());
	important->setPixmap(pict);

	QCheckBox* cont_remind_check = new QCheckBox;
	cont_remind_check->setText("&Keep reminding me according to the schedule");
	cont_remind_check->setChecked(true);
	cont_remind_check->setDisabled(true);

	QPushButton* ok_button = new QPushButton("OK");
	ok_button->setAutoDefault(true);
	auto c = connect(ok_button, &QAbstractButton::clicked, this, &Reminder::deleteLater);

	QVBoxLayout* vlayout = new QVBoxLayout;
	vlayout->addWidget(remind_message);
	vlayout->addWidget(date_time);
	vlayout->addWidget(remains);

	QHBoxLayout* hlayout = new QHBoxLayout;
	hlayout->addLayout(vlayout, 1);
	if ( shp_event_->important_ )
		hlayout->addWidget( important, 0, Qt::AlignRight | Qt::AlignTop);

	QVBoxLayout* mainvlayout = new QVBoxLayout;
	mainvlayout->addWidget(category);
	mainvlayout->addLayout(hlayout);
	mainvlayout->addStretch();
	mainvlayout->addWidget(cont_remind_check);
	mainvlayout->addStretch();
	mainvlayout->addWidget(ok_button, 0, Qt::AlignHCenter);

	setLayout(mainvlayout);
	show();
}



/*bool operator <(const Reminder& left, const Reminder& right)
{
	return left.date_time_ < right.date_time_;
}*/



/*void Reminder::DebugPrint() const
{
	qDebug() << date_time_ << shp_event_.get() << shp_event_->description_
			 << shp_event_->date_ << shp_event_->time_;
}*/
