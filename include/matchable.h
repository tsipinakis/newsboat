#ifndef NEWSBOAT_MATCHABLE_H_
#define NEWSBOAT_MATCHABLE_H_

#include <string>

namespace newsboat {

class Matchable {
public:
	Matchable();
	virtual ~Matchable();
	virtual bool has_attribute(const std::string& attribname) = 0;
	virtual std::string get_attribute(const std::string& attribname) = 0;
};

} // namespace newsboat

extern "C" {
bool matchable_has_attribute(const void *ptr, const char *attr);
const char* matchable_get_attribute(const void *ptr, const char *attr);
}

#endif /* NEWSBOAT_MATCHABLE_H_ */

