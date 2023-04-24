#pragma once


#include "../macros.h"
#include <stdlib.h>
#include <QWidget>
#include <QMap>
#include <QPainter>
#include <QKeyEvent>

extern "C"{
    #include "draw.h"
}

//#define QT_GRAPHIC_TEST

#ifdef QT_GRAPHIC_TEST
typedef struct PlayerDash{
    int player_1_direction_key;
    int player_1_attack_key;
    int player_1_change_skill_key;
    int player_1_use_skill_key;
    
    int player_2_direction_key;
    int player_2_attack_key;
    int player_2_change_skill_key;
    int player_2_use_skill_key;
}PlayerDash;
#else
#include "../processor/processor.h"

void anime_repack(AnimePack* anime_pack, int anime_pack_size, InfoEffect* infoEffect, int* lengthEffect, InfoMove* infoMove, int* lengthMove);
#endif




class MyWidget : public QWidget {
    Q_OBJECT

public:
    MyWidget(QWidget *parent = 0);
    void import_image();
    void import_info(Info info);
    void refresh();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QMap<int, QImage> m_images;
    Info m_info;
    int m_counter;
    PlayerDash m_playerdash;
    int m_map[22][40];
};

