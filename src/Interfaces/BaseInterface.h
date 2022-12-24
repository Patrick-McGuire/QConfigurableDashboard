#ifndef QCONFIGURABLEDASHBOARD_BASEINTERFACE_H
#define QCONFIGURABLEDASHBOARD_BASEINTERFACE_H

#include "QObject"
#include "../Core/AppManager.h"

namespace QCD {

    class BaseInterface : public QObject {
    Q_OBJECT
    public:
        BaseInterface();

        virtual void run();

        virtual void update();

        virtual void finish();

        virtual void setGuiManager(AppManager *a_guiManager);

    protected:
        AppManager *m_appManager;


    private:

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASEINTERFACE_H
