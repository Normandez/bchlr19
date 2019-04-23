#include "QVideoPlayerWdgt.h"

QVideoPlayerWdgt::QVideoPlayerWdgt( QWidget* parent /*= nullptr*/ )
	: QWidget(parent)
{
	m_video_wdgt = new QVideoWidget();
	m_media_player = new QMediaPlayer(this);
	m_media_player->setVideoOutput(m_video_wdgt);
	m_video_wdgt->setFixedSize( QSize( 632, 525 ) );

	QHBoxLayout* time_lyt = new QHBoxLayout();
	m_slider_time = new QSlider(Qt::Horizontal);
	m_lbl_total_time = new QLabel("00:00");
	QLabel* lbl_time_sep = new QLabel("/");
	m_lbl_current_time = new QLabel("00:00");
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
	m_slider_volume = new QSlider(Qt::Horizontal);
	m_slider_volume->setFixedWidth(100);
	player_control_lyt->addWidget(m_btn_stop);
	player_control_lyt->addWidget(m_btn_backward);
	player_control_lyt->addWidget(m_btn_play_pause);
	player_control_lyt->addWidget(m_btn_forward);
	player_control_lyt->addWidget(m_btn_volume);
	player_control_lyt->addWidget(m_slider_volume);
	player_control_lyt->addSpacerItem( new QSpacerItem( 20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum ) );

	m_no_source_wdgt = new QWidget();
	QVBoxLayout* no_source_wdgt_lyt = new QVBoxLayout();
	QLabel* no_source_lbl = new QLabel();
	m_no_source_wdgt->setStyleSheet("background-color:#a0a0a0");
	no_source_lbl->setPixmap( QPixmap(":/res/no_source.png") );
	m_no_source_wdgt->setFixedSize( QSize( 632, 525 ) );
	no_source_wdgt_lyt->addWidget(no_source_lbl);
	no_source_wdgt_lyt->setAlignment( no_source_lbl, Qt::AlignCenter );
	m_no_source_wdgt->setLayout(no_source_wdgt_lyt);
	m_no_source_wdgt->setVisible(false);

	QVBoxLayout* common_lyt = new QVBoxLayout();
	common_lyt->addWidget(m_video_wdgt);
	common_lyt->addLayout(time_lyt);
	common_lyt->addLayout(player_control_lyt);
	common_lyt->addSpacerItem( new QSpacerItem( 20, 40, QSizePolicy::Maximum, QSizePolicy::Expanding ) );
	this->setLayout(common_lyt);

	DisableUi();
}

QVideoPlayerWdgt::~QVideoPlayerWdgt()
{

}

void QVideoPlayerWdgt::EnableUi()
{

}

void QVideoPlayerWdgt::DisableUi()
{
	this->layout()->replaceWidget( m_video_wdgt, m_no_source_wdgt );
	m_no_source_wdgt->setVisible(true);

	m_slider_time->setEnabled(false);
	m_slider_volume->setEnabled(false);
	m_btn_stop->setEnabled(false);
	m_btn_backward->setEnabled(false);
	m_btn_play_pause->setEnabled(false);
	m_btn_forward->setEnabled(false);
	m_btn_volume->setEnabled(false);


}
