#ifndef NEWSBOAT_CONFIGCONTAINER_H_
#define NEWSBOAT_CONFIGCONTAINER_H_

#include <unordered_set>
#include <mutex>

#include "configparser.h"

namespace newsboat {

enum class ConfigDataType { INVALID, BOOL, INT, STR, PATH, ENUM };

enum class FeedSortMethod {
	NONE,
	FIRST_TAG,
	TITLE,
	ARTICLE_COUNT,
	UNREAD_ARTICLE_COUNT,
	LAST_UPDATED
};

enum class ArtSortMethod { TITLE, FLAGS, AUTHOR, LINK, GUID, DATE, RANDOM };

enum class SortDirection { ASC, DESC };

struct FeedSortStrategy {
	FeedSortMethod sm = FeedSortMethod::NONE;
	SortDirection sd = SortDirection::DESC;

	bool operator==(const FeedSortStrategy& other) const
	{
		return sm == other.sm && sd == other.sd;
	}

	bool operator!=(const FeedSortStrategy& other) const
	{
		return !(*this == other);
	}
};

struct ArticleSortStrategy {
	ArtSortMethod sm = ArtSortMethod::DATE;
	SortDirection sd = SortDirection::ASC;

	bool operator==(const ArticleSortStrategy& other) const
	{
		return sm == other.sm && sd == other.sd;
	}

	bool operator!=(const ArticleSortStrategy& other) const
	{
		return !(*this == other);
	}
};

struct ConfigData {
	ConfigData(const std::string& v = "",
		ConfigDataType t = ConfigDataType::INVALID,
		bool m = false)
		: value(v)
		, default_value(v)
		, type(t)
		, enum_values()
		, multi_option(m)
	{
	}

	ConfigData(const std::string& v,
		const std::unordered_set<std::string>& values)
		: value(v)
		, default_value(v)
		, type(ConfigDataType::ENUM)
		, enum_values(values)
		, multi_option(false)
	{
	}

	std::string value;
	std::string default_value;
	ConfigDataType type;
	const std::unordered_set<std::string> enum_values;
	bool multi_option;
};

class ConfigContainer : public ConfigActionHandler {
public:
	ConfigContainer();
	~ConfigContainer() override;
	void register_commands(ConfigParser& cfgparser);
	void handle_action(const std::string& action,
		const std::vector<std::string>& params) override;
	void dump_config(std::vector<std::string>& config_output) override;

	bool get_configvalue_as_bool(const std::string& key) const;
	int get_configvalue_as_int(const std::string& key) const;
	std::string get_configvalue(const std::string& key) const;
	void set_configvalue(const std::string& key, const std::string& value);
	void reset_to_default(const std::string& key);
	void toggle(const std::string& key);
	std::vector<std::string> get_suggestions(const std::string& fragment) const;
	FeedSortStrategy get_feed_sort_strategy() const;
	ArticleSortStrategy get_article_sort_strategy() const;

	static const std::string PARTIAL_FILE_SUFFIX;

private:
	std::map<std::string, ConfigData> config_data;
	mutable std::recursive_mutex config_data_mtx;
};

} // namespace newsboat

#endif /* NEWSBOAT_CONFIGCONTAINER_H_ */
