#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "Logger.h"
#include "LogLevel.h"

#include <QString>
#include <QStringList>
#include <QMap>

namespace q2d {
namespace logging {

class LogManager {
private:

    QMap<QString, Logger> m_loggers;
    QMap<QString, LogLevel> m_logLevels;

public:
    /**
     * @brief logger will get the logger with the given name
     * or create a new one, if a logger with the given name does not exist.
     * A weak pointer is returned since the returned object should only be observed and called upon,
     * but not be managed by the caller.
     * @param name
     * It is assumed that the name is valid.
     * @return
     */
    Logger& logger(QString name) const;

    QStringList loggerNames() const;

    /**
     * @brief logLevel will get the log level with the given name
     * or create a new one, if a log level with the given name does not exist.
     * If the log level is created anew, its default color is white.
     * A weak pointer is returned since the returned object should only be observed and called upon,
     * but not be managed by the caller.
     * @param name
     * It is assumed that the name is valid.
     * @return
     */
    LogLevel& logLevel(QString name) const;

    QStringList logLevelNames() const;
};

} // namespace logging
 // namespace q2d
}

#endif // LOGMANAGER_H
