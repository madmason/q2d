#include "JsonHelpers.h"

#include "Constants.h"
#include "gui/ComponentGraphicsItem.h"
#include "gui/SchematicsSceneChild.h"
#include "model/ModelElement.h"
#include "model/PortDirection.h"
#include "ComponentFactory.h"
#include "metamodel/ComponentType.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonValue>

using namespace q2d::constants;

void
q2d::WriteJsonFile(QString path, QJsonDocument doc) {

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(doc.toJson());
    file.close();
}

QJsonObject
q2d::PointToJson(QPointF point) {
    Q_ASSERT(!point.isNull());

    QJsonObject result = QJsonObject();

    result.insert(JSON_POSITION_X, QJsonValue(point.x()));
    result.insert(JSON_POSITION_Y, QJsonValue(point.y()));

    return result;
}

QPointF q2d::JsonToPoint(QJsonObject json) {
    Q_ASSERT(json.contains(JSON_POSITION_X));
    Q_ASSERT(json.contains(JSON_POSITION_Y));

    float x = json.value(JSON_POSITION_X).toInt();
    float y = json.value(JSON_POSITION_Y).toInt();

    return QPointF(x, y);
}

QJsonObject
q2d::DocumentToJson(Document* doc) {

    QJsonArray entriesArray = QJsonArray();

    // Write the entries
    for (DocumentEntry * entry : doc->entries()) {
        entriesArray.append(QJsonValue(DocumentEntryToJson(entry)));
    }

    QJsonObject entriesWrapper = QJsonObject();
    entriesWrapper.insert(JSON_DOCENTRY, entriesArray);

    return entriesWrapper;
}

q2d::Document*
q2d::JsonToDocument(QJsonObject json, QString name, Project* parent) {
    Q_CHECK_PTR(parent);
    Q_ASSERT(!name.isEmpty());

    Document* doc =  new Document(name, parent);

    QJsonArray entries = json.value(JSON_DOCENTRY).toArray();

    // Read the entries
    for (QJsonValue jsonEntry : entries) {
        parseDocumentEntry(jsonEntry.toObject(), doc);
    }

    return doc;
}

QJsonObject
q2d::DocumentEntryToJson(DocumentEntry* entry) {
    Q_CHECK_PTR(entry);

    QJsonObject result = QJsonObject();

    // contain ID, ModelElement, SchematicItem, type, parent entry
    // parentDocument is implicitly given by the JSON document,
    // this object will be passed into.

    result.insert(JSON_DOCENTRY_ID, QJsonValue(entry->id()));
    result.insert(JSON_DOCENTRY_SCHEMATIC_ELEMENT,
                  QJsonValue(SchematicsSceneChildToJson(
                                 entry->schematicElement())));

    // general type
    result.insert(JSON_DOCENTRY_TYPE,
                  QJsonValue(DocumentEntryTypeToString(entry->type())));
    // the parent id, if there is one
    if (entry->parent() != nullptr) {
        result.insert(JSON_DOCENTRY_PARENT, QJsonValue(entry->parent()->id()));
    } else {
        result.insert(JSON_DOCENTRY_PARENT, QJsonValue::Null);
    }

    // TODO is there something about the model to save?

    return result;
}

/**
 * @brief q2d::parseDocumentEntry
 * The parsed DocumentEntry will automatically be added to the given document.
 * @param json
 * @param document
 */
void
q2d::parseDocumentEntry(QJsonObject json, Document* document) {
    Q_ASSERT(json.contains(JSON_DOCENTRY_ID));


    QString id = json.value(JSON_DOCENTRY_ID).toString();
    DocumentEntryType type = StringToDocumentEntryType(
                                 json.value(JSON_DOCENTRY_TYPE).toString());

    // TODO reconstruct the schematics element
    QJsonObject schematicJson =
        json.value(JSON_DOCENTRY_SCHEMATIC_ELEMENT).toObject();
    QString typeId = schematicJson.value(JSON_DOCENTRY_TYPE).toString();
    QPointF position = JsonToPoint(
                           schematicJson.value(JSON_SCHEMATIC_POSITION).toObject());

    // reconstruct the parent
    QJsonValue parentValue = json.value(JSON_DOCENTRY_PARENT);
    DocumentEntry* parent;
    if (parentValue.isNull()) {
        parent = nullptr;
    } else {
        parent = document->entry(parentValue.toString());
    }

    switch (type) {
    case COMPONENT :
        document->componentFactory()->instantiateComponent(
            document, typeId, position, id);
        break;
    case PORT : {
        QString directionString = json.value(JSON_SCHEMATIC_SUB_TYPE).toString();
        document->componentFactory()->instantiatePort(
            document, parent, position, model::StringToPortDirection(directionString), id);
    }
    break;
    case WIRE : {
        QJsonObject additional = json.value(JSON_SCHEMATIC_ADDITIONAL).toObject();
        Q_ASSERT(!additional.isEmpty());

        DocumentEntry* sender = document->entry(additional.value(JSON_WIRE_START).toString());
        Q_CHECK_PTR(sender);

        DocumentEntry* receiver = document->entry(additional.value(JSON_WIRE_END).toString());
        Q_CHECK_PTR(receiver);

        document->componentFactory()->instantiateWire(document, sender, receiver, id);
    }
    break;
    default:
        ;
        // ignore everything else for now
    }


}

QJsonObject
q2d::SchematicsSceneChildToJson(gui::SchematicsSceneChild* ssc) {
    QJsonObject result = QJsonObject();

    result.insert(JSON_SCHEMATIC_SUB_TYPE, QJsonValue(ssc->specificType()));
    result.insert(JSON_SCHEMATIC_POSITION, PointToJson(ssc->pos()));

    QJsonObject additionalInfo = ssc->additionalJson();
    if (!additionalInfo.isEmpty()) {
        result.insert(JSON_SCHEMATIC_ADDITIONAL, QJsonValue(additionalInfo));
    }

    return result;
}
