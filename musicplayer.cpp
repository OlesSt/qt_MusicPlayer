#include "musicplayer.h"
#include "ui_musicplayer.h"

MusicPlayer::MusicPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);
    ui->horizontalVolumeSlider->setValue(80);

    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(ui->horizontalVolumeSlider->value());

    connect(ui->pushPlay, SIGNAL(clicked(bool)), this, SLOT(buttonPlay()));
    connect(ui->pushPause, SIGNAL(clicked(bool)), this, SLOT(buttonPause()));
    connect(ui->pushStop, SIGNAL(clicked(bool)), this, SLOT(buttonStop()));
    connect(ui->pushMute, SIGNAL(clicked(bool)), this, SLOT(buttonMute()));

    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &MusicPlayer::stateChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicPlayer::positionChanged);



}

MusicPlayer::~MusicPlayer()
{
    delete mediaPlayer;
    delete audioOutput;
    delete ui;
}

void MusicPlayer::stateChanged(QMediaPlayer::PlaybackState state)
{

}

void MusicPlayer::positionChanged(qint64 position)
{

}

void MusicPlayer::buttonPlay()
{

}

void MusicPlayer::buttonPause()
{

}

void MusicPlayer::buttonStop()
{

}

void MusicPlayer::buttonMute()
{

}

void MusicPlayer::sliderPlayMove()
{

}

void MusicPlayer::sliderVolumeMove()
{

}

void MusicPlayer::fileOpen()
{

}

void MusicPlayer::fileExit()
{

}
