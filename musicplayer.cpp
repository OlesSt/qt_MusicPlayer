#include "musicplayer.h"
#include "ui_musicplayer.h"

MusicPlayer::MusicPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);
    ui->horizontalVolumeSlider->setValue(80);
    isMute = false;

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

void MusicPlayer::buttonPlay()  {mediaPlayer->play();}
void MusicPlayer::buttonPause() {mediaPlayer->pause();}
void MusicPlayer::buttonStop()  {mediaPlayer->stop();}
void MusicPlayer::buttonMute()
{
    if (isMute)
    {
        audioOutput->setMuted(true);
        ui->pushMute->setText("Muted");
        isMute = false;
    }
    else
    {
        audioOutput->setMuted(false);
        ui->pushMute->setText("Mute");
        isMute = true;
    }
}

void MusicPlayer::sliderPlayMove(float position)   {mediaPlayer->setPosition(position);}
void MusicPlayer::sliderVolumeMove(float position) {audioOutput->setVolume(position);}

void MusicPlayer::fileOpen()
{

}

void MusicPlayer::fileExit()
{

}
