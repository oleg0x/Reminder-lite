#include "main_window.h"

#include <QApplication>

#include "event.h"
#include "reminder_manager.h"
#include <QtDebug>
#include <QSystemTrayIcon>
#include <QMenu>



#ifndef DEBUG

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(false);
//	MainWindow w;
//	w.show();
//	return a.exec();

	ReminderManager rm("data.txt");

	QMenu* tray_menu_ =	new QMenu;
//	QAction* show_hide_act = new QAction("Show/Hide Reminder");
//	tray_menu_->addAction(show_hide_act);
//	connect(show_hide_act, &QAction::triggered, this, [&](){ setVisible(!isVisible()); } );
	QAction* exit_act = new QAction("Exit");
	tray_menu_->addAction(exit_act);
	QObject::connect(exit_act, &QAction::triggered, qApp, &QApplication::quit);


	QIcon tr_ic("reminder.png");
	QSystemTrayIcon* tray_icon_ = new QSystemTrayIcon(tr_ic);
	tray_icon_->setToolTip("Reminder");
	tray_icon_->show();
	tray_icon_->setContextMenu(tray_menu_);

	return app.exec();
}

#endif
