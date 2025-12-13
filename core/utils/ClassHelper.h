#pragma once

namespace Ps::Core {

#define COPY_CONSTRUCTOR(className) className(const className&)
#define MOVE_CONSTRUCTOR(className) className(className&&)
#define COPY_ASSIGNMENT(className) className& operator=(const className&)
#define MOVE_ASSIGNMENT(className) className& operator=(className&&)

}  // namespace Ps::Core
