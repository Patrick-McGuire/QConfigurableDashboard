#ifndef QCONFIGURABLEDASHBOARD_MAINPAGE_H
#define QCONFIGURABLEDASHBOARD_MAINPAGE_H

#include <TabModule.h>
#include <GraphWidget.h>

namespace QCD {

    class MainPageExample : public TabModule {
    Q_OBJECT
    public:
        MainPageExample();

    private:
        void resetGraph(const Json&a_args);

        std::vector<GraphWidget*> m_graphs;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_MAINPAGE_H
