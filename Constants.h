#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace q2d {
namespace constants {

// Keys for QSettings (application wide)
extern QString KEY_COMPONENTS_DIR;
extern QString KEY_PROJECTS_DIR;

// JSON keywords
extern QString JSON_COMPONENT_NAME;
extern QString JSON_PORTS;
extern QString JSON_PORT_DIRECTION;
extern QString JSON_PORT_NAME;
extern QString JSON_PORT_POSITION;
extern QString JSON_PORT_POSITION_X;
extern QString JSON_PORT_POSITION_Y;
extern QString JSON_SYMBOL_PATH;

} // namespace constants
} // namespace q2d

#endif // CONSTANTS_H
