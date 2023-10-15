#include "musicplayer.h"
#include "ui_musicplayer.h"

#include <QTime>
#include <QFileDialog>
#include <QFileInfo>

MusicPlayer::MusicPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);

    ui->horizontalVolumeSlider->setMinimum(0);
    ui->horizontalVolumeSlider->setMaximum(100);
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
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(fileOpen()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(fileExit()));
    connect(ui->horizontalVolumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderVolumeMove(int)));
    connect(ui->horizontalVolumeSlider, &QSlider::valueChanged, this, &MusicPlayer::sliderVolumeMove);
    connect(ui->horizontalPlaySlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderPlayMove(int)));

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
    if (state == QMediaPlayer::PlayingState)
    {
        ui->pushPlay->setEnabled(true);
        ui->pushPause->setEnabled(true);
        ui->pushStop->setEnabled(true);
    }
    else if (state == QMediaPlayer::PausedState)
    {
        ui->pushPlay->setEnabled(true);
        ui->pushPause->setEnabled(false);
        ui->pushStop->setEnabled(true);
    }
    else if (state == QMediaPlayer::StoppedState)
    {
        ui->pushPlay->setEnabled(true);
        ui->pushPause->setEnabled(false);
        ui->pushStop->setEnabled(false);
    }
}

void MusicPlayer::positionChanged(qint64 position)
{
    auto duration = mediaPlayer->duration();
    if (ui->horizontalPlaySlider->maximum() != duration)
        ui->horizontalPlaySlider->setMaximum(mediaPlayer->duration());

    ui->horizontalPlaySlider->setValue(position);

    int seconds = position/1000 % 60;
    int minut = seconds/60 % 60;
    int hours = minut/60 % 24;

    QTime time (hours, minut, seconds);
    ui->labelTimer->setText(time.toString());
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

void MusicPlayer::sliderPlayMove(int position)   {mediaPlayer->setPosition(position);}
void MusicPlayer::sliderVolumeMove(int position) {audioOutput->setVolume(position);}

void MusicPlayer::fileOpen()
{
    filename = QFileDialog::getOpenFileName(this, "Select File");
    QFileInfo fileinfo(filename);
    ui->labelName->setText(fileinfo.fileName());

    mediaPlayer->setSource(QUrl::fromLocalFile(filename));
    ui->pushPlay->setEnabled(true);
    ui->pushPlay->click();
}

void MusicPlayer::fileExit() {this->close();}

