#include <QApplication>
#include "musicplayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MusicPlayer player;
    player.show();

    return a.exec();
}
