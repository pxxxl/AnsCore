#include "qt_draw.h"

#ifdef QT_GRAPHIC_TEST
PlayerDash player_dash;
#else
extern "C"{
    extern PlayerDash player_dash;
}


void anime_repack(AnimePack* anime_pack, int anime_pack_size, InfoEffect* infoEffect, int* lengthEffect, InfoMove* infoMove, int* lengthMove){
    *lengthEffect = 0;
    *lengthMove = 0;
    for(int i = 0; i < anime_pack_size; i++){
        if(anime_pack[i].pack_type == ANIME_PACK_TYPE_EFFECT_INFO){
            int j = *lengthEffect;
            infoEffect[j].tag = anime_pack[i].tag;
            infoEffect[j].x = anime_pack[i].x;
            infoEffect[j].y = anime_pack[i].y;
            (*lengthEffect)++;
        }else if(anime_pack[i].pack_type == ANIME_PACK_TYPE_MOVE_INFO){
            int j = *lengthMove;
            infoMove[j].tag = anime_pack[i].tag;
            infoMove[j].x_start = anime_pack[i].x;
            infoMove[j].y_start = anime_pack[i].y;
            infoMove[j].x_dest = anime_pack[i].des_x;
            infoMove[j].y_dest = anime_pack[i].des_y;
            (*lengthMove)++;
        }
    }
}
#endif


MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(640, 360);
    m_counter = 0;
    import_image();
}

void MyWidget::import_image()
{
    for (int i = 100; i <= 999; i++) {
        QString filename = QString("D:/Programming/CPrograms/AnsCore/image/%1.png").arg(i);
        QImage image(filename);
        if(image.isNull()) {
            continue;
        }else{
            m_images.insert(i, image);
        }
    }
}

void MyWidget::import_info(Info info)
{
    m_info = info;
    m_counter = 0;
}

void MyWidget::refresh()
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    update();
    m_counter++;
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (int i = 0; i < m_info.lengthEffect; i++) {
        int tag = m_info.infoeffect[i].tag;
        int x = m_info.infoeffect[i].x;
        int y = m_info.infoeffect[i].y;
        if (m_images.contains(tag)) {
            QImage image = m_images.value(tag);
            painter.drawImage(x * 16, y * 16, image);
        }
    }
    for (int i = 0; i < m_info.lengthMove; i++) {
        int tag = m_info.infomove[i].tag;
        int x_start = m_info.infomove[i].x_start;
        int y_start = m_info.infomove[i].y_start;
        int x_dest = m_info.infomove[i].x_dest;
        int y_dest = m_info.infomove[i].y_dest;
        if (m_images.contains(tag)) {
            QImage image = m_images.value(tag);
            int x = x_start * 16 + (x_dest - x_start) * m_counter *2;
            int y = y_start * 16 + (y_dest - y_start) * m_counter *2;
            painter.drawImage(x, y, image);
        }
    }
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)player_dash.player_1_direction_key = UP;
    if(event->key() == Qt::Key_S)player_dash.player_1_direction_key = DOWN;
    if(event->key() == Qt::Key_A)player_dash.player_1_direction_key = LEFT;
    if(event->key() == Qt::Key_D)player_dash.player_1_direction_key = RIGHT;
    if(event->key() == Qt::Key_Q)player_dash.player_1_use_skill_key = TRUE;
    if(event->key() == Qt::Key_E)player_dash.player_1_change_skill_key = LEFT;
    if(event->key() == Qt::Key_T)player_dash.player_1_change_skill_key = RIGHT;
    if(event->key() == Qt::Key_R)player_dash.player_1_attack_key = TRUE;
    if(event->key() == Qt::Key_U)player_dash.player_2_direction_key = UP;
    if(event->key() == Qt::Key_J)player_dash.player_2_direction_key = DOWN;
    if(event->key() == Qt::Key_H)player_dash.player_2_direction_key = LEFT;
    if(event->key() == Qt::Key_K)player_dash.player_2_direction_key = RIGHT;
    if(event->key() == Qt::Key_Y)player_dash.player_2_use_skill_key = TRUE;
    if(event->key() == Qt::Key_I)player_dash.player_2_change_skill_key = LEFT;
    if(event->key() == Qt::Key_P)player_dash.player_2_change_skill_key = RIGHT;
    if(event->key() == Qt::Key_O)player_dash.player_2_attack_key = TRUE;
}
extern MyWidget* widget;

Info* init_draw(){
    Info* p = (Info*)malloc(sizeof(Info));
    p->infoeffect = NULL;
    p->infomove = NULL;
    p->lengthEffect = 0;
    p->lengthMove = 0;
    return p;
}

void renew_backgrounds(int **obstacles, int length){}
void renew_status(Player players[2]){}

void import_info(Info *info, InfoMove *infomove, int lengthMove, InfoEffect *infoeffect, int lengthEffect){
    info->lengthEffect = lengthEffect;
    info->lengthMove = lengthMove;
    info->infoeffect = infoeffect;
    info->infomove = infomove;
    widget->import_info(*info);
}
void refresh(Info info, int cnt){
    widget->refresh();
}

void draw_move(InfoMove infoMove){}
void draw_effect(InfoEffect infoEffect){}
void draw_image(int image_id, int x, int y){}
void clear_screen(){}
