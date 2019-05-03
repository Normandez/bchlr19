#ifndef QMAINWND_H
#define QMAINWND_H

#include <QMainWindow>
#include <QGridLayout>
#include <QSpacerItem>
#include <QScreen>

#include <QTabBar>
#include <QProxyStyle>
#include <QStyleOption>

#include <QListView>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

#include <QFileDialog>

#include "SContext.h"

namespace Ui
{
	class QMainWnd;
}

class QMainWnd
	: public QMainWindow
{
	Q_OBJECT

public:
	explicit QMainWnd( const SContext* context, QWidget* parent = nullptr );
	QMainWnd( const QMainWnd& other ) = delete;
	QMainWnd( QMainWnd&& other ) = delete;
	void operator=( const QMainWnd& other ) = delete;
	void operator=( QMainWnd&& other ) = delete;
	~QMainWnd();

	void Show();

	void SetTransformedImage( const QString& out_image_url );
	void SetTransformedVideo( const QString& out_video_url );

private:
	class QCustomTabStyle
		: public QProxyStyle
	{
	protected:
		virtual void drawControl( QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr ) const override
		{
			if( element == CE_TabBarTab )
			{
				if( const QStyleOptionTab* tab = qstyleoption_cast< const QStyleOptionTab* >(option) )
				{
					QStyleOptionTab opt_tab(*tab);
					opt_tab.shape = QTabBar::RoundedNorth;
					QProxyStyle::drawControl( element, &opt_tab, painter, widget );
					return;
				}
			}
			QProxyStyle::drawControl( element, option, painter, widget );
		}

		virtual QSize sizeFromContents( QStyle::ContentsType type, const QStyleOption *option, const QSize &contentsSize, const QWidget *widget = nullptr ) const override
		{
			QSize size = QProxyStyle::sizeFromContents( type, option, contentsSize, widget );
			if( type == QStyle::CT_TabBarTab )
			{
				size.transpose();
			}
			return size;
		}

	};

	Ui::QMainWnd* ui;

	QString m_last_img_dir;
	QString m_last_video_dir;

	void InitStylesUi();

signals:
	void startTransformation( ETransformationType transformation_type, int checkpoint, const QString& in_path );
	void stopTransformation( ETransformationType transformation_type );

private slots:
	void on_btn_img_in_load_clicked();
	void on_btn_video_in_load_clicked();
	void on_btn_img_out_transform_clicked();
	void on_btn_img_out_stop_transform_clicked();
	void on_btn_video_out_transform_clicked();
	void on_btn_video_out_stop_transform_clicked();

};

#endif // QMAINWND_H
