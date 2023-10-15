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

private:
    Ui::MusicPlayer *ui;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;

};

#endif // MUSICPLAYER_H
