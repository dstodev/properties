#include <gtest/gtest.h>

#include <property.hxx>

struct IntToAsciiDelegate : default_delegate<char>
{
	void set(char& lhs, char const& rhs) override
	{
		lhs = rhs + '0';
	}
};

struct Container
{
	property_t<char, IntToAsciiDelegate> value;
};

TEST(Property, T_char)
{
	Container c;
	c.value = 2;
	ASSERT_EQ('2', c.value);
}
