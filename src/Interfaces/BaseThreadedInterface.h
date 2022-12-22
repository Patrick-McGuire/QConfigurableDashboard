#ifndef QCONFIGURABLEDASHBOARD_BASETHREADEDINTERFACE_H
#define QCONFIGURABLEDASHBOARD_BASETHREADEDINTERFACE_H

#include <thread>
#include "BaseInterface.h"
#include "../DataPasser.h"

namespace QCD {

    class BaseThreadedInterface : public BaseInterface {
    Q_OBJECT
    public:
        BaseThreadedInterface();

        void run() override;

        void update();

        void finish() override;

    protected:
        void setJson(const std::string &a_key, Json &a_value);

        virtual void onRun();

        bool m_active;
        bool m_autoClear;

    private:
        // Make m_dataPasser private, to avoid derived classes from accessing in thread
        using BaseInterface::m_dataPasser;

        Json m_jsonData = Json::object();

        typedef std::lock_guard<std::mutex> LockGard;
        std::thread *m_thread;
        std::mutex m_mutex;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASETHREADEDINTERFACE_H
