#include "QMainWnd.h"
#include "ui_QMainWnd.h"

QMainWnd::QMainWnd( const SContext* context, QWidget* parent /*= nullptr*/ )
	: QMainWindow(parent),
	  ui( new Ui::QMainWnd )
{
	ui->setupUi(this);

	ui->tab_wdgt->tabBar()->setStyle( new QCustomTabStyle() );
	InitStylesUi();
}

QMainWnd::~QMainWnd()
{
	delete ui;
}

void QMainWnd::InitStylesUi()
{
	QListWidgetItem* itm_la_muse = new QListWidgetItem( QIcon(":/res/la_muse.jpg"), "La Muse" );
	QListWidgetItem* itm_rain_princess = new QListWidgetItem( QIcon(":/res/rain_princess.jpg"), "Rain Princess" );
	QListWidgetItem* itm_the_scream = new QListWidgetItem( QIcon(":/res/the_scream.jpg"), "The Scream" );
	QListWidgetItem* itm_udnie = new QListWidgetItem( QIcon(":/res/udnie.jpg"), "Udnie" );
	QListWidgetItem* itm_wave = new QListWidgetItem( QIcon(":/res/wave.jpg"), "Wave" );
	QListWidgetItem* itm_wreck = new QListWidgetItem( QIcon(":/res/the_shipwreck_of_the_minotaur.jpg"), "The Shipwreck Of The Minotaur" );

	ui->list_wdgt_style->addItem(itm_la_muse);
	ui->list_wdgt_style->addItem(itm_rain_princess);
	ui->list_wdgt_style->addItem(itm_the_scream);
	ui->list_wdgt_style->addItem(itm_udnie);
	ui->list_wdgt_style->addItem(itm_wave);
	ui->list_wdgt_style->addItem(itm_wreck);

	ui->list_wdgt_style->setIconSize( QSize( 300, 300 ) );
}

void QMainWnd::Show()
{
	this->show();
}
