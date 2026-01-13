#pragma once

#include <pqxx/pqxx>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

template <typename T>
class DatabaseConnection {
public:

    explicit DatabaseConnection(const T& connectionString)
        : conn_(std::make_unique<pqxx::connection>(std::string(connectionString))) {
        if (!conn_ || !conn_->is_open()) {
            throw std::runtime_error("DatabaseConnection: failed to open connection");
        }
    }


    ~DatabaseConnection() {
        try {

            if (txn_) {
                txn_->abort();
                txn_.reset();
            }
            if (conn_ && conn_->is_open()) {
                conn_->close();
            }
        } catch (...) {

        }
    }


    std::vector<std::vector<std::string>> executeQuery(const std::string& sql) {
        try {
            pqxx::result r = active().exec(sql);

            std::vector<std::vector<std::string>> out;
            out.reserve(r.size());

            for (const auto& row : r) {
                std::vector<std::string> one;
                one.reserve(row.size());
                for (const auto& field : row) {
                    one.push_back(field.is_null() ? "" : field.c_str());
                }
                out.push_back(std::move(one));
            }

            commitIfTemp();
            return out;
        } catch (const std::exception& e) {
            rollbackIfTemp();
            throw std::runtime_error(std::string("executeQuery error: ") + e.what());
        }
    }


    void executeNonQuery(const std::string& sql) {
        try {
            active().exec(sql);
            commitIfTemp();
        } catch (const std::exception& e) {
            rollbackIfTemp();
            throw std::runtime_error(std::string("executeNonQuery error: ") + e.what());
        }
    }


    void beginTransaction() {
        if (txn_) throw std::runtime_error("beginTransaction: transaction already active");
        txn_ = std::make_unique<pqxx::work>(*conn_);
    }

    void commitTransaction() {
        if (!txn_) throw std::runtime_error("commitTransaction: no active transaction");
        txn_->commit();
        txn_.reset();
    }

    void rollbackTransaction() {
        if (!txn_) return;
        txn_->abort();
        txn_.reset();
    }


    void createFunction(const std::string& sql) { executeNonQuery(sql); }
    void createTrigger(const std::string& sql) { executeNonQuery(sql); }


    bool getTransactionStatus() const { return txn_ != nullptr; }


    void setAppUserId(int userId) {
        if (txn_) {
            txn_->exec("SET LOCAL app.user_id = " + std::to_string(userId));
        } else {
            pqxx::work w(*conn_);
            w.exec("SET app.user_id = " + std::to_string(userId));
            w.commit();
        }
    }


    std::string quote(const std::string& s) {
        if (txn_) return txn_->quote(s);
        pqxx::work w(*conn_);
        auto q = w.quote(s);
        w.commit();
        return q;
    }

private:
    std::unique_ptr<pqxx::connection> conn_;
    std::unique_ptr<pqxx::work> txn_;


    std::unique_ptr<pqxx::work> temp_;

    pqxx::work& active() {
        if (txn_) return *txn_;
        if (!temp_) temp_ = std::make_unique<pqxx::work>(*conn_);
        return *temp_;
    }

    void commitIfTemp() {
        if (temp_) {
            temp_->commit();
            temp_.reset();
        }
    }

    void rollbackIfTemp() {
        if (temp_) {
            temp_->abort();
            temp_.reset();
        }
    }
};
