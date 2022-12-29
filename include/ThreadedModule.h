#ifndef QCONFIGURABLEDASHBOARD_THREADEDMODULE_H
#define QCONFIGURABLEDASHBOARD_THREADEDMODULE_H

#include <CallbackDispatcherInterface.h>
#include <Module.h>
#include <thread>

namespace QCD {
    /**
     * @class ThreadedModule
     * @brief Base class for all threaded modules
     * @note Comments in this file refer to "this thread". This means the thread spawned by a instance of a ThreadedModule object
     * @note Only lock 1 mutex at a time!!!!
     */
    class ThreadedModule : public Module {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param a_rate Update rate, Hz. This is a dumb rate, which does not account for execution time
         */
        explicit ThreadedModule(double a_rate);

        /**
         * @brief Start this thread going
         * @pre Run in main thread only, handled internally
         */
        int run() override;

        /**
         * @brief Pass relevant data from main thread into shared memory
         * @pre Run in main thread only
         */
        void runUpdate(bool a_focus) override;

        /**
         * @brief Tell this thread to end
         * @pre Run in main thread only
         */
        void finish() override;

        /**
         * @brief Queue a callback to be tunneled into the thread
         * @pre Run in main thread only
         * @param a_name name of event
         * @param a_json data to forward
         */
        void queueCallback(const Json &a_json, const std::string &a_name);

    protected:
        //// Generic ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /**
         * @brief Overriden function that serves as the main loop for this thread
         */
        virtual void tick();

        /**
         * @brief Overriden function that serves as the setup for this thread
         */
        virtual void setup();

        bool m_autoClear;       // If true all json data and images will be reset after being copied to main thread

        //// Data passing ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /**
         * @brief Queues a json value to be passed to the GUI
         * @pre Run in this thread only
         * @param a_key Name/key of the data to be passed
         * @param a_value data to be passed
         */
        void setJson(const std::string &a_key, Json &a_value);

        /**
         * @brief Queues a image to be passed to the GUI
         * @pre Run in this thread only
         * @param a_key Name/key of the image to be passed
         * @param a_image image to be passed
         */
        void setImage(const std::string &a_key, const Image &a_image);

        /**
         * @brief Gets the incoming json data
         * @pre Run in this thread only
         * @return Json reference
         */
        Json &getIncomingData();

        //// Event //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /**
         * @brief runs all callbacks in incoming queue
         * @pre Run in this thread only
         */
        void triggerIncomingCallbacks();


        void registerCallback(const std::string &a_identifier, const Callback &a_callback) override;

        void triggerCallback(const std::string &a_identifier, const Json &a_json = Json::object(), int a_excludeIdIndex = -1) override;

    private:
        /**
         * @brief Main loop of thread, calls tick() and setup()
         */
        void internalRun();

        /**
         * @brief Checks if the current thread is this thread
         * @return if in this thread
         */
        bool isThisThread();

        // Make private, to avoid derived classes from accessing in thread
        using Module::triggerCallback;
        using Module::registerTunnelCallback;
        using Module::registerCallback;
        int m_interval;                         // Set in constructor from main thread, then only read from this thread

        //////// These variables should be locked with the mutex in their section before accessing
        //// Thread stuff
        typedef std::lock_guard<std::mutex> LockGard;
        std::thread *m_thread;
        bool m_active;
        std::mutex m_threadMutex;
        //// All JSON/Img passing objects
        Json m_outgoingData = Json::object();
        Json m_incomingData = Json::object();
        std::map<std::string, Image> m_outgoingImages;
        std::mutex m_dataMutex;
        //// All event tunnel object
        std::queue<std::pair<std::string, Json>> m_outgoingEventQueue;
        std::queue<std::pair<std::string, Json>> m_incomingEventQueue;
        CallbackDispatcher m_dispatcher;
        int m_callbackID = -1;
        std::mutex m_eventMutex;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_THREADEDMODULE_H
