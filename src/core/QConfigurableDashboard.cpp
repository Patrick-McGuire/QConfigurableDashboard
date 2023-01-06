#include <QWidgetAction>
#include <iostream>
#include <QConfigurableDashboard.h>
#include "QMenu"
#include <QCD.h>
#include <QStyleFactory>

// @todo remove macro
#define RATE_TO_INTERVAL(rateV) ((int) ((1.0 / rateV) * 1000))

namespace QCD {
    QConfigurableDashboard::QConfigurableDashboard(int a_argc, char **a_argv, double a_rate) : QObject(), CoreObject(this) {
        m_desiredRate = a_rate;
        m_currentRate = a_rate;
        // Save these because why not
        m_argv = a_argv;
        m_argc = a_argc;
        // Construct core objects
        m_qApplication = new QApplication(m_argc, m_argv);
        QApplication::setStyle(QStyleFactory::create("Fusion"));

        m_mainWindow = new QMainWindow();
        m_window = new QWidget();
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        m_window->setLayout(m_layout);
        m_mainWindow->setCentralWidget(m_window);
        m_mainWindow->show();
        m_window->show();
        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGUI()));

        addMenu("Settings");
        addMenu("Tools");
        addMenuAction("Enable Dragging", "Tools")->setData(true);
        addMenuAction("Disable Dragging", "Tools")->setData(false);
        connect(findMenu("Tools"), SIGNAL(triggered(QAction * )), this, SLOT(updateDragging(QAction * )));
        addMenu("Theme");
        for (const auto &el: m_themeData.items()) {
            addMenuAction(el.key().c_str(), "Theme");
            registerCallback(std::string(MENU_BASE_CALLBACK) + el.key(), QCD_CALLBACK(this, updateThemeCallback));
        }

        // Leave null for now;
        m_centralWidget = nullptr;
    }

    QConfigurableDashboard::~QConfigurableDashboard() {
        delete m_qApplication;
    }

    int QConfigurableDashboard::run() {
        qDebug("Initializing GUI");

        // Start all the widgets
        m_centralWidget->run();
        // Start all the modules
        for (auto &module: m_modules) {
            module->run();
        }
        qDebug("widgets initialized");

        updateTheme("Dark");
        qDebug("Theme set");

        // Start the periodic updating of widgets
        m_timer->start(RATE_TO_INTERVAL(m_currentRate));
        qDebug("Update loop started");

        // Runs QT main loop
        qDebug("Starting GUI");
        int out = QApplication::exec();
        qDebug("GUI Closed");

        // end all the modules
        qDebug("Ending modules");
        for (auto &module: m_modules) {
            module->finish();
        }

        qDebug("Done!");
        return out;
    }

    bool QConfigurableDashboard::setCentralWidget(Widget *a_widget, QFlags<Qt::AlignmentFlag> a_alignment) {
        if (a_widget != nullptr) {
            m_layout->removeWidget(m_centralWidget);
            delete m_centralWidget;
            m_layout->addWidget(a_widget, 0, a_alignment);
            m_centralWidget = a_widget;
            m_centralWidget->disableFloating();
            return true;
        }
        return false;
    }

    bool QConfigurableDashboard::addModule(Module *a_baseModule) {
        if (a_baseModule != nullptr && std::find(m_modules.begin(), m_modules.end(), a_baseModule) == m_modules.end()) {
            m_modules.push_back(a_baseModule);
            return true;
        }
        return false;
    }

    void QConfigurableDashboard::updateGUI() {
        // Track tick time
        double time = getEpochTime();
        double tickRate = 1 / (time - m_lastTime);
        m_inputData[TICK_TIME_KEY] = time - m_lastTime;
        m_inputData[TICK_RATE_KEY] = tickRate;
        if (m_times.size() > 100) m_times.pop_front();
        m_times.push_back(tickRate);
        m_lastTime = time;
        // Calc stuff todo: abstract to function
        if (m_autoScale) {
            double av;
            for (auto el: m_times) {
                av += el;
            }
            av /= (double) m_times.size();
            if (av - m_currentRate < m_currentRate * -0.075) {
                m_currentRate -= .1;
                m_timer->setInterval(RATE_TO_INTERVAL(m_currentRate));
            } else if (av - m_desiredRate < m_currentRate * -0.075 && m_currentRate < m_desiredRate) {
                m_currentRate += .2;
                m_timer->setInterval(RATE_TO_INTERVAL(m_currentRate));
            }
            m_inputData[TICK_DESIRED_RATE_KEY] = m_currentRate;
        }
        // Update all modules
        for (auto &module: m_modules) {
            module->runUpdate(false);
        }
        // Update all widgets
        m_centralWidget->runUpdate(m_updateAlways || m_mainWindow->isActiveWindow());
    }

    QMenu *QConfigurableDashboard::addMenu(const QString &a_name, const QString &a_parentName) {
        QMenu *newMenu;
        if (a_parentName == "none") {
            newMenu = m_mainWindow->menuBar()->addMenu(a_name);
        } else {
            newMenu = findMenu(a_parentName)->addMenu(a_name);
        }
        m_menus.push_back(newMenu);
        connect(newMenu, SIGNAL(triggered(QAction * )), this, SLOT(forwardEvent(QAction * )));
        return newMenu;
    }

    QAction *QConfigurableDashboard::addMenuAction(const QString &a_name, const QString &a_parentName) {
        if (a_parentName == "none") {
            auto *act = m_mainWindow->menuBar()->addAction(a_name);
            act->setData(QString(MENU_BASE_CALLBACK) + a_name);
            return act;
        }
        auto *act = findMenu(a_parentName)->addAction(a_name);
        act->setData(QString(MENU_BASE_CALLBACK) + a_name);
        return act;
    }

    QMenu *QConfigurableDashboard::findMenu(const QString &a_name) {
        for (auto &menu: m_menus) {
            if (menu->title() == a_name) {
                return menu;
            }
        }
        return nullptr;
    }


    void QConfigurableDashboard::updateThemeCallback(const Json &a_data) {
        if (a_data.is_string()) {
            std::string themeName = a_data.get<std::string>();
            themeName = themeName.substr(strlen(MENU_BASE_CALLBACK));
            updateTheme(themeName);
        }
    }

    void QConfigurableDashboard::updateTheme(const std::string &a_activeTheme) {
        setTheme(a_activeTheme);

        QString backgroundColor = getThemeDataString(QString(a_activeTheme.c_str()), CONTAINER_BACKGROUND_CLASS);
        QString highlightBackgroundColor = getThemeDataString(QString(a_activeTheme.c_str()), HIGHLIGHT_COLOR_CLASS);
        QString textColor = getThemeDataString(QString(a_activeTheme.c_str()), TITLE_TEXT_COLOR_CLASS);

        QString style;
        style += "QMenuBar, QMenuBar::item, QMenu, QMenu::item { " + backgroundColor + " ; " + textColor + ";}";
        style += "QMenuBar::item:selected, QMenu::item:selected { " + highlightBackgroundColor + ";}";
        style += "QTabBar, QTabBar::tab { " + backgroundColor + " ; " + textColor + ";}";
        style += "QTabBar::tab:selected, QTabBar::tab:hover { " + highlightBackgroundColor + ";}";
        for (const auto &el: m_themeData[a_activeTheme].items()) {
            style += getClassStylesheet(el.key().c_str(), getThemeDataString(QString(a_activeTheme.c_str()), el.key().c_str()));
        }
        m_mainWindow->setStyleSheet(style);
        triggerCallback(THEME_CHANGED_CALLBACK);
    }

    QString QConfigurableDashboard::getClassStylesheet(const QString &a_class, const QString &a_style) {
        return QString("*[") + THEME_PROPERTY + "~=\"" + a_class + "\"]{" + a_style + "}";
    }

    QString QConfigurableDashboard::getThemeDataString(const QString &a_themeName, const QString &a_attribute) {
        return m_themeData[a_themeName.toStdString()][a_attribute.toStdString()].get_ref<std::string &>().c_str();
    }

    void QConfigurableDashboard::updateDragging(QAction *a_action) {
        if (a_action->data().toBool()) {
            m_draggingEnabled = true;
        } else {
            m_draggingEnabled = false;
        }
    }

    void QConfigurableDashboard::setUpdateAlways(bool a_updateAlways) {
        m_updateAlways = a_updateAlways;
    }

    void QConfigurableDashboard::setAutoScale(bool a_autoScale) {
        m_autoScale = a_autoScale;
    }

    void QConfigurableDashboard::forwardEvent(QAction *a_action) {
        if (a_action->data().type() == QVariant::Type::String) {
            Json arg = a_action->data().toString().toStdString();
            triggerCallback(a_action->data().toString().toStdString(), arg);
        }
    }

    Widget *QConfigurableDashboard::getCentralWidget() {
        return m_centralWidget;
    }

}
