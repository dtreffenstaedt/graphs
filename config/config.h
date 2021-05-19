#ifndef MYSIM_VERSION_H
#define MYSIM_VERSION_H

#include <string>

namespace graphs::Version {

constexpr int major { @PROJECT_VERSION_MAJOR@ };
constexpr int minor { @PROJECT_VERSION_MINOR@ };
constexpr int patch { @PROJECT_VERSION_PATCH@ };
constexpr const char* additional { "@PROJECT_VERSION_ADDITIONAL@" };

[[nodiscard]] auto string() -> std::string;

}

#endif // MYSIM_VERSION_H
