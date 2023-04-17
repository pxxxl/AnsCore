#include <QWidget>
#include <QMap>
#include <QPainter>
#include <QKeyEvent>
#include "../processor.h"
#include "../anime.h"
#include "../player_dash.h"
#include "../macros.h"
#include "../object.h"
#include "../VGA_engine.h"

extern PlayerDash player_dash;

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

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(1280, 720);
    m_counter = 0;
    memset(m_map, 0, sizeof(m_map));
}

void MyWidget::import_image()
{
    for (int i = 1; i <= 999; i++) {
        QString filename = QString("../../image/%1.png").arg(i);
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
}

void MyWidget::refresh()
{
    m_counter++;
    if (m_counter >= 10) {
        m_counter = 0;
    }
    update();
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
            if (m_counter == 0) {
                painter.drawImage(x_start * 16, y_start * 16, image);
            } else if (m_counter <= 9) {
                int x = x_start + (x_dest - x_start) * m_counter / 10;
                int y = y_start + (y_dest - y_start) * m_counter / 10;
                painter.drawImage(x * 16, y * 16, image);
            }
        }
    }
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_W:
            player_dash.player_1_direction_key = UP;
            break;
        case Qt::Key_S:
            player_dash.player_1_direction_key = DOWN;
            break;
        case Qt::Key_A:
            player_dash.player_1_direction_key = LEFT;
            break;
        case Qt::Key_D:
            player_dash.player_1_direction_key = RIGHT;
            break;
        case Qt::Key_Q:
            player_dash.player_1_use_skill_key = TRUE;
            break;
        case Qt::Key_E:
            player_dash.player_1_change_skill_key = LEFT;
            break;
        case Qt::Key_T:
            player_dash.player_1_change_skill_key = RIGHT;
            break;
        case Qt::Key_R:
            player_dash.player_1_attack_key = TRUE;
            break;
        case Qt::Key_U:
            player_dash.player_2_direction_key = UP;
            break;
        case Qt::Key_J: 
            player_dash.player_2_direction_key = DOWN;
            break;
        case Qt::Key_H: 
            player_dash.player_2_direction_key = LEFT;
            break;
        case Qt::Key_K:
            player_dash.player_2_direction_key = RIGHT;
            break;
        case Qt::Key_Y:
            player_dash.player_2_use_skill_key = TRUE;
            break;
        case Qt::Key_I:
            player_dash.player_2_change_skill_key = LEFT;
            break;
        case Qt::Key_O:
            player_dash.player_2_change_skill_key = RIGHT;
            break;
        case Qt::Key_P:
            player_dash.player_2_attack_key = TRUE;
            break;
        default:
            break;
    }
}