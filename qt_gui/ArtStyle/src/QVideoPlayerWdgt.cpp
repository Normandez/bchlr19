#include "QVideoPlayerWdgt.h"

QVideoPlayerWdgt::QVideoPlayerWdgt( QWidget* parent /*= nullptr*/ )
	: QWidget(parent),
	  m_video_url(""),
	  m_is_media_playing(false),
	  m_time_format(""),
	  m_media_duration(0),
	  m_media_forward_step(0),
	  m_media_volume(0),
	  m_last_media_volume(0)
{
	m_video_wdgt = new QVideoWidget();
	m_video_wdgt->setAttribute(Qt::WA_OpaquePaintEvent);
	QPalette video_wdgt_pal;
	video_wdgt_pal.setColor( QPalette::Window, Qt::black );
	m_video_wdgt->setPalette(video_wdgt_pal);
	m_media_player = new QMediaPlayer(this);
	m_media_player->setVideoOutput(m_video_wdgt);
	m_video_wdgt->setFixedSize( QSize( 632, 525 ) );

	QHBoxLayout* time_lyt = new QHBoxLayout();
	m_slider_time = new QClickMovableSlider(Qt::Horizontal);
	m_lbl_total_time = new QLabel();
	QLabel* lbl_time_sep = new QLabel("/");
	m_lbl_current_time = new QLabel();
	time_lyt->addWidget(m_slider_time);
	time_lyt->addWidget(m_lbl_current_time);
	time_lyt->addWidget(lbl_time_sep);
	time_lyt->addWidget(m_lbl_total_time);

	QHBoxLayout* player_control_lyt = new QHBoxLayout();
	m_btn_stop = new QPushButton( QIcon(":/res/stop.png"), "" );
	m_btn_backward = new QPushButton( QIcon(":/res/backward.png"), "" );
	m_btn_play_pause = new QPushButton( QIcon(":/res/play.png"), "" );
	m_btn_forward = new QPushButton( QIcon(":/res/forward.png"), "" );
	m_btn_volume = new QPushButton( QIcon(":/res/no_volume.png"), "" );
	m_slider_volume = new QClickMovableSlider(Qt::Horizontal);
	m_slider_volume->setFixedWidth(100);
	m_slider_volume->setMaximum(100);
	player_control_lyt->addWidget(m_btn_stop);
	player_control_lyt->addWidget(m_btn_backward);
	player_control_lyt->addWidget(m_btn_play_pause);
	player_control_lyt->addWidget(m_btn_forward);
	player_control_lyt->addWidget(m_btn_volume);
	player_control_lyt->addWidget(m_slider_volume);
	player_control_lyt->addSpacerItem( new QSpacerItem( 20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum ) );

	QVBoxLayout* common_lyt = new QVBoxLayout();
	common_lyt->addWidget(m_video_wdgt);
	common_lyt->addLayout(time_lyt);
	common_lyt->addLayout(player_control_lyt);
	common_lyt->addSpacerItem( new QSpacerItem( 20, 40, QSizePolicy::Maximum, QSizePolicy::Expanding ) );
	this->setLayout(common_lyt);

	DisableUi();

	bool connection_chk = connect( m_btn_stop, &QPushButton::clicked, this, &QVideoPlayerWdgt::onBtnStopClicked );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_btn_play_pause, &QPushButton::clicked, this, &QVideoPlayerWdgt::onBtnPlayPauseClicked );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_btn_backward, &QPushButton::clicked, this, &QVideoPlayerWdgt::onBtnBackwardClicked );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_btn_forward, &QPushButton::clicked, this, &QVideoPlayerWdgt::onBtnForwardClicked );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_btn_volume, &QPushButton::clicked, this, &QVideoPlayerWdgt::onBtnVolumeClicked );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_slider_time, &QSlider::sliderPressed, this, &QVideoPlayerWdgt::onSliderTimePressed );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_slider_time, &QSlider::sliderMoved, this, &QVideoPlayerWdgt::onSliderTimeMoved );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_slider_time, &QSlider::sliderReleased, this, &QVideoPlayerWdgt::onSliderTimeReleased );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_slider_volume, &QSlider::valueChanged, this, &QVideoPlayerWdgt::onSliderVolumeValueChanged );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_media_player, &QMediaPlayer::durationChanged, this, &QVideoPlayerWdgt::onMediaDurationChanged );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_media_player, &QMediaPlayer::positionChanged, this, &QVideoPlayerWdgt::onMediaPositionChanged );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_media_player, &QMediaPlayer::mediaStatusChanged, this, &QVideoPlayerWdgt::onMediaStatusChanged );
	Q_ASSERT(connection_chk);
}

QVideoPlayerWdgt::~QVideoPlayerWdgt()
{
	this->disconnect();
}

void QVideoPlayerWdgt::SetVideo( const QString& video_url )
{
	m_video_url = video_url;

	DisableUi();
	EnableUi();
	onBtnStopClicked();

	m_media_player->setMedia( QUrl::fromLocalFile(m_video_url) );
	m_media_volume = 0;
	m_media_player->setVolume(m_media_volume);
	m_media_player->play();
	m_media_player->pause();
	m_is_media_playing = false;
}

QString QVideoPlayerWdgt::GetViedoUrl() const
{
	return m_video_url;
}

void QVideoPlayerWdgt::EnableUi()
{
	m_slider_time->setEnabled(true);
	m_slider_volume->setEnabled(true);
	m_btn_stop->setEnabled(true);
	m_btn_backward->setEnabled(true);
	m_btn_play_pause->setEnabled(true);
	m_btn_forward->setEnabled(true);
	m_btn_volume->setEnabled(true);
}

void QVideoPlayerWdgt::DisableUi()
{
	m_slider_time->setEnabled(false);
	m_slider_volume->setEnabled(false);
	m_btn_stop->setEnabled(false);
	m_btn_backward->setEnabled(false);
	m_btn_play_pause->setEnabled(false);
	m_btn_forward->setEnabled(false);
	m_btn_volume->setEnabled(false);

	m_lbl_current_time->setText("00:00");
	m_lbl_total_time->setText("00:00");
	
	m_slider_volume->setValue(0);
}

void QVideoPlayerWdgt::onBtnStopClicked()
{
	m_media_player->stop();
	m_is_media_playing = false;

	m_btn_play_pause->setIcon( QIcon(":/res/play.png") );
	m_slider_time->setValue(0);
	m_video_wdgt->repaint();
}

void QVideoPlayerWdgt::onBtnPlayPauseClicked()
{
	QMediaPlayer::State player_state = m_media_player->state();
	if( player_state == QMediaPlayer::StoppedState || player_state == QMediaPlayer::PausedState )
	{
		m_media_player->play();
		m_is_media_playing = true;
		m_btn_play_pause->setIcon( QIcon(":/res/pause.png") );
	}
	else
	{
		m_media_player->pause();
		m_is_media_playing = false;
		m_btn_play_pause->setIcon( QIcon(":/res/play.png") );
	}
}

void QVideoPlayerWdgt::onBtnBackwardClicked()
{
	if( m_media_player->state() == QMediaPlayer::StoppedState )
	{
		return;
	}
	m_media_player->setPosition( m_media_player->position() - ( m_media_forward_step * 1000 ) );
}

void QVideoPlayerWdgt::onBtnForwardClicked()
{
	if( m_media_player->state() == QMediaPlayer::StoppedState )
	{
		return;
	}
	m_media_player->setPosition( m_media_player->position() + ( m_media_forward_step * 1000 ) );
}

void QVideoPlayerWdgt::onBtnVolumeClicked()
{
	int playing_volume = m_media_player->volume();
	if( playing_volume != 0 )
	{
		m_last_media_volume = m_media_volume;
		m_slider_volume->setValue(0);
	}
	else
	{
		m_slider_volume->setValue( ( m_last_media_volume == 0 ) ? 1 : m_last_media_volume );
	}
}

void QVideoPlayerWdgt::onSliderTimePressed()
{
	m_media_player->pause();
}

void QVideoPlayerWdgt::onSliderTimeMoved( int value )
{
	if( m_media_player->state() == QMediaPlayer::StoppedState || m_media_player->state() == QMediaPlayer::PausedState )
	{
		m_media_player->setPosition( value * 1000 );
		m_media_player->pause();
	}
	else
	{
		m_media_player->setPosition( value * 1000 );
	}
}
	

void QVideoPlayerWdgt::onSliderTimeReleased()
{
	if(m_is_media_playing)
	{
		m_media_player->play();
	}
}

void QVideoPlayerWdgt::onSliderVolumeValueChanged( int value )
{
	m_media_volume = value;
	m_media_player->setVolume(m_media_volume);

	if( value == 0 )
	{
		m_btn_volume->setIcon( QIcon(":/res/no_volume.png") );
	}
	else
	{
		m_btn_volume->setIcon( QIcon(":/res/volume.png") );
	}
}

void QVideoPlayerWdgt::onMediaPositionChanged( qint64 position )
{
	qint64 pos_secs = std::round( position / 1000.0 );
	m_slider_time->setValue(pos_secs);
	QTime current_time( ( pos_secs / 3600 ) % 60, ( pos_secs / 60 ) % 60, pos_secs % 60, ( pos_secs * 1000 ) % 1000 );
	m_lbl_current_time->setText( current_time.toString(m_time_format) );
}

void QVideoPlayerWdgt::onMediaDurationChanged( qint64 duration )
{
	m_media_duration = duration / 1000;

	if( m_media_duration >= 3600 )
	{
		m_media_forward_step = 300;		// 5 min
	}
	else if ( m_media_duration >= 1800 )
	{
		m_media_forward_step = 150;		// 2.5 min
	}
	else if ( m_media_duration >= 900 )
	{
		m_media_forward_step = 75;		// 1.25 min
	}
	else if ( m_media_duration >= 120 )
	{
		m_media_forward_step = 60;		// 1 min
	}
	else
	{
		m_media_forward_step = 5;		// 5 sec
	}

	QTime current_time( 0, 0 );
	QTime duration_time( ( m_media_duration / 3600 ) % 60, ( m_media_duration / 60 ) % 60, m_media_duration % 60, ( m_media_duration * 1000 ) % 1000 );
	if( m_media_duration > 3600 )
	{
		m_time_format = "hh:mm:ss";
	}
	else
	{
		m_time_format = "mm:ss";
	}
	m_lbl_current_time->setText( current_time.toString(m_time_format) );
	m_lbl_total_time->setText( duration_time.toString(m_time_format) );

	m_slider_time->setMaximum(m_media_duration);
}

void QVideoPlayerWdgt::onMediaStatusChanged( QMediaPlayer::MediaStatus status )
{
	if( status == QMediaPlayer::EndOfMedia )
	{
		onBtnStopClicked();
	}
}
