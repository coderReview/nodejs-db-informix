#ifndef __QUERY_H_INCLUDED__
#define __QUERY_H_INCLUDED__

#include <stdlib.h>
#include <node.h>
#include <node_buffer.h>
#include <node_version.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include "node_defs.h"
#include "connection.h"
#include "events.h"
#include "exception.h"
#include "result.h"

namespace nodejs_db {
class Query : public EventEmitter {
    public:
        static void Init(v8::Handle<v8::Object> target, v8::Persistent<v8::FunctionTemplate> constructorTemplate);
        void setConnection(Connection* connection);
        v8::Handle<v8::Value> set(const v8::Arguments& args);

    protected:
        struct row_t {
            std::vector<std::string>* columns;
            unsigned long* columnLengths;
        };
        struct execute_request_t {
            v8::Persistent<v8::Object> context;
            Query* query;
            Result* result;
            std::string* error;
            uint16_t columnCount;
            bool buffered;
            std::vector<row_t*>* rows;
        };
        Connection* connection;
        std::ostringstream sql;
        std::vector< v8::Persistent<v8::Value> > values;
        bool async;
        bool cast;
        bool bufferText;
        v8::Persistent<v8::Function>* cbStart;
        v8::Persistent<v8::Function>* cbExecute;
        v8::Persistent<v8::Function>* cbFinish;

        Query();
        ~Query();
        static v8::Handle<v8::Value> Select(const v8::Arguments& args);
        static v8::Handle<v8::Value> From(const v8::Arguments& args);
        static v8::Handle<v8::Value> Join(const v8::Arguments& args);
        static v8::Handle<v8::Value> Where(const v8::Arguments& args);
        static v8::Handle<v8::Value> And(const v8::Arguments& args);
        static v8::Handle<v8::Value> Or(const v8::Arguments& args);
        static v8::Handle<v8::Value> OrderBy(const v8::Arguments& args);
        static v8::Handle<v8::Value> Limit(const v8::Arguments& args);
        static v8::Handle<v8::Value> Add(const v8::Arguments& args);
        static v8::Handle<v8::Value> Insert(const v8::Arguments& args);
        static v8::Handle<v8::Value> Update(const v8::Arguments& args);
        static v8::Handle<v8::Value> Set(const v8::Arguments& args);
        static v8::Handle<v8::Value> Delete(const v8::Arguments& args);
        static v8::Handle<v8::Value> Sql(const v8::Arguments& args);
        static v8::Handle<v8::Value> Execute(const v8::Arguments& args);
        static
#if NODE_VERSION_AT_LEAST(0, 5, 0)
        void
#else
        int
#endif
        eioExecute(eio_req* eioRequest);
        static int eioExecuteFinished(eio_req* eioRequest);
        void executeAsync(execute_request_t* request);
        static void freeRequest(execute_request_t* request, bool freeAll = true);
        std::string fieldName(v8::Local<v8::Value> value) const throw(Exception&);
        std::string tableName(v8::Local<v8::Value> value, bool escape = true) const throw(Exception&);
        v8::Handle<v8::Value> addCondition(const v8::Arguments& args, const char* separator);
        v8::Local<v8::Object> row(Result* result, row_t* currentRow) const;
        virtual std::string parseQuery() const throw(Exception&);
        virtual std::vector<std::string::size_type> placeholders(std::string* parsed) const throw(Exception&);
        virtual Result* execute() const throw(Exception&);
        std::string value(v8::Local<v8::Value> value, bool inArray = false, bool escape = true, int precision = -1) const throw(Exception&);


    private:
        static bool gmtDeltaLoaded;
        static int gmtDelta;

        std::string fromDate(const double timeStamp) const throw(Exception&);
};
}

#endif  // __QUERY_H_INCLUDED__