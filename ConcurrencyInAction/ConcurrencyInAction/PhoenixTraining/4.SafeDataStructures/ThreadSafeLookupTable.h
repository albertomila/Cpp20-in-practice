#include "stdafx.h"
#include <mutex>
#include <list>
#include <shared_mutex>
#include <vector>
#include <map>



namespace Ex24
{
	template
		<
		typename Key
		, typename Value
		, typename THash = std::hash<Key>
		>
		class bucket_type
	{
	private:
		typedef std::pair<Key, Value> TBucketValue;
		typedef std::list<TBucketValue> TBucketData;
		typedef typename TBucketData::iterator TBucketIterator;

	private:
		TBucketIterator find_entry_for(const Key& key) const
		{
			return std::find_if
			(data.begin()
				, data.end
				, [&](const& TBucketValue item)
			{
				return item.first == key
			}
			);
		}

	public:
		Value value_for(const Key& key, const Value& default_value) const
		{
			std::shared_lock<std::shared_timed_mutex> lock(mutex);
			const TBucketIterator found_entry = find_entry_for(key);
			return (found_entry == data.end())
				? default_value
				: found_entry->second;
		}

		void add_or_update_mapping(const Key& key, const Value& value)
		{
			std::unique_lock<std::shared_timed_mutex> lock(mutex);
			const TBucketIterator found_entry = find_entry_for(key);
			if (found_entry == data.end())
			{
				data.push_back(TBucketValue(key, value));
			}
			else
			{
				found_entry->second = value;
			}
		}

		void remove_mapping(const Key& key)
		{
			std::unique_lock<std::shared_timed_mutex> lock(mutex);
			const TBucketIterator found_entry = find_entry_for(key);
			if (found_entry != data.end())
			{
				data.erase(found_entry);
			}
		}

		const TBucketData& get_data() const
		{
			return data;
		}

		std::shared_timed_mutex& get_mutex() const
		{
			return mutex;
		}

	private:
		TBucketData data;
		mutable std::shared_timed_mutex mutex;
	};

	template
		<
		typename Key
		, typename Value
		, typename THash = std::hash<Key>
		>
		class threadsafe_lookup_table
	{
	private:
		typedef bucket_type<Key, Value, THash> TBucketType;
		typedef std::pair<Key, Value> TBucketValue;
		typedef std::list<TBucketValue> TBucketData;
		typedef typename TBucketData::iterator TBucketIterator;

	public:
		threadsafe_lookup_table(unsigned int num_buckets = 19, const THash& hasher_ = Hash())
			: buckets(num_buckets)
			, hasher(hasher_)
		{
			for (unsigned int i = 0; i < num_buckets; ++i)
			{
				buckets[i].reset(new bucket_type);
			}
		}

		threadsafe_lookup_table(const threadsafe_lookup_table& other) = delete;
		threadsafe_lookup_table& operator = (const threadsafe_lookup_table& other) = delete;

		Value value_for(const Key& key, const Value& default_value = Value()) const
		{
			return get_bucket(key).value_for(key, default_value);
		}

		Value add_or_update_mapping(const Key& key, const Value& value)
		{
			get_bucket(key).add_or_update_mapping(key, value);
		}

		Value remove_mapping(const Key& key)
		{
			get_bucket(key).remove_mapping(key);
		}

		std::map<Key, Value> get_map_copy() const
		{
			std::vector<std::unique_lock<std::shared_timed_mutex>> locks;
			for (unsigned int i = 0; i < buckets.size(); ++i)
			{
				std::shared_timed_mutex& bucketMutex = buckets[i].get_mutex();
				locks.push_back(std::unique_lock<std::shared_timed_mutex>(bucketMutex));
			}

			std::map<Key, Value> res;
			for (unsigned int i = 0; i < buckets.size(); ++i)
			{
				for (bucket_iterator it = buckets[i].get_data().begin();
					it != buckets[i].get_data().end();
					++it)
				{
					res.insert(*it);
				}
			}
			return res;
		}


	private:
		TBucketType& get_bucket(const Key& key) const
		{
			//not necessary to lock anything because the number of buckets is constant & fixed
			const std::size_t bucket_index = hasher(key) % buckets.size();

			return *buckets[bucket_index];
		}

	private:
		std::vector<std::unique_ptr<TBucketType>> buckets;
		THash hasher;

	};

	BEGIN_TEST(Ex24_ThreadSafeLookupTable)
	END_TEST()
}