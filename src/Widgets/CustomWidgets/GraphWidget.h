#ifndef QCONFIGURABLEDASHBOARD_GRAPHWIDGET_H
#define QCONFIGURABLEDASHBOARD_GRAPHWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include "../BaseWidget.h"
#include "../../../lib/QCustomPlot/qcustomplot.h"

namespace QCD {

    class GraphWidget : public BaseWidget {
    Q_OBJECT
    public:
        explicit GraphWidget(const QString &a_title = "");

        void listen(const std::string &a_key, const QString &a_name = "", const QString &a_color = "");

        bool setUpdateRateScale(int a_scale) override;

    private slots:

        void mouseMoveSignal(QMouseEvent *a_event);

        void mousePressSignal(QMouseEvent *a_event);

        void mouseReleaseSignal(QMouseEvent *a_event);

        void beforeReplot();

        void onThemeChange();

    private:
        struct Series {
            std::string key;
            QString name;
            QString color;
            QVector<double> values;
        };

        void onUpdate(QCD::WidgetFocus a_focus) override;

        void updateSeriesData();

        void redrawPlot();

        void updateSeriesTimes();

        void onRun() override;

        QColor getThemeData(const QString &a_attribute);

        QVBoxLayout *m_layout;
        QLabel *m_title;
        QCustomPlot *m_plot;
        std::vector<Series> m_seriesList;
        QVector<double> m_xValues;

        double m_lastTime = -1;
        int m_updateRateScale = 1;
        int m_updateCounter = 0;

        QPointF dragLegendOrigin;
        bool m_clicked = false;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_GRAPHWIDGET_H
