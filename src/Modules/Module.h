#ifndef QCONFIGURABLEDASHBOARD_MODULE_H
#define QCONFIGURABLEDASHBOARD_MODULE_H

#include "QObject"
#include "../Core/AppManager.h"

namespace QCD {
    class QConfigurableDashboard;

    class Module : public QObject {
    Q_OBJECT
    public:
        Module();

        void setAppManager(AppManager *a_guiManager);

        AppManager *getAppManager();

        void setApp(QConfigurableDashboard *a_app);

        QConfigurableDashboard *getApp();

        virtual void run();

        virtual void update();

        virtual void finish();

    protected:
        AppManager *m_appManager;
        QConfigurableDashboard *m_app;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_MODULE_H
