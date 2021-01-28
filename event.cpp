#include "event.h"

#include <QtDebug>



std::vector<uint16_t> ParseStr(const QString& str)
{
	QStringList str_list = str.split(QRegExp("\\D"), Qt::SkipEmptyParts);
	std::vector<uint16_t> result;
	for ( auto& s : str_list )  result.push_back(s.toUShort());
	return result;
}



uint32_t MonthsBetween(const QDate& start, const QDate& finish)
{
	uint32_t min_months = start.daysTo(finish) / 31;
	uint32_t i = 0;
	for ( QDate date = start.addMonths(min_months);
		  date.month() < finish.month();
		  date = date.addMonths(1) )  i++;
	return min_months + i;
}



uint32_t YearsBetween(const QDate& start, const QDate& finish)
{
	uint32_t min_years = start.daysTo(finish) / 366;
	uint32_t i = 0;
	for ( QDate date = start.addYears(min_years);
		  date.year() < finish.year();
		  date = date.addYears(1) )	 i++;
	return min_years + i;
}



void Event::Clear()
{
	date_ = QDate();
	time_ = QTime();
	description_.clear();
	category_ = 0;
	important_ = false;
	period_ = Period {0};
	period_count_ = 0;
	remind_days_.clear();
	remind_min_.clear();
}



void Event::RenewDateOfPeriodicEvent(const QDate& today)
{
	switch ( period_ )
	{
		case Period::day:
			if ( date_.daysTo(today) % period_count_ == 0 )
				date_ = today;
		break;
		case Period::week:
			if ( date_.daysTo(today) % (period_count_ * 7) == 0 )
				date_ = today;
		break;
		case Period::month:
			if ( MonthsBetween(date_, today) % period_count_ == 0 )
				date_ =  QDate( today.year(), today.month(), date_.day() );
		break;
		case Period::year:
			if ( YearsBetween(date_, today) % period_count_ == 0 )
				date_ = QDate( today.year(), date_.month(), date_.day() );
		break;
		case Period::no:
		break;
	}
}



bool Event::Read(QTextStream& stream, const QDate& today)
{
	Clear();
	QString line;
	while ( !stream.atEnd() && line != "{" )  line = stream.readLine().simplified();
	if ( line != "{" )  return false;

	line = stream.readLine();
	while ( line != "}" && !stream.atEnd() )
	{
		QStringList parts = line.split("=", Qt::SkipEmptyParts, Qt::CaseSensitive);
		if ( parts.size() == 2 )	// Split into two parts exactly
		{
			parts[0] = parts[0].simplified();
			parts[1] = parts[1].simplified();
			if		( parts[0] == "date" )			date_ = QDate::fromString(parts[1], "dd.MM.yyyy");
			else if ( parts[0] == "time" )			time_ = QTime::fromString(parts[1]);
			else if ( parts[0] == "description" )	description_ = parts[1];
			else if ( parts[0] == "category" )		category_ = parts[1].toShort();
			else if ( parts[0] == "important" )		important_ = parts[1].toShort();
			else if ( parts[0] == "period" )		period_ = static_cast<Period>(parts[1].toShort());
			else if ( parts[0] == "period_count" )	period_count_ = parts[1].toShort();
			else if ( parts[0] == "remind_days" )	remind_days_ = ParseStr(parts[1]);
			else if ( parts[0] == "remind_min" )	remind_min_ = ParseStr(parts[1]);
		}
		line = stream.readLine();
	}

	if ( description_.isEmpty() || period_ < Period::day || period_ > Period::no || line != "}" )
		return false;
	if ( period_ != Period::no && period_count_ <= 0 )
		period_count_ = 1;

	description_ = description_.right(description_.size() - 1);		// Delete first '"'
	description_.resize(description_.size() - 1);					// Delete last '"'

	RenewDateOfPeriodicEvent(today);
	return true;
}



DateTimes Event::GetReminderDateTimes() const
{
	DateTimes result;
	result.reserve(remind_days_.size() + remind_min_.size() + 1);
	QDateTime date_time(date_, time_);  // If date is valid and time is not, the time will be midnight

	for ( uint16_t days : remind_days_ )
		result.push_back(date_time.addDays(-days));
	for ( uint16_t mins : remind_min_ )
		result.push_back(date_time.addSecs(-60 * mins));
	result.push_back(date_time);

	return result;
}



/*void Event::DebugPrint() const
{
	qDebug() << date_ << time_ << description_
			 << category_ << important_ << static_cast<uint8_t>(period_) << period_count_
			 << remind_days_ << remind_min_;
}*/
