#include <UtilFunctions.h>
#include <GraphWidget.h>

namespace QCD {
    GraphWidget::GraphWidget(const QString &a_title, const QString &a_yAxisTitle) {

        m_title = new QLabel(a_title);
        registerTheme(m_title, TITLE_TEXT_COLOR_CLASS);

        m_layout = new QVBoxLayout();
        m_layout->setMargin(10);
        setLayout(m_layout);

        m_plot = new QCustomPlot(this);
        m_layout->addWidget(m_title, 0, Qt::AlignHCenter);
        m_title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        m_layout->addWidget(m_plot);
        m_plot->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        // give the axes some labels:
        m_plot->xAxis->setLabel("Time (s)");
        m_plot->yAxis->setLabel(a_yAxisTitle);
        // set axes ranges, so we see all data:
        m_plot->xAxis->setRange(-20, 1);
        m_plot->yAxis->setRange(-10, 10);

        m_plot->setInteraction(QCP::iRangeDrag, true);
        m_plot->setInteraction(QCP::iRangeZoom, true);

        m_plot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);

        connect(m_plot, SIGNAL(mouseMove(QMouseEvent * )), this, SLOT(mouseMoveSignal(QMouseEvent * )));
        connect(m_plot, SIGNAL(mousePress(QMouseEvent * )), this, SLOT(mousePressSignal(QMouseEvent * )));
        connect(m_plot, SIGNAL(mouseRelease(QMouseEvent * )), this, SLOT(mouseReleaseSignal(QMouseEvent * )));
        connect(m_plot, SIGNAL(beforeReplot()), this, SLOT(beforeReplot()));

        m_plot->legend->setVisible(true);
//        registerCallback(THEME_CHANGED_CALLBACK, QCD_CALLBACK(this, onUpdate));
    }

    void GraphWidget::onUpdate(QCD::WidgetFocus a_focus) {
        updateSeriesData();
        if (isInFocus(a_focus)) {
            m_updateCounter--;
            if (m_updateCounter <= 0 || a_focus == WidgetFocus::ON_IN_FOCUS) {
                redrawPlot();
                m_updateCounter = m_updateRateScale;
            }
        }
    }

    void GraphWidget::listen(const std::string &a_key, const QString &a_name, const QString &a_color) {
        m_seriesList.push_back({a_key, a_name, a_color});
        auto *graph = m_plot->addGraph();
        graph->setName(a_name);
        graph->setPen(QPen(QColor(a_color)));
    }

    void GraphWidget::updateSeriesData() {
        // Get the data we need
        double time = getEpochTime();
        // Add new x value to list
        m_xValues.push_back(time - m_lastTime);
        updateSeriesTimes();
        // Iterate though the series list
        for (auto &series: m_seriesList) {
            // Check if the key is valid
            auto &value = m_inputData[series.key];
            if (value.is_number()) {
                series.values.push_back(value.get<double>());
            } else if (!series.values.empty()) {
                series.values.push_back(series.values[series.values.size() - 1]);
            } else {
                series.values.push_back(0);
            }
        }
        m_lastTime = time;
    }

    void GraphWidget::redrawPlot() {
        for (int i = 0; i < m_seriesList.size(); i++) {
            m_plot->graph(i)->setData(m_xValues, m_seriesList[i].values, true);
        }
        m_plot->replot();
    }

    void GraphWidget::updateSeriesTimes() {
        double dt = m_xValues[m_xValues.size() - 1];
        for (auto &el: m_xValues) {
            el -= dt;
        }
        for(int i = 0; i < m_xValues.size(); i++) {
            if(m_xValues[i] < -m_maxTime) {
                m_xValues.remove(i);
                for(auto &el : m_seriesList) {
                    el.values.remove(i);
                }
            }
        }
    }

    bool GraphWidget::setUpdateRateScale(int a_scale) {
        if (a_scale >= 1) {
            m_updateRateScale = a_scale;
            m_updateCounter = m_updateRateScale;
            return true;
        }
        return false;
    }

    void GraphWidget::mouseMoveSignal(QMouseEvent *a_event) {
        if (m_clicked) {
            QRectF rect = m_plot->axisRect()->insetLayout()->insetRect(0);
            // since insetRect is in axisRect coordinates (0..1), we transform the mouse position:
            QPointF mousePoint((a_event->pos().x() - m_plot->axisRect()->left()) / (double) m_plot->axisRect()->width(),
                               (a_event->pos().y() - m_plot->axisRect()->top()) /
                               (double) m_plot->axisRect()->height());
            rect.moveTopLeft(mousePoint - dragLegendOrigin);
            // Clip pos
            rect.setX(std::min(1.0, std::max(0.0, rect.x())));
            rect.setY(std::min(1.0, std::max(0.0, rect.y())));
            m_plot->axisRect()->insetLayout()->setInsetRect(0, rect);
            m_plot->replot();
        }
    }

    void GraphWidget::mousePressSignal(QMouseEvent *a_event) {
        int x = a_event->x();
        int y = a_event->y();
        int xx = m_plot->legend->rect().x();
        int yy = m_plot->legend->rect().y();
        int w = m_plot->legend->rect().width();
        int h = m_plot->legend->rect().height();
        if (abs(xx - x) < w && abs(yy - y) < h) {
            m_plot->setInteraction(QCP::iRangeDrag, false);
            m_plot->setInteraction(QCP::iRangeZoom, false);
            m_clicked = true;
            // since insetRect is in axisRect coordinates (0..1), we transform the mouse position:
            QPointF mousePoint((a_event->pos().x() - m_plot->axisRect()->left()) / (double) m_plot->axisRect()->width(),
                               (a_event->pos().y() - m_plot->axisRect()->top()) /
                               (double) m_plot->axisRect()->height());
            dragLegendOrigin = mousePoint - m_plot->axisRect()->insetLayout()->insetRect(0).topLeft();
        }
    }

    void GraphWidget::mouseReleaseSignal(QMouseEvent *a_event) {
        m_clicked = false;
        m_plot->setInteraction(QCP::iRangeDrag, true);
        m_plot->setInteraction(QCP::iRangeZoom, true);
    }

    void GraphWidget::beforeReplot() {
        m_plot->legend->setMaximumSize(m_plot->legend->minimumOuterSizeHint());
    }

    void GraphWidget::onThemeChange(const Json &a_data) {
        m_plot->setBackground(QBrush(getThemeData(WIDGET_BACKGROUND_CLASS)));
        m_plot->legend->setTextColor(getThemeData(TEXT_COLOR_CLASS));
        m_plot->legend->setBrush(getThemeData(CONTAINER_BACKGROUND_CLASS));

        m_plot->xAxis->grid()->setZeroLinePen(getThemeData(HIGHLIGHT_COLOR_CLASS));
        m_plot->xAxis->grid()->setPen(getThemeData(HIGHLIGHT_COLOR_CLASS));
        m_plot->xAxis->setTickPen(QPen(getThemeData(TEXT_COLOR_CLASS)));
        m_plot->xAxis->setTickLabelColor(getThemeData(TEXT_COLOR_CLASS));
        m_plot->xAxis->setLabelColor(getThemeData(TEXT_COLOR_CLASS));
        m_plot->xAxis->setSubTickPen(getThemeData(TEXT_COLOR_CLASS));
        m_plot->xAxis->setBasePen(getThemeData(TEXT_COLOR_CLASS));
        m_plot->yAxis->grid()->setZeroLinePen(getThemeData(HIGHLIGHT_COLOR_CLASS));
        m_plot->yAxis->grid()->setPen(getThemeData(HIGHLIGHT_COLOR_CLASS));
        m_plot->yAxis->setTickPen(QPen(getThemeData(TEXT_COLOR_CLASS)));
        m_plot->yAxis->setTickLabelColor(getThemeData(TEXT_COLOR_CLASS));
        m_plot->yAxis->setLabelColor(getThemeData(TEXT_COLOR_CLASS));
        m_plot->yAxis->setSubTickPen(getThemeData(TEXT_COLOR_CLASS));
        m_plot->yAxis->setBasePen(getThemeData(TEXT_COLOR_CLASS));
    }

    void GraphWidget::onRun() {
        registerCallback(THEME_CHANGED_CALLBACK, QCD_CALLBACK(this, onThemeChange));
    }

    QColor GraphWidget::getThemeData(const QString &a_attribute) {
        std::string str = m_themeData[getTheme()][a_attribute.toStdString()].get<std::string>();
        str = str.substr(str.find("rgb(") + 4);
        std::string r, g, b;
        r = str.substr(0, str.find(','));
        g = str.substr(0, str.find(',', str.find(',')));
        b = str.substr(0, str.find(',', str.find(',', str.find(','))));
        return {std::stoi(r), std::stoi(g), std::stoi(b)};
    }

    void GraphWidget::reset(const Json &value) {
        m_xValues.clear();
        for (auto &el: m_seriesList) {
            el.values.clear();
        }
    }
} // QCD