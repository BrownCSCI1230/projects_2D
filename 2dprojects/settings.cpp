/*!

 Settings.h
 CS123 Support Code

 @author  Evan Wallace (edwallac)
 @date    9/1/2010

 This file contains various settings and enumerations that you will need to
 use in the various assignments. The settings are bound to the GUI via static
 data bindings.

**/

#include "settings.h"
#include <QFile>
#include <QSettings>

Settings settings;


/**
 * Loads the application settings, or, if no saved settings are available, loads default values for
 * the settings. You can change the defaults here.
 */
void Settings::loadDefaults() {
    // Set the default values below
    QSettings s("CS123", "CS123");

    // Brush
    brushType = s.value("brushType", BRUSH_LINEAR).toInt();
    brushRadius = s.value("brushRadius", 50).toInt();
    brushColor.r = s.value("brushRed", 127).toInt();
    brushColor.g = s.value("brushGreen", 255).toInt();
    brushColor.b = s.value("brushBlue", 0).toInt();
    brushColor.a = s.value("brushAlpha", 20).toInt();

    // Filter
    filterType = s.value("filterType", FILTER_EDGE_DETECT).toInt();
    edgeDetectSensitivity = s.value("edgeDetectSensitivity", 0.5f).toDouble();
    blurRadius = s.value("blurRadius", 10).toInt();
    scaleX = s.value("scaleX", 2).toDouble();
    scaleY = s.value("scaleY", 2).toDouble();
    rotateAngle = s.value("rotateAngle", 0).toInt();
}
