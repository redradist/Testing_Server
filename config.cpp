#include "config.h"

SenseSystem::Config config = {QString(),SenseSystem::WINDOW,0,38000};

/*
 * Parser configuration
 */
bool SenseSystem::parserConfig()
{
    QFile* file = new QFile(config.configFile);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QXmlStreamReader xml(file);

	while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "etaps")
                continue;
            if (xml.name() == "etap")
                parseEtap(xml);
        }
    }
}

/*
 * Parser etap
 */
void SenseSystem::parseEtap(QXmlStreamReader& xml)
{
    xml.readNext();
	
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "etap"))
    {
		if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "view")
                addElementDataToMap(xml, 0);
            if (xml.name() == "port")
                addElementDataToMap(xml, 1);
        }
        xml.readNext();
    }
}

/*
 * Parser parameter
 */
void SenseSystem::addElementDataToMap(QXmlStreamReader& xml, short numParm)
{
    if (xml.tokenType() != QXmlStreamReader::StartElement)
        return;
    xml.readNext();
    // Checking the
	switch(numParm){
    // Parsing the <view> teg
    case 0:
    {
        if(xml.text() == "console")
            config.typeView = CONSOLE;
        else
            config.typeView = WINDOW;
    }
        break;
    // Parsing the <port> teg
    case 1:
    {
        config.port = xml.text().toInt();
    }
        break;
    // Parsing nothing
    default:
        break;
	}
}
