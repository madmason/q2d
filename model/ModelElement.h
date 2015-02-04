#ifndef MODELELEMENT_H
#define MODELELEMENT_H

#include <QObject>
#include <QString>

namespace q2d {
namespace model {

// forward declaration
class Model;

// TODO documentation
class ModelElement : public QObject {
    Q_OBJECT
public:
    ModelElement(Model* parent);

    Model* model() const;
};

} // namespace model
} // namespace q2d

#endif // MODELELEMENT_H
