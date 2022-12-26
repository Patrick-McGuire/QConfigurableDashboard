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

        virtual void run();

        virtual void update();

        virtual void finish();

    protected:
        AppManager *m_appManager;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_MODULE_H
