#pragma once
#include "DatabaseConnection.h"
#include <string>

inline void logError(DatabaseConnection<std::string>& db,
                     const std::string& entityType,
                     int entityId,
                     int performedBy,
                     const std::string& details) {
    db.executeNonQuery(
        "INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details) VALUES (" +
        db.quote(entityType) + ", " + std::to_string(entityId) + ", " + db.quote("error") + ", " +
        std::to_string(performedBy) + ", " + db.quote(details) + ");"
    );
}
