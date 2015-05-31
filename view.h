#ifndef VIEW_H
#define VIEW_H

#include "server.h"

class View
{
public:
    // No-arguments constructor
    View()
    {
        state = 0;
        server = NULL;
    }

    // Destructor of view
    ~View() {
        if(server != NULL)
        {
            delete server;
        }
    }

    virtual std::string inStream(void) = 0;

public slots:
    virtual void outStream(QString str) = 0;
    virtual void addClientToList(int IDSocket) = 0;
    virtual void removeClientFromList(int IDSocket) = 0;
    virtual void displayInfoOfClient(int IDSocket) = 0;
    virtual void displayAllClient() = 0;

protected:
    bool state;
    friend class SenseSystem::TechServer;
    SenseSystem::TechServer *server;
};

#endif // VIEW_H

