#include <QWidgetAction>
#include <iostream>
#include <QConfigurableDashboard.h>
#include "QMenu"
#include <QCD.h>
#include <QStyleFactory>

// @todo remove macro
#define RATE_TO_INTERVAL(rateV) ((int) ((1.0 / rateV) * 1000))

namespace QCD {
    AppManager *QConfigurableDashboard::m_appManager = nullptr;

    QConfigurableDashboard::QConfigurableDashboard(int a_argc, char **a_argv, double a_rate) {
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

        if(m_appManager == nullptr) {
            m_appManager = new AppManager(this);
            QCD::Widget::setAppManager(m_appManager);
            QCD::Module::setAppManager(m_appManager);
        } else {
            throw std::runtime_error("Please only construct 1 instance of QCD::ConfigurableDashboard");
        }

        addMenu("Settings");
        addMenu("Tools");
        addMenuAction("Enable Dragging", "Tools")->setData(true);
        addMenuAction("Disable Dragging", "Tools")->setData(false);
        connect(findMenu("Tools"), SIGNAL(triggered(QAction * )), this, SLOT(updateDragging(QAction * )));
        addMenu("Theme");
        for (const auto &el: m_appManager->getThemeData().items()) {
            addMenuAction(el.key().c_str(), "Theme")->setData(QString(el.key().c_str()));
        }
        connect(findMenu("Theme"), SIGNAL(triggered(QAction * )), this, SLOT(updateTheme(QAction * )));

        // Leave null for now;
        m_centralWidget = nullptr;
    }

    QConfigurableDashboard::~QConfigurableDashboard() {
        delete m_qApplication;
        delete m_appManager;
    }

    int QConfigurableDashboard::run() {
        qDebug("Initializing GUI");

        // Start all the widgets
        m_centralWidget->run();
        // Start all the modules
        for (auto &module: m_modules) {
            module->run();
        }
        qDebug("Widgets initialized");

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
        m_appManager->getInputData()[TICK_TIME_KEY] = time - m_lastTime;
        m_appManager->getInputData()[TICK_RATE_KEY] = tickRate;
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
            m_appManager->getInputData()[TICK_DESIRED_RATE_KEY] = m_currentRate;
        }
        // Update all modules
        for (auto &module: m_modules) {
            module->update();
        }
        // Update all widgets
        m_centralWidget->smartUpdate(m_updateAlways || m_mainWindow->isActiveWindow());
    }

    QMenu *QConfigurableDashboard::addMenu(const QString &a_name, const QString &a_parentName) {
        QMenu *newMenu;
        if (a_parentName == "none") {
            newMenu = m_mainWindow->menuBar()->addMenu(a_name);
        } else {
            newMenu = findMenu(a_parentName)->addMenu(a_name);
        }
        m_menus.push_back(newMenu);
        return newMenu;
    }

    QAction *QConfigurableDashboard::addMenuAction(const QString &a_name, const QString &a_parentName) {
        if (a_parentName == "none") {
            return m_mainWindow->menuBar()->addAction(a_name);
        }
        return findMenu(a_parentName)->addAction(a_name);
    }

    QMenu *QConfigurableDashboard::findMenu(const QString &a_name) {
        for (auto &menu: m_menus) {
            if (menu->title() == a_name) {
                return menu;
            }
        }
        return nullptr;
    }


    void QConfigurableDashboard::updateTheme(QAction *a_action) {
        updateTheme(a_action->data().toString());
    }

    void QConfigurableDashboard::updateTheme(const QString &a_activeTheme) {
        m_appManager->setTheme(a_activeTheme.toStdString());

        QString backgroundColor = getThemeData(a_activeTheme, CONTAINER_BACKGROUND_CLASS);
        QString highlightBackgroundColor = getThemeData(a_activeTheme, HIGHLIGHT_COLOR_CLASS);
        QString textColor = getThemeData(a_activeTheme, TITLE_TEXT_COLOR_CLASS);

        QString style;
        style += "QMenuBar, QMenuBar::item, QMenu, QMenu::item { " + backgroundColor + " ; " + textColor + ";}";
        style += "QMenuBar::item:selected, QMenu::item:selected { " + highlightBackgroundColor + ";}";
        style += "QTabBar, QTabBar::tab { " + backgroundColor + " ; " + textColor + ";}";
        style += "QTabBar::tab:selected, QTabBar::tab:hover { " + highlightBackgroundColor + ";}";
        for (const auto &el: m_appManager->getThemeData()[a_activeTheme.toStdString()].items()) {
            style += getClassStylesheet(el.key().c_str(), getThemeData(a_activeTheme, el.key().c_str()));
        }
        m_mainWindow->setStyleSheet(style);

        emit m_appManager->themeChanged();
    }

    QString QConfigurableDashboard::getClassStylesheet(const QString &a_class, const QString &a_style) {
        return QString("*[") + THEME_PROPERTY + "~=\"" + a_class + "\"]{" + a_style + "}";
    }

    QString QConfigurableDashboard::getThemeData(const QString &a_themeName, const QString &a_attribute) {
        return m_appManager->getThemeData()[a_themeName.toStdString()][a_attribute.toStdString()].get_ref<std::string &>().c_str();
    }

    void QConfigurableDashboard::updateDragging(QAction *a_action) {
        if (a_action->data().toBool()) {
            m_appManager->enableDragging();
        } else {
            m_appManager->disableDragging();
        }
    }

    void QConfigurableDashboard::setUpdateAlways(bool a_updateAlways) {
        m_updateAlways = a_updateAlways;
    }

    AppManager *QConfigurableDashboard::getAppManager() {
        return m_appManager;
    }

    void QConfigurableDashboard::setAutoScale(bool a_autoScale) {
        m_autoScale = a_autoScale;
    }

}
