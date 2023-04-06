#include <QMap>
#include <QWidget>
#include <QPainter>
#include <QTimer>

typedef struct InfoMove {
    int tag;
    int x_start, y_start;
    int x_dest, y_dest;
} InfoMove;

typedef struct InfoEffect {
    int tag;
    int x, y;
} InfoEffect;

typedef struct Info {
    InfoMove *infomove;
    int lengthMove;
    InfoEffect *infoeffect;
    int lengthEffect;
} Info;

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent), refresh_counter(0) {
        setFixedSize(1280, 720);
        load_images();
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
        timer->start(100); // refresh every 100ms
    }
    
    void import_info(const Info& info) {
        this->info = info;
        refresh_counter = 0;
    }

private:
    QMap<int, QImage> images;
    Info info;
    int refresh_counter;
    QTimer *timer;

    void load_images() {
        for (int i = 1; i <= 100; i++) {
            QImage img(QString("../image/%1.png").arg(i));
            images.insert(i, img);
        }
    }

    void draw_image(QPainter& painter, int tag, int x, int y, int phase) {
        QImage img = images.value(tag);
        int size = img.width(); // assuming image is square
        int mesh_size = 32;
        int num_phases = 10;
        int dx = (x * mesh_size) + ((info.infomove->x_dest - info.infomove->x_start) * mesh_size * phase / num_phases);
        int dy = (y * mesh_size) + ((info.infomove->y_dest - info.infomove->y_start) * mesh_size * phase / num_phases);
        painter.drawImage(dx, dy, img);
    }

    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event)
        QPainter painter(this);
        painter.fillRect(rect(), Qt::black);
        for (int i = 0; i < info.lengthEffect; i++) {
            int tag = info.infoeffect[i].tag;
            int x = info.infoeffect[i].x;
            int y = info.infoeffect[i].y;
            draw_image(painter, tag, x, y, 0);
        }
        for (int i = 0; i < info.lengthMove; i++) {
            int tag = info.infomove[i].tag;
            int x_start = info.infomove[i].x_start;
            int y_start = info.infomove[i].y_start;
            int x_dest = info.infomove[i].x_dest;
            int y_dest = info.infomove[i].y_dest;
            if (refresh_counter == 0) {
                draw_image(painter, tag, x_start, y_start, 0);
            } else if (refresh_counter < 10) {
                int phase = refresh_counter;
                draw_image(painter, tag, x_start, y_start, phase);
            } else {
                draw_image(painter, tag, x_dest, y_dest, 0);
            }
        }
    }

private slots:
    void refresh() {
        refresh_counter++;
        if (refresh_counter >= 10) {
            timer->stop();
        }
        update();
    }
};
