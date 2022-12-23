#include <QWidgetAction>
#include <iostream>
#include "QConfigurableDashboard.h"
#include "QMenuBar"
#include "QMenu"
#include "QCD.h"

namespace QCD {

    QConfigurableDashboard::QConfigurableDashboard(int a_argc, char **a_argv) {
        // Save these because why not
        m_argv = a_argv;
        m_argc = a_argc;
        // Construct core objects
        m_qApplication = new QApplication(m_argc, m_argv);
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
        m_dataPasser = new DataPasser();

        addMenu("Settings");
        addMenu("Tools");
        addMenuAction("Enable Dragging", "Tools")->setData(true);
        addMenuAction("Disable Dragging", "Tools")->setData(false);
        connect(findMenu("Tools"), SIGNAL(triggered(QAction * )), this, SLOT(updateDragging(QAction * )));
        addMenu("Theme");
        for (const auto &el: m_dataPasser->getThemeData().items()) {
            addMenuAction(el.key().c_str(), "Theme")->setData(QString(el.key().c_str()));
        }
        connect(findMenu("Theme"), SIGNAL(triggered(QAction * )), this, SLOT(updateTheme(QAction * )));

        // Leave null for now;
        m_centralWidget = nullptr;
    }

    QConfigurableDashboard::~QConfigurableDashboard() {
        delete m_qApplication;
        delete m_dataPasser;
    }

    int QConfigurableDashboard::run() {
        // Start all the widgets
        m_centralWidget->run();
        // Start all the interfaces
        for (auto &interface: m_interfaces) {
            interface->run();
        }

        updateTheme("Dark");

        // Start the periodic updating of widgets
        m_timer->start(10);

        // Runs QT main loop
        int out = QApplication::exec();

        // end all the interfaces
        for (auto &interface: m_interfaces) {
            interface->finish();
        }

        return out;
    }

    bool QConfigurableDashboard::setCentralWidget(BaseWidget *a_widget, QFlags<Qt::AlignmentFlag> a_alignment) {
        if (a_widget != nullptr) {
            m_layout->removeWidget(m_centralWidget);
            delete m_centralWidget;
            m_layout->addWidget(a_widget, 0, a_alignment);
            m_centralWidget = a_widget;
            m_centralWidget->disableFloating();
            m_centralWidget->setGuiManager(m_dataPasser);
            return true;
        }
        return false;
    }

    bool QConfigurableDashboard::addInterface(BaseInterface *a_baseInterface) {
        if (a_baseInterface != nullptr && std::find(m_interfaces.begin(), m_interfaces.end(), a_baseInterface) == m_interfaces.end()) {
            m_interfaces.push_back(a_baseInterface);
            a_baseInterface->setGuiManager(m_dataPasser);
            return true;
        }
        return false;
    }

    void QConfigurableDashboard::updateGUI() {
        // Update all interfaces
        for(auto &interface : m_interfaces) {
            interface->update();
        }
        // Update all widgets
        m_centralWidget->smartUpdate(m_mainWindow->isActiveWindow() || m_updateAlways);
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
        m_dataPasser->setTheme(a_activeTheme.toStdString());

        QString backgroundColor = getThemeData(a_activeTheme, CONTAINER_BACKGROUND_CLASS);
        QString highlightBackgroundColor = getThemeData(a_activeTheme, HIGHLIGHT_COLOR_CLASS);
        QString textColor = getThemeData(a_activeTheme, TITLE_TEXT_COLOR_CLASS);

        QString style;
        style += "QMenuBar, QMenuBar::item, QMenu, QMenu::item { " + backgroundColor + " ; " + textColor + ";}";
        style += "QMenuBar::item:selected, QMenu::item:selected { " + highlightBackgroundColor + ";}";
        style += "QTabBar, QTabBar::tab { " + backgroundColor + " ; " + textColor + ";}";
        style += "QTabBar::tab:selected, QTabBar::tab:hover { " + highlightBackgroundColor + ";}";
        for (const auto &el: m_dataPasser->getThemeData()[a_activeTheme.toStdString()].items()) {
            style += getClassStylesheet(el.key().c_str(), getThemeData(a_activeTheme, el.key().c_str()));
        }
        m_mainWindow->setStyleSheet(style);

        emit m_dataPasser->themeChanged();
    }

    QString QConfigurableDashboard::getClassStylesheet(const QString &a_class, const QString &a_style) {
        return QString("*[") + THEME_PROPERTY + "~=\"" + a_class + "\"]{" + a_style + "}";
    }

    QString QConfigurableDashboard::getThemeData(const QString &a_themeName, const QString &a_attribute) {
        return m_dataPasser->getThemeData()[a_themeName.toStdString()][a_attribute.toStdString()].get_ref<std::string &>().c_str();
    }

    void QConfigurableDashboard::updateDragging(QAction *a_action) {
        if (a_action->data().toBool()) {
            m_dataPasser->enableDragging();
        } else {
            m_dataPasser->disableDragging();
        }
    }

    void QConfigurableDashboard::setUpdateAlways(bool a_updateAlways) {
        m_updateAlways = a_updateAlways;
    }

}
