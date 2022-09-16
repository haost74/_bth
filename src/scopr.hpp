#ifndef SCOPEGUARD_H
#define SCOPEGUARD_H

// Taken from "Declarative Control Flow" (CppCon 2015)

#include <exception>
#include <utility>

#define CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1, s2)
#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(str) CONCATENATE(str, __COUNTER__)
#else
#define ANONYMOUS_VARIABLE(str) CONCATENATE(str, __LINE__)
#endif

namespace detail
{
	enum class ScopeGuardOnExit
	{
	};

	enum class ScopeGuardOnFail
	{
	};

	enum class ScopeGuardOnSuccess
	{
	};

	template <typename Fun>
	class ScopeGuard
	{
		public:
		ScopeGuard(Fun &&fn)
			: fn(std::move(fn))
		{
		}
		~ScopeGuard()
		{
			fn();
		}

		private:
		Fun fn;
	};

	class UncaughtExceptionCounter
	{
		int exceptionCount_;

		public:
		UncaughtExceptionCounter()
			: exceptionCount_(std::uncaught_exceptions())
		{
		}

		bool newUncaughtException() noexcept
		{
			return std::uncaught_exceptions() > exceptionCount_;
		}
	};

	template <typename FunctionType, bool executeOnException>
	class ScopeGuardForNewException
	{
		FunctionType function_;
		UncaughtExceptionCounter ec_;

		public:
		explicit ScopeGuardForNewException(const FunctionType &fn)
			: function_(fn)
		{
		}

		explicit ScopeGuardForNewException(FunctionType &&fn)
			: function_(std::move(fn))
		{
		}

		~ScopeGuardForNewException() noexcept(executeOnException)
		{
			if(executeOnException == ec_.newUncaughtException())
			{
				function_();
			}
		}
	};

	template <typename Fun>
	auto operator+(ScopeGuardOnExit, Fun &&fn)
	{
		return ScopeGuard<Fun>(std::forward<Fun>(fn));
	}

	template <typename Fun>
	auto operator+(detail::ScopeGuardOnFail, Fun &&fn)
	{
		return ScopeGuardForNewException<typename std::decay_t<Fun>, true>(std::forward<Fun>(fn));
	}

	template <typename Fun>
	auto operator+(detail::ScopeGuardOnSuccess, Fun &&fn)
	{
		return ScopeGuardForNewException<typename std::decay_t<Fun>, false>(std::forward<Fun>(fn));
	}
}

#define SCOPE_FAIL auto ANONYMOUS_VARIABLE(SCOPE_FAIL_STATE) = ::detail::ScopeGuardOnFail() + [&]() noexcept
#define SCOPE_SUCCESS auto ANONYMOUS_VARIABLE(SCOPE_FAIL_STATE) = ::detail::ScopeGuardOnSuccess() + [&]()
#define SCOPE_EXIT auto ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) = ::detail::ScopeGuardOnExit() + [&]() noexcept

#endif