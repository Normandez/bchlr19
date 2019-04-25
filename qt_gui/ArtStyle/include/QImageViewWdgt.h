#ifndef QIMAGEVIEWWDGT_H
#define QIMAGEVIEWWDGT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPixmap>

#include <QScrollArea>
#include <QLabel>

#include <QPushButton>

class QImageViewWdgt :
	public QWidget
{
	Q_OBJECT

public:
	explicit QImageViewWdgt( QWidget* parent = nullptr );
	QImageViewWdgt( const QImageViewWdgt& other ) = delete;
	QImageViewWdgt( QImageViewWdgt&& other ) = delete;
	void operator=( const QImageViewWdgt& other ) = delete;
	void operator=( QImageViewWdgt&& other ) = delete;
	~QImageViewWdgt();

	void SetImage( const QString& img_path );

private:
	QPixmap m_no_source_pixmap;
	QPixmap m_loaded_pixmap;
	bool m_is_adjusted;

	QScrollArea* m_img_placeholder;
	QLabel* m_img;

	QPushButton* m_btn_normal_size;
	QPushButton* m_btn_fit_to_wnd;
	QPushButton* m_btn_zoom_in;
	QPushButton* m_btn_zoom_out;

	bool m_is_enable_ui;

	void EnableUi();
	void DisableUi();

	void NormalSize();
	void FitToWindow();
	void ZoomIn();
	void ZoomOut();

private slots:
	void onBtnNormalSizeClicked();	
	void onBtnFitToWindowClicked();
	void onBtnZoomInClicked();
	void onBtnZoomOutClicked();

};

#endif // QIMAGEVIEWWDGT_H
