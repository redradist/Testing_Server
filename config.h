#ifndef CONFIG_H
#define CONFIG_H

#include <QXmlStreamReader>
#include "console.h"

#define VERFIRWARE  1.0

namespace SenseSystem {
    // Type displaying information
    enum TypeView {
        NON,
        CONSOLE,
        WINDOW,
    };

    // Configuration of system
    struct Config {
        QString         configFile;
        TypeView        typeView;
        View            *display;
        int             port;
    };

    bool parserConfig();
    void parseEtap(QXmlStreamReader& xml);
    void addElementDataToMap(QXmlStreamReader& xml, short numParm);
}

#endif // CONFIG_H
