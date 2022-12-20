#ifndef QCONFIGURABLEDASHBOARD_BASEINTERFACE_H
#define QCONFIGURABLEDASHBOARD_BASEINTERFACE_H

#include "QObject"
#include "../DataPasser.h"

namespace QCD {

    class BaseInterface : public QObject {
    Q_OBJECT
    public:
        BaseInterface();

        virtual void run();

        void setGuiManager(DataPasser *a_guiManager);

    protected:
        DataPasser *m_guiManager;


    private:

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASEINTERFACE_H
