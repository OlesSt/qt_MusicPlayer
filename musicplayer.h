#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QAudioOutput>

namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer();

    void stateChanged(QMediaPlayer::PlaybackState state);
    void positionChanged(qint64 position);

private slots:
    void buttonPlay();
    void buttonPause();
    void buttonStop();

    void buttonMute();
    void sliderPlayMove(int position);
    void sliderVolumeMove(int position);

    void fileOpen();
    void fileExit();

private:
    Ui::MusicPlayer *ui;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
    bool isMute;
    QString filename;

};

#endif // MUSICPLAYER_H
