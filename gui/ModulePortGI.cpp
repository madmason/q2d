
#include "../DocumentEntry.h"
#include "../factories/GIFactory.h"
#include "ModulePortGI.h"
#include "PortGraphicsItem.h"

#include <QGraphicsItem>

using namespace q2d::gui;

ModuleInterfaceGI::ModuleInterfaceGI(
    QPointF position,
    DocumentEntry* relatedEntry,
    model::enums::PortDirection direction)
    : ParentSchematicElement(position, relatedEntry) {

    m_moduleDirection = direction;

    QGraphicsItem* decal;
    switch (direction) {
    case model::enums::PortDirection::OUT :
        decal = factories::GIFactory::createModulePortDecalOut();
        break;
    case model::enums::PortDirection::IN :
        decal = factories::GIFactory::createModulePortDecalIn();
        break;
    default : // should not happen
        Q_ASSERT(false);
    }
    decal->setZValue(-1);
    this->addActual(decal);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges); // needed to detect movement
}

QString
ModuleInterfaceGI::specificType() {
    return model::enums::PortDirectionToString(m_moduleDirection);
}

QVariant
ModuleInterfaceGI::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionHasChanged) {
        emit signal_posChanged();
    }
    return QGraphicsItem::itemChange(change, value);
}
