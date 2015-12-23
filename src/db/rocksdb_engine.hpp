/*
 * rocksdb.hpp
 *
 *  Created on: 2015��8��21��
 *      Author: wangqiying
 */

#ifndef ROCKSDB_HPP_
#define ROCKSDB_HPP_

#include "common/common.hpp"
#include "thread/spin_rwlock.hpp"
#include "rocksdb/db.h"
#include "rocksdb/write_batch.h"
#include "rocksdb/comparator.h"
#include "rocksdb/cache.h"
#include "rocksdb/filter_policy.h"
#include "rocksdb/statistics.h"
#include "rocksdb/merge_operator.h"
#include "codec.hpp"
#include "context.hpp"
#include <vector>
#include <sparsehash/dense_hash_map>

OP_NAMESPACE_BEGIN
    class RocksDBEngine: public Engine
    {
        private:
            typedef google::dense_hash_map<Data, rocksdb::ColumnFamilyHandle*, DataHash, DataEqual> ColumnFamilyHandleTable;
            rocksdb::DB* m_db;
            rocksdb::Options m_options;
            ColumnFamilyHandleTable m_handlers;
            SpinRWLock m_lock;
            rocksdb::ColumnFamilyHandle* GetColumnFamilyHandle(Context& ctx, const Data& name);
        public:
            RocksDBEngine();
            int Init(const std::string& dir, const std::string& conf);
            int Put(Context& ctx, KeyObject& key, const ValueObject& value);
            int Get(Context& ctx, const KeyObject& key, ValueObject& value);
            int Del(Context& ctx, const KeyObject& key);
            int Merge(Context& ctx, const KeyObject& key, const MergeOperation& op);bool Exists(Context& ctx, const KeyObject& key);
            int BeginTransaction() = 0;
            int CommitTransaction() = 0;
            int DiscardTransaction() = 0;
    };

OP_NAMESPACE_END
#endif /* SRC_ROCKSDB_HPP_ */