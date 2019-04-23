#ifndef QVIDEOPLAYERWDGT_H
#define QVIDEOPLAYERWDGT_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class QVideoPlayerWdgt
	: public QWidget
{
	Q_OBJECT

public:
	explicit QVideoPlayerWdgt( QWidget* parent = nullptr );
	QVideoPlayerWdgt( const QVideoPlayerWdgt& other ) = delete;
	QVideoPlayerWdgt( QVideoPlayerWdgt&& other ) = delete;
	void operator=( const QVideoPlayerWdgt& other ) = delete;
	void operator=( QVideoPlayerWdgt&& other ) = delete;
	~QVideoPlayerWdgt();

private:
	QWidget* m_no_source_wdgt;
	QVideoWidget* m_video_wdgt;
	QMediaPlayer* m_media_player;

	QSlider* m_slider_time;
	QLabel* m_lbl_current_time;
	QLabel* m_lbl_total_time;

	QPushButton* m_btn_stop;
	QPushButton* m_btn_backward;
	QPushButton* m_btn_play_pause;
	QPushButton* m_btn_forward;
	QPushButton* m_btn_volume;
	QSlider* m_slider_volume;

	void EnableUi();
	void DisableUi();

};

#endif // QVIDEOPLAYERWDGT_H

/* # Need extra isnstall:
	1. K-Lite base codecs pack;
	2. LAV filters pack
*/
