#ifndef QCONFIGURABLEDASHBOARD_BASEINTERFACE_H
#define QCONFIGURABLEDASHBOARD_BASEINTERFACE_H

#include "QObject"
#include "../GuiManager.h"

namespace QCD {

    class BaseInterface : public QObject {
    Q_OBJECT
    public:
        BaseInterface();

        virtual void run();

        void setGuiManager(GuiManager *a_guiManager);

    protected:
        GuiManager *m_guiManager;


    private:

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASEINTERFACE_H
