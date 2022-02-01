#ifndef PROPERTY_HXX
#define PROPERTY_HXX

template <typename T>
struct default_delegate
{
	virtual void set(T& lhs, T const& rhs)
	{
		lhs = rhs;
	}

	virtual T get(T const& lhs) const
	{
		return lhs;
	}
};

template <typename T, typename Delegate = default_delegate<T>>
class property_t
{
public:
	typedef T value_type;

	property_t()
	    : _value()
	{}

	property_t(value_type const& value)  // NOT marked explicit! For calling set() implicitly.
	{
		set(value);
	}

	~property_t() = default;

	property_t& operator=(value_type const& value)
	{
		set(value);
		return *this;
	}

	void set(value_type const& value)
	{
		_delegate.set(_value, value);
	}

	value_type get() const
	{
		return _delegate.get(_value);
	}

	operator value_type() const  // For calling get() implicitly.
	{
		return get();
	}

	Delegate& delegate()
	{
		return _delegate;
	}

private:
	value_type _value;
	Delegate _delegate;
};

#endif
