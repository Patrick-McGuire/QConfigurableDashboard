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

        virtual void update();

        virtual void finish();

        virtual void setGuiManager(DataPasser *a_guiManager);

    protected:
        DataPasser *m_dataPasser;


    private:

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASEINTERFACE_H
