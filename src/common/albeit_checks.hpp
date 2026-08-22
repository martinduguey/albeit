#ifndef __ALBEIT_CHECKS_HPP__
#define __ALBEIT_CHECKS_HPP__

// Debug builds (default) validate `condition` and throw `exception` when it
// fails. Release builds (compiled with -DNDEBUG) skip the check entirely,
// including evaluation of `condition`, so callers must only pass valid
// arguments.
#ifdef NDEBUG
    #define ALBEIT_CHECK(condition, exception) ((void)0)
#else
    #define ALBEIT_CHECK(condition, exception) \
        do { if (!(condition)) { throw (exception); } } while (0)
#endif

#endif
