#ifndef QCONFIGURABLEDASHBOARD_OBJECT_H
#define QCONFIGURABLEDASHBOARD_OBJECT_H

#include <QCD.h>
#include <QConfigurableDashboard.h>
namespace QCD {

    class Object {
    public:
        Object();

        virtual void run();

        virtual void runUpdate();

        virtual void finish();

    protected:
        static bool m_draggingEnabled;

        static Json m_inputData;
        static Json m_outputData;
        static Json m_configData;
        static Json m_themeData;
        static ImageMap m_images;
        static std::string m_theme;

        static QConfigurableDashboard *m_app;

    private:
        static bool m_staticInit;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_OBJECT_H
