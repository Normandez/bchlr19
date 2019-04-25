#ifndef QVIDEOPLAYERWDGT_H
#define QVIDEOPLAYERWDGT_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QSlider>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>

#include <QTime>
#include <cmath>

class QClickMovableSlider
	: public QSlider
{
	Q_OBJECT

public:
	QClickMovableSlider( Qt::Orientation orientation, QWidget* parent = nullptr ) : QSlider( orientation, parent ) { }
	~QClickMovableSlider() { }

protected:
	virtual void mousePressEvent ( QMouseEvent* ev ) override
	{
		if( ev->button() == Qt::LeftButton )
		{
			if ( orientation() == Qt::Vertical )
			{
				setValue( minimum() + ( (maximum() - minimum() ) * ( height() - ev->y() ) ) / height() );
			}
			else
			{
				setValue( std::round( static_cast<float>( minimum() ) + ( ( static_cast<float>( maximum() ) - static_cast<float>( minimum() ) ) * static_cast<float>( ev->x() ) ) / static_cast<float>( width() ) ) );
			}

			ev->accept();
			emit sliderMoved( value() );
		}
		QSlider::mousePressEvent(ev);
	}

};

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

	void SetVideo( const QString& video_path );

private:
	bool m_is_media_playing;

	QVideoWidget* m_video_wdgt;
	QMediaPlayer* m_media_player;

	QClickMovableSlider* m_slider_time;
	QLabel* m_lbl_current_time;
	QLabel* m_lbl_total_time;

	QPushButton* m_btn_stop;
	QPushButton* m_btn_backward;
	QPushButton* m_btn_play_pause;
	QPushButton* m_btn_forward;
	QPushButton* m_btn_volume;
	QClickMovableSlider* m_slider_volume;

	QString m_time_format;
	qint64 m_media_duration;
	qint64 m_media_forward_step;
	int m_media_volume;
	int m_last_media_volume;

	void EnableUi();
	void DisableUi();

private slots:
	void onBtnStopClicked();
	void onBtnPlayPauseClicked();
	void onBtnBackwardClicked();
	void onBtnForwardClicked();
	void onBtnVolumeClicked();

	void onSliderTimeMoved( int value );
	void onSliderTimePressed();
	void onSliderTimeReleased();
	void onSliderVolumeValueChanged( int value );

	void onMediaDurationChanged( qint64 duration );
	void onMediaPositionChanged( qint64 position );
	void onMediaStatusChanged( QMediaPlayer::MediaStatus status );

};

#endif // QVIDEOPLAYERWDGT_H

/* # Need extra isnstall:
	1. K-Lite base codecs pack;
	2. LAV filters pack
*/
