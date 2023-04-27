#pragma once

#include "qboxlayout.h"
#include "qlabel.h"
#include "qtextformat.h"
#include "qwidget.h"
#include <QVector>
#include <stdlib.h>
#include <QWidget>
#include <QMap>
#include <QPainter>
#include <QKeyEvent>
#include <QTextBlock>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "QPixmap"

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
    friend class TWidget;
public:
    MyWidget(QWidget *parent = 0);
    void import_image();
    void key_step();
    void import_info(Info info);
    void refresh();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QMap<int, QImage> m_images;
    Info m_info;
    int m_counter;
    PlayerDash m_playerdash;
    int m_map[22][40];
    int keyPressingA = 0;
    int keyPressingB = 0;
    QVector<int> key_queueA;
    QVector<int> key_queueB;
};

class TWidget : public QWidget {
    Q_OBJECT
    public:
        TWidget(QWidget *parent = 0){
            m_widget = new MyWidget(parent);
            m_textview_1 = new QLabel();
            m_textview_2 = new QLabel();
            m_hboxlayout = new QHBoxLayout();
            m_vboxlayout = new QVBoxLayout();
            m_player1_skills = new QHBoxLayout();
            m_player2_skills = new QHBoxLayout();
            m_player1_skill_label = new QLabel("Player1 Skills: ");
            m_player2_skill_label = new QLabel("Player2 Skills: ");
            m_player1_skills->addWidget(m_player1_skill_label);
            m_player2_skills->addWidget(m_player2_skill_label);
            
            for(int i = 0; i < 6; i++){
                m_player1_skill_pic[i] = new QLabel();
                m_player2_skill_pic[i] = new QLabel();
                m_player1_skills->addWidget(m_player1_skill_pic[i]);
                m_player2_skills->addWidget(m_player2_skill_pic[i]);
            }
            
            m_player1_skills -> addWidget(m_textview_1);
            m_player1_skills -> addWidget(m_textview_2);
            m_player2_skills -> addWidget(m_textview_1);
            m_player2_skills -> addWidget(m_textview_2);

            m_hboxlayout->addWidget(m_textview_1);
            m_hboxlayout->addWidget(m_textview_2);
            m_vboxlayout->addWidget(m_widget);
            m_vboxlayout->addLayout(m_hboxlayout);
            m_vboxlayout->addLayout(m_player1_skills);
            m_vboxlayout->addLayout(m_player2_skills);
            setLayout(m_vboxlayout);
        }
        void import_image(){
            m_widget->import_image();
        }
        void key_step(){
            m_widget->key_step();
        }
        void import_info(Info info){
            m_widget->import_info(info);
        }
        void refresh(){
            m_widget->refresh();
        }
        void refresh_hp(int hp1, int hp2){
            m_textview_1->setText(QString("Player1 HP: %1").arg(hp1));
            m_textview_2->setText(QString("Player2 HP: %1").arg(hp2));
        }
        void refresh_skill(Player players[2]){
            for(int i = 0; i < 6; i++){
                if(i < players[0].skillNum){
                    QString str = QString::number(players[0].skills[i]);
                    if(i == players[0].selectSkill){
                        str.append(QString("_Chosen"));
                    }
                    m_player1_skill_pic[i]->setText(str);
                }else{
                    m_player1_skill_pic[i]->setText("None");
                }
                if(i < players[1].skillNum){
                    QString str = QString::number(players[1].skills[i]);
                    if(i == players[1].selectSkill){
                        str.append(QString("_Chosen"));
                    }
                    m_player2_skill_pic[i]->setText(str);
                }else{
                    m_player2_skill_pic[i]->setText("None");
                }
            }
        }
        void refresh_player(Player players[2]){
            refresh_hp(players[0].hp, players[1].hp);
            refresh_skill(players);
        }
        unsigned get_rand_0_to_99(){
            return rand_key % 100;
        }
    protected:
        void paintEvent(QPaintEvent *event){
            m_widget->paintEvent(event);
        }
        void keyPressEvent(QKeyEvent *event){
            rand_key += event->key() * event->key();
            m_widget->keyPressEvent(event);
        }
        void keyReleaseEvent(QKeyEvent *event){
            m_widget->keyReleaseEvent(event);
        }
    private:
        MyWidget* m_widget;
        QLabel* m_textview_1;
        QLabel* m_textview_2;
        QLabel* m_player1_skill_pic[6];
        QLabel* m_player2_skill_pic[6];
        QHBoxLayout* m_hboxlayout;
        QHBoxLayout* m_player1_skills;
        QHBoxLayout* m_player2_skills;
        QHBoxLayout* m_player_skills;
        QVBoxLayout* m_vboxlayout;
        QLabel* m_player1_skill_label;
        QLabel* m_player2_skill_label;
        unsigned rand_key;
};