#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include <qstring.h>

class DefaultSettings
{
public:
    DefaultSettings();
    void readJsonFromFile();
    QString getUserPasswordParameter();
};

#endif // DEFAULTSETTINGS_H
