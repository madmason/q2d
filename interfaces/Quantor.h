#ifndef INTERFACE_H
#define INTERFACE_H

#include "Iterator.h"
#include "QIContext.h"

#include <vector>
#include <string>

#include <QMap>
#include <QList>
#include <QObject>

namespace q2d {

// forward declaration
namespace model {
class Model;
}

namespace quantor {
class QICircuit;

/**
 * @brief The Quantor class provides utility functions and keeps the state necessary for interfacing with the tool quantor.
 */
class QuantorInterface :
        QObject {
    Q_OBJECT
private:

    // NOTE make sure, the lowest variable index is 1, NOT 0
    // since 0 is already used for terminating

    QMap<QString, QIContext> m_contexts;

    // the solver will return a zero-terminated array of int
    int* (*m_solverMain)(QICircuit const&, std::vector<int>&) = nullptr;
    QList<QList<int>> m_solutions;

    // helper functions
    void buildContexts(const q2d::model::Model* contextSource);
    Iterator<unsigned int> varsForType(VariableType requestedType, QList<unsigned int>* container);

    // creates the thread and collects the result once it finfished
    void solve();
public:
    QuantorInterface(int * (*solverMain)(QICircuit const&, std::vector<int>&));
    QMap<QString, QIContext> contexts() const { return m_contexts; }

public slots:
    void slot_solveProblem();
};



} // namespace quantor
} // namespace q2d


#endif // INTERFACE_H